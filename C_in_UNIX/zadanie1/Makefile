#==============================================================================
#                   Przykladowy plik Makefile
#==============================================================================
# make all, hello.x, mcint.x, run1, run2s, run2d1, run2d2, clean, tar
#==============================================================================
# Objasnienia:
#------------------------------------------------------------------------------
# Jezeli nie chcemy by make wykonal okreslone dzialania, a jedynie wypisal
# na ekranie odpowiednie instrukcje, to wywolujemy go z opcja -n, np.
# make -n all
#------------------------------------------------------------------------------
# Wszystko co jest po znaku # do konca linii jest traktowane jako komentarz.
#------------------------------------------------------------------------------
# Jezeli uzywamy rozszerzen w nazwach plikow, ktore nie znajduja sie na
# liscie parametrow wewnetrznych make (mozna je sprawdzic wykonujac: make -p),
# to nalezy je umiescic po slowie .SUFFIXES:, np.:
.SUFFIXES: .c .cpp .o .x .h
#------------------------------------------------------------------------------
# Ponizej przyklady definiowania makr (nie musza byc oznaczane wielkimi literami,
# ale moze byc to wygodne, np.latwiej je odroznic od reszty).
# Do makra MAKRO sie przez $(MAKRO)
# Nazwa katalogu (moze sie przydac); wstawiamy wynik polecenia basename, 
# ktore z nazwy sciezkowej wybiera wlasciwa nazwe katalogu lub pliku (po ostatnim /). 
DIR = `basename $(CURDIR)`
# Nazwy, ktorych bedziemy uzywac, tu: rdzenie nazw plikow
NAME1 = a
NAME2 = b
NAME3 = c
NAME4 = d
NAME5 = e
# Program wykonawczy: dodajemy rozszerzenie .x, ale moze byc dowolne.
EXEC1  = $(NAME1).x  
EXEC2  = $(NAME2).x  
EXEC3  = $(NAME3).x  
EXEC4  = $(NAME4).x  
EXEC5  = $(NAME5).x  
# Pliki powstale po kompilacji plikow zrodlowych, tzw. object files
OBJS1  = $(NAME1).o
OBJS2  = $(NAME2).o
OBJS3  = $(NAME3).o
OBJS4  = $(NAME4).o
OBJS5  = $(NAME5).o
# Dolaczane biblioteki (poza standardowymi). 
# Makra moga byc puste, np. przewidziane na przyszlosc.
LIBS1  = 
# Pliki naglowkowe
HEADS1 = 
#------------------------------------------------------------------------------
# Opcje kompilatora i linkera
CFLAGS = -Wall -std=c99 -pedantic -O -fPIC
LFLAGS = -Wall -std=c99 -pedantic -O
# Biblioteki linkera zainstalowane w systemie 
# (tu: biblioteka matematyczna libm)
LDLIBS = -lm
# Kompilator i linker (czesto ta sama nazwa)
CO = gcc
LD = $(CO)
# Program-archiwizer do tworzenia bibliotek statycznych
AR = ar
# Opcje archiwizera: tworzenie/uaktualnianie biblioteki wraz z indeksem plikow
#                    i wypisywanie komunikatow 
ARFLAGS = rsv
###############################################################################
# Ponizej przyklady definiowania regul zaleznosci
###############################################################################
# Tzw. regula wzorcowa - mowiaca jak pliki z rozszerzeniem .o otrzymac 
# z plikow o rozszerzeniach .c i .h. 
# To co jest po lewej stronie dwukropka nazywa sie "cel", a to co jest po
# prawej - "prerekwizyty" (tzn. to od czego zalezy "cel"). 
# Najpierw make sprawdza czy plik celowy (tu: odpowiedni plik z rozszerzeniem 
# .o) jest aktualny (tzn. nowszy od odpowiednich plikow .c i .h) - jezeli nie, 
# to wykonuje komende ponizej (tutaj: kompilacja). 
# Znak % oznacza wzorzec, tzn. dowolny ciag znakow, ktore tworza rdzen nazwy 
# pliku. 
# Zmienna wewnetrzna $< oznacza pierwszy prerekwizyt, tu: nazwe odpowiedniego 
# pliku z rozszerzeniem .c, ktory nalezy uaktualnic aby otrzymac plik .o. 
# Uwaga: Komenda zaczyna sie od znaku tabulacji (niewidocznego).
%.o: %.c %.h
	$(CO) $(CFLAGS) -c $<
# Jak wyzej, ale bez zaleznosci od plikow naglowkowych
%.o: %.c
	$(CO) $(CFLAGS) -c $<
###############################################################################
# Regula zaleznosci - uaktualnij pliki po prawej stronie dwukropka.
# Na ogol zakladamy, ze w danym katalogu nie ma pliku o nazwie all,
# tzn. ze dana regula zawsze sie wykona. 
# Gdyby plik o takiej nazwie przypadkowo znalazl sie w danym katalogu,
# to mozna wymusic bezwzgledne wykonanie sie ponizszej reguly wpisujac
# nazwe celu po slowie .PHONY:, np.
.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4) $(EXEC5)
###############################################################################
# Jawna regula zaleznosci - najpierw uaktualnij pliki po prawej stronie 
# dwukropka, a potem wykonaj komende, ktora jest w nastepnej linijce (tu:
# wykonaj linkowanie). 
# Zmienna wewnetrzna $@ oznacza cel, tzn. obiekt, ktory jest po lewej stronie 
# dwukropka, tu: $(EXEC1);  a zmienna $^ oznacza wszystkie prerekwizyty, tzn.
# obiekty stojace po prawej stronie dwukropka (tutaj wszystkie pliki .o, ktore
# powinny byc zlinkowane). 
$(EXEC1): $(OBJS1) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^
$(EXEC2): $(OBJS2) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^
$(EXEC3): $(OBJS3) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^
$(EXEC4): $(OBJS4) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^
$(EXEC5): $(OBJS5) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^
###############################################################################
# Aby zapewnic bezwzgledne wykonanie niezaleznie czy istnieja pliki o danych
# nazwach (podobie jak dla all). Jezeli jestesmy pewni, ze plikow o takich
# nazwach nie bedzie w danym katalogu, to mozemy pominac ponizsza deklaracje.
.PHONY: run1
###############################################################################
# Uruchom program $(EXEC1); najpierw sprawdz, czy kod wykonawczy jest aktualny
run1: $(EXEC1)
	./$(EXEC1)

run2: $(EXEC2)
	./$(EXEC2)

run3: $(EXEC3)
	./$(EXEC3)

run4: $(EXEC4)
	./$(EXEC4)

run5: $(EXEC5)
	./$(EXEC5)
# ###############################################################################
# Sprzataczka (tez "phony target")
###############################################################################
.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
