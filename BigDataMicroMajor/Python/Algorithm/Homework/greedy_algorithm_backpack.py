# -*- coding: utf-8 -*-
# @Time    : 2021/12/28 22:46
# @Author  : 咸鱼型233
# @File    : greedy_algorithm_backpack.py
# @Software: PyCharm
# @Function: 贪心算法解背包问题
from numpy.random import randint  # 用于生成随机数组

n = randint(1, 10)  # 生成一个10以内的物品数
w = randint(1, 10, n)  # 生成一个n个元素的物品重量数组
v = randint(5, 15, n)  # 生成一个n个元素的物品价值数组
c = randint(min(w) + 1, sum(w))  # 背包容量应当是大于物品最小重量并且小于物品总重量的值
print("共有{0}个物品,背包容量为{1}".format(n, c))
print("物品重量数组:\n{0}\n物品价值数组:\n{1}\n".format(w, v))

# 各物品价格/体重
v_val = list()

# 计算价格与体重之比
for i in range(n):
    v_val.append([v[i] / w[i], i])

# 冒泡排序
# 遍历所有数组元素
for i in range(n):
    for j in range(0, n-1):
        if v_val[j][0] > v_val[j + 1][0]:
            v_val[j], v_val[j + 1] = v_val[j + 1], v_val[j]
print("价重比数组:{0}".format(v_val))

sum=0   # 重量计算累加值
sum_value = 0
select=list()   # 最终选择物品序号
for i in range(n-1,-1,-1):
    if sum+w[v_val[i][1]]<c:
        select.append(v_val[i][1]+1)
        sum = sum+w[i]
        sum_value += v[i]
    else:
        if sum!=c:
            part_per = (c-sum)/w[v_val[i][1]]
            sum = c
            sum_value += part_per*v[i]
            str_last = "{0}".format(v_val[i][1]+1)+"(取{0}％)".format(100*part_per)

print("应选择的物品序号为:{0}{1}".format(select,str_last))

