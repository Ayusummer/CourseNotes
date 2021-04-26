# -*- coding: utf-8 -*-
# @Time    : 2021/4/25 22:31
# @Author  : 咸鱼型233
# @File    : sobel.py
# @Software: PyCharm
# @Function:
import cv2
import matplotlib.pyplot as plt
import os

# 图像路径定义
meanFilter1Img = os.path.abspath(os.path.join(os.path.dirname(__file__),
                                              '../../../resource/pic/Experiment/Ex3-ImageEnhancement/meanFilter1.png'))

plt.subplot(1, 2, 1)
img = cv2.imread(meanFilter1Img, 0)  # 0为灰度图
plt.axis('off')             # 关闭坐标轴
plt.imshow(img, cmap='gray')

plt.subplot(1, 2, 2)
depth = cv2.CV_16S
# 求X方向梯度（创建grad_x, grad_y矩阵）
grad_x = cv2.Sobel(img, depth, 1, 0)
abs_grad_x = cv2.convertScaleAbs(grad_x)

# 求Y方向梯度
grad_y = cv2.Sobel(img, depth, 0, 1)
abs_grad_y = cv2.convertScaleAbs(grad_y)

# 合并梯度
sobel_img = cv2.addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0)

plt.imshow(sobel_img, cmap='gray')
plt.axis('off')             # 关闭坐标轴
plt.show()
