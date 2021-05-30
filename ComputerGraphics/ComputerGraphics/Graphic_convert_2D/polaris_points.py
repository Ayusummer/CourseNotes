# -*- coding: utf-8 -*-
# @Time    : 2021/5/7 10:26
# @Author  : 咸鱼型233
# @File    : polaris_points.py
# @Software: PyCharm
# @Function: 用于生成北极星顶点的脚本,与主体功能无关
x_lst = [1295, 1267, 1211, 1231, 1194, 1239, 1220, 1267, 1295, 1323, 1380, 1362, 1409, 1362, 1389, 1324]
y_lst = [341, 454, 437, 496, 522, 540, 596, 587, 684, 587, 607, 549, 522, 502, 426, 455]
xx = []
yy = []
for i in range(x_lst.__len__()):
    xx.append(x_lst[i]-1220)
    yy.append((y_lst[i] - 341))
print(xx)
print(yy)