# -*- coding: utf-8 -*-
# @Time    : 2021/4/21 10:14
# @Author  : 咸鱼型233
# @File    : abnormal_img_show.py
# @Software: PyCharm
# @Function: plt显示图像色差问题
import cv2
from matplotlib import pyplot as plt

# 读取图像
img = cv2.imread("../../resource/pic/lena.jpg")

# cv显示图像
cv2.imshow("cv-show", img)
cv2.waitKey(0)  # 等待窗口关闭

# plt显示图像
plt.rcParams['font.family'] = ['SimHei']  # 使用黑体
plt.axis('off')  # 关闭坐标轴
plt.title('plt显示原图')
plt.imshow(img)
plt.show()

# plt显示图像-cv读取图像后提取通道并按照RGB顺序重新组合图像
b, g, r = cv2.split(img)  # 分别提取B、G、R通道
img_new1 = cv2.merge([r, g, b])  # 重新组合为R、G、B
plt.axis('off')  # 关闭坐标轴
plt.title('plt显示原图\n-cv读取图像后提取通道并按照RGB顺序重新组合图像\n方案一提取并重组通道')
plt.imshow(img_new1)
plt.show()

# img[:,:,0]表示图片的蓝色通道，对一个字符串s进行翻转用的是s[::-1]，同样img[:,:,::-1]就表示BGR通道翻转，变成RGB
img_new2 = img[:, :, ::-1]
plt.axis('off')  # 关闭坐标轴
plt.title('plt显示原图\n-cv读取图像后提取通道并按照RGB顺序重新组合图像\n方案2-类字符串翻转')
plt.imshow(img_new2)
plt.show()

# ============ 灰度图像显示 ============ #
img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
plt.axis('off')             # 关闭坐标轴
plt.title("plt显示灰度图像")
plt.imshow(img_gray)
plt.show()

# plt正常显示灰度图像
plt.axis('off')             # 关闭坐标轴
plt.title("plt正常显示灰度图像")
plt.imshow(img_gray, cmap='gray')
plt.show()
