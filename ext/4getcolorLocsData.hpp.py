from PIL import Image
from _InputData import * #get width and height

numToColor = ['r','g','b','rg','rb','gb','rgb']
numLocs = [0 for i in range(7)]
tups = [() for i in range(7)]
numLocs[0] = 2; tups[0] = (255,0,0)
numLocs[1] = 2; tups[1] = (0,255,0)
numLocs[2] = 4; tups[2] = (0,0,0)
numLocs[3] = 0; tups[3] = (127,127,0)
numLocs[4] = 0; tups[4] = (127,0,0)
numLocs[5] = 0; tups[5] = (0,127,0)
numLocs[6] = 0; tups[6] = (85,85,0)

locs = [[] for i in range(7)]

im = Image.open('4colorLocs.bmp').transpose(Image.FLIP_TOP_BOTTOM)
im = im.resize((WIDTH, HEIGHT))
pix = im.load()

#create bmp of all locations
for y in range(HEIGHT):
	for x in range(WIDTH):
		if pix[x,y] not in tups:
			pix[x,y] = (255,255,255) #white

im.save('5colorLocsFlipped.bmp')
del im

def conv(x,y):
	return y*WIDTH+x

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

def detectShape(startX,startY,colorTup):
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
	return finalSet

def isInListOfSets(lst, item):
	for i in range(len(lst)):
		if item in lst[i]:
			return True
	return False

for col in range(7):
	for locnum in range(numLocs[col]):
		for y in range(HEIGHT):
			for x in range(WIDTH):
				if pix[x,y]==tups[col] and not isInListOfSets(locs[col], (x,y)):
					currLoc = (x,y)
					break
			else: continue
			break
		print('{}Loc{} = {}'.format(numToColor[col], locnum, currLoc))
		newShape = detectShape(currLoc[0], currLoc[1], tups[col])
		img = Image.new('RGB', (WIDTH,HEIGHT), (255,255,255)) #create new white image
		imgPix = img.load()
		for tup in newShape:
			imgPix[tup[0], tup[1]] = tups[col]
		img.save("6{}Loc{}.bmp".format(numToColor[col], locnum))
		locs[col].append(newShape)


def lstToCppArr(lst):
	lst = [sorted(list(x), key = lambda x:(x[1],x[0])) for x in lst]
	for i in range(len(lst)):
		for j in range(len(lst[i])):
			lst[i][j] = conv(lst[i][j][0], lst[i][j][1])
		# lst[i] = str(lst[i]).replace('[','{').replace(']','}')
	# lst = str(lst).replace('[','{').replace(']','}')
	return lst

for i in range(7):
	locs[i] = lstToCppArr(locs[i])

f = open('colorLocsData.hpp','w')
f.write('#pragma once\n\n')
for i in range(7):
	if numLocs[i]>0:
		for j in range(numLocs[i]):
			f.write('static const uint32_t {}Loc{}[] = {};\n\n\n\n\n'.format(numToColor[i], j, str(locs[i][j]).replace('[','{').replace(']','}') ))
f.close()