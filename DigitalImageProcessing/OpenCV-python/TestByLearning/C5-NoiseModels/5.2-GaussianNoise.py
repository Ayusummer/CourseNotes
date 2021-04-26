# -*- coding: utf-8 -*-
# @Time    : 2021/4/21 9:40
# @Author  : 咸鱼型233
# 引自https://www.cnblogs.com/wojianxin/p/12499928.html
# @File    : 5.2-GaussianNoise.py
# @Software: PyCharm
# @Function: 高斯噪声
import numpy as np
import random
import cv2
from matplotlib import pyplot as plt


def gasuss_noise(image, mean=0, var=0.001):
    """
    添加高斯噪声

    mean : 均值

    var : 方差
    """

    image = np.array(image / 255, dtype=float)
    noise = np.random.normal(mean, var ** 0.5, image.shape)
    out = image + noise
    if out.min() < 0:
        low_clip = -1.
    else:
        low_clip = 0.
    out = np.clip(out, low_clip, 1.0)
    out = np.uint8(out * 255)
    # cv.imshow("gasuss", out)
    return out


# ========= 函数测试 ======= #
# 读取图像
img = cv2.imread("../../../resource/pic/lena.jpg")
img_plt = img[:, :, ::-1]  # 重新拼合适用于plt显示的图像

# 添加高斯噪声，均值为0，方差为0.001
out2 = gasuss_noise(img_plt, mean=0, var=0.001)

# 显示图像
plt.rcParams['font.family'] = ['SimHei']  # 使用黑体
plt.figure(1)
plt.subplot(121)
plt.axis('off')  # 关闭坐标轴
plt.title('原图')
plt.imshow(img_plt)

plt.subplot(122)
plt.axis('off')
plt.title('添加高斯噪声')
plt.imshow(out2)

plt.show()
