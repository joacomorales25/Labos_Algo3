import random as r

def generate_random_pairs(n, m):
    numbers = list(range(1, n+1))
    pairs = []
    seen = set()
    while len(pairs) < m:
        a = r.choice(numbers)
        b = r.choice(numbers)
        pair = (a, b)
        if a != b and pair not in seen:
            seen.add(pair)
            pairs.append(pair)
    return pairs

def gen_test_densos():
    with open("test_n2.txt", "w") as f:
        f.write("15\n")
        for i in range(5, 3000, 200): # nodos
            edges = i*(i+1)//2
            especiales = r.randint(1,min(i,300))
            edges_que_imprimo = max(0, edges-especiales)
            f.write(str(i) + " " + str(edges_que_imprimo) + " " + str(especiales) + " " + str(r.randint(1,i)) + " " +str(r.randint(1,i)) + "\n")
            list = generate_random_pairs(i, edges)
            for k in list:
                f.write(str(k[0]) + " " + str(k[1]) + " " + str(r.randint(1,30)) + "\n")

def gen_test():
    with open("test.txt", "w") as f:
        f.write("15\n")
        for i in range(5, 3000, 200): # nodos
            edges = r.randint(1, i*(i+1)//2)
            especiales = r.randint(1,min(i,300))
            edges_que_imprimo = max(0, edges-especiales)
            f.write(str(i) + " " + str(edges_que_imprimo) + " " + str(especiales) + " " + str(r.randint(1,i)) + " " +str(r.randint(1,i)) + "\n")
            list = generate_random_pairs(i, edges)
            for k in list:
                f.write(str(k[0]) + " " + str(k[1]) + " " + str(r.randint(1,30)) + "\n")


gen_test()




