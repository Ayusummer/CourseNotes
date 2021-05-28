# -*- coding : utf-8 -*-
# @Time      : 2021/5/26 11:28
# @Author    : 咸鱼型233
# 原作者      : https://www.bug234.com/article/51
# @File      : face_recognition.py
# @Software  : PyCharm
# @Function  : 
# @ChangeLog :
import matplotlib.pyplot as plt
import cv2
from config import path_baqiao
from config import path_haarcascade


# cv2 读图并返回转化成的灰度图像
def pic_gray(image):
    img_read = cv2.imread(image)
    img_read = cv2.cvtColor(img_read, cv2.COLOR_BGR2RGB)
    return img_read


# plt显示图像
def pic_show(image):
    plt.axis('off')
    plt.imshow(image)
    plt.show()


image_son = pic_gray(path_baqiao)
# pic_show(image_son)

detector = cv2.CascadeClassifier(path_haarcascade)

# Parameters:
# cascade      – Haar classifier cascade (OpenCV 1.x API only). It can be loaded from XML or YAML file using Load(). When the cascade is not needed anymore, release it using cvReleaseHaarClassifierCascade(&cascade).
# image        – Matrix of the type CV_8U containing an image where objects are detected.
# objects      – Vector of rectangles where each rectangle contains the detected object.
# scaleFactor  – 每次缩小图像的比例 每次检测都会缩小一次图像
# minNeighbors – 匹配成功的所需矩阵框数量 默认3
# flags        – Parameter with the same meaning for an old cascade as in the function cvHaarDetectObjects. It is not used for a new cascade.
# minSize      – 匹配人脸的最小范围
# maxSize      – 匹配人脸的最大范围

rects = detector.detectMultiScale(image_son,
                                  scaleFactor=1.1,
                                  minNeighbors=2,
                                  minSize=(10, 10),
                                  flags=cv2.CASCADE_SCALE_IMAGE)

for (x, y, w, h) in rects:
    # 根据坐标画矩形框  rectangle参数 pt1:矩形的顶点(x,y)  pt2:矩形的顶点pt1相反(x+w,y+h)。
    cv2.rectangle(image_son, (x, y), (x + w, y + h), (0, 255, 0), 2)

pic_show(image_son)
