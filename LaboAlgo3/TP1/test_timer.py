import pandas as pd
import time
import random
import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns

def rand_input():
    sizes = [5,10,15,50,100,200,300,500,1000,3000,5000,10000,20000,50000,100000,200000,500000, 700000,10000000]
    order = dict()

    with open('iguales.txt','w') as f:
        f.write(str(len(sizes)) + '\n')
        for size in sizes:
            f.write(str(size) + '\n')
            start = random.randint(1, 2*size)
            end = random.randint(start+1, 2*size+1)
            for i in range(1, size+1):
                f.write(str(start) + ' ' + str(end) + '\n')
'''
    with open('input.txt', 'w') as f:
        f.write(str(len(sizes)) + '\n')
        for size in sizes:
            vector = []
            f.write(str(size) + '\n')
            for i in range(1, size+1):
                start = random.randint(1, 2*size)
                end = random.randint(start+1, 2*size+1)
                vector.append((start, end))
                f.write(str(start) + ' ' + str(end) + '\n')
            order[size] = vector
    
    for key in sizes:
        order[key].sort(key=lambda x: x[1])

    with open('order.txt', 'w') as f:
        f.write(str(len(sizes)) + '\n')
        for key in sizes:
            f.write(str(key) + '\n')
            for pair in order[key]:
                f.write(str(pair[0]) + ' ' + str(pair[1]) + '\n')
'''

        

#rand_input()

def txtToCsv():
    
    df = pd.read_csv('output.txt', sep=" ", header=None)
    df2 = pd.read_csv('output_order.txt', sep=" ", header=None)
    df3 = pd.read_csv('output_iguales.txt', sep=" ", header=None)
    df.columns = ["size", "time"]
    df2.columns = ["size", "time"]
    df3.columns = ["size", "time"]
    df['time'] = df['time']/1000000
    df2['time'] = df2['time']/1000000
    df3['time'] = df3['time']/1000000
    df = np.log(df)
    df2 = np.log(df2)
    df3 = np.log(df3)

    plt.plot(df['size'],df['time'], label='Actividades randoms')
    plt.plot(df2['size'],df2['time'], label='Actividades ordenadas')
    plt.plot(df3['size'],df3['time'], label='Actividades iguales')
    plt.title('Tiempos de ejecución del algoritmo')
    plt.xlabel('Tamaño de entrada')
    plt.ylabel('Tiempo (segundos)')
    plt.legend()
    plt.grid()
    plt.show()



# print the data frame


txtToCsv()