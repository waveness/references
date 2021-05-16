from sympy import symbols, diff, solve
import numpy as np

# 数据集 D
X = np.array([1.51, 1.64, 1.6, 1.73, 1.82, 1.87])
y = np.array([1.63, 1.7, 1.71, 1.72, 1.76, 1.86])

# 构造经验误差函数
w, b = symbols('w b', real=True)
RDh = 0
for (xi, yi) in zip(X, y):
	RDh += (yi - (xi*w + b))**2
RDh *= 1/len(X)

# 对 w 和 b 求偏导
eRDhw = diff(RDh, w)
eRDhb = diff(RDh, b)

# 求解方程组
ans = solve((eRDhw, eRDhb), (w, b))
print('使得经验误差函数 RD(h) 取最小值的参数为：{}'.format(ans))