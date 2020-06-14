
HASH=`git rev-parse --short HEAD` 
gcc -DHASH=\"$HASH\" -o lxi_siglent_check lxi_siglent_check.c -llxi



