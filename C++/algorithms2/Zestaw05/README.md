Jak używać:

make
./Generator.x n m
./BubbleSort.x
./SelectionSort.x
./InsertionSort.x

Insertion sort

pesymistyczna - 1 + 2 + ... + (n-1) = (1 + (n - 1))/2 * (n-1) = (n*n -2)/2
(2 z 1; 3 z 2,1 ...)

optymistyczna - (n-1)
(dla kazdego porownujemy raz - posortowana)

miara - (n*n -2)/2 - (n-1)

srednia
dla ustalonego i - suma od k do i k * P(k) = 1/i * suma od k do i k = 1/i * (i+1)/2 * i = (i+1)/2
(while wykona sie i razy wiec P(k) = 1/i)
ogolna - suma od i=1 do (n-1) (i+1)/2 = suma od i=2 do n (i+1)/2 = 1/2 suma od i=2 do n (i+1) = (n^2 + 3n - 4)/4


10000 dat- 24765864
ze wzoru - 25007499
20000 dat- 98604493
ze wzoru - 100014999
30000 dat- 224388362
ze wzoru - 225022499
100 dat posortowane - 99
ze wzoru - 99

