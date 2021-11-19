#begin
# import the necessary packages
from vosk import Model, KaldiRecognizer
import pyaudio
import os
import subprocess
from picamera.array import PiRGBArray
from picamera import PiCamera
from multiprocessing import *
import numpy as np
import imutils
import serial
import time
import cv2
import pygame
byte_begin = 254
default_command = 50
scr_size = 500


UI = True
# 1 - SEARCH, 2 - STOP, 3 - MOVE, 4 - LISTEN

tXCenter = 0
tYCenter = 0


def convert(x, min1, max1, min2, max2):
    x1 = int((x*(max2-min2)+max1*min2-max2*min1)/(max1 - min1))
    return x1
def start_stream():
    p = pyaudio.PyAudio()
    global stream
    stream = p.open(format=pyaudio.paInt16, channels=1, rate=16000, input=True, frames_per_buffer=8000)

def model_init(model_path):
    model = Model(model_path)
    global rec
    rec = KaldiRecognizer(model, 16000)
    
def commands_init():
    global commands
    commands = {'gymnastic' : 7,
                'exercise' : 7,
                'acrobatic' : 7,
                'athletics' : 7,
                'sport' : 7,
                
                'square' : 1,
                
                'fly' : 2,
                'flight' : 2,
                
                'dance' : 3,
                'dancing' : 3,
                'dense' : 3,
                'disco' : 3,
                
 
                'sing' : 4,
                'seen' : 4,
                'sin' : 4,
                'melody' : 4,
                'song' : 4,
                'vocal' : 4,
                'music' : 4,
 
                'peg-top' : 5,
                'spinning top' : 5,
                'spinning' : 5,
                'pinwheel' : 5,
                'top toy' : 5,
                
                'scar' : 6,
                'frighten' : 6}


def find_command(word, commands):
    for comm in commands:
        if comm in word:
            return commands[comm]
        
    return default_command
def play_sound():
    songs = [0, r'/home/pi/Documents/sound/0002square.mp3', r'/home/pi/Documents/sound/0003fly.mp3', r'/home/pi/Documents/sound/0004dance.mp3', r'/home/pi/Documents/sound/123.mp3', r'/home/pi/Documents/sound/0006yula.mp3', r'/home/pi/Documents/sound/0007_scary.mp3',r'/home/pi/Documents/sound/0001givefive.mp3']
    if command.value != default_command:
        if True:
            time.sleep(0.75)
        pygame.mixer.music.load(songs[command.value])
        pygame.mixer.music.play()
    '''while pygame.mixer.music.get_busy() == True:
        continue'''
        
def processing_the_result(res):
    start_index = res.rfind(':')
    res = res[start_index + 2 : -2].replace('"', '')
    return res



class ShapeDetector:
	def __init__(self):
		pass
	# shape:
	# 0 unidentified
	# 1 circle
	# 3 triangle
	# 4 square
	# 5 line
	def detect(self, c):
		# initialize the shape name and approximate the contour
		shape = 0
		peri = cv2.arcLength(c, True)
		approx = cv2.approxPolyDP(c, 0.038 * peri, True)
		#print("approx =", len(approx))
		if (len(approx) == 0)or(len(approx) == 1)or(len(approx) == 2):
			shape = 1
		if len(approx) == 3:
			shape = 3
		
		# if the shape has 4 vertices, it is either a square or
		# a rectangle
		elif len(approx) == 4:
			# compute the bounding box of the contour and use the
			# bounding box to compute the aspect ratio
			(x, y, w, h) = cv2.boundingRect(approx)
			ar1 = w / float(h)
			ar2 = float(h) / w
			if(0.6 < ar1 < 1.8)and (0.6 < ar2 < 1.8):
				shape = 4
			elif(ar1 > 3.0)or (ar2>3.0):
				shape = 5  
		else:
			shape = 1
		# return the name of the shape
		return shape
	
	def getCoords(self, c):
		M = cv2.moments(c)
		sumX = M['m10']
		sumY = M['m01']
		count = M['m00']
		peri = cv2.arcLength(c, True)
		approx = cv2.approxPolyDP(c, 0.038 * peri, True)
		(x, y, side1, h) = cv2.boundingRect(approx)
		if count > 0:
			cX = int(sumX / count)
			cY = int(sumY / count)
			return (cX, cY, count, side1)
		else:
			return(0, 0, 0, 0)



def getArduinoPort():
  usbList = os.listdir('/dev')
  for p in usbList:
    if 'ttyUSB' in p or 'ttyACM' in p:
      return '/dev/' + p
  return 'none'

