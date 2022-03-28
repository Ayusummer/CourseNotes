# -*- coding: utf-8 -*-
# @Time    : 2021/1/5 13:23
# @Author  : 咸鱼型233
# @File    : 0-1backpack_branch_restrict.py
# @Software: PyCharm
# @Function: 分支限界法解0-1背包问题
# coding : utf-8
import numpy as np
import Queue
import math

w = [3, 5, 2, 1]  # weight
v = [9, 10, 7, 4]  # value


def test(capacity):
    vec_len = 2 ** (len(v) + 1) - 1  # tree `s size
    vec_v = np.zeros(vec_len)
    vec_w = np.zeros(vec_len)
    vec_w[0] = capacity
    que = Queue.Queue();
    que.put(0)
    best = 0
    while (not que.empty()):
        current = que.get()
        level = int(math.log(current + 1, 2))
        if (vec_v[current] > vec_v[best]):
            best = current

        left = 2 * current + 1  # left child   index
        right = 2 * current + 2  # right child index

        if (left < vec_len and vec_w[current] - w[level] > 0 and vec_v[current] + v[level] > vec_v[best]):
            vec_v[left] = int(vec_v[current] + v[level])
            vec_w[left] = vec_w[current] - w[level]
            que.put(left)
        if (right < vec_len and sum(v[level + 1:-1]) + vec_v[current] > vec_v[best]):
            vec_v[right] = vec_v[current]
            vec_w[right] = vec_w[current]
            que.put(right)
    print(vec_w[best], vec_v[best])


if __name__ == '__main__':
    test(7)
