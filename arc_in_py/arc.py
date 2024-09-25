from collections import deque
from random import randint
class Cache(object):
    """
    >>> dec_cache = Cache(10)
    >>> @dec_cache
    ... def identity(f):
    ...     return f
    >>> dummy = [identity(x) for x in range(20) + range(11,15) + range(20) +
    ... range(11,40) + [39, 38, 37, 36, 35, 34, 33, 32, 16, 17, 11, 41]] 
    >>> dec_cache.t1
    deque([(41,)])
    >>> dec_cache.t2
    deque([(11,), (17,), (16,), (32,), (33,), (34,), (35,), (36,), (37,)])
    >>> dec_cache.b1
    deque([(31,), (30,)])
    >>> dec_cache.b2
    deque([(38,), (39,), (19,), (18,), (15,), (14,), (13,), (12,)])
    >>> dec_cache.p
    5
    """
    def __init__(self, size):
        self.cached = {}
        self.c = size
        self.p = 0
        self.t1 = deque()
        self.t2 = deque()
        self.b1 = deque()
        self.b2 = deque()

    def replace(self, args):
        if self.t1 and (
            (args in self.b2 and len(self.t1) == self.p) or
            (len(self.t1) > self.p)):
            old = self.t1.pop()
            self.b1.appendleft(old)
        else:
            old = self.t2.pop()
            self.b2.appendleft(old)
        del(self.cached[old])

    def __call__(self, func):
        def wrapper(*orig_args):
            """decorator function wrapper"""
            args = orig_args[:]
            if args in self.t1: 
                self.t1.remove(args)
                self.t2.appendleft(args)
                # return self.cached[args]
                return 1
            if args in self.t2: 
                self.t2.remove(args)
                self.t2.appendleft(args)
                # return self.cached[args]
                return 1
            result = func(*orig_args)
            self.cached[args] = result
            if args in self.b1:
                self.p = min(
                    self.c, self.p + max(len(self.b2) / len(self.b1) , 1))
                self.replace(args)
                self.b1.remove(args)
                self.t2.appendleft(args)
                return 0
            if args in self.b2:
                self.p = max(0, self.p - max(len(self.b1)/len(self.b2) , 1))
                self.replace(args)
                self.b2.remove(args)
                self.t2.appendleft(args)
                return 0
            if len(self.t1) + len(self.b1) == self.c:
                if len(self.t1) < self.c:
                    self.b1.pop()
                    self.replace(args)
                else:
                    del(self.cached[self.t1.pop()])
            else:
                total = len(self.t1) + len(self.b1) + len(
                    self.t2) + len(self.b2)
                if total >= self.c:
                    if total == (2 * self.c):
                        self.b2.pop()
                    self.replace(args)
            self.t1.appendleft(args)
            return 0
        return wrapper

# Ntests = 2000
# N = 10
# file = open('data_10.txt', 'w')
# for i in range(Ntests):
#     cache_size = randint(3, N // 2)
#     file.write('{0:d} '.format(cache_size))
#     file.write('{0:d} '.format(N))
#     cache = Cache(cache_size)
#     arr = []
#     for j in range(N):
#         x = randint(1, N // 2)
#         arr.append(x)
#         file.write('{0:d} '.format(x))
#     @cache
#     def identity(f):
#         return f
#     res = 0
#     for k in arr:
#         res += identity(k)
#     file.write('{0:d}\n'.format(res))
# file.close()

arr = [12, 9, 4, 1, 14, 15, 4, 4, 15, 12, 7, 5, 9, 12, 1, 10, 13, 3, 8, 4, 6, 2, 1, 2, 7, 6, 4, 3, 12, 13]
cache = Cache(6)
@cache
def identity(f):
    return f
res = 0
for k in arr:
    print (identity(k))






