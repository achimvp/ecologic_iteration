import numpy as np
import matplotlib.pyplot as plt

# simple load lyapunov exponents
le_simp = np.loadtxt("data/lyapunov_exponent_simple.csv", delimiter=",",skiprows=1, unpack=True)
r_simp = le_simp[0,:]

# load advanced lyapunov exponents
le_adv = np.loadtxt("data/lyapunov_exponent_advanced.csv", delimiter=",",skiprows=1, unpack=True)
r_adv = le_adv[0,:]

# load meta information such as number of iterations
# n after which the lyapunov exponent was calculated
header = np.loadtxt("data/lyapunov_exponent_advanced.csv", delimiter=",",max_rows=1, usecols = range(1,5))

# plot a comparison between the two methods for different values of n
fig, axes = plt.subplots(nrows=2, ncols=2, sharex=True, figsize=(10,7))
for i in range(4):
    ax=axes.flat[i]
    # plotting
    ax.plot(r_simp, le_simp[i+1], label="simple", linewidth=1)
    ax.plot(r_adv, le_adv[i+1], label="advanced", linestyle=(0,(.5,.5)), linewidth=1,alpha=1)
    # Styling the plot
    ax.legend()
    ax.grid()
    ax.set_title(r"$\lambda$ nach "+f"{int(header[i])} Iterationen", fontsize=10)
    ax.set_xlabel(r"$r$")
    ax.set_ylabel(r"$\lambda$")
plt.suptitle(r"Vergleich der Lyapunov Exponenten $\lambda$ mit $x_0 = 0.5$ und $\Delta x_0 = 1e-3$", fontsize=15)
plt.tight_layout()
plt.savefig("img/lyapunov_exponents")
#plt.show()