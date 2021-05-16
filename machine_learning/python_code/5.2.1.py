import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap
import numpy as np

rnd = np.random.RandomState(3)	# 为了演示，采用固定的随机
x_min, x_max = -1, 1
z_min, z_max = -0.1, 1.1

# 上帝函数 y=f(x)
def f(x):
	return x**2

# 上帝分布 P(Y|X)
def P(X):
	return f(X) + rnd.normal(scale=0.1, size=X.shape)

# 通过 P(X, Y) 生成数据集 D
X = rnd.uniform(x_min, x_max, 10)   # 通过均匀分布产生 X
Z = X ** 2 # 坐标转换
y = P(X)                            # 通过 P(Y|X) 产生 y

# 绘制 xy 和 zy 下的数据集
# 设置字体大小
plt.rcParams.update({'font.size': 14})
# 设置subfigure
fig, axes = plt.subplots(figsize = (6, 3), nrows=1, ncols=2)
plt.subplots_adjust(left=0.04, right=0.999, top=0.999, bottom=0.1, wspace=0.33)

xz_min_maxs = ((x_min, x_max), (z_min, z_max))
xylabels = (('$x$', '$y$'), ('$z=x^2$', '$y$'), )
Xs = (X, Z)
for ax, xylabel, min_max, X in zip(axes.flat, xylabels, xz_min_maxs, Xs):
	ax.set(xticks=[], yticks=[])
	ax.set_xlabel(xylabel[0]),ax.set_ylabel(xylabel[1])
	ax.set_xlim(min_max[0], min_max[1])

	ax.scatter(x=X, y=y)

# 在 zy 坐标系下，通过最小二乘法的矩阵算法来计算 w
# 给 Z 增加一行 1
Z = Z.reshape(-1, 1)
ones = np.ones(Z.shape[0]).reshape(-1, 1)
Z = np.hstack((ones, Z))

pinvZ = np.linalg.pinv(Z) # 计算伪逆
w = np.matmul(pinvZ, y) # 最小二乘法的矩阵算法

# 在 zy 坐标系下绘制直线
zz = np.linspace(z_min, z_max)
yy = w[0] + w[1]*zz
axes[1].plot(zz, yy, 'k')

# 在 xy 坐标系下绘制抛物线
xx = np.linspace(x_min, x_max)
yy = w[0] + w[1]*xx**2
axes[0].plot(xx, yy, 'k')

axes[0].text(1.2, 0.3, '<=')

plt.show()