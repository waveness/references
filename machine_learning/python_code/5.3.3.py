import matplotlib.pyplot as plt
import numpy as np
from sklearn.preprocessing import PolynomialFeatures
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error

rnd = np.random.RandomState(3)	# 为了演示，采用固定的随机
x_min, x_max = 0, 10

# 上帝函数 y=f(x)
def f(x):
	return x**5-22*x**4+161*x**3-403*x**2+36*x+938

# 上帝分布 P(Y|X)
def P(X):
	return f(X) + rnd.normal(scale=30, size=X.shape)

# 通过 P(X, Y) 生成数据集 D
X = rnd.uniform(x_min, x_max, 50)   # 通过均匀分布产生 X
y = P(X)                            # 通过 P(Y|X) 产生 y

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size =0.3, random_state = 0)

degrees = (1, 2, 3, 5, 7, 10) # 多项式的最高次数
for degree in degrees:
	# 在 zy 坐标系进行线性回归
	poly = PolynomialFeatures(degree=degree)    		    # 建立多项式的坐标转换
	Z_train = poly.fit_transform(X_train.reshape(-1, 1))    # 将 X_train 转化为 Z_train
	LR = LinearRegression().fit(Z_train, y_train)		    # 在 zy 坐标系进行线性回归

	# 在 zy 坐标系下计算测试集的
	Z_test = poly.fit_transform(X_test.reshape(-1, 1))		# 将 X_test 转化为 Z_test
	y_pred = LR.predict(Z_test)							    # 在 zy 坐标系下进行预测
	print('多项式的最高次数为：{}，测试集上的经验误差为：{}'.format(degree, mean_squared_error(y_pred, y_test)))