
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

int buffer_size = 200000000;
char *buffer;

void query(int file, char *cmd)
{
    printf("Cmd: %s\n", cmd);
    write(file,cmd,strlen(cmd));

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

        query(myfile, "*IDN?");
        query(myfile, "*OPT?");
        query(myfile, "C1:WF? DESC");
//        query(myfile, "C1:WF? DAT2");
        close(myfile);
    }
}
