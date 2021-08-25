import numpy as np
import matplotlib.pyplot as plt

# load the data part of the iteration values
data = np.loadtxt("data/iteration_values.csv", delimiter=",", skiprows=1)

# read the values for the bifurcation parameter r
with open('data/iteration_values.csv') as f:
    rs = f.readline().strip().split(",")[1:]

plt.figure(figsize=(15,10))
for i in range(1, data.shape[1]):
	plt.plot(data[:, 0], data[:, i], linewidth=1, label=f"r={rs[i-1]}")  # skip the first 100 values as burn in phase
plt.legend()
plt.xlabel("time step n")
plt.ylabel(r"$x_n$")
plt.title("Evolution of the ecologic map vs # of iterations")
plt.savefig("img/ecologic_map_trajectories")
plt.show()