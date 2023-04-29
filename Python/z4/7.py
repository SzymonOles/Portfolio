def flatten(sequence):
    wynik = []
    for x in sequence:
        if isinstance(x, (list, tuple)):
            wynik.extend(flatten(x))
        else:
            wynik.append(x)
    return wynik

seq = [1,(2,3),4,(5,6,7,(8,9))]
print(flatten(seq))