import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("ecologic_map_fine.csv", delimiter=",")
plt.figure(figsize=(15,10))
for i in range(1,50):
    plt.scatter(data[:, 0], data[:,i], linewidths=0, s=0.1, alpha=0.1, c='blue')
plt.ylim(ymax = 10, ymin = 0)
plt.xlabel(r"$r$")
plt.ylabel(r"$x_{i}$")
plt.title("Evolution of the ecologic map")
plt.tight_layout()
plt.savefig("ecologic_map_fine")
plt.show()