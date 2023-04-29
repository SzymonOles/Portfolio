line = "a b cde\t fg hij\n kl m no zy\nkl m nr"
l2 = line.split()
sum=0
for word in l2:
    sum += len(word)
print(sum)