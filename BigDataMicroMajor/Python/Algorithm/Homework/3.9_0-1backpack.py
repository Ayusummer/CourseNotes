# -*- coding: utf-8 -*-
# @Time    : 2021/12/25 9:19
# @Author  : 咸鱼型233
# @File    : 3.9_0-1backpack.py
# @Software: PyCharm
# @Function: 动态规划法解0-1背包问题
from numpy.random import randint  # 用于生成随机数组


def bag(n, c, w, v):
    res = [[0 for j in range(c + 2)] for i in range(n + 1)]
    res[0][0] = ""
    for j in range(1, c + 2):
        res[0][j] = j - 1
    for i in range(1, n + 1):
        res[i][0] = i;
    for j in range(1, c + 2):
        if j - 1 < w[n - 1]:
            res[n][j] = 0
        else:
            res[n][j] = v[n - 1]
    for i in range(n - 1, 0, -1):
        for j in range(1, c + 2):
            if j-1 < w[i - 1]:
                res[i][j] = res[i + 1][j]
            else:
                res[i][j] = max(res[i + 1][j], res[i + 1][j - w[i - 1]] + v[i - 1])
    for i in range(n + 1):
        print(res[i])
    return res


def show(n, c, w, res):
    print('最大价值为:', res[1][c])
    x = [False for i in range(n+1)]
    j = c
    for i in range(1, n):
        if res[i][j] > res[i + 1][j]:
            x[i] = True
            j -= w[i - 1]
    if res[n][j] > 0:
        x[n] = True
    print('选择的物品为:')
    for i in range(n):
        if x[i]:
            print('第', i, '个,')
    print('')


if __name__ == '__main__':
    n = randint(1, 10)  # 生成一个10以内的物品数
    w = randint(1, 10, n)  # 生成一个n个元素的物品重量数组
    v = randint(5, 15, n)  # 生成一个n个元素的物品价值数组
    c = randint(min(w) + 1, sum(w))  # 背包容量应当是大于物品最小重量并且小于物品总重量的值
    print("共有{0}个物品,背包容量为{1}".format(n, c))
    print("物品重量数组:\n{0}\n物品价值数组:\n{1}\n".format(w, v))
    res = bag(n, c, w, v)
    show(n, c, w, res)