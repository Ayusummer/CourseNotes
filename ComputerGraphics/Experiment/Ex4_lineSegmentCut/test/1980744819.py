# -*- coding : utf-8 -*-
# @Time      : 2021/5/21 9:57
# @Author    : 咸鱼型233
# @File      : 1980744819.py
# @Software  : PyCharm
# @Function  : 
# @ChangeLog :
from PIL import ImageDraw
from PIL import Image

sz = (1080, 720)
blk = (0, 0, 0)
wt = (255, 255, 255)
INSIDE = 0
LEFT = 1
RIGHT = 2
BOTTOM = 4
TOP = 8
Xmin = 0
Ymin = 0
Xmax = 1079
Ymax = 719


def code_outcode(x, y):
    code = 0
    if x < Xmin:
        code |= LEFT
    elif x > Xmax:
        code |= RIGHT
    if y < Ymin:
        code |= TOP
    elif y > Ymax:
        code |= BOTTOM
    return code


def judge_and_draw(x1, y1, x2, y2, im):
    outcode0 = code_outcode(x1, y1)
    outcode1 = code_outcode(x2, y2)
    flag = False
    while True:
        if outcode0 == 0 and outcode1 == 0:
            flag = True
            break
        elif outcode0 & outcode1 != 0:
            break
        else:
            outcode = 0
            if outcode0 != 0:
                outcode = outcode0
            else:
                outcode = outcode1
            if outcode & TOP:
                x = x1 + (x2 - x1) * (Ymin - y1) / (y2 - y1)
                y = Ymin
            elif outcode & BOTTOM:
                x = x1 + (x2 - x1) * (Ymax - y1) / (y2 - y1)
                y = Ymax
            elif outcode & RIGHT:
                y = y1 + (y2 - y1) * (Xmax - x1) / (x2 - x1)
                x = Xmax
            elif outcode & LEFT:
                y = y1 + (y2 - y1) * (Xmin - x1) / (x2 - x1)
                x = Xmin
            if outcode == outcode0:
                x1 = x
                y1 = y
                outcode0 = code_outcode(x1, y1)
            else:
                x2 = x
                y2 = y
                outcode1 = code_outcode(x2, y2)

    if flag:
        tp = ImageDraw.Draw(im)
        tp.line((x1, y1, x2, y2), blk)
        im.show()


if __name__ == "__main__":
    im = Image.new("RGB", sz, wt)
    # im.show()
    (x1, y1, x2, y2) = map(int, input("please input start point and end point :").split(' '))
    judge_and_draw(x1, y1, x2, y2, im)