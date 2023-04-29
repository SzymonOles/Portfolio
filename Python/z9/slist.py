# -*- coding: utf-8 -*-


class Node:
    def __init__(self, data=None, next=None):
        self.data = data
        self.next = next

    def __str__(self):
        return str(self.data)  # bardzo ogólnie


class SingleList:
    def __init__(self):
        self.length = 0  # nie trzeba obliczać za każdym razem
        self.head = None
        self.tail = None

    def is_empty(self):
        # return self.length == 0
        return self.head is None

    def count(self):  # tworzymy interfejs do odczytu
        return self.length

    def insert_head(self, node):
        if self.head:  # dajemy na koniec listy
            node.next = self.head
            self.head = node
        else:  # pusta lista
            self.head = self.tail = node
        self.length += 1

    def insert_tail(self, node):  # klasy O(1)
        if self.head:  # dajemy na koniec listy
            self.tail.next = node
            self.tail = node
        else:  # pusta lista
            self.head = self.tail = node
        self.length += 1

    def remove_head(self):  # klasy O(1)
        if self.is_empty():
            raise ValueError("pusta lista")
        node = self.head
        if self.head == self.tail:  # self.length == 1
            self.head = self.tail = None
        else:
            self.head = self.head.next
        node.next = None  # czyszczenie łącza
        self.length -= 1
        return node  # zwracamy usuwany node

    def remove_tail(self):  # klasy O(n)
        if self.is_empty():
            raise ValueError("pusta lista")

        oldtail = self.tail
        if self.head == self.tail:
            self.head = self.tail = None
        else:
            newtail = self.head
            while newtail.next != self.tail:
                newtail = newtail.next
            newtail.next = None
            self.tail = newtail

        self.length -= 1
        return oldtail

        # Zwraca cały węzeł, skraca listę.
        # Dla pustej listy rzuca wyjątek ValueError.

    def join(self, other):  # klasy O(1)
        self.tail.next = other.head
        self.tail = other.tail
        self.length += other.length
        other.clear()

        # Węzły z listy other są przepinane do listy self na jej koniec.
        # Po zakończeniu operacji lista other ma być pusta.

    def clear(self):  # czyszczenie listy
        self.length = 0
        self.head = None
        self.tail = None
