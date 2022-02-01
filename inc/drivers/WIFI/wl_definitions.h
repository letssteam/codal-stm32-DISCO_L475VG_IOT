#pragma once

#define WL_SSID_MAX_LENGTH        32     // Maximum size of a SSID
#define WL_WPA_KEY_MAX_LENGTH     63     // Length of passphrase. Valid lengths are 8-63.
#define WL_WEP_KEY_MAX_LENGTH     13     // Length of key in bytes. Valid values are 5 and 13.
#define WL_MAC_ADDR_LENGTH        6      // Size of a MAC-address or BSSID
#define WL_IPV4_LENGTH            4      // Size of a IPV4
#define WL_NETWORKS_LIST_MAXNUM   10     // Maximum size of a SSID list
#define MAX_SOCK_NUM              4      // Maximum number of socket
#define SOCK_NOT_AVAIL            255    // Socket not available constant
#define NA_STATE                  -1     // Default state value for Wi-Fi state field
#define WL_MAX_ATTEMPT_CONNECTION 10     // Maximum number of attempts to establish Wi-Fi connection
#define WIFI_TIMEOUT              5000U  // Defines the Wi-Fi request timeout in milliseconds

typedef enum {
    WL_NO_SHIELD   = 255,
    WL_IDLE_STATUS = 0,
    WL_NO_SSID_AVAIL,
    WL_SCAN_COMPLETED,
    WL_CONNECTED,
    WL_CONNECT_FAILED,
    WL_CONNECTION_LOST,
    WL_DISCONNECTED
} wl_status_t;