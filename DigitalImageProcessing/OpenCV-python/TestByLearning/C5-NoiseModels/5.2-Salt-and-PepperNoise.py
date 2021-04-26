# -*- coding: utf-8 -*-
# @Time    : 2021/4/21 9:41
# @Author  : 咸鱼型233(引自https://www.cnblogs.com/wojianxin/p/12499928.html)
# @File    : 5.2-Salt-and-PepperNoise.py
# @Software: PyCharm
# @Function: 椒盐噪声
import numpy as np
import random
import cv2
from matplotlib import pyplot as plt


def sp_noise(image, prob):
    """

    添加椒盐噪声

    prob:噪声比例

    """

    output = np.zeros(image.shape, np.uint8)
    thres = 1 - prob

    for i in range(image.shape[0]):
        for j in range(image.shape[1]):
            rdn = random.random()
            if rdn < prob:
                output[i][j] = 0
            elif rdn > thres:
                output[i][j] = 255
            else:
                output[i][j] = image[i][j]
    return output


# ========= 函数测试 ======= #
# 读取图像
img = cv2.imread("../../../resource/pic/lena.jpg")
img_plt = img[:, :, ::-1]   # 重新拼合适用于plt显示的图像

# 添加椒盐噪声，噪声比例为 0.02
out1 = sp_noise(img_plt, prob=0.02)

# 显示图像
plt.rcParams['font.family'] = ['SimHei']  # 使用黑体
plt.figure(1)
plt.subplot(121)
plt.axis('off')  # 关闭坐标轴
plt.title('原图')
plt.imshow(img_plt)

plt.subplot(122)
plt.axis('off')
plt.title('添加椒盐噪声')
plt.imshow(out1)

plt.show()
