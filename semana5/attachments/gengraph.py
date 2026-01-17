import random

# Genera un grafo aleatorio con n vertices y m aristas
# Util para hacer testing intensivo de algoritmos de grafos

# n, m = map(int, input().split())
n, m = 10, 20

edges = []
while len(edges) < m:
    u = random.randint(1, n)
    v = random.randint(1, n)
    if u != v and (u, v) not in edges and (v, u) not in edges:
        edges.append((u, v))

# estilo tipico de competencia de programacion
print(n, m)
for u, v in edges:
    print(u, v)


# # formato para graphviz
# for i in range(1, n+1):
#     print(f"{i} [label=\"{i}\",shape=circle];")
# for u, v in edges:
#     print(f"{u} -- {v};")

