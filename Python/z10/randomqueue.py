import random

class RandomQueue:

    def __init__(self):
        self.items = []

    def insert(self, item):   # wstawia element w czasie O(1)
        self.items.append(item)

    def remove(self):    # zwraca losowy element w czasie O(1)
        n = random.randint(0,len(self.items)-1)
        item = self.items[n]
        self.items[n] = self.items[-1]
        self.items.pop()
        return item

    def is_empty(self): 
        return not self.items

    def is_full(self): 
        return False

    def clear(self):    # czyszczenie listy
        self.items.clear()

rq = RandomQueue()
for i in range(10):
    rq.insert(i)

for i in range(10):
    print(rq.remove())
