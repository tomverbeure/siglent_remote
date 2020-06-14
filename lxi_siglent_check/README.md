
# `LXI_SIGLENT_CHECK`

The goal of this program is to gather information from Siglent scopes about
the way they support SCPI.

Some scopes have bugs, others doesn't. There might be subtle differences etc.

The tool checks for the presence of known bugs, queries capabilities, records a 
waveform and fetches that etc.

Using it is easy:

* Install `liblxi`

    On Ubuntu: `sudo apt install liblxi-dev`

* Compile
    `run.sh`

* Figure out the IP address of your Siglent scope

    * Plug in the Ethernet cable into the scope
    * Power cycle the scope
    * On the scope: 
        * Press `[Utility] -> [I/O] *(Page 2/3)* -> [LAN]`
        * Write down the IP address
        * Press `[Single]` to exit the menu

* Run the tool

    `./lxi_siglent_check <IP address of the scope> | tee siglent_results.log`

* Email the log to `hombre at gmail dot com`


