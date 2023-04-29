import itertools
import random

a = itertools.cycle((0,1))
b = iter(lambda: random.choice(("N","S","E","W")), -1)
c = itertools.cycle(range(0, 7))

for i in range(10):
    print(next(a))

print("===================")

for i in range(10):
    print(next(b))

print("===================")

for i in range(10):
    print(next(c))