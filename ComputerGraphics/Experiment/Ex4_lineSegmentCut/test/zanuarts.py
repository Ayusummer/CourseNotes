# -*- coding : utf-8 -*-
# @Time      : 2021/5/21 9:55
# @Author    : 咸鱼型233
# @File      : zanuarts.py
# @Software  : PyCharm
# @Function  : 
# @ChangeLog :
from tkinter import *

# Defining region codes
INSIDE = 0  # 0000
LEFT = 1  # 0001
RIGHT = 2  # 0010
BOTTOM = 4  # 0100
TOP = 8  # 1000

x_max = 350
y_max = 350
x_min = 50
y_min = 50


def computeCode(x, y):
    code = INSIDE
    if x < x_min:  # to the left of rectangle
        code |= LEFT
    elif x > x_max:  # to the right of rectangle
        code |= RIGHT
    if y < y_min:  # below the rectangle
        code |= BOTTOM
    elif y > y_max:  # above the rectangle
        code |= TOP

    print(code)
    return code


def hitung():
    x1 = float(entry_x1.get())
    y1 = float(entry_y1.get())
    x2 = float(entry_x2.get())
    y2 = float(entry_y2.get())

    my_canvas.create_line(x1, y1, x2, y2, fill='red')
    my_canvas.grid(row=6, column=0)

    # region = [x1, y1, x2, y2]

    code1 = computeCode(x1, y1)
    code2 = computeCode(x2, y2)
    accept = False

    while True:

        # If both endpoints lie within rectangle
        if code1 == 0 and code2 == 0:
            accept = True
            break

        # If both endpoints are outside rectangle
        elif (code1 & code2) != 0:
            break

        # Some segment lies within the rectangle
        else:

            # Line Needs clipping
            # At least one of the points is outside,
            # select it
            x = 1.0
            y = 1.0
            if code1 != 0:
                code_out = code1
            else:
                code_out = code2

                # Find intersection point
            # using formulas y = y1 + slope * (x - x1),
            # x = x1 + (1 / slope) * (y - y1)
            if code_out & TOP:

                # point is above the clip rectangle
                x = x1 + ((x2 - x1) / (y2 - y1)) * (y_max - y1)
                y = y_max

            elif code_out & BOTTOM:

                # point is below the clip rectangle
                x = x1 + ((x2 - x1) / (y2 - y1)) * (y_min - y1)
                y = y_min

            elif code_out & RIGHT:

                # point is to the right of the clip rectangle
                y = y1 + ((y2 - y1) / (x2 - x1)) * (x_max - x1)
                x = x_max

            elif code_out & LEFT:

                # point is to the left of the clip rectangle
                y = y1 + ((y2 - y1) / (x2 - x1)) * (x_min - x1)
                x = x_min

                # Now intersection point x, y is found
            # We replace point outside clipping rectangle
            # by intersection point
            if code_out == code1:
                x1 = x
                y1 = y
                code1 = computeCode(x1, y1)

            else:
                x2 = x
                y2 = y
                code2 = computeCode(x2, y2)

    if accept:
        print("Line accepted from %.2f, %.2f to %.2f, %.2f" % (x1, y1, x2, y2))
        my_canvas.create_line(x1, y1, x2, y2, fill='blue', width=1)
        my_canvas.grid(row=6, column=0)
        # Here the user can add code to display the rectangle
        # along with the accepted (portion of) lines

    else:
        print("Line rejected")

    #   ui


my_window = Tk()
my_window.title("Cohen Sutherland Algorithm by Zanuar")

#   input
Label(my_window, text="Masukan titik x1 : ", fg="black", font="none 12").grid(row=1, column=0, sticky=W)
entry_x1 = Entry(my_window, width=20, bg="white")
entry_x1.grid(row=1, column=0)
Label(my_window, text="Masukan titik y1 : ", fg="black", font="none 12").grid(row=2, column=0, sticky=W)
entry_y1 = Entry(my_window, width=20, bg="white")
entry_y1.grid(row=2, column=0)
Label(my_window, text="Masukan titik x2 : ", fg="black", font="none 12").grid(row=3, column=0, sticky=W)
entry_x2 = Entry(my_window, width=20, bg="white")
entry_x2.grid(row=3, column=0)
Label(my_window, text="Masukan titik y2 : ", fg="black", font="none 12").grid(row=4, column=0, sticky=W)
entry_y2 = Entry(my_window, width=20, bg="white")
entry_y2.grid(row=4, column=0)

#   button
Button(my_window, text="SUBMIT", width=6, command=hitung).grid(row=5, column=0)

#   canvas
my_canvas = Canvas(my_window, width=400, height=400)
my_canvas.grid(row=6, column=0)
my_canvas.create_line(50, 350, 350, 350, fill='black')
my_canvas.create_line(350, 50, 350, 350, fill='black')
my_canvas.create_line(50, 50, 50, 350, fill='black')
my_canvas.create_line(50, 50, 350, 50, fill='black')

my_window.mainloop()