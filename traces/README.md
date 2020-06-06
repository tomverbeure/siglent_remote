

USB capture setup instructions: https://wiki.wireshark.org/CaptureSetup/USB

After each reboot, run 
```
sudo modprobe usbmon
sudo setfacl -m u:$USER:r /dev/usbmon*
```
