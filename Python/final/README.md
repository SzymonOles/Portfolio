format pliku z grafem:

d/u [directed/undirected]  
a b [polaczenia]  
a c  
...  

graph.py zawiera klasę grafu i funkcje do wczytywania  
graphRUN.py uruchamia interfejs do operacji na grafie  
test_graph.py zawiera testy z pytest na grafie  

Klasa Graph:  
__init__(self, n=0, directed=False):
    możemy za jej pomocą stworzyć graf, n definiuje ilość wierzchołków, directed definiuje czy graf jest skierowany

def __repr__(self):
    pozwala nam na wypisane grafu za pomocą bezpośredniego odniesienia do jego nazwy (np. print(graph))

def v(self):
    zwraca liczbę wierzchołków

def e(self):
    zwraca liczbę krawędzi

def is_directed(self):
    zwraca czy graf jest skierowany

def add_node(self, node):
    dodaje wierzchołek, zwraca 0/1 w zależności od powodzenia operacji

def has_node(self, node):
    zwraca bool, czy graf posiada dany wierzchołek

def del_node(self, node):
    usuwa wierzchołek, zwraca 0/1 w zależności od powodzenia operacji

def add_edge(self, edge):
    dodaje krawędź, zwraca 0/1 w zależności od powodzenia operacji, automatycznie dodaje nieistniejące wierzchołki

def has_edge(self, edge):
    sprawdza czy ma krawędź

def del_edge(self, edge):
    usuwa krawędź, zwraca 0/1 w zależności od powodzenia operacji

def iternodes(self):
    zwraca iterator po wierzchołkach

def iteradjacent(self, node):
    zwraca iterator po wierzchołkach sąsiednich

def iteroutedges(self, node):
    zwraca iterator po krawędziach wychodzących

iterinedges(self, node):
    iterator po krawędziach przychodzących

def BFS(self, node):
    zwraca listę wierzchołków po przejściu BFS

def DFS(self, node):
    zwraca listę wierzchołków po przejściu DFS

dodatkowo dodane są 2 funkcje dla dodawania grafu, i jedna dla interaktywnych operacji

def importGraphFile(dir):
    przyjmuje stringa ze ścieżką do pliku, zwraca strukturę grafu

def importGraphManual():
    zwraca strukturę grafu, wywołuje interaktywne manualne wczytywanie pliku

def GraphMENU():
    wywołuje interaktywną sesję pozwalającą na wczytywanie i operowanie na grafie

Przykład użycia:
1 - możemy korzystać wyłącznie z GraphMENU() aby przetestować graf

    from graph import *
    GraphMENU()

2 - możemy wczytać graf z pliku o opisanej wyżej strukturze

    from graph import *
    g = importGraphFile("test.txt")

3 - możemy wczytać graf manualnie za pomocą sesji interaktywnej

    from graph import *
    g = importGraphManual()

2,3 cd. - operacje na grafie

po wczytaniu możemy wyświetlić graf,liczbę wierzchołków, czy liczbę krawędzi, czy jest skierowany

    print(g)
    print(g.v())
    print(g.e())
    print(g.directed())

możemy operować na wierzchołkach i krawędziach i sprawdzać czy istnieją

    g.del_node("a")
    print(g.has_node("a"))

    g.add_edge(("a","b"))
    g.del_edge(("a","b"))
    print(g.has_edge(("a","b")))

możemy wyświetlić listę wierzchołków po przejściu BFS i DFS

    print(g.DFS("a"))
    print(g.BFS("a"))

możemy skorzystać z iteratorów do przechodzenia po strukturze

    i = iternodes()
    i = iteradjacent("a")
    i = iteroutedges("a")
    i = iterinedges("a")

    print(next(i))...
