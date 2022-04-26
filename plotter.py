import numpy as np
import matplotlib.pyplot as plt
from math import ceil

fig = plt.figure(figsize=(19, 9))

data = open("/home/ilya/code/ded/2sem/hashtable/data/dump.txt").readlines()
for idx, line in enumerate(data, 1):
    name, values = line.split(':')
    values = values.split()

    values = np.array(list(map(int, values)))

    ax = fig.add_subplot(ceil(len(data) / 3), 3, idx)
    plt.bar(np.arange(0, len(values)), values, width=1)
    ax.set_title(name)

plt.show()