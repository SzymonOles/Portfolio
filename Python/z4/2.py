def make_ruler(n):
    line = "|"
    numbers = "0"
    for i in range (1,n+1):
        line+= "....|"
        for z in range(5 - len(str(i))):
            numbers+= " "
        numbers+=str(i)
    wynik = line+"\n"+numbers
    return wynik

def make_grid(rows, cols):
    string = ""
    for i in range(rows):
        for j in range(cols):
            string+= "+---"
        string+="+\n"
        for j in range(cols):
            string+="|   "
        string+="|\n"

    for j in range(cols):
        string+= "+---"
    string+="+\n"
    return string

print(make_ruler(10))
print(make_grid(3,2))