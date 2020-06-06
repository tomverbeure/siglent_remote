/* usbtmc_trivial.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

// The scope has a maximum waveform capture size of 140M.
int buffer_size = 150000000;
char *buffer;

int cmd(int file, char *cmd)
{
    printf("Cmd: %s\n", cmd);
    write(file,cmd,strlen(cmd));
}

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
        if (argc == 2){
            if (strchr(argv[1], '?') || strcmp(argv[1], "SCDP") == 0)
                query(tmc_file, argv[1]);
            else
                cmd(tmc_file, argv[1]);
        }
    }
}

