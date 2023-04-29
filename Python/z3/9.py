a= [[],[4],(1,2),[3,4],(5,6,7)]
b=[]
temp=0
for i in a:
    temp=0
    for x in i:
        temp+=x
    b.append(temp)
print(b)