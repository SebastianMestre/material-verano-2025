import random

def gen(maxn, maxx, maxv):
	n = random.randint(1, maxn)
	x = random.randint(1, maxx)
	return (x, [random.randint(1, maxv) for _ in range(n)])

x, a = gen(1000, 100, 3)

print(len(a), x)
print(' '.join(map(str, a)))
