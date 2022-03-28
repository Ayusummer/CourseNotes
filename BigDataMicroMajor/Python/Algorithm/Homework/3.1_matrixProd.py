# -*- coding: utf-8 -*-
# @Time    : 2020/12/20 11:34
# @Author  : 咸鱼型233
# @File    : 3.1_matrixProd.py
# @Software: PyCharm
# @Function: 矩阵连乘问题
import random
from pandas import *

num_matrix = int(input("输入矩阵数："))
matrix = [[0] * 2 for i in range(num_matrix)]
for i in range(num_matrix):  # 生成矩阵
    if i == 0:
        matrix[i][0] = random.randrange(100)
        matrix[i][1] = random.randrange(100)
    else:
        matrix[i][0] = matrix[i - 1][1]
        matrix[i][1] = random.randrange(100)
m = [[0] * num_matrix for i in range(num_matrix)]  # 记录连乘次数
s = [[0] * num_matrix for j in range(num_matrix)]  # 记录括号位置


def MatrixMultiplication(inp):
    for i in range(inp):
        m[i][i] = 0
    for r in range(1, inp):
        for i in range(inp - r):
            j = i + r
            m[i][j] = m[i + 1][j] + matrix[i][0] * matrix[i][1] * matrix[j][1]
            s[i][j] = i + 1
            for k in range(i + 1, j):
                judge = m[i][k] + m[k + 1][j] + matrix[i][0] * matrix[k][1] * matrix[j][1]
                if judge < m[i][j]:
                    m[i][j] = judge
                    s[i][j] = k + 1


def print_matrix(left, right):
    if left == right:
        print("A" + str(left + 1), end='')
    else:
        print("(", end='')
        print_matrix(left, s[left][right] - 1)
        print_matrix(s[left][right], right)
        print(")", end='')


MatrixMultiplication(num_matrix)
dm = DataFrame(m, index=list(range(1, num_matrix + 1)), columns=list(range(1, num_matrix + 1)))
ds = DataFrame(s, index=list(range(1, num_matrix + 1)), columns=list(range(1, num_matrix + 1)))
print(matrix)
print("数乘次数：\n", dm)
print("括号位置：\n", ds)
print("最终结果：")
print_matrix(0, num_matrix - 1)