def doit():
  while True:
    
    port = getArduinoPort()
    if 'none' in port:
      print('Arduino not connected')
    else:
      print('Arduino connected to %s' % port)
      arduino = serial.Serial(port, 115200, timeout=.1)
      time.sleep(2)
      canSendToArduino = True
      while canSendToArduino:
        try:                   
          arduino = serial.Serial(port, 115200, timeout=.1)
          
          if side.value > 240:
              side.value = 240
          elif side.value < 0:
              side.value = 0
          arduino.write([byte_begin,mode.value, command.value, xCenter.value,yCenter.value,side.value])#serial.to_bytes(
          
          print(mode.value, command.value, xCenter.value, yCenter.value, side.value)
          time.sleep(0.05)
        except serial.SerialException:
          print('Connection was lost')
          port = getArduinoPort()
          
          

def voice():
    model_path = r'/home/pi/Documents/microfon/vosk-model-small-en-us-zamia-0.5'
    song = r'/home/pi/Documents/sound/123.mp3'
    start_stream()
    model_init(model_path)
    commands_init()
    pygame.mixer.init()
    while True:
        
        if (canListen.value):
            stream.start_stream()
            #print("listening")
            command.value = default_command
            data = stream.read(1000, exception_on_overflow = False)
            #print("data:", data)

            if len(data) == 0:
                break
            if rec.AcceptWaveform(data):
                res = rec.Result()
                res = processing_the_result(res)
                print(res)
                stream.stop_stream()
                command.value = find_command(res, commands)
                play_sound()
                if command.value != default_command:
                    canListen.value = False
    
