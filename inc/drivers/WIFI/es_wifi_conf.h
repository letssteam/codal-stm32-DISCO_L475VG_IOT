#pragma once

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
