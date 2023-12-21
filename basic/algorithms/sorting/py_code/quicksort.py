#quicksort explanation
#https://www.youtube.com/watch?v=9KBwdDEwal8&t=12s

n=[5,4,3,2,1]

def quicksort(n, left, right):
    print("n: left right",n[left:right+1],left,right)
    if not left < right:
        return
    i=left
    j=right-1
    pivot=right
    while i < j:
        while i < pivot:
            if n[i] > n[pivot]:
                break
            else:
                i+=1
        while j > left:
            if n[j] < n[pivot]:
                break
            else:
                j-=1
        if i<j:
            temp=n[j]
            n[j]=n[i]
            n[i]=temp
    if n[i] > n[pivot]:
        temp=n[pivot]
        n[pivot]=n[i]
        n[i]=temp
    print("n: i j",n[left:right+1], i, j)
    quicksort(n, left, i-1)
    quicksort(n, i+1, right)

if __name__ == "__main__":
    quicksort(n, 0, len(n)-1)
    print("sorted n", n)
