Jak używać:

make

Jakie operacje są relatywnie szybko wykonywane na drzewie BST, porównaj złożoności czasowez innymi strukturami danych
    Search - O(log(n)) w porownaniu z nieposortowanymi strukturami np.Lista  O(n)

Na czym polega iteracyjne przechodzenie drzewa bez użycia rekurencji?
    na przechodzeniu w lewa strone zapisujac przebyte wezly do stosu, nastepnie dla kazdego elementu stosu natrafiwszy na wezel gdzie nie mozemy przejsc w lewo wracamy na ostatni element stosu idziemy w prawo i lewo(w nieskonczonosc) dodajac elementy do stosu.  

W jaki sposób można użyć drzewo BST do sortowania elementów? Wskaż podobieństwo do wcześniej poznanego algorytmu sortowania. Omów wady takiego rozwiązania.
    wstawiamy elementy mniejsze po lewej wieksze po prawej nastepnie wypisujemy inorderem. podobnie wylgada quicksort

Na czym polega przechodzenie drzewapreorder?
    idziemy w lewo / wracamy i prawo , wypisujemy przy pierwszym odwiedzeniu

Na czym polega przechodzenie drzewainorder?  Jaka będzie kolejność wypisywanych elemen-tów?
    W BST kolejnosc bedzie niemalejaca, idziemy w lewo jesli nie mozemy wypisujemy wracamy wypisujemy i w prawo(wypisanie przy drugim odwiedzeniu)

Na czym polega przechodzenie drzewapostorder,
    ziemy w lewo / wracamy i prawo, wypisujemy jesli odwiedzilismy wszystkie liscie elementu