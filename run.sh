
lxi scpi -a 192.168.1.177 "*RST"
lxi scpi -a 192.168.1.177 "CHDR LONG"
lxi scpi -a 192.168.1.177 "*IDN?"
lxi scpi -a 192.168.1.177 "C2: CPL?"
lxi scpi -a 192.168.1.177 "CHDR SHORT"
lxi scpi -a 192.168.1.177 "*IDN?"
lxi scpi -a 192.168.1.177 "C2: CPL?"
lxi scpi -a 192.168.1.177 "CHDR OFF"
lxi scpi -a 192.168.1.177 "*IDN?"
lxi scpi -a 192.168.1.177 "C2: CPL?"

# What is Siglent hiding in here?
lxi scpi -a 192.168.1.177 "c1:wf? desc" > desc.bin
lxi scpi -a 192.168.1.177 "c1:wf? dat2" > c0_data.bin

