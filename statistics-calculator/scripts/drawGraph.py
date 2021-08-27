import numpy as np
import matplotlib.pyplot as plt
import sys
from math import sqrt

data = [float(idx) for idx in sys.argv[1].split(',')]

n_bins = int(sqrt(len(data)))
n, bins, patches = plt.hist(data, n_bins, facecolor='b', edgecolor='black', linewidth=0.8, alpha=0.75)

plt.xlabel('Value')
plt.ylabel('Frequency')
plt.title('Histogram of the data')
plt.grid(True)
plt.show()
