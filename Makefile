
IP_ADDR = 192.168.1.177

view:
	./screenshot.py -o screenshot.png $(IP_ADDR)
	eog screenshot.png
