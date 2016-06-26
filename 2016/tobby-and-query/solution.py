
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


def main():

    n = 0
    q = 0
    v = []
    while (True):
        try:
            n = read_int()
        except EOFError:
            break

        v = read_ints()

        pre = {}
        for i in range(0, 10):
            pre[i] = [0]

        for i in range(0, n):
            num = v[i]
            for j in range(0, 10):
                val = 0
                if (num == j):
                    val = 1

                last = len(pre[j]) - 1;
                pre[j].append(pre[j][last] + val)


        q = read_int()
        for i in range(0, q):
            l,r = read_ints()

            ans = 0
            for j in range(0, 10):
                ans = ans + (1 if pre[j][r] - pre[j][l - 1] > 0 else 0)

            print ans


main()
