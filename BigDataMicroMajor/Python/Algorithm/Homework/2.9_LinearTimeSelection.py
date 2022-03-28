# -*- coding: utf-8 -*-
# @Time    : 2020/12/13 20:13
# @Author  : 咸鱼型233
# @File    : 2.9_LinearTimeSelection.py
# @Software: PyCharm
# @Function: 线性时间选择

import copy  # 用于列表的深拷贝
from numpy.random import randint  # 用于生成随机数组
import numpy as np
from typing import Tuple


# 数组调整函数(以最后一个元素为基准调整数组)
def partition(array: np.ndarray, low: int, high: int) -> int:
    """
    以数组尾部元素(假设为pivot)为基准调整数组,调整后数组样式为:

    [元素<pivot, pivot, 元素>pivot];

    参数
    ------
    array : 待调整数组

    low : 数组起始下标[起始索引]

    high : 数组末尾下标[结束索引]

    return :返回调整后的中间项下标,对应调整前的末尾元素
    """
    index = (low - 1)  # 最小元素索引
    pivot = array[high]

    for j in range(low, high):
        # 当前元素小于或等于 pivot
        if array[j] <= pivot:
            index = index + 1
            array[index], array[j] = array[j], array[index]
    array[index + 1], array[high] = array[high], array[index + 1]
    return index + 1


# 快速排序函数
def quickSort(array: np.ndarray, low: int, high: int) -> None:
    """
    快速排序递增排序一个数组

    参数
    -----------
    array : 待排序数组

    low : 数组首元素下标

    high : 数组尾元素下标

    return :无返回值
    """
    if low < high:
        pi = partition(array, low, high)
        quickSort(array, low, pi - 1)
        quickSort(array, pi + 1, high)


# 数组调整函数(以数组中下标为i_piv的元素为基准调整数组)
def partitionByPiv(array: np.ndarray, low: int, high: int, i_piv: int) -> int:
    """
    以数组中下标为i_piv的元素(假设为pivot)为基准调整数组,调整后数组样式为:

    [元素<pivot, pivot, 元素>pivot];

    参数
    ------
    array : 待调整数组

    low : 数组起始下标[起始索引]

    high : 数组末尾下标[结束索引]

    i_piv : 基准元素在原数组中的下标(索引)

    return :返回调整后的中间项下标,对应pivot
    """
    index = (low - 1)  # 最小元素索引
    pivot = array[i_piv]

    for j in range(low, i_piv):
        # 当前元素小于或等于 pivot
        if array[j] <= pivot:
            index = index + 1
            array[index], array[j] = array[j], array[index]
    for j in range(i_piv + 1, high + 1):
        if array[j] <= pivot:
            index = index + 1
            array[index], array[j] = array[j], array[index]
    array[index + 1], array[i_piv] = array[i_piv], array[index + 1]
    return index + 1


# 冒泡排序
def bubbleSort(arr: np.ndarray, low: int, high: int):
    # 遍历所有数组元素
    for i in range(low, high + 1):
        for j in range(0, high - low - i):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]


# 一趟冒泡
def bubble(arr: np.ndarray, low: int, high: int) -> None:
    """
    一趟从起始索引到终止索引的冒泡

    参数
    ----
    arr : 待冒泡数组

    low : 冒泡起始索引

    high : 冒泡终止索引
    """
    for i in range(low, high - 1):
        if arr[i] > arr[i + 1]:
            arr[i], arr[i + 1] = arr[i + 1], arr[i]


# 线性时间选择函数
def select(array: np.ndarray, low: int, high: int, k: int) -> Tuple[int, np.ndarray]:
    """以每组中位数组成的数列的中位数为基准重排数组并返回重排后数组中基准的下标
    :param array : 待处理数组
    :param low : 数组起始索引
    :param high : 数组结束索引
    :param k : '待寻找的第k小的元素'中的k
    :return : 以每组中位数组成的数列的中位数为基准重排后的数组中基准的下标与值的元组
    """
    # 若数组元素不足5个则直接冒泡排序后返回对应元素
    if high - low < 5:
        bubbleSort(array, low, high)
        return low + k - 1, array[low + k - 1]
    # 若数组元素>=5个
    for i in range(((high - low - 4) // 5) + 1):
        low_tmp = low + 5 * i   # 每组起始索引
        high_tmp = low_tmp + 4  # 每组结束索引
        for j in range(3):
            bubble(array, low_tmp, high_tmp - j)
        array[low + i], array[low_tmp + 2] = array[low_tmp + 2], array[low + i]
    x = select(array, low, low + (high - low - 4) // 5, (high - low + 6) // 10)
    i = partitionByPiv(array, low, high, x[0])
    if k >= j:
        return select(array, low, i, k)
    else:
        return select(array, i + 1, high, k - j)


arr1 = randint(0, 1000, 31)
arr2 = copy.deepcopy(arr1)
print(arr1)
quickSort(arr1, 0, 30)
print("arr1(使用快速排序排序数组):\n{0}".format(arr1))
print("arr2(原数组):\n{0}".format(arr2))
print("该数组中第4小的数值为:{0}".format(select(arr2, 0, 30, 4)[1]))
