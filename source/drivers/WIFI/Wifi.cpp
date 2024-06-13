#include "Wifi.h"

#include <memory>

int codal::WiFi::networksVisible()
{
    ism43362.ES_WIFI_ListAccessPoints();
    return ism43362.ES_WIFI_GetApNbr();
}

void codal::WiFi::attach(const ManagedString& ssid, const ManagedString& passphrase)
{
    ES_WIFI_Status_t attachStatus =
        ism43362.ES_WIFI_Connect(ssid.toCharArray(), passphrase.toCharArray(), ES_WIFI_SEC_WPA_WPA2);

    if (attachStatus == ES_WIFI_STATUS_OK) {
        wifi_status = WL_CONNECTED;
    }
    else {
        ism43362.ES_WIFI_Disconnect();
        wifi_status = WL_CONNECT_FAILED;
    }
}

bool codal::WiFi::isAttached()
{
    return wifi_status == WL_CONNECTED;
}

void codal::WiFi::detach()
{
    if (wifi_status != WL_NO_SHIELD) {
        ism43362.ES_WIFI_Disconnect();
        wifi_status = WL_DISCONNECTED;
    }
}

std::unique_ptr<codal::WiFiClient> codal::WiFi::connect(const ManagedString& host, uint16_t port)
{
    std::unique_ptr<codal::WiFiClient> client(new WiFiClient(this));
    client->connect(host, port);
    return client;
}

uint8_t codal::WiFiClient::getFirstSocket()
{
    return wifi->ism43362.getFreeSocket();
}

uint8_t codal::WiFiClient::connectionState()
{
    if (sock == SOCK_NOT_AVAIL) {
        return SOCKET_FREE;
    }
    else {
        return wifi->ism43362.getSocketState(sock);
    }
}

bool codal::WiFiClient::isConnected()
{
    return connected;
}

bool codal::WiFiClient::connect(IPAddress ip, uint16_t port)
{
    int8_t sock;

    if (this->sock == NO_SOCKET_AVAIL) {
        sock = getFirstSocket();  // get next free socket
        if (sock != -1) {
            this->sock = sock;
        }
    }

    if (this->sock != NO_SOCKET_AVAIL) {
        // set connection parameter and start client
        wifi->ism43362.ES_WIFI_SetConnectionParam(this->sock, ES_WIFI_TCP_CONNECTION, port, ip);
        wifi->ism43362.ES_WIFI_StartClientConnection(this->sock);
        this->connected = true;
        return true;
    }

    return false;
}

bool codal::WiFiClient::connect(const ManagedString& host, uint16_t port)
{
    IPAddress remoteHostAddress;

    wifi->ism43362.ES_WIFI_DNS_LookUp(host.toCharArray(), &remoteHostAddress);

    return connect(remoteHostAddress, port);
}

void codal::WiFiClient::disconnect()
{
    if (this->sock == NO_SOCKET_AVAIL) {
        return;
    }

    wifi->ism43362.ES_WIFI_StopServerSingleConn(this->sock);

    this->sock      = NO_SOCKET_AVAIL;
    this->connected = false;
}

/**
 * @brief  Read a single byte from the current packet
 * @param  None
 * @retval the read byte
 */
char codal::WiFiClient::read()
{
    uint8_t receivedByte    = '\0';  // data received
    uint16_t receivedLength = 0;     // number of data received

    wifi->ism43362.ES_WIFI_ReceiveData(this->sock, &receivedByte, 1, &receivedLength, WIFI_TIMEOUT);

    return receivedByte;
}

int codal::WiFiClient::read(char* buf, size_t size)
{
    if (rxInUse()) return DEVICE_SERIAL_IN_USE;

    lockRx();

    // lazy initialisation of our buffers
    if (!(status & WIFI_ISM43362_STATUS_RX_BUFF_INIT)) {
        int result = initialiseReceptionBuffer();

        if (result != DEVICE_OK) return result;
    }

    uint16_t receivedLength = 0;

    wifi->ism43362.ES_WIFI_ReceiveData(this->sock, (uint8_t*)buf, size, &receivedLength, WIFI_TIMEOUT);

    if (receivedLength < size) {
        buf[receivedLength] = '\0';
    }

    unlockRx();

    return receivedLength;
}

size_t codal::WiFiClient::write(const char* buf, size_t size)
{
    uint16_t sentLength = 0;  // number of data really send
    uint8_t* temp       = (uint8_t*)buf;

    wifi->ism43362.ES_WIFI_SendResp(this->sock, temp, size, &sentLength, WIFI_TIMEOUT);

    return sentLength;
}

int codal::WiFiClient::isReadable()
{
    if (!(status & WIFI_ISM43362_STATUS_RX_BUFF_INIT)) {
        int result = initialiseReceptionBuffer();

        if (result != DEVICE_OK) return result;
    }

    return (rxBuffTail != rxBuffHead) ? 1 : 0;
}

int codal::WiFiClient::rxInUse()
{
    return (status & WIFI_ISM43362_STATUS_RX_IN_USE);
}

void codal::WiFiClient::lockRx()
{
    status |= WIFI_ISM43362_STATUS_RX_IN_USE;
}

void codal::WiFiClient::unlockRx()
{
    status &= ~WIFI_ISM43362_STATUS_RX_IN_USE;
}