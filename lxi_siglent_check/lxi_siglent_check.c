#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lxi.h>
#include <assert.h>

int device, timeout = 5000;

char *reply; 
int reply_size = 100000000;

int send(char *cmd)
{
    printf("\nSending: %s\n", cmd);

    int ret = lxi_send(device, cmd, strlen(cmd), timeout);
    if (ret == LXI_ERROR){
        printf("lxi_send error.\n");
        exit(-1);
    }

    return ret;
}

int query(char *cmd, char *reply, int reply_len)
{
    printf("\nQuery: %s\n", cmd);

    int ret = lxi_send(device, cmd, strlen(cmd), timeout);
    if (ret == LXI_ERROR){
        printf("lxi_send error.\n");
        exit(-1);
    }

    ret = lxi_receive(device, reply, reply_len, timeout);
    if (ret == LXI_ERROR){
        printf("lxi_receive error.\n");
        exit(-1);
    }

    printf("Received: %d bytes\n", ret);
    reply[ret] = '\0';
    printf("Reply: %s\n", reply);

    return ret;
}

int check_vdiv_bug()
{
    printf("Setting probe attenuation to value to 10\n");
    send("C1:ATTN 10");
    query("C1:ATTN?", reply, reply_size);

    printf("Trying to setting vdiv to 1V/div\n");
    send("C1:VOLT_DIV 1.00E+00");
    query("C1:VOLT_DIV?", reply, reply_size);

    double vdiv = atof(reply);
    if ((vdiv-1.0) > 0.1){
        printf("ERROR: asked for 1V/div, but got %lfV/div!\n", vdiv);
    }
}

void print_hex(unsigned char *bytes, int len)
{
    for(int i=0;i<len;++i){
        printf("%02x ", bytes[i]);
        if (i%32 == 31){
            printf("\n");
        }
    }
    printf("\n");
}

int check_wavedesc_length_bug()
{
    for(int i=0;i<6;++i){
        int ret = query("C1:WF? DESC", reply, reply_size);
        if (ret != 363){
            printf("ERROR: WF? DESC length expected to be 363 bytes. Received %d!\n", ret);
        }

        print_hex(reply, ret);
    }
}

int capture_wf()
{
    printf("Capturing test waveform...\n");

    send("C1:ATTN 10");
    query("C1:ATTN?", reply, reply_size);

    send("C1:VOLT_DIV 0.1");
    query("C1:VOLT_DIV?", reply, reply_size);

    send("TDIV 1ms");
    query("TDIV?", reply, reply_size);

    query("SAST?", reply, reply_size);

    query("TRIG_MODE?", reply, reply_size);

    send("TRIG_MODE AUTO");
    query("TRIG_MODE?", reply, reply_size);
    
    // Trigger mode must be AUTO, otherwise MSIZ doesn't work.
    query("MSIZ?", reply, reply_size);
    send("MSIZ 7K");
    query("MSIZ?", reply, reply_size);

    int nr_bytes;
    nr_bytes = query("C1:WF? DESC", reply, reply_size);
    print_hex(reply, nr_bytes);

    nr_bytes = query("C1:WF? DAT2", reply, reply_size);
    print_hex(reply, nr_bytes);

    nr_bytes = query("C1:WF? ALL", reply, reply_size);
    print_hex(reply, nr_bytes);

    query("TMPL?", reply, reply_size);
}

int main(int argc, char **argv)
{
    printf("lxi_siglent_check version: %s\n", HASH);

    reply = malloc(reply_size);
    assert(reply);

    char cmd[200];

    // Initialize LXI library
    lxi_init();

    if (argc != 2){
        printf("Usage: %s <ip address>\n", argv[0]);
        exit(-1);
    }

    // Connect to LXI device
    device = lxi_connect(argv[1], 0, "inst0", timeout, VXI11);

    if (device == LXI_ERROR){
        printf("Error: can't connect to scope!\n");
        exit(-2);
    }

    printf("Connected to %s.\n", argv[1]);

    query("*IDN?", reply, reply_size);
    query("*OPT?", reply, reply_size);
    query("COMM_HEADER?", reply, reply_size);
    send("COMM_HEADER OFF");
    query("COMM_HEADER?", reply, reply_size);

    printf("============================================================\n");
    printf("Save current probe attentuation\n");
    query("C1:ATTN?", reply, reply_size);
    char cur_attn[256];
    strcpy(cur_attn, reply);

    printf("Save vdiv\n");
    query("C1:VOLT_DIV?", reply, reply_size);
    char cur_vdiv[256];
    strcpy(cur_vdiv, reply);

    printf("Save offset\n");
    query("C1:OFST?", reply, reply_size);
    char cur_offset[256];
    strcpy(cur_offset, reply);

    printf("Save sample points\n");
    query("SANU? C1", reply, reply_size);
    char cur_sample_points[256];
    strcpy(cur_sample_points, reply);

    printf("Save sample rate\n");
    query("SARA?", reply, reply_size);
    char cur_sample_rate[256];
    strcpy(cur_sample_rate, reply);

    printf("Save time division\n");
    query("TDIV?", reply, reply_size);
    char cur_tdiv[256];
    strcpy(cur_tdiv, reply);

    printf("Save memory size\n");
    query("MSIZ?", reply, reply_size);
    char cur_mem_size[256];
    strcpy(cur_mem_size, reply);

    printf("============================================================\n");
    check_vdiv_bug();
    check_vdiv_bug();

    printf("============================================================\n");
    check_wavedesc_length_bug();

    printf("============================================================\n");
    capture_wf();

    // Restore changed parameters
    printf("============================================================\n");
    printf("Restore probe attenuation\n");
    sprintf(cmd, "C1:ATTN %s", cur_attn);
    send(cmd);
    query("C1:ATTN?", reply, reply_size);

    // Disconnect
    lxi_disconnect(device);
}
