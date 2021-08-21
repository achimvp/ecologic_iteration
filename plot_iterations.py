from matplotlib import colors
import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("iteration_values.csv", skiprows=1, delimiter=",")

plt.figure(figsize=(15,10))
plt.plot(data[:, 0], data[:, 1:], linewidth=1, label=[r"$r=0.1$",r"$r=0.5$",r"$r=0.9$",r"$r=1.5$"])  # skip the first 100 values as burn in phase
plt.legend()
plt.xlabel("time step n")
plt.ylabel(r"$x_n$")
plt.title("Evolution of the ecologic map vs # of iterations")
plt.savefig("ecologic_map_trajectories")
plt.show()