/* usbtmc_trivial_hang.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

// The scope has a maximum waveform capture size of 140M.
int buffer_size = 150000000;
char *buffer;

int query(int file, char *cmd)
{
    printf("Cmd: %s\n", cmd);
    write(file,cmd,strlen(cmd));

    int bytes_fetched=read(file,buffer,buffer_size);
    printf("Size: %d\n",bytes_fetched);
    buffer[bytes_fetched]=0;
    printf("Response:\n%s\n",buffer);

    return bytes_fetched;
}

int main(int argc, char **argv)
{
    buffer = (char *)malloc(buffer_size);

    int tmc_file=open("/dev/usbtmc0",O_RDWR);
    if(tmc_file>0)
    {
        query(tmc_file, "*IDN?");
        query(tmc_file, "C1:WF? DESC");
        query(tmc_file, "C1:WF? DAT2");
    }
}

