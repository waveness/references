#椭圆决策边界
import numpy as np

#初始化w和w0
w, w0 = np.array([0, 0]), 0 # np.array 相当于定义向量

#定义d(x)函数
def d(x):
    return np.dot(w,x) + w0 # np.dot 是向量的点积

#定义sign函数
def sign(x):
    return 1 if x >= 0 else -1

#定义h(x)函数
def h(x):
    return sign(d(x))

# 计算决策边界的评分
def clf_score(X, y):
    score = 0
    for xi, yi in zip(X, y):
        score += yi*h(xi)
    return score
# 数据集
X = np.array([[-1.8, 0.6], [0.48, -1.36], [3.68, -3.64], [1.44, 0.52], [3.42, 3.5], [-4.18, 1.68],])
Z = X**2 #转换为z1z2坐标系的点
y = np.array([1, 1, -1, 1, -1, -1, ])

# 感知机的口袋算法
best_w, best_w0 = w, w0
best_cs = clf_score(Z, y)
epochs = 100
for _ in range(epochs):
    # 顺序遍历数据集X
    for zi, yi in zip(Z, y):
        # 如果有分错的
        if yi*d(zi) <= 0:
            # 更新法向量w和w0
            w, w0 = w + yi*zi, w0+yi
            # 对新得到的决策边界进行评分
            cs = clf_score(Z, y)
            # 如果更好，则进行更新
            if cs > best_cs:
                best_cs = cs
                best_w, best_w0 = w, w0
            break
w, w0 = best_w, best_w0
print('w0 = {}, w1 = {}, w_2 = {}'.format(w0, w[0], w[1]))