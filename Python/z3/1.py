# nie uzywa sie ; tylko nowej linii
x = 2; y = 3;
if (x > y):
    result = x;
else:
    result = y;
    
# w instrukcjach zaawansowanych nie mozna pomijac wciecia
for i in "axby": if ord(i) < 100: print (i)

# ok
for i in "axby": print (ord(i) if ord(i) < 100 else i)
