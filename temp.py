f=open("output.txt", "r")
if f.mode == 'r':
	contents =f.read()
contentArray=contents.split('\n')
contentArray.pop()
mu =[] 
for i in contentArray:
	mu.append(i.split(','))
print(mu)