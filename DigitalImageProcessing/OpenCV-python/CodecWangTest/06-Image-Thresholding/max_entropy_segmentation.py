# -*- coding: utf-8 -*-
# @Time    : 2021/4/18 22:41
# @Author  : 咸鱼型233
# @File    : max_entropy_segmentation.py
# @Software: PyCharm
# @Function:
import numpy as np
import cv2
import os

# 原图路径定义
file_path_rice_Ear = os.path.abspath(os.path.join(os.path.dirname(__file__),
                                                  '../../../resource/pic/riceEar/RiceEar1.png'))


def segment(img):
    """
    最大熵分割
    :param img:
    :return:
    """

    def calculate_current_entropy(hist, threshold):
        data_hist = hist.copy()
        background_sum = 0.
        target_sum = 0.
        for i in range(256):
            if i < threshold:  # 累积背景
                background_sum += data_hist[i]
            else:  # 累积目标
                target_sum += data_hist[i]
        background_ent = 0.
        target_ent = 0.
        for i in range(256):
            if i < threshold:  # 计算背景熵
                if data_hist[i] == 0:
                    continue
                ratio1 = data_hist[i] / background_sum
                background_ent -= ratio1 * np.log2(ratio1)
            else:
                if data_hist[i] == 0:
                    continue
                ratio2 = data_hist[i] / target_sum
                target_ent -= ratio2 * np.log2(ratio2)
        return target_ent + background_ent

    def max_entropy_segmentation(img):
        channels = [0]
        hist_size = [256]
        prange = [0, 256]
        hist = cv2.calcHist(img, channels, None, hist_size, prange)
        hist = np.reshape(hist, [-1])
        max_ent = 0.
        max_index = 0
        for i in range(256):
            cur_ent = calculate_current_entropy(hist, i)
            if cur_ent > max_ent:
                max_ent = cur_ent
                max_index = i
        ret, th = cv2.threshold(img, max_index, 255, cv2.THRESH_BINARY)
        return th

    img = max_entropy_segmentation(img)
    return img


if __name__ == "__main__":
    img = cv2.imread(file_path_rice_Ear)
    img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    res = segment(img)
    cv2.imshow("max_entropy_segmentation", res)
    cv2.waitKey()
