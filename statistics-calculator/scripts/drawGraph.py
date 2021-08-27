import numpy as np
import matplotlib.pyplot as plt
import sys
from math import sqrt

data = [float(idx) for idx in sys.argv[1].split(',')]
print(data)

# Fixing random state for reproducibility
# np.random.seed(19680801)

# mu, sigma = 100, 15
# x = mu + sigma * np.random.randn(10000)

# the histogram of the data
n_bins = int(sqrt(len(data)))
n, bins, patches = plt.hist(data, n_bins, density=True, facecolor='g', alpha=0.75)


plt.xlabel('Values')
plt.ylabel('Probability')
plt.title('Histogram of the data')
plt.grid(True)
plt.show()