def main_proc():
    
    time.sleep(1)
    # initialize the camera and grab a reference to the raw camera capture
    camera = PiCamera()
    camera.meter_mode = 'average'
    camera.awb_mode = 'auto'
    #camera.brightness = 40
    camera.color_effects = None
    #camera.contrast = 25
    #camera.exposure_compensation = 10
    camera.image_effect = 'denoise'
    camera.video_stabilization = True
    camera.resolution = (500, 500)# 640 480
    camera.framerate = 32
    rawCapture = PiRGBArray(camera, size=(scr_size, scr_size))# 640 480
    # allow the camera to warmup
    time.sleep(2.5) #0.1
    # capture frames from the camera

    if UI:
        cv2.namedWindow('image') # Main image
        cv2.namedWindow('color_filter') # Changed image
    

    sd = ShapeDetector()
    detectTriangles = False
    bufferedTriangles = []
    
    bufferedRectangles = []
    bufferedLines = []

    for frame in camera.capture_continuous(rawCapture, format='bgr', use_video_port=True):
        # grab the raw NumPy array representing the image, then initialize the timestamp
        # and occupied/unoccupied text
        #time.sleep(0.01)
        image = frame.array
        # show the frame
        # cv2.imshow('Frame', image)

        black = np.zeros((scr_size, scr_size, 3), np.uint8)
        
        hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
        h1 = 0
        s1 = 0
        v1 = 0
        h2 = 255
        s2 = 255
        v2 = 60
        h_min = np.array((h1, s1, v1), np.uint8)
        h_max = np.array((h2, s2, v2), np.uint8)
        color_filter = cv2.inRange(hsv, h_min, h_max)

        blurred = cv2.GaussianBlur(color_filter, (5,5), 0)
        thresh = cv2. threshold(blurred, 60, 255, cv2.THRESH_BINARY)[1]
        
        # find contours in the thresholded image and initialize the
        # shape detector
        cnts = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL,
            cv2.CHAIN_APPROX_SIMPLE)
        cnts = imutils.grab_contours(cnts)
        
        # if marker not detected, we need to find triangles firstly
        
        rectangles = []
        lines = []
        if not detectTriangles:
            triangles = []
            for c in cnts:
                M = cv2.moments(c)
                sumX = M['m10']
                sumY = M['m01']
                count = M['m00']
                
                if count > 1000 and count <25000:
                    shape = sd.detect(c)
                    
                    if shape == 3:
                        triangles.append(c)
                    elif shape == 4:
                        rectangles.append(c)
                    elif shape == 5:
                        lines.append(c)
            if len(triangles) == 3:
                count = 0
                (t1X, t1Y, count, s) = sd.getCoords(triangles[0])
                (t2X, t2Y, count, s) = sd.getCoords(triangles[1])
                (t3X, t3Y, count, s) = sd.getCoords(triangles[2])
                
                tXCenter = int((t1X + t2X + t3X) / 3)
                tYCenter = int((t1Y + t2Y + t3Y) / 3)
                
                if UI:
                    cv2.putText(image, '%d' % len(triangles), (tXCenter, tYCenter),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 2)
                    
                
            
                detectLine = False
                detectRectangle = False
                
                if len(lines) > 0:
                    for c in lines:
                        (cX, cY, count, s) = sd.getCoords(c)
                        if abs(cX - tXCenter) < 40 and abs(cY - tYCenter) < 40:
                            bufferedLines.append(c)
                            if UI:
                                c = c.astype('int')
                                cv2.drawContours(black, [c], -1, (255, 255, 255), 2)
                                cv2.putText(image, '%s' % 'LISTEN', (cX, cY),
                                    cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 2)
                            mode.value = 4 # LISTEN
                            detectLine = True
                            canListen.value = True
                            break
                
                elif len(rectangles) > 0:
                    for c in rectangles:
                        (cX, cY, count, s) = sd.getCoords(c)
                        if abs(cX - tXCenter) < 40 and abs(cY - tYCenter) < 40:
                            bufferedRectangles.append(c)
                            if UI:
                                c = c.astype('int')
                                cv2.drawContours(black, [c], -1, (255, 0, 0), 2)
                                cv2.putText(image, '%s' % 'MOVE', (cX, cY),
                                    cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 2)
                            mode.value = 3 # MOVE
                            detectRectangle = True
                            command.value = default_command
                            break
                
                
                if (detectRectangle) or detectLine:
                    for c in triangles:
                        bufferedTriangles.append(c)
                        (cX, cY, count, s) = sd.getCoords(c)
                        if UI:
                            c = c.astype('int')
                            cv2.drawContours(black, [c], -1, (0, 255, 0), 2)
                            cv2.putText(image, '%d' % count, (cX, cY),
                                cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 2)
                    detectTriangles = True
        if detectTriangles:
            minRadius = 300
            bufferedRectangles = []
            bufferedTriangles = []
            bufferedLines = []

            if mode.value == 3:
                for c in cnts:
                    M = cv2.moments(c)
                    count = M['m00']
                    #print("count = ", count)
                    if count > 1000 and count < 30000:
                        shape = sd.detect(c)
                        if shape == 4:
                            (cX, cY, count, s) = sd.getCoords(c)
                            if (cX - xCenter.value)**2 + (cY - yCenter.value)**2 < minRadius**2:
                                    bufferedRectangles.append(c)
                                    break                                
                if len(bufferedRectangles) > 0:
                    movingRectangle = bufferedRectangles[0]
                    (cX, cY, count, s) = sd.getCoords(movingRectangle)
                    movingRectangle = movingRectangle.astype('int')
                    xCenter.value = convert(cX, 0, scr_size, 0, 240)
                    yCenter.value = convert(cY, 0, scr_size, 0, 240)
                    side.value = convert(s, 0, scr_size, 0, 240)
                    

                    if UI:
                        cv2.drawContours(black, [movingRectangle], -1, (255, 0, 0), 2)
                else:
                    detectTriangles = False
                    mode.value = 1
            elif mode.value == 4:
                for c in cnts:
                    M = cv2.moments(c)
                    count = M['m00']
                    if count > 1000 and count < 30000:
                        shape = sd.detect(c)
                        if shape == 5:
                            (cX, cY, count, s) = sd.getCoords(c)
                            if (cX - xCenter.value)**2 + (cY - yCenter.value)**2 < minRadius**2:
                                    bufferedLines.append(c)
                                    break                                
                if len(bufferedLines) > 0:
                    movingLine = bufferedLines[0]
                    (cX, cY, count, s) = sd.getCoords(movingLine)
                    movingLine= movingLine.astype('int')
                    xCenter.value = convert(cX, 0, scr_size, 0, 240)
                    yCenter.value = convert(cY, 0, scr_size, 0, 240)
                    side.value = convert(s, 0, scr_size, 0, 240)
                    
                    if UI:
                        cv2.drawContours(black, [movingLine], -1, (255, 0, 0), 2)
                else:
                    detectTriangles = False
                    mode.value = 1
                    lines = []
                
        if UI:
            cv2.putText(black, '%d' % mode.value, (20, 20),
                cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 2)
            cv2.imshow('color_filter', black)
            cv2.imshow('image', image)
        
        key = cv2.waitKey(1) & 0xFF
        # clear the stream in prepatation for the next frame
        rawCapture.truncate(0)
        # if the 'q' key was pressed, break from the loop
        if key == ord('q'):
            break
 
if __name__=='__main__':
    mode = Value('i', 1)
    xCenter = Value('i', 0)
    yCenter = Value('i', 0)
    side = Value('i', 0)
    command = Value('i', default_command)
    canListen = Value('b', False)

    arduino = Process(target=doit)
    arduino.start()
    
    voice_proc = Process(target=voice)
    voice_proc.start()
    
    camera = Process(target=main_proc)
    camera.start()





                      
   








