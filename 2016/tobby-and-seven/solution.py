
readLine = raw_input
readArgs = lambda : readLine().split()
readInts = lambda : map(int, readArgs())
readInt = lambda : readInts()

def read_int():
    while (True):
        n = readInt()
        if (len(n) > 0):
            return n[0]

def read_ints():
    while (True):
        v = readInts()
        if (len(v) > 0):
            return v

def next_permutation(v):
    k = -1
    l = -1
    size = len(v)
    for i in range(size - 1, 0, -1):
        if (v[i - 1] < v[i]):
            k = i - 1
            for j in range(size - 1, k, -1):
                if (v[j] > v[k]):
                    l = j
                    break
            break

    if (k == -1): return False;

    tmp = v[k]
    v[k] = v[l]
    v[l] = tmp

    i = k + 1
    ind = size - 1
    while i < ind:
        tmp = v[i]
        v[i] = v[ind]
        v[ind] = tmp
        ind = ind - 1
        i = i + 1

    return True

def main():
    n = 0
    k = 0
    while True:
        try:
            n = read_int()
        except EOFError:
            break

        k = read_int()

        pos = read_ints();
        v = []
        append = v.append
        for i in range(0, k):
            if ((1 << pos[i]) & n):
                append(1)
            else:
                append(0)

        v.sort()

        ans = 0
        while True:
            n2 = n
            for i in range(0, k):
                one = (1 << pos[i]) & n
                one = 1 if one > 0 else 0
                if ( one != v[i] ):
                    n2 = n2 ^ (1 << pos[i])

            if (n2 % 7 == 0):
                ans = ans if ans > n2 else n2

            if not next_permutation(v):
                break


        print ans

main()

