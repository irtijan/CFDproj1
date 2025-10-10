import numpy as np
import matplotlib.pyplot as plt

# 1. Load the T matrix from your CSV file
T = np.loadtxt('T.csv', delimiter=',')

# 2. Create x, y grid coordinates (assuming uniform spacing)
s = T.shape[0]
x = np.linspace(0, 1, s)
y = np.linspace(0, 1, s)
X, Y = np.meshgrid(x, y)

# 3. Set contour levels from 0 to 1 in increments of 0.05
levels = np.arange(0, 1.05, 0.05)  # [0.00, 0.05, 0.10, ..., 1.00]

# 4. Plot filled contours
plt.figure(figsize=(6,5))
contour = plt.contourf(X, Y, T, levels=levels, cmap='plasma')
plt.colorbar(contour, label='Temperature (T)')

# 5. Add labels and show
plt.xlabel('x')
plt.ylabel('y')
plt.title('Temperature Contours')
plt.axis('equal')
plt.show()

data = np.loadtxt("Convergence.csv", delimiter=",")
plt.plot(data[:, 0], data[:, 1])

ax = plt.gca()
ax.set_xscale('log')
ax.set_yscale('log')

plt.xlabel("Iteratation")
plt.ylabel("Lnorm")

plt.show()