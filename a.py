import random

def f(m,n):
    return random.randint(m,n-1)

A = "abcdefghijklmnopqrstuvwxyz"

if __name__ == '__main__':
    ts = 1
    for t in range(ts):
        m = 1000
        n = 100
        print m
        for i in range(m):
            s = ""
            for j in range(n):
                s = s+A[f(0,len(A)-1)]
            print s
