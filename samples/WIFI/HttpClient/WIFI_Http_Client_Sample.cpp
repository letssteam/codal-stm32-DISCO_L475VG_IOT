#include "WIFI_Http_Client_Sample.h"

#include "ssd1306.h"

#define TERMINAL_USE

/* Update SSID and PASSWORD with own Access point settings */
#define SSID     "MySSID"
#define PASSWORD "MyPasswd"

uint8_t RemoteIP[] = {192, 168, 3, 110};
#define RemotePORT 8002

#define WIFI_WRITE_TIMEOUT 10000
#define WIFI_READ_TIMEOUT  10000

#define CONNECTION_TRIAL_MAX 10

#if defined(TERMINAL_USE)
#define TERMOUT(...) printf(__VA_ARGS__)
#else
#define TERMOUT(...)
#endif

static uint8_t RxData[500];

void Wifi_Http_Client_Sample_main(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    uint8_t MAC_Addr[6];
    uint8_t IP_Addr[4];
    uint8_t TxData[] = "STM32 : Hello!\n";
    int32_t Socket   = -1;
    uint16_t Datalen;
    int32_t ret;
    int16_t Trials = CONNECTION_TRIAL_MAX;

    codal::SSD1306_I2C oled(&discoL475VgIot.i2c1, 0x78, 128, 64, false);

    oled.init();
    oled.fill(0);
    oled.drawText("Demo wifi", 0, 0, 1);
    oled.show();

    if (WIFI_Init() == WIFI_STATUS_OK) {
        oled.drawText("WIFI Initialized.", 0, 8, 1);
        oled.show();
    }
    else {
        oled.drawText("WIFI Not Initialized.", 0, 8, 1);
        oled.show();
    }

    //     if (WIFI_GetMAC_Address(MAC_Addr) == WIFI_STATUS_OK) {
    //         TERMOUT("> es-wifi module MAC Address : %X:%X:%X:%X:%X:%X\n", MAC_Addr[0], MAC_Addr[1], MAC_Addr[2],
    //                 MAC_Addr[3], MAC_Addr[4], MAC_Addr[5]);
    //     }
    //     else {
    //         TERMOUT("> ERROR : CANNOT get MAC address\n");
    //     }

    //     if (WIFI_Connect(SSID, PASSWORD, WIFI_ECN_WPA2_PSK) == WIFI_STATUS_OK) {
    //         TERMOUT("> es-wifi module connected \n");
    //         if (WIFI_GetIP_Address(IP_Addr) == WIFI_STATUS_OK) {
    //             TERMOUT("> es-wifi module got IP Address : %d.%d.%d.%d\n", IP_Addr[0], IP_Addr[1], IP_Addr[2],
    //                     IP_Addr[3]);

    //             TERMOUT("> Trying to connect to Server: %d.%d.%d.%d:%d ...\n", RemoteIP[0], RemoteIP[1],
    //             RemoteIP[2],
    //                     RemoteIP[3], RemotePORT);

    //             while (Trials--) {
    //                 if (WIFI_OpenClientConnection(0, WIFI_TCP_PROTOCOL, "TCP_CLIENT", RemoteIP, RemotePORT, 0) ==
    //                     WIFI_STATUS_OK) {
    //                     TERMOUT("> TCP Connection opened successfully.\n");
    //                     Socket = 0;
    //                     break;
    //                 }
    //             }
    //             if (Socket == -1) {
    //                 TERMOUT("> ERROR : Cannot open Connection\n");
    //             }
    //         }
    //         else {
    //             TERMOUT("> ERROR : es-wifi module CANNOT get IP address\n");
    //         }
    //     }
    //     else {
    //         TERMOUT("> ERROR : es-wifi module NOT connected\n");
    //     }
    // }
    // else {
    //     TERMOUT("> ERROR : WIFI Module cannot be initialized.\n");
    // }

    // while (1) {
    //     if (Socket != -1) {
    //         ret = WIFI_ReceiveData(Socket, RxData, sizeof(RxData) - 1, &Datalen, WIFI_READ_TIMEOUT);
    //         if (ret == WIFI_STATUS_OK) {
    //             if (Datalen > 0) {
    //                 RxData[Datalen] = 0;
    //                 TERMOUT("Received: %s\n", RxData);
    //                 ret = WIFI_SendData(Socket, TxData, sizeof(TxData), &Datalen, WIFI_WRITE_TIMEOUT);
    //                 if (ret != WIFI_STATUS_OK) {
    //                     TERMOUT("> ERROR : Failed to Send Data, connection closed\n");
    //                     break;
    //                 }
    //             }
    //         }
    //         else {
    //             TERMOUT("> ERROR : Failed to Receive Data, connection closed\n");
    //             break;
    //         }
    //     }
    // }
}