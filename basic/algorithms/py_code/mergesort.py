#mergesort explanation
#https://www.youtube.com/watch?v=cVZMah9kEjI

n=[5,4,3,2,1]

def _merge(n, l, r):
    print(" n:",n)
    print(" l:",l)
    print(" r:",r)
    i=0
    j=0
    index=0
    while i<len(l) and j<len(r):
        #print("  before merge", i, j, index)
        #print ("  before merge",n)
        if l[i]<r[j]:
            n[index]=l[i]
            i += 1
        else:
            n[index]=r[j]
            j += 1
        index += 1
        #print("  after merge", i, j, index)
        #print ("  after merge",n)
    while i<len(l):
        n[index]=l[i]
        i += 1
        index += 1
    while j<len(r):
        n[index]=r[k]
        j += 1
        index += 1

def mergesort(n):
    if len(n) > 1:
        print("n:",n)
        m=len(n)//2
        l=n[:m]
        r=n[m:]
        mergesort(l)
        mergesort(r)
        _merge(n, l, r)

if __name__ == "__main__":
    mergesort(n)
    print("sorted n", n)
