# EZ Connect - A derivative of ARM's Easy-Connect to easily add supported for Avnet connectivity solutions to your mbed OS project


Give your application the ability to switch between connectivity methods. The NetworkInterface API makes this easy, but you need a mechanism for the user to chooce the method. EZ Connect handles all of this for you. Just declare the desired connectivity method in the mbed_app.json file and call easy_connect() from your application.

## Specifying the connectivity method

Add the following to your `mbed_app.json` file:

```json
{
    "config": {
        "network-interface":{
            "help": "options are ETHERNET, CELLULAR_WNC14A2A, CELLULAR_BG96",
            "value": "ETHERNET"
        }
    }
}
```


## Using EZ Connect from your application

EZ Connect has just one function that returns either a `NetworkInterface`-pointer or `NULL`:

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

If you'd like to use EZ Connect with mbed Client then you're in luck. EZ Connect automatically defines the `MBED_SERVER_ADDRESS` macro depending on your connectivity method (either IPv4 or IPv6 address). Use this address to connect to the right instance of mbed Device Connector.
