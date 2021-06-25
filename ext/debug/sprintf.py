var,types=[],[]
with open('sprintf.txt','r') as f:
	for line in f:
		a,b=line.split()
		var.append(a);types.append(b)
# print(var,types)
s='sprintf(info,"'
myDict={
	'int':'d',
	'double':'.1f'
}
for i in range(len(var)):
	s+='%s=%%%s;'%(var[i],myDict[types[i]])
s+='"'
for i in var:
	s+=','+i
s+=');'
open('sprintfO.txt','w').write(s+'\n\treturn info;')