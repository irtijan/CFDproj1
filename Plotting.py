import numpy as np                  # Python package used of rloading CSV file
import matplotlib.pyplot as plt     # Python package used for plotting

# Load the T matrix from CSV file
T = np.loadtxt('T.csv', delimiter=',')

# Create x, y grid coordinates
s = T.shape[0]
x = np.linspace(0, 1, s)
y = np.linspace(0, 1, s)
X, Y = np.meshgrid(x, y)

# Set contour levels from 0 to 1 in increments of 0.05
levels = np.arange(0, 1.05, 0.05)

# Plot filled contours
plt.figure(figsize=(6,5))
contour = plt.contourf(X, Y, T, levels=levels, cmap='plasma')
plt.colorbar(contour, label='Temperature (T)')

# Add labels and show plot
plt.xlabel('x')
plt.ylabel('y')
plt.title('Temperature Contours')
plt.axis('equal')
plt.show()

# Load convergence history vector from CSV file
data = np.loadtxt("Convergence.csv", delimiter=",")
plt.plot(data[:, 0], data[:, 1])

# Add labels, log axes, and show plot
ax = plt.gca()
ax.set_yscale('log')

plt.xlabel("Iteration")
plt.ylabel("Lnorm")

plt.show()

# Load error vs mesh size array from CSV file
data = np.loadtxt("error.csv", delimiter=",")
plt.plot(data[:, 0], data[:, 1])

# Add labels, log axes, and show plot
ax = plt.gca()
ax.set_xscale('log')
ax.set_yscale('log')
plt.xlabel("Mesh Size")
plt.ylabel("Lnorm")

plt.show()