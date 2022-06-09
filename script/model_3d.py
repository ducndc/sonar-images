from __future__ import division, print_function, unicode_literals
import numpy as np 
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from sklearn import datasets, linear_model



fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

point = np.loadtxt("../map/xyz.txt")

X = np.loadtxt("../map/xyz.txt")[:,0]
Y = np.loadtxt("../map/xyz.txt")[:,1]
Z = np.loadtxt("../map/xyz.txt")[:,2]

#X = np.array([X]).T
#Y = np.array([Y]).T

#one = np.ones((X.shape[0], 1))
#Xbar = np.concatenate((one, X), axis = 1)

# fit the model by Linear Regression
# regr = linear_model.LinearRegression(fit_intercept=False) # fit_intercept = False for calculating the bias
# regr.fit(X, Y)
# print( 'Solution found by scikit-learn  : ', regr.coef_ )

# plt.plot(X, Y, 'ro')
ax.scatter(X, Y, Z)
plt.show()
