line = "a b cde\t fg hij\n kl m no zy\nkl m nr"
l2 = line.split()
max = max(l2, key=len)
lenmax = len(max)
print(max)
print(lenmax)