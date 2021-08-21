import numpy as np
import matplotlib.pyplot as plt

data_ts= np.loadtxt("ecologic_map_twostep.csv", delimiter=",")
data_os = np.loadtxt("ecologic_map_onestep.csv", delimiter=",")
fig, axs = plt.subplots(2,1, figsize=(15,20))
for i in range(1,50):
    axs[0].scatter(data_ts[:, 0], data_ts[:,i], linewidths=0, s=0.1, alpha=0.1, c='blue')
    axs[1].scatter(data_os[:, 0], data_os[:,i], linewidths=0, s=0.1, alpha=0.1, c='red')
axs[0].set_ylim(ymax = 10, ymin = 0)
# plt.xlabel(r"$r$")
# plt.ylabel(r"$x_{i}$")
axs[0].set_title("Two step iteration")
axs[1].set_title("One step iteration")
plt.tight_layout()
plt.savefig("ecologic_map_bifurcation diagrams")
plt.show()