from PIL import Image
im=Image.open('2greenMapEdited.bmp')
pix=im.load()

xCoords=[];yCoords=[]
with open('path.txt','r') as f:
	for line in f:
		if line[0]!='(': break
		x,y=map(int,line.rstrip()[1:-1].split(','))
		xCoords.append(x)
		yCoords.append(y)

for i in range(len(xCoords)):
	pix[xCoords[i],yCoords[i]]=(255,0,0)

im.save('path.bmp')