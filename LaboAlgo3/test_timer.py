import pandas as pd
import time
import random
import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns

def rand_input():
    sizes = [5,10,15,50,100,200,1000,10000,100000,10000000,20000000]
    with open('input.txt', 'w') as f:
        f.write(str(len(sizes)) + '\n')
        tries_per_size = 10
        f.write(str(tries_per_size) + '\n')
        for size in sizes:
            for i in range(1, tries_per_size+1):
                f.write(str(size) + '\n')
                for i in range(1, size+1):
                    start = random.randint(1, 2*size)
                    end = random.randint(start+1, 2*size+1)
                    f.write(str(start) + ' ' + str(end) + '\n')



#rand_input()

def txtToCsv():
    with open('output.txt', 'r') as f:
        lines = f.read().splitlines()
        input_sizes = []
        times = []
        for i in range(0, len(lines), 2):
            input_sizes.append(int(lines[i]))
            times.append(float(lines[i+1]))
        
        print(input_sizes) 
        print(times)
        df = pd.DataFrame({'input_sizes': input_sizes, 'times': times})
        df.to_csv('output.csv', index=False)

    df = pd.read_csv('output.csv')

    df['log_cota'] = np.log(df['input_sizes'])
    df['log_tiempo'] = np.log(df['times'])
    print(df)
    ax1 = sns.lmplot(x='times', y='log_cota', data=df)
    plt.xlabel("log_tiempo (s)")
    plt.ylabel("log_cota")
    ax1.savefig("cota.png")
    plt.show()

txtToCsv()