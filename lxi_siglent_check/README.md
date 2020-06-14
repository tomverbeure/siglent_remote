
# `LXI_SIGLENT_CHECK`

The goal of this program is to gather information from Siglent scopes about
the way they support SCPI.

Some scopes have bugs, others don't. There might be subtle differences etc.

The tool checks for the presence of known bugs, queries capabilities, records a 
waveform and fetches that etc.

Using it is easy:

* Install `liblxi`

    On Ubuntu: `sudo apt install liblxi-dev`

* Compile

    ```
    cd ./lxi_siglent_check
    ./run.sh
    ```

* Figure out the IP address of your Siglent scope

    * Plug in the Ethernet cable into the scope
    * Power cycle the scope
    * On the scope: 
        * Press `[Utility] -> [I/O] *(Page 2/3)* -> [LAN]`
        * Write down the IP address
        * Press `[Single]` to exit the menu

* Connect the probe of channel 1 to the calibration 1kHz output

* Configure the scope so that it triggers on channel 1 and so that it shows a nice square wave.

    Something like this:

    ![Scope screenshot](./test_waveform.png)

* Run the tool

    `./lxi_siglent_check <IP address of the scope> | tee siglent_results.log`

    When running the tool, a number of settings of the scope will be changed: vdiv, timebase, probe attenuation, 
    number of sample points, ... Nothing major though.

* Email the log to `hombre at gmail dot com`

