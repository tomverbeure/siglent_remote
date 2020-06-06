/* usbtmc_multiple_reads.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

// The scope has a maximum waveform capture size of 140M.
int buffer_size = 150000000;
char *buffer;

#define MIN(x,y) ((x)<(y) ? (x) : (y))

void query(int file, char *cmd)
{
    printf("Cmd: %s\n", cmd);
    write(file,cmd,strlen(cmd));

    int max_bytes_per_req = buffer_size;
    int i = 0;
    int bytes_fetched, bytes_requested;
    do{
        bytes_requested = MIN(max_bytes_per_req, buffer_size-i);
        bytes_fetched = read(file, buffer+i, bytes_requested);
        printf("Size: %d\n",bytes_fetched);
        i += bytes_fetched;
    } while(bytes_fetched == bytes_requested);

    buffer[i]=0;
    printf("Response:\n%s\n",buffer);
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

