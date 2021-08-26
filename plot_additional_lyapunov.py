import numpy as np
import matplotlib.pyplot as plt

###
#    Plotting comparison of the lyapunov exponent and the bifurkation diagram
###

# load the lyapunov exponent as a function of r
le_adv = np.loadtxt("data/lyapunov_exponent_advanced.csv", delimiter=",",skiprows=1, unpack=True)
r_adv = le_adv[0,:]

# load the bifurkation data as a function of r
data_os = np.loadtxt("data/ecologic_map_onestep.csv", delimiter=",")

fig, axs = plt.subplots(2,1, figsize=(12,7),sharex=True)
#plot lyapunov
axs[0].plot(r_adv, le_adv[4,:], label="Lyapunov Exponent", linewidth=1)
#plot bifurkation
for i in range(1,50):
    axs[1].scatter(data_os[:, 0], data_os[:,i], linewidths=0, s=0.2, alpha=0.4, c='red')

#styling of the plots
axs[0].grid()
axs[0].set_title("Lyapunov Exponent")
axs[0].set_ylabel(r"$\lambda$")
axs[1].grid()
axs[1].set_xlim(xmax = 3, xmin = 0)
axs[1].set_title("Bifurkationsdiagram")
axs[1].set_xlabel(r"Bifurkationsparameter $r$")
axs[1].set_ylabel(r"$x_n$")
fig.suptitle(r"Lyapunov Exponent und Bifurkationsdiagram für $x_0=0.5$", fontsize=15)
plt.tight_layout()
#export plot
plt.savefig("img/lyapunov_and_bifurkation")
#plt.show()

###
#   Analyzing the trajectories and differences of the function
#   as a function of n. Those plots are later used to better
#   Understand the problems of the simple calcualtion of LE
###

# Load data
data = np.loadtxt("data/differences.csv", skiprows=1, delimiter=",")
index = data[:,0]
header = np.loadtxt("data/differences.csv", delimiter=",", max_rows=1)
rs = header[2:]

# Create Plot
fig, axes = plt.subplots(ncols=2,nrows=3, sharex=True, figsize=(10,7))
fig.suptitle(r"Entwicklung der Trajektorien und Differenzen $\Delta x_n$ für $x_0=$" + f"{header[0]} und "+r"$\delta =$"+f"{header[1]}", fontsize=15)
for i in range(0,3):
    # Plotting the data
    axes.flat[2*i].plot(index, data[:,3*i+1], linewidth=1,linestyle = "solid")
    axes.flat[2*i].plot(index, data[:,3*i+2], linewidth=1,linestyle = "dashed")
    axes.flat[2*i+1].plot(index, data[:,3*i+3], linewidth=1)

    # Styling of the ploz
    axes.flat[2*i].legend([r"$x_n$", r"$x_n+\delta$"],loc='lower right')
    axes.flat[2*i+1].legend([r"$\Delta x_n$"],loc='lower right')
    axes.flat[2*i].set_title(r"Trajektorien für $r=$"+ f"{rs[i]}")
    axes.flat[2*i+1].set_title(r"$\Delta x_n$ für $r=$"+ f"{rs[i]}")
    
    # only add x labels to the last row of plots as they use shared axis
    if i == 2:
        axes.flat[2*i].set_xlabel(r"Zeitschritt $n$")
        axes.flat[2*i+1].set_xlabel(r"Zeitschritt $n$")
plt.savefig("img/error_tracking")
#plt.show()
