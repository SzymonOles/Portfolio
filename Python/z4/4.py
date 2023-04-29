def fibonacci(n):
    f1, f2 = 0, 1

    for count in range(n):
        temp = f1 + f2
        f1 = f2
        f2 = temp
    return f1

print(fibonacci(5))