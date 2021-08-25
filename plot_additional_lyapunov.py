import numpy as np
import matplotlib.pyplot as plt

le_adv = np.loadtxt("data/lyapunov_exponent_advanced.csv", delimiter=",",skiprows=1, unpack=True)
r_adv = le_adv[0,:]

data_os = np.loadtxt("data/ecologic_map_onestep.csv", delimiter=",")
fig, axs = plt.subplots(2,1, figsize=(12,7),sharex=True)
axs[0].plot(r_adv, le_adv[4,:], label="Lyapunov Exponent", linewidth=1)
for i in range(1,50):
    axs[1].scatter(data_os[:, 0], data_os[:,i], linewidths=0, s=0.2, alpha=0.4, c='red')

axs[0].grid()
axs[1].grid()
axs[1].set_xlim(xmax = 3, xmin = 0)
# plt.xlabel(r"$r$")
# plt.ylabel(r"$x_{i}$")
axs[0].set_title("Lyapunov Exponent")
axs[1].set_title("Bifurkationsdiagram")
fig.suptitle(r"Lyapunov Exponent und Bifurkationsdiagram für $x_0=0.5$", fontsize=15)
plt.tight_layout()
plt.savefig("img/lyapunov_and_bifurkation")
plt.show()

data = np.loadtxt("data/differences.csv", skiprows=1, delimiter=",")
index = data[:,0]
header = np.loadtxt("data/differences.csv", delimiter=",", max_rows=1)
rs = header[2:]
fig, axes = plt.subplots(ncols=2,nrows=3, sharex=True, figsize=(10,7))
fig.suptitle(r"Entwicklung der Trajektorien und Differenzen $\Delta x_n$ für $x_0=$" + f"{header[0]} und "+r"$\delta =$"+f"{header[1]}", fontsize=15)
for i in range(0,3):
    axes.flat[2*i].plot(index, data[:,3*i+1], linewidth=1,linestyle = "solid")
    axes.flat[2*i].plot(index, data[:,3*i+2], linewidth=1,linestyle = "dashed")
    axes.flat[2*i+1].plot(index, data[:,3*i+3], linewidth=1)

    #legend
    axes.flat[2*i].legend([r"$x_n$", r"$x_n+\delta$"],loc='lower right')
    axes.flat[2*i+1].legend([r"$\Delta x_n$"],loc='lower right')
    #title
    axes.flat[2*i].set_title(r"Trajektorien für $r=$"+ f"{rs[i]}")
    axes.flat[2*i+1].set_title(r"$\Delta x_n$ für $r=$"+ f"{rs[i]}")
    
    
    
    
    if i == 2:
        axes.flat[2*i].set_xlabel(r"Zeitschritt $n$")
        axes.flat[2*i+1].set_xlabel(r"Zeitschritt $n$")
plt.savefig("img/error_tracking")
plt.show()
