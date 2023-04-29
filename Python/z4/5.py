def odwracanieI(L, left, right):
    for x in range(int((right+1-left)/2)):
        temp = L[left+x]
        L[left+x] = L[right-x]
        L[right-x] = temp
    return L

def odwracanieR(L, left, right):
    if left>=right:
        return L
    temp = L[left]
    L[left] = L[right]
    L[right] = temp
    left+=1
    right-=1
    return odwracanieR(L, left, right)

L=[1,2,3,4,5,6,7]
odwracanieI(L,1,5)
print(L)
odwracanieR(L,1,5)
print(L)