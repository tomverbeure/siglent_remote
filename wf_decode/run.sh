
gcc -g -O0 -o wf_decode wf_decode.c
lxi scpi -a 192.168.1.177 "c1:wf? dat2" > c0_data.bin
./wf_decode c0_data.bin
