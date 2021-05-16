#任意的二次曲线
import numpy as np
import pandas as pd

#初始化w和w0
w, w0 = np.array([0, 0, 0, 0, 0]), 0 # np.array 相当于定义向量

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
X = np.array([[-1.8, 0.6], [0.48, -1.36], [3.68, -3.64], [1.44, 0.52], [3.42, 3.5], [-4.18, 1.68], ])
Z = np.hstack((X**2, (X[:,0]*X[:,1]).reshape(-1, 1), X, )) # 转换为 z1z2z3z4z5 坐标系中的点
y = np.array([1, 1, -1, 1, -1, -1, ])
print("特征转换后的数据集为：")
Zy = np.hstack((Z, y.reshape(-1, 1)))
df = pd.DataFrame(Zy, columns=('z1', 'z2', 'z3', 'z4', 'z5', 'y'))
print(df)

# 感知机的口袋算法
best_w, best_w0 = w, w0
best_cs = clf_score(Z, y)
epochs = 100
for _ in range(epochs):
    # 顺序遍及数据集 X
    for zi, yi in zip(Z, y):
        # 如果有分错的
        if yi * d(zi) <= 0:
            # 更新法向量 w 和 w0
            w, w0 = w + yi * zi, w0 + yi
            # 对新得到的决策边界进行评分
                cs = clf_score(Z, y)
            # 如果更好，则进行更新
            if cs > best_cs:
                best_cs = cs
                best_w, best_w0 = w, w0
            break
w, w0 = best_w, best_w0
print("感知机口袋算法的结果为：")
print('w0 = {:.02f}, w1 = {:.02f}, w2 = {:.02f}, w3={:.02f}, w4={:.02f}, w5={:.02f}'.format(w0, w[0], w[1], w[2], w[3], w[4]))