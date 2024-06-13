#pragma once

#include <stdint.h>

#include "IPAddress.h"

#define ES_WIFI_MAX_SSID_NAME_SIZE 32
#define ES_WIFI_MAX_PSWD_NAME_SIZE 32
#define ES_WIFI_PRODUCT_ID_SIZE    32
#define ES_WIFI_PRODUCT_NAME_SIZE  32
#define ES_WIFI_FW_REV_SIZE        24
#define ES_WIFI_API_REV_SIZE       16
#define ES_WIFI_STACK_REV_SIZE     16
#define ES_WIFI_RTOS_REV_SIZE      16

#ifndef ES_WIFI_DATA_SIZE
#define ES_WIFI_DATA_SIZE 2000 /*Increased from 1400 to fit scan result.*/
#endif
#ifndef ES_WIFI_MAX_DETECTED_AP
#define ES_WIFI_MAX_DETECTED_AP 10
#endif
#ifndef ES_WIFI_TIMEOUT
#define ES_WIFI_TIMEOUT 0x0FFF
#endif
#define NO_SOCKET_AVAIL 255

#ifndef ES_WIFI_PAYLOAD_SIZE
#define ES_WIFI_PAYLOAD_SIZE 1200
#endif
#ifndef TIMEOUT_OFFSET
#define TIMEOUT_OFFSET 100U
#endif

/* Exported typedef ----------------------------------------------------------*/

typedef enum { SOCKET_FREE = 0, SOCKET_BUSY } socket_status_t;

typedef enum {
    ES_WIFI_STATUS_OK             = 0,
    ES_WIFI_STATUS_REQ_DATA_STAGE = 1,
    ES_WIFI_STATUS_ERROR          = 2,
    ES_WIFI_STATUS_TIMEOUT        = 3,
    ES_WIFI_STATUS_IO_ERROR       = 4,
} ES_WIFI_Status_t;

typedef enum {
    ES_WIFI_MODE_SINGLE = 0,
    ES_WIFI_MODE_MULTI  = 1,
} ES_WIFI_ConnMode_t;

typedef enum {
    ES_WIFI_TCP_CONNECTION      = 0,
    ES_WIFI_UDP_CONNECTION      = 1,
    ES_WIFI_UDP_LITE_CONNECTION = 2,
    ES_WIFI_TCP_SSL_CONNECTION  = 3,
    ES_WIFI_MQTT_CONNECTION     = 4,
} ES_WIFI_ConnType_t;

/* Security settings for Wi-Fi network */
typedef enum {
    ES_WIFI_SEC_OPEN = 0x00, /*!< Wi-Fi is open */
    ES_WIFI_SEC_WEP  = 0x01, /*!< Wired Equivalent Privacy option for Wi-Fi security. \note This mode can't be used when
                                setting up ES_WIFI Wi-Fi */
    ES_WIFI_SEC_WPA       = 0x02, /*!< Wi-Fi Protected Access */
    ES_WIFI_SEC_WPA2      = 0x03, /*!< Wi-Fi Protected Access 2 */
    ES_WIFI_SEC_WPA_WPA2  = 0x04, /*!< Wi-Fi Protected Access with both modes */
    ES_WIFI_SEC_WPA2_TKIP = 0x05, /*!< Wi-Fi Protected Access with both modes */
    ES_WIFI_SEC_UNKNOWN   = 0xFF, /*!< Wi-Fi Unknown Security mode */
} ES_WIFI_SecurityType_t;

typedef enum {
    ES_WIFI_IPV4 = 0x00,
    ES_WIFI_IPV6 = 0x01,
} ES_WIFI_IPVer_t;

typedef enum {
    ES_WIFI_AP_NONE     = 0x00,
    ES_WIFI_AP_ASSIGNED = 0x01,
    ES_WIFI_AP_JOINED   = 0x02,
    ES_WIFI_AP_ERROR    = 0xFF,
} ES_WIFI_APState_t;

/* Communication interface */
typedef enum { COMM_UART, COMM_SPI, COMM_USB_HID, COMM_USB_VCP } comm_mode;

/* virtual class necessary to abstract the Wi-Fi device                       */
class WiFiDriver {
  public:
    virtual ~WiFiDriver(){};

