import numpy as np
import matplotlib.pyplot as plt

r, le = np.loadtxt("lyapunov_exponent_simple.csv", delimiter=",", skiprows = 1, unpack=True)
plt.figure(figsize=(15,10))
plt.plot(r, le)
plt.xlabel(r"$r$")
plt.ylabel(r"Lyapunov exponent")
plt.title("Lyapunov exponent as a function of r")
plt.tight_layout()
plt.savefig("lyapunov_exponent_simple")
plt.show()