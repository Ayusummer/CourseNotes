# -*- coding: utf-8 -*-
# @Time    : 2021/4/7 15:28
# @Author  : 咸鱼型233
# @File    : 1.1_read_show_img.py
# @Software: PyCharm
# @Function:
import cv2


lena = cv2.imread('../../resource/pic/lena.jpg')
cv2.imshow('lena', lena)
cv2.waitKey(0)  # 等待窗口关闭


