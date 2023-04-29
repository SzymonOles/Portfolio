line = "a b cde\t fg hij\nkl m no zy\nkl m nr"
l2 = line.splitlines()
first = ""
last = ""
for word in l2:
    first += word[0]
    last += word[len(word)-1]
print(first)
print(last)