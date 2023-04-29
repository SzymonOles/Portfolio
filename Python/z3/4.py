while 1:
    n = raw_input("Podaj float: ")
    if n == "stop": break
    try:
        fn = float(n)
        print(fn)
        print(pow(fn,3))
    except:
        print("zle dane")