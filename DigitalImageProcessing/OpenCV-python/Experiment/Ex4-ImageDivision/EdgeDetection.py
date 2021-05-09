# -*- coding: utf-8 -*-
# @Time    : 2021/5/9 12:26
# @Author  : 咸鱼型233
# @File    : EdgeDetection.py
# @Software: PyCharm
# @Function: 边缘检测
# @ChangeLog
from skimage import io, filters, img_as_ubyte
import matplotlib.pyplot as plt
from skimage import feature  # 含canny算子
import numpy as np
from scipy import signal
import cv2

# 导入上级目录里的配置文件中的图像路径
import sys

sys.path.append('../')
from config import path_Hei


def createLoGKernel(sigma, size):
    H, W = size
    r, c = np.mgrid[0:H:1.0, 0:W:1.0]
    r -= (H - 1) / 2
    c -= (W - 1) / 2
    sigma2 = np.power(sigma, 2.0)
    norm2 = np.power(r, 2.0) + np.power(c, 2.0)
    LoGKernel = (norm2 / sigma2 - 2) * np.exp(-norm2 / (2 * sigma2))  # 省略掉了常数系数 1\2πσ4

    # print(LoGKernel)
    return LoGKernel


def LoG(image, sigma, size, _boundary='symm'):
    LoGKernel = createLoGKernel(sigma, size)
    edge = signal.convolve2d(image, LoGKernel, 'same', boundary=_boundary)
    return edge


# 图像读取
img = io.imread(path_Hei, as_gray=True)

# sobel边缘检测
edges = filters.sobel(img)
# 浮点型转成uint8型
edges = img_as_ubyte(edges)

# sobel 水平方向边缘检测
edgesh = filters.sobel_h(img)
edgesh = img_as_ubyte(edgesh)

# sobel 竖直方向边缘检测
edgesv = filters.sobel_v(img)
edgesv = img_as_ubyte(edgesv)

# Roberts算子
edges_roberts = filters.roberts(img)
edges_roberts = img_as_ubyte(edges_roberts)

# prewitt算子
edges_prewitt = filters.prewitt(img)
edges_prewitt = img_as_ubyte(edges_prewitt)

edges_prewitt_h = filters.prewitt_h(img)  # 水平方向边缘检测
edges_prewitt_h = img_as_ubyte(edges_prewitt_h)

edges_prewitt_v = filters.prewitt_v(img)  # 垂直方向边缘检测
edges_prewitt_v = img_as_ubyte(edges_prewitt_v)

# canny算子
edges_canny = feature.canny(img, sigma=1.0)  # sigma越小，边缘线条越细小
edges_canny = img_as_ubyte(edges_canny)


# 高斯拉普拉斯
img1 = cv2.imread(path_Hei, 0)

LoG_edge = LoG(img1, 1, (11, 11))
LoG_edge[LoG_edge > 255] = 255
# LoG_edge[LoG_edge>255] = 0
LoG_edge[LoG_edge < 0] = 0
LoG_edge = LoG_edge.astype(np.uint8)

LoG_edge1 = LoG(img1, 1, (37, 37))
LoG_edge1[LoG_edge1 > 255] = 255
LoG_edge1[LoG_edge1 < 0] = 0
LoG_edge1 = LoG_edge1.astype(np.uint8)

LoG_edge2 = LoG(img1, 2, (11, 11))
LoG_edge2[LoG_edge2 > 255] = 255
LoG_edge2[LoG_edge2 < 0] = 0
LoG_edge2 = LoG_edge2.astype(np.uint8)


# 显示图像
plt.rcParams['font.family'] = ['SimHei']
plt.suptitle('边缘检测')
plt.tight_layout()  # 自动调整子图

# 原图灰度图
plt.subplot(6, 3, 1)  # 6行3列,第1个子图
plt.title('原图灰度图')
plt.imshow(img, cmap='gray')
plt.axis('off')  # 关闭坐标轴

# sobel 边缘检测
plt.subplot(6, 3, 4)  # 6行3列,第4个子图
plt.title('sobel 边缘检测')
plt.imshow(edges, cmap='gray')
plt.axis('off')  # 关闭坐标轴

# sobel 水平方向边缘检测
plt.subplot(6, 3, 5)  # 6行3列,第5个子图
plt.title('sobel 水平方向边缘检测')
plt.imshow(edgesh, cmap='gray')
plt.axis('off')  # 关闭坐标轴

# sobel 竖直方向边缘检测
plt.subplot(6, 3, 6)
plt.title('sobel 竖直方向边缘检测')
plt.imshow(edgesv, cmap='gray')
plt.axis('off')  # 关闭坐标轴


# roberts算子
plt.subplot(6, 3, 7)
plt.title('Roberts算子')
plt.imshow(edges_roberts, cmap='gray')
plt.axis('off')  # 关闭坐标轴


# prewitt算子
plt.subplot(6, 3, 10)
plt.title('prewitt算子')
plt.imshow(edges_prewitt, cmap='gray')
plt.axis('off')  # 关闭坐标轴

# prewitt 水平
plt.subplot(6, 3, 11)
plt.title('prewitt 水平方向边缘检测')
plt.imshow(edges_prewitt_h, cmap='gray')
plt.axis('off')  # 关闭坐标轴

# prewitt 竖直
plt.subplot(6, 3, 12)
plt.title('prewitt 竖直方向边缘检测')
plt.imshow(edges_prewitt_v, cmap='gray')
plt.axis('off')  # 关闭坐标轴


# canny算子
plt.subplot(6, 3, 13)
plt.title('canny算子')
plt.imshow(edges_canny, cmap='gray')
plt.axis('off')  # 关闭坐标轴


# 高斯拉普拉斯
plt.subplot(6, 3, 16)
plt.title('高斯拉普拉斯算子1')
plt.imshow(LoG_edge, cmap='gray')
plt.axis('off')  # 关闭坐标轴

plt.subplot(6, 3, 17)
plt.title('高斯拉普拉斯算子2')
plt.imshow(LoG_edge1, cmap='gray')
plt.axis('off')  # 关闭坐标轴

plt.subplot(6, 3, 18)
plt.title('高斯拉普拉斯算子3')
plt.imshow(LoG_edge2, cmap='gray')
plt.axis('off')  # 关闭坐标轴


plt.show()