    virtual ES_WIFI_Status_t ES_WIFI_Init()                                                              = 0;
    virtual void ES_WIFI_ListAccessPoints()                                                              = 0;
    virtual int ES_WIFI_GetApNbr()                                                                       = 0;
    virtual ES_WIFI_Status_t ES_WIFI_Connect(const char* SSID, const char* Password,
                                             ES_WIFI_SecurityType_t SecType)                             = 0;
    virtual void ES_WIFI_Disconnect()                                                                    = 0;
    virtual uint8_t* ES_WIFI_GetMACAddress(uint8_t* mac)                                                 = 0;
    virtual IPAddress ES_WIFI_GetIPAddress()                                                             = 0;
    virtual IPAddress ES_WIFI_GetSubnetMask()                                                            = 0;
    virtual IPAddress ES_WIFI_GetGatewayIP()                                                             = 0;
    virtual uint8_t* ES_WIFI_GetSSID()                                                                   = 0;
    virtual uint8_t* ES_WIFI_GetSSID(uint8_t networkItem)                                                = 0;
    virtual uint8_t* ES_WIFI_GetBSSID(uint8_t* bbsid)                                                    = 0;
    virtual int ES_WIFI_GetEncryptionType()                                                              = 0;
    virtual int ES_WIFI_GetEncryptionType(uint8_t networkItem)                                           = 0;
    virtual int32_t ES_WIFI_GetRSSI()                                                                    = 0;
    virtual int32_t ES_WIFI_GetRSSI(uint8_t networkItem)                                                 = 0;
    virtual uint8_t* ES_WIFI_GetProductID()                                                              = 0;
    virtual char* ES_WIFI_GetFWRevID()                                                                   = 0;
    virtual uint8_t* ES_WIFI_GetRTOSRev()                                                                = 0;
    virtual uint8_t* ES_WIFI_GetProductName()                                                            = 0;
    virtual uint8_t* ES_WIFI_GetAPIRev()                                                                 = 0;
    virtual uint8_t* ES_WIFI_GetStackRev()                                                               = 0;
    virtual void ES_WIFI_SetMACAddress(uint8_t* mac)                                                     = 0;
    virtual void ES_WIFI_ResetToFactoryDefault()                                                         = 0;
    virtual void ES_WIFI_ResetModule()                                                                   = 0;
    virtual void ES_WIFI_SetProductName(uint8_t* ProductName)                                            = 0;
    virtual void ES_WIFI_Ping(uint8_t* address, uint16_t count, uint16_t interval_ms)                    = 0;
    virtual void ES_WIFI_DNS_LookUp(const char* url, IPAddress* ipaddress)                               = 0;
    virtual void ES_WIFI_getRemoteData(uint8_t sock, uint8_t* ip, uint16_t* port)                        = 0;
    virtual void ES_WIFI_StartServerSingleConn(uint8_t index, comm_mode mode)                            = 0;
    virtual void ES_WIFI_StopServerSingleConn(uint8_t index)                                             = 0;
    virtual void ES_WIFI_StartServerMultiConn(uint8_t socket, comm_mode mode)                            = 0;
    virtual void ES_WIFI_StopServerMultiConn()                                                           = 0;
    virtual void ES_WIFI_StartClientConnection(uint8_t index)                                            = 0;
    virtual void ES_WIFI_StopClientConnection(uint8_t index)                                             = 0;
    virtual void ES_WIFI_ReceiveData(uint8_t Socket, uint8_t* pdata, uint16_t Reqlen, uint16_t* Receivedlen,
                                     uint32_t Timeout)                                                   = 0;
    virtual void ES_WIFI_SetConnectionParam(uint8_t Number, ES_WIFI_ConnType_t Type, uint16_t LocalPort) = 0;
    virtual void ES_WIFI_SetConnectionParam(uint8_t Number, ES_WIFI_ConnType_t Type, uint16_t LocalPort,
                                            IPAddress Ip)                                                = 0;
    virtual void ES_WIFI_SendResp(uint8_t Socket, uint8_t* pdata, uint16_t Reqlen, uint16_t* SentLen,
                                  uint32_t Timeout)                                                      = 0;
    virtual uint8_t getCurrentSocket(void)                                                               = 0;
    virtual int8_t getFreeSocket(void)                                                                   = 0;
    virtual uint8_t getSocketState(uint8_t socket)                                                       = 0;
};