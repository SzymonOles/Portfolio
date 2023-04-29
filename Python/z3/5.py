x = 10
line = "|"
numbers = "0"
for i in range (1,x):
    line+= "....|"
    for x in range(5 - len(str(i))):
        numbers+= " "
    numbers+=str(i)
wynik = line+"\n"+numbers
print(wynik)