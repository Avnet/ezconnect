 
#ifndef __EASY_CONNECT_H__
#define __EASY_CONNECT_H__

#include "mbed.h"

#define CELLULAR_WNC14A2A 203
#define CELLULAR_BG96     204

// This is address to mbed Device Connector
#define MBED_SERVER_ADDRESS "coap://api.connector.mbed.com:5684"

/* \brief print_MAC - print_MAC  - helper function to print out MAC address
 * in: network_interface - pointer to network i/f
 *     bool log-messages   print out logs or not
 * MAC address is print, if it can be acquired & log_messages is true.
 *
 */
void print_MAC(NetworkInterface* network_interface, bool log_messages);


/* \brief easy_connect - easy_connect function to connect the pre-defined network bearer,
 *                       config done via mbed_app.json (see README.md for details).
 * IN: bool  log_messages  print out diagnostics or not.
 */
NetworkInterface* easy_connect(bool log_messages = false);

// This is address to mbed Device Connector
#define MBED_SERVER_ADDRESS "coap://api.connector.mbed.com:5684"

/* \brief print_MAC - print_MAC  - helper function to print out MAC address
 * in: network_interface - pointer to network i/f
 *     bool log-messages   print out logs or not
 * MAC address is print, if it can be acquired & log_messages is true.
 *
 */
void print_MAC(NetworkInterface* network_interface, bool log_messages);


/* \brief easy_connect - easy_connect function to connect the pre-defined network bearer,
 *                       config done via mbed_app.json (see README.md for details).
 * IN: bool  log_messages  print out diagnostics or not.
 */
NetworkInterface* easy_connect(bool log_messages = false);

/* \brief easy_get_netif - easy_connect function to get pointer to network interface w/o connect it.
                           You might need this for example getting the WiFi interface, then doing a scan
                           and then connecting to one of the SSIDs found with a password end user supplies.
 * IN: bool  log_messages  print out diagnostics or not.
 */
NetworkInterface* easy_get_netif(bool log_messages);

#endif // __EASY_CONNECT_H__
