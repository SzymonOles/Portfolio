word = "test"
w2 = ""
for char in word:
    w2+= char + "_"
w2 = w2[0:len(w2)-1]
print(w2)