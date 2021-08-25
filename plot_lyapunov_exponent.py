import numpy as np
import matplotlib.pyplot as plt

le_simp = np.loadtxt("data/lyapunov_exponent_simple.csv", delimiter=",",skiprows=1, unpack=True)
r_simp = le_simp[0,:]

le_adv = np.loadtxt("data/lyapunov_exponent_advanced.csv", delimiter=",",skiprows=1, unpack=True)
r_adv = le_adv[0,:]

header = np.loadtxt("data/lyapunov_exponent_advanced.csv", delimiter=",",max_rows=1, usecols = range(1,5))



fig, axes = plt.subplots(nrows=2, ncols=2, sharex=True, figsize=(10,7))
for i in range(4):
    ax=axes.flat[i]
    ax.plot(r_simp, le_simp[i+1], label="simple", linewidth=1)
    ax.plot(r_adv, le_adv[i+1], label="advanced", linestyle="dashed", linewidth=1,alpha=0.8)
    ax.legend()
    ax.grid()
    ax.set_title(r"$\lambda$ nach "+f"{int(header[i])} Iterationen", fontsize=10)
    ax.set_xlabel(r"$r$")
    ax.set_ylabel(r"$\lambda$")
plt.suptitle(r"Vergleich der Lyapunov Exponenten $\lambda$ mit $x_0 = 0.5$ und $\Delta x_0 = 1e-3$", fontsize=15)
#plt.xlabel(r"$r$")
#plt.ylabel(r"Lyapunov exponent")
#plt.title("Lyapunov exponent as a function of r")
#plt.legend()
#plt.grid()
#plt.legend()
plt.tight_layout()
plt.savefig("img/lyapunov_exponents")
plt.show()