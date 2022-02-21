#include <memory>

#include "CodalComponent.h"
#include "Ism43362Driver.h"
#include "ManagedString.h"

#define WIFI_ISM43362_DEVICE_ID 2510

#define WIFI_ISM43362_DEFAULT_BUFFER_SIZE ES_WIFI_DATA_SIZE

#define WIFI_ISM43362_EVT_DATA_RECEIVED 1
#define WIFI_ISM43362_EVT_RX_FULL       2

#define WIFI_ISM43362_STATUS_RX_IN_USE    0x01
#define WIFI_ISM43362_STATUS_TX_IN_USE    0x02
#define WIFI_ISM43362_STATUS_RX_BUFF_INIT 0x04
#define WIFI_ISM43362_STATUS_TX_BUFF_INIT 0x08
#define WIFI_ISM43362_STATUS_RXD          0x10

namespace codal {

class WiFiClient;

class WiFi : public CodalComponent {
  private:
    Ism43362Driver ism43362;
    uint8_t wifi_status;

  public:
    /**
     * @brief Contructor
     *
     */
    WiFi(codal::STM32SPI* spi, codal::STM32Pin* cs, codal::STM32Pin* commandDataReady, codal::STM32Pin* reset,
         codal::STM32Pin* wakeup)
        : CodalComponent(WIFI_ISM43362_DEVICE_ID, 0),
          ism43362(spi, cs, commandDataReady, reset, wakeup),
          wifi_status(WL_NO_SHIELD)
    {
    }

    /**
     * @brief Contructor
     *
     */
    WiFi(Ism43362Driver& ism43362)
        : CodalComponent(WIFI_ISM43362_DEVICE_ID, 0), ism43362(ism43362), wifi_status(WL_NO_SHIELD)
    {
    }

    virtual int init() override final
    {
        if (wifi_status == WL_NO_SHIELD) {
            if (ism43362.ES_WIFI_Init() != ES_WIFI_STATUS_OK) {
                wifi_status = WL_NO_SHIELD;
                return DEVICE_INVALID_STATE;
            }
            else {
                wifi_status = WL_IDLE_STATUS;
            }
        }

        return DEVICE_OK;
    }

    /**
     * @brief Destructor
     *
     */
    virtual ~WiFi()
    {
        if (isAttached()) {
            detach();
        }
    }

    /**
     * @brief Get the number of networks visible.
     * @param None
     * @retval Number of discovered networks. The device can see 10 AP max.
     */
    int networksVisible();

    /**
     * @brief Connect to the wifi network.
     * @param ssid name of the network
     * @param passphrase Passphrase. Valid characters in a passphrase
     *         must be between 32-126 chars.
     * @retval none
     */
    void attach(const ManagedString& ssid, const ManagedString& passphrase);

    /**
     * @brief Check if we are connected to the wifi network.
     * @param None
     * @retval true if the device is connected to an AP
     */
    bool isAttached();

    /**
     * @brief Disconnect from the wifi network.
     * @param None
     * @retval none
     */
    void detach();

    /**
     * @brief  Start a Client connection to a remote host
     * @param  hostname : name of the host to which to connect
     * @param  port : port to which to connect
     * @retval A pointer to the client object connected to the remote host
     */
    std::unique_ptr<WiFiClient> connect(const ManagedString& host, uint16_t port);

    /**
     * @brief
     *
     */
    virtual void idleCallback() final override
    {
        if (this->status & WIFI_ISM43362_STATUS_RXD) {
            Event(this->id, WIFI_ISM43362_EVT_DATA_RECEIVED);
            this->status &= ~WIFI_ISM43362_STATUS_RXD;
        }
    }

    friend WiFiClient;
};

class WiFiClient {
  private:
    WiFi* wifi;
    uint8_t sock;
    bool connected;
    uint16_t status;

    uint8_t* rxBuff;
    uint8_t rxBuffSize;
    volatile uint16_t rxBuffHead;
    uint16_t rxBuffTail;

  public:
    /**
     * @brief Destroy the WiFiClient object
     *
     */
    ~WiFiClient()
    {
        if ((this->status & WIFI_ISM43362_STATUS_RX_BUFF_INIT) != 0) {
            free(this->rxBuff);
        }
    }

    /**
     * @brief  Check if the connection is active with the remote host
     * @param  None
     * @retval true if the client is connected to the remote host
     */
    bool isConnected();

    /**
     * @brief  Get connection state
     * @param  None
     * @retval Socket state, FREE or BUSY
     */
    uint8_t connectionState();

    /**
     * @brief  Close the to the remote host connection
     * @param  None
     * @retval None
     */
    void disconnect();

    /**
     * Determines whether there is any data waiting in our reception buffer.
     *
     * @return 1 if we have space, 0 if we do not.
     *
     */
    int isReadable();

    /**
     * Determines if the socket is currently in use by another fiber for reception.
     *
     * @return The state of our mutex lock for reception.
     *
     */
    int rxInUse();

    /**
     * Locks the mutex so that others can't use this serial instance for reception
     */
    void lockRx();

    /**
     * Unlocks the mutex so that others can use this serial instance for reception
     */
    void unlockRx();

    /**
     * @brief  Read up to size bytes from the current packet and place them into buffer
     * @param  buffer : Where to place read data
     * @param  size : length of data to read
     * @retval Returns the number of bytes read, or 0 if none are available
     */
    int read(char* buf, size_t size);

    /**
     * @brief  Read a single byte from the current packet
     * @param  None
     * @retval the read byte
     */
    char read();

    /**
     * @brief  Write size bytes from buffer into the packet
     * @param  buf : data to write
     * @param  size : size of data to write
     * @retval size of write data
     */
    size_t write(const char* buf, size_t size);

    friend WiFi;

  private:
    /**
     * @brief Construct a WiFiClient object
     *
     */
    WiFiClient(WiFi* wifi) : wifi(wifi), sock(SOCK_NOT_AVAIL), connected(false), status(0) {}

    /**
     * @brief  Get the first socket number free.
     * @param  None
     * @retval socket number or -1 if no available.
     */
    uint8_t getFirstSocket();

    /**
     * @brief  Start a TCP connection to the remote host
     * @param  ip : IP to which to send packets
     * @param  port : port to which to send packets
     * @retval true if successful, false if there was a problem with the supplied IP address or port
     */
    bool connect(IPAddress ip, uint16_t port);

    /**
     * @brief  Start a TCP connection to the remote host
     * @param  host : host to which to send the packet
     * @param  port : port to which to send the packet
     * @retval true if successful, false if there was a problem with the supplied IP address or port
     */
    bool connect(const ManagedString& host, uint16_t port);

    /**
     * We do not want to always have our buffers initialised, especially if users to not
     * use them. We only bring them up on demand.
     */
    int initialiseReceptionBuffer()
    {
        if ((this->status & WIFI_ISM43362_STATUS_RX_BUFF_INIT) != 0) {
            free(this->rxBuff);
        }

        this->status &= ~WIFI_ISM43362_STATUS_RX_BUFF_INIT;

        if ((this->rxBuff = (uint8_t*)malloc(rxBuffSize)) == NULL) {
            return DEVICE_NO_RESOURCES;
        }

        this->rxBuffHead = 0;
        this->rxBuffTail = 0;

        this->status |= WIFI_ISM43362_STATUS_RX_BUFF_INIT;

        return DEVICE_OK;
    }
};
}  // namespace codal