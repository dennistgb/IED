import serial
import time
import serial.tools.list_ports
def appi(port):
	print("connected")
	ser=serial.Serial(port,9600)
	ser.open()
	startOfData=False
	data=[]
	while (ser.isOpen()):
		b = ser.readline()         # read a byte string
		string_n = b.decode()  # decode byte string into Unicode  
		string = string_n.rstrip() # remove \n and \r
		if startOfData:
			if string=="end": break
			data.append(string.split(" "))
		if ("Summery" in string):
			startOfData=True

		time.sleep(0.1)
	ser.close()
while True:
	myports = [tuple(p) for p in list(serial.tools.list_ports.comports())]
	for i in myports:
		if i[1]=="USB Serial":
			appi(i[0])
	print("cannot try again in 5 seconed")
	time.sleep(5)

