# from tkinter.filedialog import askopenfilename
from PIL import Image
# im=Image.open(askopenfilename(initialdir="C:\\Users\\Aureliony\\Desktop\\Cospace py progs",
	# title='LOAD BMP')).transpose(Image.FLIP_TOP_BOTTOM)
im=Image.open('2greenMapEdited.bmp')
pix=im.load()
RED = (255,0,0)

xCoords=[];yCoords=[]
with open('path.txt','r') as f:
	for line in f:
		if line[0]!='(': break
		x,y=map(int,line.rstrip()[1:-1].split(','))
		xCoords.append(x)
		yCoords.append(y)
cnt=0
print(len(xCoords))
for i in range(len(xCoords)):
	if cnt==100:
		im.show()
		cnt=0
	pix[xCoords[i],yCoords[i]]=RED
	cnt+=1