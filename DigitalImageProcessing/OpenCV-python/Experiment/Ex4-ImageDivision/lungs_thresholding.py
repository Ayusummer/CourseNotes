# -*- coding: utf-8 -*-
# @Time    : 2021/5/9 14:02
# @Author  : 咸鱼型233
# @File    : lungs_thresholding.py
# @Software: PyCharm
# @Function: 
# @ChangeLog
import cv2
import numpy as np

# 导入上级目录里的配置文件中的图像路径
import sys
sys.path.append('../')
from config import path_lungs


# TRIANGLE阈值处理
src = cv2.imread(path_lungs, cv2.IMREAD_GRAYSCALE)

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
