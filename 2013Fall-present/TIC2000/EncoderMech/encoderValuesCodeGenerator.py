values = [-1]*255#make initial empty list
with open('encoderValues.txt','r') as valuesFile:
    index = 0
    for line in valuesFile:
        values[int(line.split(' ')[-1])] = index
        index+=1
print 'int conversionArray[254] = {'
for index in range(255):
    if (index+1)%20==0:
        print '\n',
    if index<254:
        print str(values[index])+',',
    else:
        print str(values[index])+'};'



