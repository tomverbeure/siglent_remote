#include <stdio.h>
#include <string.h>
#include <lxi.h>

 int main()
 {
     char response[65536];
     int device, length, timeout = 1000;
     char command[256];

     // Initialize LXI library
     lxi_init();

     // Connect to LXI device
     device = lxi_connect("192.168.1.177", 0, "inst0", timeout, VXI11);

     // Send SCPI command
     strcpy(command, "C1:TRACE?");
     lxi_send(device, command, strlen(command), timeout);
     strcpy(command, "C2:TRACE?");
     lxi_send(device, command, strlen(command), timeout);

     // Wait for response
     lxi_receive(device, response, sizeof(response), timeout);
     printf("%s\n", response);
     lxi_receive(device, response, sizeof(response), timeout);
     printf("%s\n", response);

     // Disconnect
     lxi_disconnect(device);
}
