import os
from datetime import datetime
import serial
import time
import serial.tools.list_ports
def appi(port):
	print("connected")
	ser=serial.Serial(port,9600)
	if(ser.isOpen() == False):
	    ser.open()
	startOfData=False
	data=[]
	print("Please scan Master card")
	while (ser.isOpen()):
		try:
			b = ser.readline()         # read a byte string
		except:
			print("Something went wrong, please reconnect PillPal")
			return
		string_n = b.decode()  # decode byte string into Unicode  
		string = string_n.rstrip() # remove \n and \r
		if startOfData:
			if string=="End": break
			data.append(string.split("\t"))
		if ("Summary" in string):
			startOfData=True
		time.sleep(0.1)
	print("Data received: ")
	ser.close()
	now=datetime.now()
	filename=os.path.join(os.getcwd(),"logs" ,"log at " + str(now.strftime("%H:%M"))+".csv")
	with open(filename,"a+") as f:
		f.write("\n".join(",".join(i) for i in data))
		print("log saved to: ", filename)
	print("Thank you!")
	exit()
		
while True:
	myports = [tuple(p) for p in list(serial.tools.list_ports.comports())]
	for i in myports:
		if i[1]=="USB Serial":
			appi(i[0])
			break
	print("cannot try again in 5 seconed")
	print(myports)
	time.sleep(5)

