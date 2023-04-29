Jak używać:
LinkedList:
make run1
./LinkedList.x

Generator:
make run2
./Generator.x [arg]

Pytania:

1. Jakie są zalety implementacji wskaźnikowej, a jakie implementacji tablicowej?
    wskaźnikowa jest prostsza w implementacji (np. dodawanie elementów) ale w tablicowej możemy bezpośrednio odwołać się do i-tego elementu
2. Zastanowić się jak zaimplementować listę dwukierunkową zapamiętując tylko jeden wskaźnik?
    będziemy przechowywać next a prev będzie szukać wszystkie elementy od początku aż nie natrafi na nasz element