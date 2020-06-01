
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#include <sys/ioctl.h>
#include <linux/usb/tmc.h>

int buffer_size = 200000000;
char *buffer;

void query(int file, char *cmd, int write_only)
{
    printf("Cmd: %s\n", cmd);
    write(file,cmd,strlen(cmd));

    if (write_only)
        return;

    int actual=read(file,buffer,buffer_size);
    printf("Size: %d\n",actual);
    buffer[actual+1]=0;
    printf("Response:\n%s\n",buffer);
}

int main(int argc, char **argv)
{
    int myfile;
    int actual;
    //char buffer[4000];


    buffer = (char *)malloc(buffer_size);
    assert(buffer);

    myfile=open("/dev/usbtmc0",O_RDWR);
    if(myfile>0)
    {
        //int retval;

        //retval = ioctl(myfile, USBTMC_IOCTL_CLEAR);
        //printf("IOCTL_CLEAR: %d\n", retval);

        /*
        retval = ioctl(myfile, USBTMC_IOCTL_CLEAR_IN_HALT);
        printf("IOCTL_CLEAR_IN_HALT: %d\n", retval);
        */

        /*
        retval = ioctl(myfile, USBTMC_IOCTL_ABORT_BULK_IN);
        printf("IOCTL_ABORT_BULK_IN: %d\n", retval);
        */

        char *cmd = "*IDN?";
        //char *cmd = "C1: WF? DESC\n";
        //char *cmd = "C1:TRACE?\n";
        //char *cmd = "C1:WF? DAT2\n";
        //char *cmd = "SCDP?\n";
        //char *cmd = "SANU? C1\n";

        /*
        write(myfile,cmd,strlen(cmd));
        actual=read(myfile,buffer, 4000);
        buffer[actual]=0;
        printf("Response:\n%s\n(%d)\n",buffer, actual);
        */

        query(myfile, "*IDN?", 0);
        query(myfile, "*OPT?", 0);
        query(myfile, "C1:WF? DESC", 0);
#if 0
        int nr_points = 14000;
        int max_points_per_req = 3000;
        for(int i=0;i<nr_points;i += max_points_per_req){
            char cmd[100];
            sprintf(cmd, "WFSU FP,%d,SP,0,NP,%d",i,max_points_per_req);
            query(myfile, cmd, 1);
            query(myfile, "C1:WF? DAT2", 0);
        }
#endif

#if 1
        query(myfile, "C1:WF? DAT2", 1);
        int actual;
//        actual=read(myfile,buffer,64);
//        printf("Size: %d\n",actual);
        int max_points_per_req = 2032;
        do{
            actual=read(myfile,buffer,max_points_per_req);
            printf("Size: %d\n",actual);
        } while(actual == max_points_per_req);
#endif
        close(myfile);
    }
}
