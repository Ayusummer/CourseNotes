# -*- coding: utf-8 -*-
# @Time    : 2021/4/10 15:33
# @Author  : 咸鱼型233
# @File    : cv2_contrast_brightness_2.py
# @Software: PyCharm
# @Function:
import cv2
import numpy as np


def contrast_img(img1, c, b):  # 亮度就是每个像素所有通道都加上b
    rows, cols, channels = img1.shape

    # 新建全零(黑色)图片数组:np.zeros(img1.shape, dtype=uint8)
    blank = np.zeros([rows, cols, channels], img1.dtype)
    dst = cv2.addWeighted(img1, c, blank, 1 - c, b)
    cv2.imshow('original_img', img)
    cv2.imshow("contrast_img", dst)


img = cv2.imread("../resource/pic/lena_gray.jpg", cv2.IMREAD_COLOR)
contrast_img(img, 1.3, -200)
cv2.waitKey(0)
cv2.destroyAllWindows()