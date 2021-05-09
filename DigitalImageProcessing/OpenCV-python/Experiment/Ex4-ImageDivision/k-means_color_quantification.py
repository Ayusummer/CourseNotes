# -*- coding: utf-8 -*-
# @Time    : 2021/5/9 11:43
# @Author  : 咸鱼型233
# @Author_author : play4fun
# @File    : k-means_color_quantification.py
# @Software: PyCharm
# @Function: 
# @ChangeLog
import sys
import numpy as np
import cv2
from matplotlib import pyplot as plt
# 导入上级目录里的配置文件中的图像路径
sys.path.append('../')
from config import path_Hei

img_origin = cv2.imread(path_Hei)
img = img_origin/255
img = img[:, :, ::-1]
# 构造显示图像
tmp = img

Z = img.reshape((-1, 3))
# convert to np.float32
Z = np.float32(Z)

# define criteria, number of clusters(K) and apply k-means()
criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 10, 1.0)
# K = 8
# K = 3
# K = 14
K = 5

ret, label, center = cv2.kmeans(Z, K, None, criteria, 10, cv2.KMEANS_RANDOM_CENTERS)

# 分离颜色
for y in range(len(center)):
    a1 = []
    for i, x in enumerate(label.ravel()):
        if x == y:
            a1.append(list(Z[i]))
        else:
            a1.append([0, 0, 0])
    a2 = np.array(a1)
    a3 = a2.reshape(img.shape)
    # 两张图片横向合并（便于对比显示）
    tmp = np.hstack((tmp, a3))


# plt显示图像
plt.rcParams['font.family'] = ['SimHei']  # 使用黑体
plt.axis('off')  # 关闭坐标轴
plt.title('k-means颜色量化')
plt.imshow(tmp)
plt.show()
