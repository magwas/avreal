#!/usr/bin/python
import os
import select

class Counters(object):
	counters = {
		'storetokenandreturn' : 4,
		'handledata' :5,
		'overflow' : 6,
		'ignorepacket' : 7,
		'sendnakandreti' : 8,
		'handlein' : 9,
		'handlein1' : 10,
		'handlein3' : 11,
		'se0' : 12,
		'soferror': 13
	}
	def __init__(self,instring):
		#instring is with the heading 'd'
		self.instring = instring
		self.values = {}
		for (k,v) in self.counters.items():
			n = int(instring[1+(v-4)*2:3+(v-4)*2],16)
			self.values[k]=n

	def __repr__(self):
		restr=""
		for k in self.counters:
			restr += "%s = 0x%02x (%u)\n"%(k,self.values[k],self.values[k])
		sum = self.handledata + self.ignorepacket + self.handlein + self.storetokenandreturn
		restr += "0x%02x ?= 0x%02x diff = 0x%02x \n"%(self.values['se0'], sum, self.se0-sum)
		# se0 = handledata + ignorepacket + handlein +  storetokenandreturn
		restr += "lag = 0x%02x\n"%(self.se0-self.handlein1)
		return restr

	def __getattr__(self,attname):
		return self.values[attname]


def nreadline(f):
	
	try:
		signal.alarm(1);line = self.readline()
	except IOError:
		line = ""
	return line

def nread(self):
	try:
		signal.alarm(1);line = self.read()
	except IOError:
		line = ""
	return line

f=open("/var/lock/LCK..ttyAMA0","w")
f.write(str(os.getpid()))
f.close()

if __name__ == '__main__':
	serial=open("/dev/ttyAMA0","w+b")
	usb=open("/dev/ttyACM0","w+b")
	
	print "usb:",nread(usb)
	print "serial:",nread(serial)
	
	serial.write("d")
	line = serial.readline()
	print line
	print Counters(line)
	
	
	serial.write("d")
	line = serial.readline()
	print line
	print Counters(line)
	
