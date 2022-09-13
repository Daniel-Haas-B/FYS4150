import numpy as np
import matplotlib.pyplot as plt
import sys

n = ["10", "100", "1000", "10000", "100000", "1000000", "10000000"]


def Exact(x):
    return 1 - (1 - np.exp(-10)) * x - np.exp(-10 * x)


for i in n:
    # Loading Data file
    data2 = np.loadtxt("General_solution_" + i + ".txt")
    x = data2[:, 0]
    v = data2[:, 1]

    u = Exact(x)
    Error_log = np.log10(np.abs((u[1:-1] - v[1:-1]) / u[1:-1]))
    Error_log_abs = np.log10(np.abs((u[1:-1] - v[1:-1])))

    plt.plot(x[1:-1], Error_log, "o", label=f"n_Steps={i}")
    print(np.max(Error_log))

plt.xlabel("x")
plt.ylabel(r"$log_{10}(\epsilon_i)$")
plt.legend()
plt.savefig("error1.pdf")
plt.show()


for i in n:
    # Loading Data file
    data2 = np.loadtxt("General_solution_" + i + ".txt")
    x = data2[:, 0]
    v = data2[:, 1]

    u = Exact(x)
    Error_log = np.log10(np.abs((u[1:-1] - v[1:-1]) / u[1:-1]))
    Error_log_abs = np.log10(np.abs((u[1:-1] - v[1:-1])))

    # ax[0].plot(x[1:-1],Error_log,'o',label=f'n_Steps={i}')

    plt.plot(x[1:-1], Error_log_abs, "o", label=f"n_Steps={i}")


plt.xlabel("x")
plt.ylabel(r"$log_{10}(\Delta_i)$")
plt.legend()
plt.savefig("error2.pdf")
plt.show()
