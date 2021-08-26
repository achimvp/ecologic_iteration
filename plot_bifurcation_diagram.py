import numpy as np
import matplotlib.pyplot as plt

# load data
data_ts= np.loadtxt("data/ecologic_map_twostep.csv", delimiter=",")
data_os = np.loadtxt("data/ecologic_map_onestep.csv", delimiter=",")

# create plot
fig, axs = plt.subplots(2,1, figsize=(15,10))
# plot data
for i in range(1,50):
    axs[0].scatter(data_ts[:, 0], data_ts[:,i], linewidths=0, s=0.2, alpha=0.1, c='blue')
    axs[1].scatter(data_os[:, 0], data_os[:,i], linewidths=0, s=0.2, alpha=0.1, c='red')
# Styling of the plot
axs[0].set_ylim(ymax = 10, ymin = -0.5)
axs[0].set_ylabel(r"$x_{\infty}$")
axs[1].set_ylabel(r"$x_{\infty}$")
axs[0].set_xlabel(r"Bifurkationsparameter $r$")
axs[1].set_xlabel(r"Bifurkationsparameter $r$")
axs[0].set_title("Zweistufige Iteration")
axs[1].set_title("Einstufige Iteration")
plt.tight_layout()
#export
plt.savefig("img/ecologic_map_bifurcation_diagrams")
#plt.show()