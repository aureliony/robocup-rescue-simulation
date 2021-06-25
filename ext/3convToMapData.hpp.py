from PIL import Image

pix1=Image.open('2greenMapEdited.bmp').load()
pix2=Image.open('2greenMapEditedNoTrap.bmp').load()
from _InputData import * #get width and height

def isGreen(r,g,b):
	R,G,B=0,255,0
	return r==R and g==G and b==B
def isWhite(r,g,b):
	R,G,B=255,255,255
	return r==R and g==G and b==B
def isGrey(r,g,b):
	R,G,B=127,127,127
	return r==R and g==G and b==B
def isDarkGrey(r,g,b):
	R,G,B=80,80,80
	return r==R and g==G and b==B
def isBlack(r,g,b):
	R,G,B=0,0,0
	return r==R and g==G and b==B

def checkPix(r,g,b):
	if isGreen(r,g,b):
		return 0
	if isWhite(r,g,b):
		return 1
	if isGrey(r,g,b):
		return 2
	if isDarkGrey(r,g,b):
		return 3
	if isBlack(r,g,b):
		return 4
	raise Exception('checkPix FAILED!')
def con(x,y):
	return y*WIDTH+x

w2mapWithTrap=[]
for y in range(HEIGHT):
	for x in range(WIDTH):
		w2mapWithTrap.append(checkPix(pix1[x,y][0],pix1[x,y][1],pix1[x,y][2]))

w2mapNoTrap=[]
for y in range(HEIGHT):
	for x in range(WIDTH):
		w2mapNoTrap.append(checkPix(pix2[x,y][0],pix2[x,y][1],pix2[x,y][2]))

with open('mapData.hpp','w') as f:
	f.write('#pragma once\n\n')
	f.write('static uint8_t* w2map=NULL;\n\n')
	f.write('static uint8_t w2mapWithTrap[]={'+str(w2mapWithTrap).lstrip('[').rstrip(']')+'};\n\n')
	f.write('static uint8_t w2mapNoTrap[]={'+str(w2mapNoTrap).lstrip('[').rstrip(']')+'};\n\n')