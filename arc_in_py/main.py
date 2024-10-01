from arc import Cache
from random import randint
import sys

filename = "../tests/data.txt"
Ntests = 2000

if(len(sys.argv) == 3):
    if(sys.argv[1] == "-f"):
        filename = sys.argv[2]
    elif(sys.argv[1] == "-n"):
        Ntests = int(sys.argv[2])
    else:
        print("incorrect arguments\n")
        exit(1)
elif(len(sys.argv) == 5):
    if(sys.argv[1] == "-f"):
        filename = sys.argv[2]
        if(sys.argv[3] == "-n"):
            Ntests = int(sys.argv[4])
        else:
            print("incorrect arguments\n")
            exit (1)
    elif(sys.argv[1] == "-n"):
        Ntests = int(sys.argv[2])
        if(sys.argv[3] == "-f"):
            filename = sys.argv[4]
    else:
        print("incorrect arguments")
        exit(1)
else:
    print("incorrect arguments")
    exit(1)

N = 30

file = open(filename, 'w')
for i in range(Ntests):
    cache_size = randint(3, N // 2)
    file.write('{0:d} '.format(cache_size))
    file.write('{0:d} '.format(N))
    cache = Cache(cache_size)
    arr = []
    for j in range(N):
        x = randint(1, N // 2)
        arr.append(x)
        file.write('{0:d} '.format(x))
    @cache
    def identity(f):
        return f
    res = 0
    for k in arr:
        res += identity(k)
    file.write('{0:d}\n'.format(res))
file.close()

