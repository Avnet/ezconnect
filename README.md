# EZ Connect - A derivative of ARM's Easy-Connect to add supported connectivity using Avnet solutions to your mbed OS project

Give your application the ability to switch between connectivity methods. The `NetworkInterface` API makes this easy, but you need a mechanism for the user to chooce the method. EZ Connect handles all of this for you. Just declare the desired connectivity method in the `mbed_app.json` file and call `easy_connect()` from your application.

## Specifying the connectivity method

Add the following to your `mbed_app.json` file:

```json
{
    "config": {
        "network-interface":{
            "help": "options are ETHERNET, CELLULAR_WNC14A2A, CELLULAR_BG96",
            "value": "ETHERNET"
        }
    },
    "target_overrides": {
        "*": {
            "target.features_add": ["NANOSTACK", "LOWPAN_ROUTER", "COMMON_PAL"],
            "mbed-mesh-api.6lowpan-nd-channel-page": 0,
            "mbed-mesh-api.6lowpan-nd-channel": 12
        }
    }
}
```


If you use `MESH_LOWPAN_ND` or `MESH_THREAD` you need to specify your radio module:

```json
    "config": {
        "network-interface":{
            "help": "options are ETHERNET, WIFI_ESP8266, WIFI_IDW0XX1, WIFI_ODIN, WIFI_RTW, WIFI_WIZFI310, MESH_LOWPAN_ND, MESH_THREAD, CELLULAR_ONBOARD",
            "value": "MESH_LOWPAN_ND"
        },
        "mesh_radio_type": {
        	"help": "options are ATMEL, MCR20, SPIRIT1, EFR32",
        	"value": "ATMEL"
        }
    }
```

If you use `CELLULAR_ONBOARD` (for which user documentation can be found [here](https://docs.mbed.com/docs/mbed-os-api-reference/en/latest/APIs/communication/cellular/)) you must specify the following:

```json
    "target_overrides": {
        "*": {
            "ppp-cell-iface.apn-lookup": true
        }
    }
```
...and you may also need to specify one or more of the following:

```json
    "config": {
        "cellular-apn": {
            "help": "Please provide the APN string for your SIM if it is not already included in APN_db.h.",
            "value": "\"my_sims_apn\""
        },
        "cellular-username": {
            "help": "May or may not be required for your APN, please consult your SIM provider.",
            "value": "\"my_sim_apns_username\""
        },
        "cellular-password": {
            "help": "May or may not be required for your APN, please consult your SIM provider.",
            "value": "\"my_sim_apns_password\""
        },
        "cellular-sim-pin": {
            "help": "Please provide the PIN for your SIM (as a four digit string) if your SIM is normally locked",
            "value": "\"1234\""
        }
    }
```

## Using Easy Connect from your application

Easy Connect has just one function that returns either a `NetworkInterface`-pointer or `NULL`:

```cpp
#include "easy-connect.h"

int main(int, char**) {
    NetworkInterface* network = easy_connect(true); /* has 1 argument, enable_logging (pass in true to log to serial port) */
    if (!network) {
        printf("Connecting to the network failed... See serial output.\r\n");
        return 1;
    }

    // Rest of your program
}
```

## Overriding settings

Easy-connect was changed recently with [PR #59](https://github.com/ARMmbed/easy-connect/pull/59) - where some of the defines expected via `mbed_app.json` were
moved to the [`mbed_lib.json`](https://github.com/ARMmbed/easy-connect/blob/master/mbed_lib.json). 
This minimises the amount of lines needed (in typical cases) in the applications `mbed_app.json`. However, due to this the overrides
need to be done slightly differently, as you need to override the `easy-connect` defines.

So, for example changing the ESP8266 TX/RX pins and enable debugs - you would now have modify as below.

```json
    "target_overrides": {
        "*": {
            "easy-connect.wifi-esp8266-tx": "A1",
            "easy-connect.wifi-esp8266-rx": "A2",
            "easy-connect.wifi-esp8266-debug: true
         }
    }
```


## Configuration examples

There are many things that you have to modify for all of the combinations. Examples for configurations are available for example in the [mbed-os-example-client](https://github.com/ARMmbed/mbed-os-example-client/tree/master/configs) repository.

## Network errors

If Easy Connect cannot connect to the network, it returns a network error with an error code. To see what the error code means, see the [mbed OS Communication API](https://os.mbed.com/docs/latest/reference/network-socket.html).

## CR/LF in serial output

If you want to avoid using `\r\n` in your printouts and just use normal C style `\n` instead, please specify these to your `mbed_app.json`:

```json
       "target_overrides": {
        "*": {
            "platform.stdio-baud-rate": 115200,
            "platform.stdio-convert-newlines": true
        }
    }
```

## Extra defines

If you'd like to use Easy Connect with mbed Client then you're in luck. Easy Connect automatically defines the `MBED_SERVER_ADDRESS` macro depending on your connectivity method (either IPv4 or IPv6 address). Use this address to connect to the right instance of mbed Device Connector.
