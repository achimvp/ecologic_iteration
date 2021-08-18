import numpy as np
import matplotlib.pyplot as plt

n, x = np.loadtxt("iteration_values.csv", skiprows=1, delimiter=",", unpack=True)

plt.plot(n[100:], x[100:])  # skip the first 100 values as burn in phase
plt.title("Evolution of the ecologic map vs # of iterations")
plt.show()