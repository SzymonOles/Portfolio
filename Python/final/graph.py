# -*- coding: utf-8 -*-
import os

class Graph:
    """Klasa dla grafu skierowanego lub nieskierowanego."""

    def __init__(self, n=0, directed=False):
        # ilość elementów
        self.n = n

        # bool, czy graf skierowany
        self.directed = directed

        # lista list sąsiedztwa
        self.adj_list = [[] for _ in range(n)]

        # słownik do zamiany nazw w indeksy i odwrotnie
        self.dict = {}
        self.rdict = {}

    def __repr__(self):
        s = ""
        for key in self.dict.keys():
            s += key
            s += " =>"
            for adj in self.adj_list[self.dict[key]]:
                s += " " + self.rdict[adj]
            s += "\n"

        return s

        # zwraca liczbę wierzchołków
    def v(self):
        return self.n

        # zwraca liczbę krawędzi
    def e(self):
        if self.directed:
            return sum(len(adj) for adj in self.adj_list)
        return sum(len(adj) for adj in self.adj_list)/2

        # bool, czy graf skierowany
    def is_directed(self):
        return self.directed

        # dodaje wierzchołek
    def add_node(self, node):

        if node not in self.dict.keys():
            if len(self.dict) == self.n:
                raise OverflowError
            self.rdict[len(self.dict)] = node
            self.dict[node] = len(self.dict)
            return 1
        return 0

        # bool, czy ma dany node
    def has_node(self, node):
        return node in self.dict.keys()

        # usuwa wierzchołek
    def del_node(self, node):
        if self.has_node(node):
            nodei = self.dict[node]

            self.adj_list[nodei] = []
            for adj in self.adj_list:
                if nodei in adj:
                    adj.remove(nodei)
            self.n -= 1
            self.dict.pop(node)
            return 1
        return 0

        # wstawienie krawędzi
    def add_edge(self, edge):
        u, v = edge
        self.add_node(u)
        self.add_node(v)
        
        if self.has_node(u) and self.has_node(v):
            if not self.has_edge(edge):
                u,v = self.dict[u],self.dict[v]

                self.adj_list[u].append(v)

                if not self.directed:
                    self.adj_list[v].append(u)

                return 1
        return 0

        # bool czy ma krawędź
    def has_edge(self, edge):
        u, v = edge
        u,v = self.dict[u],self.dict[v]
        return v in self.adj_list[u]

        # usunięcie krawędzi
    def del_edge(self, edge):
        u, v = edge
        u,v = self.dict[u],self.dict[v]

        if self.has_edge(edge):
            self.adj_list[u].remove(v)

            if not self.directed:
                self.adj_list[v].remove(u)

            return 1

        return 0

        # iterator po wierzchołkach
    def iternodes(self):
        return (key for key in self.dict.keys())

        # iterator po wierzchołkach sąsiednich
    def iteradjacent(self, node):
        node = self.dict[node]
        return (self.rdict[ad] for ad in self.adj_list[node])

        # iterator po krawędziach wychodzących
    def iteroutedges(self, node):
        node = self.dict[node]
        return ((self.rdict[node], self.rdict[v]) for v in self.adj_list[node])

        # iterator po krawędziach przychodzących
    def iterinedges(self, node):
        node = self.dict[node]
        if self.directed:
            return ((self.rdict[u], self.rdict[node]) for u in range(self.n) if node in self.adj_list[u])
        else:
            return ((self.rdict[node], self.rdict[v]) for v in self.adj_list[node])

        # BFS
    def BFS(self, node):
        """Zwraca drzewo BFS dla danego grafu i wierzchołka."""
        node = self.dict[node]
        out = []
        queue = [node]
        visited = set()

        while queue:
            curr_node = queue.pop(0)
            visited.add(curr_node)
            out.append(curr_node)

            for adj_node in self.adj_list[curr_node]:
                if adj_node not in visited and adj_node not in queue:
                    queue.append(adj_node)

        out = [self.rdict[k] for k in out]
        return out

        # DFS
    def DFS(self, node):
        """Zwraca drzewo DFS dla danego grafu i wierzchołka."""
        node = self.dict[node]
        tree = []
        stack = [node]
        visited = set()

        while stack:
            curr_node = stack.pop()
            visited.add(curr_node)
            tree.append(curr_node)

            for adj_node in self.adj_list[curr_node]:
                if adj_node not in visited and adj_node not in stack:
                    stack.append(adj_node)

        tree = [self.rdict[k] for k in tree]
        return tree


def importGraphFile(dir):

# otworz plik
    dir = os.path.join(os.sys.path[0], dir)
    f = open(dir)

# czytaj plik
    lines = f.readlines()

# sprawdz czy skierowany
    isdirectred = (lines[0].split()[0] == 'd')

# sprawdz ilosc wierzcholkow
    n=set()
    for line in lines[1:]:
        a,b = line.split()
        n.add(a)
        n.add(b)
    n = len(n)

# zainicjuj graf
    g = Graph(n,isdirectred)

# wczytaj dane
    for file_line in lines[1:]:
        u,v = file_line.split()
        g.add_node(u)
        g.add_node(v)

        g.add_edge((u,v))

    f.close()
    return g

def importGraphManual():
    n = int(input("Podaj ilosc wierzcholkow: "))
    directed = input("Czy graf jest skierowany? (t/n): ")
    directed = (directed == "t")
    g = Graph(n,directed)
    print("Wpisz wszystkie polaczenia w formacie x y, aby wyjsc wpisz quit")
    inp = input()
    while inp != "quit":
        u,v = inp.split()
        g.add_node(u)
        g.add_node(v)

        g.add_edge((u,v))
        inp = input()
    return g

def GraphMENU():
    g = importGraphFile('test.txt')
    while True:
        print("\n1: Dodaj graf z pliku\n2: Dodaj graf manualnie\n3: wyswietl graf\n4: usun wierzcholek\n5: dodaj krawedz\n6: usun krawedz\n7: BFS\n8: DFS\nq: WYJDZ\n")
        inp = input()
        if inp == "1":
            z = input("podaj sciezke: ")
            g = importGraphFile(z)
        elif inp == "2":
            g = importGraphManual()
        elif inp == "3":
            print(g)
        elif inp == "4":
            z = input("podaj nazwe wierzcholka: ")
            g.del_node(z)
        elif inp == "5":
            x,y = input("podaj krawedz x y: ").split()
            g.add_edge((x,y))
        elif inp == "6":
            x,y = input("podaj krawedz x y: ").split()
            g.del_edge((x,y))
        elif inp == "7":
            z = input("podaj nazwe wierzcholka: ")
            print(g.BFS(z))
        elif inp == "8":
            z = input("podaj nazwe wierzcholka: ")
            print(g.DFS(z))
        elif inp == "q":
            return 0
