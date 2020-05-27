
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

SARA 2.00GSa/s
```

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
