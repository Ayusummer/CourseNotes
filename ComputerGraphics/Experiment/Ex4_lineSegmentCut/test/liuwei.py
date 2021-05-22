# -*- coding : utf-8 -*-
# @Time      : 2021/5/21 13:18
# @Author    : 深入灵魂的热爱
# @File      : liuwei.py
# @Software  : PyCharm
# @Function  : 
# @ChangeLog :
import turtle
import math
import time

LEFT = 1  # 0001
RIGHT = 2  # 0010
BOTTOM = 4  # 0100
TOP = 8  # 1000


# 编码
def encode(x, y):
    c = 0
    if x < xl:
        c = c | LEFT
    if x > xr:
        c = c | RIGHT
    if y < yb:
        c = c | BOTTOM
    if y > yt:
        c = c | TOP
    return c


# 以(x,y)为底点画一个半径为r的圆
def draw(x, y, r):
    turtle.color('red')  # 画笔为红色
    turtle.penup()  # 提笔
    turtle.goto(x, y)  # 在指定坐标位置抬笔
    turtle.pendown()  # 落笔
    turtle.circle(r)


# 用颜色为color的笔触画条(x,y)到(ex,ey)的线段
def join(x, y, ex, ey, color):  # 连接线段
    turtle.color(color)
    turtle.penup()
    turtle.goto(x, y)
    turtle.pendown()
    turtle.goto(ex, ey)


# 编码裁剪方案
def CohenSutherland(x1, y1, x2, y2):
    code1 = encode(x1, y1)  # 线段端点1，线段端点2
    code2 = encode(x2, y2)
    outcode = code1  # 假设outcode是总在窗口外的那个端点
    x, y = 0, 0
    area = False  # 设置一个是否满足条件的区分标志
    while True:
        if (code2 | code1) == 0:
            area = True  # 线段完全在窗口内部
            break
        if (code1 & code2) != 0:  # 简弃之
            break  # 在外部
        if code1 == 0:  # 如果有一个端点在线段内部，开始求交点
            outcode = code2  # 交换两个端点
        if (LEFT & outcode) != 0:  # 与窗口左边界相交，求交点
            x = xl
            y = y1 + (y2 - y1) * (xl - x1) / (x2 - x1)  # 赋给新点
        elif (RIGHT & outcode) != 0:
            x = xr
            y = y1 + (y2 - y1) * (xr - x1) / (x2 - x1)
        elif (BOTTOM & outcode) != 0:
            y = yb
            x = x1 + (x2 - x1) * (yb - y1) / (y2 - y1)
        elif (TOP & outcode) != 0:
            y = yt
            x = x1 + (x2 - x1) * (yt - y1) / (y2 - y1)
        # x = int(x)  # 转换为整型
        # y = int(y)
        if outcode == code1:
            x1 = x
            y1 = y
            code1 = encode(x, y)
        else:
            x2 = x
            y2 = y
            code2 = encode(x, y)
    if area:  # 若满足条件即可划线
        join(x1, y1, x2, y2, 'green')  # 这里传递的点的坐标必须是整型，否则出错?
    return


if __name__ == '__main__':
    rid = int(turtle.textinput('输入', '输入半径'))
    xl = 0
    xr = rid
    yb = 0
    yt = rid  # 窗口的边界值

    # turtle.setup(width=500, height=500)
    turtle.speed(0)     # 0表示最快
    # draw(0,0,300)
    xlist = []
    ylist = []

    for i in range(0, 10):
        xlist.append(rid * math.cos(math.pi / 5 * i))
        ylist.append(rid * math.sin(math.pi / 5 * i))
        # print(12*i,' R == ',i*15);
        # draw(0,(i+1)*-(rid/30),(i+1)*(rid/30));

    for i in range(0, xlist.__len__()):
        for j in range(0, xlist.__len__()):
            CohenSutherland(xlist[i], ylist[i], xlist[j], ylist[j])

    # 画出矩形框
    join(0, 0, rid, 0, 'black')
    join(0, 0, 0, rid, 'black')
    join(0, rid, rid, rid, 'black')
    join(rid, 0, rid, rid, 'black')

    time.sleep(40)
