
IP_ADDR = 192.168.1.177

id:
	./vxi11_ident.py $(IP_ADDR)

view:
	./screenshot.py -o screenshot.png $(IP_ADDR)
	eog screenshot.png
