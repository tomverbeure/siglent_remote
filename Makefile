
IP_ADDR = 192.168.1.176

view:
	./screenshot.py -o screenshot.png $(IP_ADDR)
	eog screenshot.png
