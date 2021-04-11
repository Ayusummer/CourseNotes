# -*- coding: utf-8 -*-
# @Time    : 2021/4/7 15:28
# @Author  : 咸鱼型233
# @File    : 1.2_save_img.py
# @Software: PyCharm
# @Function:
import cv2

# 先定义窗口，后显示图片
cv2.namedWindow('lena2')
# 加载灰度图
lena = cv2.imread('../../resource/pic/lena.jpg', 0)
cv2.imshow('lena2', lena)
cv2.imwrite('../../resource/pic/lena_gray.jpg', lena)
cv2.waitKey(0)  # 等待窗口关闭
