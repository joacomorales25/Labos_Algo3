import pandas as pd
import matplotlib.pyplot as plt
import numpy as np


def plot_res():

    with open('tiempos_log_n.txt', 'r') as f:
        lines = f.readlines()
        nodos = []
        df = pd.DataFrame()
        tiempos = []
        for line in lines:
            line = line.split()
            n = int(line[0])
            tiempo = float(line[1])
            nodos.append(n)
            tiempos.append(tiempo)
        
        df['nodos'] = nodos
        df['tiempo'] = tiempos
    
    with open('tiempos_n_2.txt', 'r') as f:
        lines = f.readlines()
        nodos = []
        df2 = pd.DataFrame()
        tiempos = []
        for line in lines:
            line = line.split()
            n = int(line[0])
            tiempo = float(line[1])
            nodos.append(n)
            tiempos.append(tiempo)
        df2['nodos'] = nodos
        df2['tiempo'] = tiempos
        df2['tiempo'] = df2['tiempo']/1000
        df['tiempo'] = df['tiempo']/1000
    
    plt.plot(df['nodos'], df['tiempo'], color='red')
    plt.plot(df2['nodos'], df2['tiempo'], color='blue')
    plt.xlabel('nodos')
    plt.ylabel('tiempo (s)')
    plt.title('Tiempo de ejecución en función de la cantidad de nodos')
    plt.legend(['O(n*log(n))', 'O(n^2)'])
    plt.savefig('tiempos.png')
    plt.show()

plot_res()
            
