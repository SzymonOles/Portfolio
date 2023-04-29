# niepotrzebne bledne przypisanie przy sort
L = [3, 5, 4] ; L = L.sort()

# nieodpowiednie przypisanie 3 do 2
x, y = 1, 2, 3

# nie można podmieniac elementow w tuplach
X = 1, 2, 3 ; X[1] = 4

# poza zasiegiem - numerowanie od zera
X = [1, 2, 3] ; X[3] = 4

# nie mozna appendowac stringow
X = "abc" ; X.append("d")

# nie przekazujemy odpowiednich argumentow do pow
L = list(map(pow, range(8)))