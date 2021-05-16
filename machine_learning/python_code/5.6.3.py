import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap
import numpy as np
from sklearn import datasets
from sklearn.metrics import accuracy_score

# 初始化权重向量 w
w = np.array([0, 0, 0])

# 定义 d(x) 函数
def d(x):
    return x @ w.reshape(-1, 1) # 利用矩阵乘法来完成点积

# 定义 h(x) 函数
def h(x):
    return np.sign(d(x))

# 计算决策边界的评分
def clf_score(X, y):
    score = 0
    for xi, yi in zip(X, y):
        score += yi*h(xi)
    return score

# 载入breast_cancer数据集
breast_cancer = datasets.load_breast_cancer()
# 取前面100个数据，并且只取两个特征，以及取出对应的类别
sampleNumber = 100
X = np.insert(breast_cancer.data[:sampleNumber, [0,26]], 0, 1, axis=1)	# 给每个xi第一列增加1
y = np.where(breast_cancer.target[:sampleNumber] == 1, -1, 1)			# 将两种类别转为-1和1

# 通过最小二乘法求出 w
pinvX = np.linalg.pinv(X)   # 计算伪逆
w = pinvX @ y               # 最小二乘法的矩阵算法

# # 下面是绘制代码
# # 设置字体大小
plt.rcParams.update({'font.size': 14})
# 设置subfigure
fig, ax = plt.subplots(figsize = (6, 3))
fig.subplots_adjust(left=0.25, right=0.75, top=0.999, bottom=0.1)
ax.set(xticks=[], yticks=[])
ax.set_xlabel('通过最小二乘法得到 w，其准确率 = {}'.format(accuracy_score(y, h(X))))

# 绘制数据集
markers = ('x', 'o')
vmin, vmax = min(y), max(y)
cm = ListedColormap(('blue', 'red'))
for cl, m in zip(np.unique(y), markers):
	ax.scatter(x=X[y==cl, 1], y=X[y==cl, 2], c=y[y==cl], alpha=1, vmin = vmin, vmax = vmax, cmap=cm, edgecolors='k', marker = m)

# # 绘制决策区域
resolution = 0.01
x1_min, x1_max = X[:, 1].min() - 0.2, X[:, 1].max() + 0.2
x2_min, x2_max = X[:, 2].min() - 0.2, X[:, 2].max() + 0.2
xx1, xx2 = np.meshgrid(np.arange(x1_min, x1_max, resolution), np.arange(x2_min, x2_max, resolution))
xx = np.insert(np.column_stack((xx1.ravel(), xx2.ravel())), 0, 1, axis=1)
yy = h(xx).reshape(xx1.shape)
ax.contourf(xx1, xx2, yy, alpha=0.4, cmap=cm)

plt.show()