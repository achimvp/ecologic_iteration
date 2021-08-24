import numpy as np
import matplotlib.pyplot as plt

r_simp, le_simp = np.loadtxt("lyapunov_exponent_simple.csv", delimiter=",",skiprows=1, unpack=True)
r_adv, le_adv = np.loadtxt("lyapunov_exponent_advanced.csv", delimiter=",",skiprows=1, unpack=True)
data_os = np.loadtxt("ecologic_map_onestep.csv", delimiter=",")
fig, axs = plt.subplots(2,1, figsize=(15,20),sharex=True)
for i in range(1,50):
    axs[0].plot(r_adv, le_adv, label="advanced", linestyle="dashed")   
    axs[1].scatter(data_os[:, 0], data_os[:,i], linewidths=0, s=0.1, alpha=0.1, c='red')
axs[0].grid()
axs[1].set_xlim(xmax = 3, xmin = 0)
# plt.xlabel(r"$r$")
# plt.ylabel(r"$x_{i}$")
axs[0].set_title("Two step iteration")
axs[1].set_title("One step iteration")
plt.tight_layout()
plt.savefig("ecologic_map_bifurcation diagrams")
plt.show()

data = np.loadtxt("differences.csv", skiprows=1, delimiter=",")
index = data[:,0]
header = np.loadtxt("differences.csv", delimiter=",", max_rows=1)
rs = header[2:]
fig, axes = plt.subplots(ncols=2,nrows=3, sharex=True, figsize=(10,7))
fig.suptitle(r"Entwicklung der Trajektorien and Abweichungen for $x_0=$" + f"{header[0]} und "+r"$\delta =$"+f"{header[1]}")
for i in range(0,3):
    axes.flat[2*i].plot(index, data[:,3*i+1], linewidth=1,linestyle = "solid")
    axes.flat[2*i].plot(index, data[:,3*i+2], linewidth=1,linestyle = "dashed")
    axes.flat[2*i+1].plot(index, data[:,3*i+3], linewidth=1)

    #legend
    axes.flat[2*i].legend([r"$x_n$", r"$x_n+\delta$"],loc='lower right')
    axes.flat[2*i+1].legend([r"$\Delta x_n$"],loc='lower right')
    #title
    axes.flat[2*i].set_title(r"Trajektorien für $r=$"+ f"{rs[i]}")
    axes.flat[2*i+1].set_title(r"Abweichung für $r=$"+ f"{rs[i]}")
    #axes
    axes.flat[2*i].set_ylabel(r"$x_n$")
    
    if i == 2:
        axes.flat[2*i].set_xlabel(r"Zeitschritt $n$")
        axes.flat[2*i+1].set_xlabel(r"Zeitschritt $n$")
plt.savefig("error_tracking")
plt.show()