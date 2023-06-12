import pandas as pd
import time
import random
import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns

def rand_input():
    sizes = [5,10,15,50,100,200,300,500,1000,3000,5000,10000,20000]
    file = open("input.txt", "w")
    file.write(str(len(sizes)) + "\n")
    for i in sizes:
        dist, modems, costo_utp, costo_fibra = random.randint(1,100), random.randint(1,i-2), random.randint(1,100), random.randint(1,100)
        file.write(str(i) + " " + str(dist) + " " + str(modems) + " " + str(costo_utp) + " " + str(costo_fibra) + "\n")
        set = []
        for j in range(i):
            x = random.randint(1,200)
            y = random.randint(1,200)
            file.write(str(x) + " " + str(y) + "\n")
    file.close()

#rand_input()

def txtToCsv():
    
    df = pd.read_csv('output_DSU.txt', sep=" ", header=None)
    df2 = pd.read_csv('output_DSU_Path.txt', sep=" ", header=None)
    df3 = pd.read_csv('output_kruskal_n2.txt', sep=" ", header=None)
    df.columns = ["size", "time"]
    df2.columns = ["size", "time"]
    df3.columns = ["size", "time"]
    df['time'] = df['time']/1000000
    df2['time'] = df2['time']/1000000
    df3['time'] = df3['time']/1000000
    #df2 = np.log(df2)
    #df3 = np.log(df3)

    plt.plot(df['size'],df['time'], label='DSU')
    plt.plot(df2['size'],df2['time'], label='DSU Path Compression')
    plt.plot(df3['size'],df3['time'], label='Kruskal N^2')
    plt.title('Tiempos de ejecución de Kruskal para sus distintas implementaciones')
    plt.xlabel('Tamaño de entrada')
    plt.ylabel('Tiempo (segundos)')
    plt.legend()
    plt.grid()
    plt.savefig('tiempos.png')
    plt.show()



# print the data frame

txtToCsv()