from PIL import Image
im=Image.open('0map.bmp').transpose(Image.FLIP_TOP_BOTTOM)

from _InputData import * #get width and height
im=im.resize((WIDTH,HEIGHT))
pix=im.load()
r,g,b=[],[],[]

for y in range(HEIGHT):
	for x in range(WIDTH):
		tup=pix[x,y]
		r.append(tup[0])
		g.append(tup[1])
		b.append(tup[2])

# im.save('maap.bmp')  # Save the modified pixels as .png

RGBoff=45

def inRange(subject,lower,upper):
    return lower<=subject and subject<=upper
def isYellow(r,g,b):
	R,G,B = 255,255,0
	return inRange(r,R-RGBoff,R+RGBoff) and inRange(g,G-RGBoff,G+RGBoff) and inRange(b,B-RGBoff,B+RGBoff)
def isTrap(r,g,b):
	R,G,B = 192,0,0
	R1,G1,B1 = 153,102,255
	return  (inRange(r,R-RGBoff,R+RGBoff) and inRange(g,G-RGBoff,G+RGBoff) and inRange(b,B-RGBoff,B+RGBoff)) or (inRange(r,R1-RGBoff,R1+RGBoff) and inRange(g,G1-RGBoff,G1+RGBoff) and inRange(b,B1-RGBoff,B1+RGBoff))
def isWall(r,g,b):
	R,G,B = 0,0,0
	return inRange(r,R-RGBoff,R+RGBoff) and inRange(g,G-RGBoff,G+RGBoff) and inRange(b,B-RGBoff,B+RGBoff)
def isSwamp(r,g,b):
	R,G,B = 127,127,127
	return inRange(r,R-RGBoff,R+RGBoff) and inRange(g,G-RGBoff,G+RGBoff) and inRange(b,B-RGBoff,B+RGBoff)
def checkPix(r,g,b):
	if isWall(r,g,b):
		return 3
	if isYellow(r,g,b) or isTrap(r,g,b):
		return 2
	if isSwamp(r,g,b):
		return 1
	return 0
def con(x,y):
	return y*WIDTH+x

types=[]
for i in range(VERTICES):
	types.append(checkPix(r[i],g[i],b[i]))
# print(types)

for y in range(HEIGHT):
	for x in range(WIDTH):
		if types[con(x,y)]==0:
			pix[x,y]=(0,255,0)
		elif types[con(x,y)]==1:
			pix[x,y]=(127,127,127)
		elif types[con(x,y)]==2:
			pix[x,y]=(80,80,80)
		elif types[con(x,y)]==3:
			pix[x,y]=(0,0,0)
im.save('1mapFlipped.bmp')