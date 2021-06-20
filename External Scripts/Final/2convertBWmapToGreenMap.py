from sys import exit
from tkinter.filedialog import askopenfilename
from PIL import Image
# im=Image.open(askopenfilename(initialdir="C:\\Users\\Aureliony\\Desktop\\Cospace py progs",
	# title='LOAD BMP')).transpose(Image.FLIP_TOP_BOTTOM)
im=Image.open('1mapFlipped.bmp') #do not transpose

RADIUS = 16

from _InputData import * #get width and height
pix=im.load()
r,g,b=[],[],[]

for y in range(HEIGHT):
	for x in range(WIDTH):
		tup=pix[x,y]
		r.append(tup[0])
		g.append(tup[1])
		b.append(tup[2])

RGBoff=0

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
def convX(d):
	return int((d%WIDTH))*int(360/WIDTH)
def convY(d):
	return int((d/WIDTH))*int(270/HEIGHT)
def convPosToNode(fromX, fromY, toIndex):
	if toIndex == 1: return (fromX-1, fromY-1)
	elif toIndex == 2: return (fromX, fromY-1)
	elif toIndex == 3: return (fromX+1, fromY-1)
	elif toIndex == 4: return (fromX-1, fromY)
	elif toIndex == 5: return (fromX+1, fromY)
	elif toIndex == 6: return (fromX-1, fromY+1)
	elif toIndex == 7: return (fromX, fromY+1)
	elif toIndex == 8: return (fromX+1, fromY+1)
	print("toIndex =", toIndex)
	raise Exception("convPosToNode ERROR")

visited = set()

def detectShape(startX,startY,colorTup):
	global visited
	openList = [(startX, startY)]
	finalSet = {(startX, startY)}
	while len(openList)!=0:
		currX, currY = openList.pop()
		for i in range(1, 8+1):
			newX, newY = convPosToNode(currX, currY, i)
			if (newX, newY) in finalSet or newX<0 or newX>WIDTH-1 or newY<0 or newY>HEIGHT-1:
				continue
			if pix[newX, newY]==colorTup:
				finalSet.add((newX, newY))
				openList.append((newX, newY))
				visited.add((newX, newY))
	return finalSet

def getOutline(startX,startY,colorTup):
	global pix
	shape = sorted(list(detectShape(startX,startY,colorTup)), key = lambda x:(x[1],x[0]))
	outline = []
	for currX,currY in shape:
		isOnEdge=False
		for i in range(1, 8+1):
			newX, newY = convPosToNode(currX, currY, i)
			if newX<0 or newX>WIDTH-1 or newY<0 or newY>HEIGHT-1 or pix[newX,newY]!=colorTup:
				isOnEdge=True
				break
		if isOnEdge:
			outline.append((currX,currY))

	# img = Image.new('RGB', (WIDTH,HEIGHT), (255,255,255)) #create new white image
	# imgPix = img.load()
	# for tup in outline:
	# 	imgPix[tup[0], tup[1]] = (255,0,0)
	# img.save('test.bmp')
	# exit(0)
	return outline

types=[]
for i in range(VERTICES):
	types.append(checkPix(r[i],g[i],b[i]))
# print(types)

for y in range(HEIGHT):
	for x in range(WIDTH):
		if types[con(x, y)]>1 and (x,y) not in visited: #grey or black
			curroutline = getOutline(x,y,pix[x,y])
			for currX,currY in curroutline:
				for newX in range(currX-int(RADIUS/(360/WIDTH)), currX+int(RADIUS/(360/WIDTH)+1)):
					for newY in range(currY-int(RADIUS/(360/WIDTH)), currY+int(RADIUS/(360/WIDTH)+1)):
						if 0<=newX<WIDTH and 0<=newY<HEIGHT and types[con(newX,newY)]<=1:
							if (currX - newX)**2 + (currY - newY)**2 < (14.414/(360/WIDTH))**2:
								pix[newX,newY] = (255,255,255)
								types[con(newX,newY)] = 1 #white cost

for y in range(HEIGHT):
	for x in range(WIDTH):
		if convX(con(x,y))<4 or convX(con(x,y))>355 or convY(con(x,y))<4 or convY(con(x,y))>265 :
			pix[x,y] = (127,127,127)

im.save('2greenMap.bmp')