from django.shortcuts import render_to_response
from django.core.context_processors import csrf
from django.http import HttpResponseRedirect
import serial

def index(request):
	return render_to_response('home.html')

def post(request,post_id=1):
	print 'entered function'
	d = str(post_id) + '\n'
	print 'some = ', d
	ser = serial.Serial('/dev/ttyACM1')
	print ser
	print 'port opened'
	ser.write(d)
	print 'data written'
	return HttpResponseRedirect('/')


