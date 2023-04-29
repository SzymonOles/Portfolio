# sposoby
# 1- uzywany przeze mnie
# definiujemy wartosci pojedynczych liter i czytamy po kolei zachowujac zasady - jesli nastepny jest wiekszy to odpowiedio odejmujemy
# 2
# definiujemy wartosci pojedynczych liter i kombinacji(IV -> IIII) podmieniamy kombinacje po czym czytamy normalnie 

roman1 = "MMMDCCXXIV"

def r2a(roman):
    # definiujemy wartosci
    wartosc = {'I': 1, 'V': 5, 'X': 10, 'L': 50, 'C': 100, 'D': 500, 'M': 1000} 
    # inicjujemy zmienna przechowujaca wynik
    arab = 0
    # petla po dlugosci napisu
    for i in range(len(roman)):
        # if dla przypadkow poprzedzajacych mniejszych liter
        if i > 0 and wartosc[roman[i]] > wartosc[roman[i - 1]]:
            arab += wartosc[roman[i]] - 2 * wartosc[roman[i - 1]]
        # else dla przypadkow normalnych
        else:
            arab += wartosc[roman[i]]
    return arab

print(r2a(roman1))