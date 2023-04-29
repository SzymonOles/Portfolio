def sum_seq(sequence):
    sum=0
    for x in sequence:
        if isinstance(x, (list, tuple)):
            sum += sum_seq(x)
        else:
            sum += x
    return sum

seq = [1,(2,3),4,(5,6,7),8,9]
print(sum_seq(seq))