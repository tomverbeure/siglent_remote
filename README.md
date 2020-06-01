Limitations:
* USBTMC on Linux:
    * 2 ways to talk to a USBTMC device
        * usbtmc kernel driver
        * generic libusb -> user mode driver
        
* USBTMC using the kernel
    * reads can have a buffer of max 2032
        * higher than 2032 -> USBTMC device hangs. Need to reboot scope!
        * no way to recover: have tried various IOCTLs...
    * kernel 4.15 (Ubuntu 18.04 LTS) code is here: https://github.com/torvalds/linux/blob/v4.17/drivers/usb/class/usbtmc.c
         * #define USBTMC_SIZE_IOBUFFER 2048
    * kernel 4.20 and later
        * USBTMC_API_VERSION 2
        * #define USBTMC_SIZE_IOBUFFER 4096
        * timeout: still defaults to 5s, but programmable
            * IOCTL_SET_TIMEOUT/IOCTL_GET_TIMEOUT
        * upgrade to later kernel: https://ubuntu.com/kernel/lifecycle
        * new API has IOCTL_API_VERSION call
        * new include file: https://github.com/torvalds/linux/blob/master/include/uapi/linux/usb/tmc.h

    * download times (size 2032):
        * 14k: 0.07s
        * 28k: 0.13s
        * 140k: 0.6s
        * 280k: 1.2s
        * 1.4M: 5.9s -> 1.9Mbit/s
        * 2.8M: timeout after 5s
            * after such a timeout -> USBTMC device hangs. Need to reboot scope!
            * 5s timeout USBTMC_TIMEOUT
        * downloading seems to have 2 steps:
            * preparing the data inside the scope: when this last longer than 5s, you can a timeout (using default settings)
            * downloading the data 
    * maximum size of waveform: 1.4M points.

* libusb USBTMC driver
    * Sigrok has one: https://sigrok.org/gitweb/?p=libsigrok.git;a=blob;f=src/scpi/scpi_usbtmc_libusb.c
    * pyvisa-py implements a USBTMC driver in pure python: https://github.com/pyvisa/pyvisa-py/blob/master/pyvisa-py/protocols/usbtmc.py
        * uses pyusb, which is a wrapper around (among others) libusb

* LXI
    * download times: 
        * 14k: 0.110s
        * 28k: 0.14s
        * 140k: 0.45s
        * 280k: 0.87s
            * Wait for 0.65s after READ call -> data transfer is only 0.22s
        * 1.4M: 4.3s
            * Wait for 3.1s after call -> data transfer is only 1.2s
            * First a few seconds hanging, then output
        * 2.8M: 8.6s
            * Wait for 6.2s after call -> data transfer is only 2.4s
        * 14M: "failed to receive message"
            * VXI-11 DESTROY_LINK call exactly 25s after VXI11 DEVICE_READ call:

                liblxi/src/vxi11core_clnt.c (auto-generated) 

                /* Default timeout can be changed using clnt_control() */
                static struct timeval TIMEOUT = { 25, 0 };

                man clnt_control -> standard RPC call
                
            * lxi -t 50: increase lock_timeout doesn't work

Usage:

* Set IP address in the Makefile
* Dump screenshot in a file:

```
make view
```

Working queries:

```
*IDN?
SCDP            - screendump
```

```
SANU? C1        - return number of sample points from last acquisition

./visa_query.py 192.168.1.177 "SANU? C1"
*IDN SIGLENT,SDS2304X,SDS2XJBD1R2754,1.2.2.2 R10

SANU 140Mpts
```

```
SARA?           - current sample rate

./visa_query.py 192.168.1.177 "SARA?"
*IDN SIGLENT,SDS2304X,SDS2XJBD1R2754,1.2.2.2 R10

SARA 2.00GSa/s ```

```
SKEW?           - Skew value of the specified trace

./visa_query.py 192.168.1.177 "SKEW?"
*IDN SIGLENT,SDS2304X,SDS2XJBD1R2754,1.2.2.2 R10

C1:SKEW 0.00ns
```


SCPI replies have 3 different headers: long, short, and off. Here's the difference:


```
# Long
*IDN SIGLENT,SDS2304X,SDS2XJBD1R2754,1.2.2.2 R10
C1:COUPLING D1M
# Short
*IDN SIGLENT,SDS2304X,SDS2XJBD1R2754,1.2.2.2 R10
C1:CPL D1M
# Off
SIGLENT,SDS2304X,SDS2XJBD1R2754,1.2.2.2 R10
D1M
```


WF? format description, mode in detail: https://siglentna.com/wp-content/uploads/dlm_uploads/2017/10/ProgrammingGuide_forSDS-1-1.pdf
Page 142.
The format of the descriptor can be received with the "TMPL?" query.


# ScopeHal

* Getting started: https://github.com/azonenberg/scopehal-docs/blob/master/section-gettingstarted.tex

```
sudo apt install build-essential cmake pkg-config libglm-dev libgtkmm-3.0-dev libsigc++-2.0-dev libyaml-cpp-dev
cd ~/projects

git clone https://github.com/anthonix/ffts.git
cd ffts/
mkdir build
cd build/
cmake ../
make -j 4
sudo make install

cd ~/projects
git clone https://github.com/azonenberg/scopehal-cmake.git --recurse-submodules
cd scopehal-cmake
mkdir build
cd build
cmake ../
make

cd ~/projects
git clone https://github.com/azonenberg/scopehal-docs.git
mkdir build
cd build
cmake ../
make
```


Use LXI to connect to Siglent scope. Command line:

```
lldb ./src/glscopeclient/glscopeclient --debug myscope:siglent:lxi:192.168.1.177
```

# USBTMC

* https://www.testandmeasurementtips.com/remote-communication-with-usbtmc-faq/
* https://github.com/torvalds/linux/blob/master/drivers/usb/class/usbtmc.c
* https://github.com/dpenkler/linux-usbtmc - update version of Linux kernel driver 
* http://literature.cdn.keysight.com/litweb/pdf/5989-6718EN.pdf
* https://www.xmos.com/download/AN00135:-USB-Test-and-Measurement-Device(2.0.0rc3).pdf

    Create your own USBTMC compatible device


# Info

* [PyVISA Manual](https://pyvisa.readthedocs.io/en/latest/)
* [Control a SIGLENT oscilloscope with Python](https://ktln2.org/2018/02/20/control-siglent-oscilloscope/)
* [Siglent Digital Oscillloscope Series Programming Guide](https://evision-webshop.de/WebRoot/Store13/Shops/e6077b56-ef34-48be-850f-07696838e42e/MediaGallery/Siglent/Siglent-Programming-Guide-2.pdf)
* [Smaller Siglent Programming Guide but specific for SDS?](https://siglentna.com/wp-content/uploads/dlm_uploads/2017/10/ProgrammingGuide_forSDS-1-1.pdf)
