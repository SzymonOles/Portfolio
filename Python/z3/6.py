y = 3
x = 2
string = ""
for i in range(y):
    for j in range(x):
        string+= "+---"
    string+="+\n"
    for j in range(x):
        string+="|   "
    string+="|\n"

for j in range(x):
    string+= "+---"
string+="+\n"

print(string)