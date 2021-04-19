# -*- coding: utf-8 -*-
# @Time    : 2021/4/18 22:35
# @Author  : 咸鱼型233
# @File    : OTSU_thresholding.py
# @Software: PyCharm
# @Function:
import cv2
import os
import numpy as np

# 原图路径定义
file_path_rice_Ear = os.path.abspath(os.path.join(os.path.dirname(__file__),
                                                  '../../../resource/pic/riceEar/RiceEar1.png'))

# TRIANGLE阈值处理
src = cv2.imread(file_path_rice_Ear, cv2.IMREAD_GRAYSCALE)

triThe = 0
maxval = 255
triThe, dst_tri = cv2.threshold(src, triThe, maxval, cv2.THRESH_OTSU + cv2.THRESH_BINARY)
triThe1, dst_tri1 = cv2.threshold(src, triThe, maxval, cv2.THRESH_OTSU + cv2.THRESH_BINARY_INV)
print(triThe)
print(triThe1)

# 3张图片横向合并（便于对比显示）
tmp = np.hstack((src, dst_tri, dst_tri1))
cv2.imshow("OTSUThresholding", tmp)
cv2.waitKey(0)
cv2.destroyAllWindows()
