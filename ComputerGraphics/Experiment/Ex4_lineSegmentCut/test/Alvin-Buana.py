# -*- coding: utf-8 -*-
"""
Created on Thu Feb 25 15:58:54 2021
@author: Alvin Buana
"""

# -*- coding: utf-8 -*-
"""
Created on Sun Feb 21 23:41:21 2021
@author: Alvin Buana
"""

from tkinter import *
from tkinter import filedialog

current_x, current_y = 0, 0
coord_x1, coord_y1, coord_x2, coord_y2 = 0, 0, 0, 0


class Clipping():
    def __init__(self, root):
        self.root = root
        self.root.title("Clipping Application")
        self.root.geometry("800x520")
        self.root.configure(background='white')
        self.root.resizable(0, 0)
        self.pen_color = "black"
        self.eraser_color = "white"
        self.rect = None
        self.click = 0
        self.line = []
        self.line2 = []
        self.square = []
        self.isClip = False
        self.isCropOutside = 0
        self.isCropInside = 0
        self.line3 = []
        self.line4 = []
        self.acc = None
        self.dec = None
        self.tick = 0
        self.dotIn = []
        self.dotOut = []
        self.lineIn = []
        self.lineOut = []

        menubar = Menu(root)
        filemenu = Menu(menubar, tearoff=0)
        filemenu.add_command(label="Clear", command=self.clear)
        filemenu.add_command(label="Open", command=self.openFile)
        filemenu.add_command(label="Save", command=self.save_file)
        filemenu.add_command(label="Refresh", command=self.onlyrefresh)
        filemenu.add_separator()
        filemenu.add_command(label="Exit", command=root.quit)
        menubar.add_cascade(label="File", menu=filemenu)
        menubar.add_command(label="About Us",
                            command=lambda: self.popupmsg("This Program is created by Alvin, Farel, and Ribka"))
        root.config(menu=menubar)

        self.select_button = Button(self.root, text="SELECT", bd=4, bg='white', command=self.onClick, width=8,
                                    relief=RIDGE)
        self.select_button.place(x=5, y=10)

        self.delete_button = Button(self.root, text="DELETE", bd=4, bg='white', command=self.onDelete, width=8,
                                    relief=RIDGE)
        self.delete_button.place(x=5, y=45)

        self.dot_button = Button(self.root, text="DOT", bd=4, bg='white', command=self.onlydot, width=8, relief=RIDGE)
        self.dot_button.place(x=5, y=95)

        self.line_button = Button(self.root, text="LINE", bd=4, bg='white', command=self.onlyline, width=8,
                                  relief=RIDGE)
        self.line_button.place(x=5, y=130)

        self.clip_button = Button(self.root, text="CLIP", bd=4, bg='white', command=self.selectRect, width=8,
                                  relief=RIDGE)
        self.clip_button.place(x=5, y=180)
        self.cropInside_button = Button(self.root, text="INSIDE", bd=4, bg='white', command=self.cropInside,
                                        width=8,
                                        relief=RIDGE)
        self.cropInside_button.place(x=5, y=230)
        self.cropOutside_button = Button(self.root, text="OUTSIDE", bd=4, bg='white', command=self.cropOutside,
                                         width=8,
                                         relief=RIDGE)
        self.cropOutside_button.place(x=5, y=265)

        self.canvas = Canvas(self.root, bg='white', bd=5, relief=GROOVE, height=500, width=700)
        self.canvas.place(x=80, y=0)

    def openFile(self):
        filepath = filedialog.askopenfilename()
        file = open(filepath, 'r')
        self.clear()
        hu = int(file.readline())
        for i in range(hu):
            data = file.readline()
            data = data.split(" ")
            a = int(data[0])
            b = int(data[1])
            c = int(data[2])
            d = int(data[3])
            if a == c:
                self.canvas.create_oval(a - 5, b - 5, c + 5, d + 5, fill="black", tags="line")
            else:
                self.canvas.create_line(a, b, c, d, tags="line")

            temp = [a, b, c, d]
            self.line.append(temp)
        file.close()

    def save_file(self):
        f = filedialog.asksaveasfile(mode='w', defaultextension='.txt',
                                     )
        if f is None:
            return
        listLine = len(self.line)
        f.write(str(listLine) + "\n")
        for index in range(listLine):
            f.write(
                str(self.line[index][0]) + " " + str(self.line[index][1]) + " " + str(self.line[index][2]) + " " + str(
                    self.line[index][3]) + "\n")
        f.close()

    def popupmsg(self, msg):
        popup = Tk()
        popup.wm_title("About the Program")
        label = Label(popup, text=msg)
        label.pack(side="top", fill="x", pady=10)
        B1 = Button(popup, text="Okay", command=popup.destroy)
        B1.pack()
        popup.mainloop()

    def onlydot(self):
        self.canvas.delete("square")
        self.select_button.configure(relief=RIDGE)
        self.delete_button.configure(relief=RIDGE)
        self.dot_button.configure(relief=SUNKEN)
        self.line_button.configure(relief=RIDGE)
        self.clip_button.configure(relief=RIDGE)
        self.cropOutside_button.configure(relief=RIDGE)
        self.cropInside_button.configure(relief=RIDGE)

        self.canvas.bind('<Button-1>', self.nudot)
        self.canvas.bind("<B1-Motion>", self.none)
        self.canvas.bind("<ButtonRelease-1>", self.dot_release)

    def none(self, event):
        pass

    def nudot(self, event):
        global current_x, current_y
        current_x, current_y = event.x, event.y

        x1, y1 = (event.x - 5), (event.y - 5)
        x2, y2 = (event.x + 5), (event.y + 5)
        self.line2.append(self.canvas.create_oval(x1, y1, x2, y2, fill="black", tags="line"))
        self.passdot(x1, y1)

    def passdot(self, x1, y1):
        temp = [x1, y1, x1, y1]
        self.line.append(temp)

    def dot_release(self, event):
        if self.rect is not None:
            self.cohen(self.line)

    def locate_xy_2(self, event):
        global current_x, current_y
        self.canvas.delete(self.rect)
        self.rect = self.canvas.create_rectangle(0, 0, 1, 1, dash=(1, 1), tags="square2")
        current_x, current_y = event.x, event.y

    def onlyrefresh(self):
        global rect
        self.canvas.delete(self.rect)
        self.rect = None
        self.canvas.itemconfigure("line", fill='black', width=0)
        self.canvas.itemconfigure("line2", fill='black', width=0)
        self.canvas.itemconfigure("line3", fill='black', width=0)
        self.canvas.delete("square")

        self.canvas.bind('<Button-1>', self.locate_xy_2)
        self.canvas.bind("<B1-Motion>", self.selectime)
        self.canvas.bind("<ButtonRelease-1>", self.releaseevent2)

    def releaseevent2(self, event):
        self.square.clear()
        new_square = [current_x, current_y, self.nux, self.nuy]

        self.square.append(new_square)
        self.cohen(self.line)
        self.isClip = True
        self.tick = 1
        pass

    def passvalue(self, linee, lineee):
        for i in range(len(lineee)):
            linee.append(lineee[i])

    def cropOutside(self):
        # self.isCropOutside = 1
        self.select_button.configure(relief=RIDGE)
        self.delete_button.configure(relief=RIDGE)
        self.dot_button.configure(relief=RIDGE)
        self.line_button.configure(relief=RIDGE)
        self.clip_button.configure(relief=RIDGE)
        self.cropOutside_button.configure(relief=SUNKEN)
        self.cropInside_button.configure(relief=RIDGE)

        if self.rect is None:
            pass
        else:
            self.canvas.delete("line2")
            self.line.clear()
            self.recreateline(self.line, self.lineOut)
            self.linebaru(self.lineOut)
            self.lineIn.clear()

    def linebaru(self, linein):
        self.canvas.delete("line")
        self.canvas.delete("line2")
        self.line2.clear()
        for i in range(len(linein)):
            if linein[i][0] == linein[i][2]:
                self.line2.append(
                    self.canvas.create_oval(linein[i][0], linein[i][1], linein[i][2] + 10, linein[i][3] + 10,
                                            fill="Black", tags="line"))
            else:
                self.line2.append(
                    self.canvas.create_line(linein[i][0], linein[i][1], linein[i][2], linein[i][3], tags="line"))
            # print(self.line2)

    def recreateline(self, line, linein):
        for i in range(len(linein)):
            line.append(linein[i])

    def cropInside(self):
        self.select_button.configure(relief=RIDGE)
        self.delete_button.configure(relief=RIDGE)
        self.dot_button.configure(relief=RIDGE)
        self.line_button.configure(relief=RIDGE)
        self.clip_button.configure(relief=RIDGE)
        self.cropOutside_button.configure(relief=RIDGE)
        self.cropInside_button.configure(relief=SUNKEN)

        if self.rect is None:
            pass
        else:
            self.line.clear()
            self.recreateline(self.line, self.lineIn)
            self.linebaru(self.lineIn)
            self.lineOut.clear()

    def onDelete(self):
        self.canvas.delete("square")
        self.canvas.delete("square2")
        self.canvas.delete("line2")
        self.square.clear()
        self.select_button.configure(relief=RIDGE)
        self.delete_button.configure(relief=SUNKEN)
        self.dot_button.configure(relief=RIDGE)
        self.line_button.configure(relief=RIDGE)
        self.clip_button.configure(relief=RIDGE)
        self.cropOutside_button.configure(relief=RIDGE)
        self.cropInside_button.configure(relief=RIDGE)

        self.canvas.bind("<Button-1>", self.onDelete2)
        self.canvas.bind("<B1-Motion>", self.none)

    def onDelete2(self, event):
        item = self.canvas.find_closest(event.x, event.y)

        for i in range(len(self.line)):
            # print(self.canvas.coords(item))
            # print(self.line[i])
            if self.canvas.coords(item) == self.line[i]:
                self.canvas.delete(item)
                del self.line[i]
                break
            if self.canvas.coords(item)[3] == self.line[i][3] + 10:
                self.canvas.delete(item)
                del self.line[i]
                break

    def onClick(self):
        self.canvas.delete("square2")
        self.canvas.delete("line2")
        self.canvas.delete("line3")
        self.select_button.configure(relief=SUNKEN)
        self.delete_button.configure(relief=RIDGE)
        self.dot_button.configure(relief=RIDGE)
        self.line_button.configure(relief=RIDGE)
        self.clip_button.configure(relief=RIDGE)
        self.cropOutside_button.configure(relief=RIDGE)
        self.cropInside_button.configure(relief=RIDGE)

        self.canvas.bind('<Button-1>', self.selectime2)
        self.canvas.bind("<B1-Motion>", self.click2)
        self.canvas.bind("<ButtonRelease-1>", self.releaseevent3)

    def click2(self, event):
        global current_x, current_y
        current_x, current_y = event.x, event.y

        self.x1 = (event.x - 15)
        self.y1 = (event.y - 15)
        self.x2 = (event.x + 15)
        self.y2 = (event.y + 15)

    def selectime2(self, event):
        global current_x, current_y
        current_x, current_y = event.x, event.y
        self.x1 = (event.x - 15)
        self.y1 = (event.y - 15)
        self.x2 = (event.x + 15)
        self.y2 = (event.y + 15)
        self.canvas.delete("square")

    def releaseevent3(self, event):
        self.square.clear()
        new_square = [self.x1, self.y1, self.x2, self.y2]
        self.square.append(new_square)
        self.square.append(self.canvas.create_rectangle(self.x1, self.y1, self.x2, self.y2, tags="square"))
        # print("select", self.square)
        self.cohen2(self.line)

    def cohen2(self, lines):
        pos = self.clip_position()
        top = 8
        bottom = 4
        left = 1
        right = 2
        for i in range(len(lines)):
            x1 = lines[i][0]
            y1 = lines[i][1]
            x2 = lines[i][2]
            y2 = lines[i][3]
            post = self.repeat(x1, y1)
            post1 = self.repeat(x2, y2)
            x, y = 0, 0

            while post & post1 == 0 and post | post1 != 0:
                changer = [post, post1]
                c = max(changer)
                M = (y2 - y1) / (x2 - x1)
                if c & top != 0:
                    x = 1 / M * (pos[3] - y1) + x1
                    y = pos[3]
                elif c & bottom != 0:
                    x = 1 / M * (pos[2] - y1) + x1
                    y = pos[2]

                elif c & left != 0:
                    y = M * (pos[0] - x1) + y1
                    x = pos[0]

                elif c & right != 0:
                    y = M * (pos[1] - x1) + y1
                    x = pos[1]

                if c == post:
                    x1 = int(x)
                    y1 = int(y)
                    post = self.repeat(x1, y1)

                if c == post1:
                    x2 = int(x)
                    y2 = int(y)
                    post1 = self.repeat(x2, y2)

            if post & post1 == 0 and post | post1 == 0:
                # print("Dot accepted")
                self.change_color_acc2(self.line2[i])
            elif post | post1 != 0 and post & post1 != 0:
                # print("dot Reject")
                self.change_color_rejected2(self.line2[i])

    def change_color_rejected2(self, line):
        self.dec = self.canvas.itemconfigure(line, width=0)

    def change_color_acc2(self, line):
        self.acc = self.canvas.itemconfigure(line, width=5)

    def clear(self):
        self.canvas.delete("all")
        self.line.clear()
        self.line3.clear()
        self.line2.clear()
        self.rect = None
        self.tick = 0

    def locate_xy(self, event):
        global current_x, current_y

        current_x, current_y = event.x, event.y

    def clip_position(self):
        clip_pos = []

        if self.square[0][0] > self.square[0][2]:
            clip_pos.append(self.square[0][2])
            clip_pos.append(self.square[0][0])
        else:
            clip_pos.append(self.square[0][0])
            clip_pos.append(self.square[0][2])
        if self.square[0][1] > self.square[0][3]:
            clip_pos.append(self.square[0][3])
            clip_pos.append(self.square[0][1])
        else:
            clip_pos.append(self.square[0][1])
            clip_pos.append(self.square[0][3])
        return clip_pos  # LEFT RIGHT BOTTOM TOP

    def repeat(self, x1, y1):
        pos = self.clip_position()
        post = 0
        top = 8
        bottom = 4
        left = 1
        right = 2
        if x1 < pos[0]:  # LEFT
            post += left
        elif x1 > pos[1]:  # RIGHT
            post += right
        if y1 < pos[2]:  # BOTTOM
            post += bottom
        elif y1 > pos[3]:  # TOP
            post += top
        return post

    def cohen(self, lines):
        # self.canvas.delete("line")
        self.canvas.itemconfigure("line", fill='black', width=0)
        self.canvas.delete("line2")
        self.canvas.delete("line3")
        self.lineOut.clear()
        self.lineIn.clear()

        pos = self.clip_position()
        top = 8
        bottom = 4
        left = 1
        right = 2
        for i in range(len(lines)):
            x1 = lines[i][0]
            y1 = lines[i][1]
            x2 = lines[i][2]
            y2 = lines[i][3]

            x1_2 = lines[i][0]
            y1_2 = lines[i][1]
            x2_2 = lines[i][2]
            y2_2 = lines[i][3]

            post = self.repeat(x1, y1)
            post1 = self.repeat(x2, y2)
            x, y = 0, 0

            while post & post1 == 0 and post | post1 != 0:
                changer = [post, post1]
                c = max(changer)
                M = (y2 - y1) / (x2 - x1)
                if c & top != 0:
                    x = 1 / M * (pos[3] - y1) + x1
                    y = pos[3]
                elif c & bottom != 0:
                    x = 1 / M * (pos[2] - y1) + x1
                    y = pos[2]

                elif c & left != 0:
                    y = M * (pos[0] - x1) + y1
                    x = pos[0]

                elif c & right != 0:
                    y = M * (pos[1] - x1) + y1
                    x = pos[1]

                if c == post:
                    x1 = int(x)
                    y1 = int(y)
                    post = self.repeat(x1, y1)

                if c == post1:
                    x2 = int(x)
                    y2 = int(y)
                    post1 = self.repeat(x2, y2)

            if post & post1 == 0 and post | post1 == 0:

                if x1_2 != x2_2:
                    self.line4.append(self.canvas.create_line(x1, y1, x2, y2, fill="red", width=3, tags="line2"))

                    if x1 != x2:
                        temp = [x1, y1, x2, y2]
                        self.lineIn.append(temp)

                    if x1_2 != x1:
                        temp = [x1_2, y1_2, x1, y1]
                        self.lineOut.append(temp)
                    if x2_2 != x2:
                        temp = [x2_2, y2_2, x2, y2]
                        self.lineOut.append(temp)
                else:
                    self.dotIn.append(
                        self.canvas.create_oval(x1_2, y1_2, x2_2 + 10, y2_2 + 10, fill="red", tags="line2"))
                    temp = [x1, y1, x2, y2]
                    self.lineIn.append(temp)


            elif post | post1 != 0 and post & post1 != 0:
                if x1_2 != x2_2:

                    temp = [x1_2, y1_2, x2_2, y2_2]
                    self.lineOut.append(temp)
                else:
                    self.dotIn.append(self.canvas.create_oval(x1_2, y1_2, x2_2 + 10, y2_2 + 10, tags="line"))
                    temp = [x1_2, y1_2, x2_2, y2_2]
                    # print("Dot is avaiable")
                    self.lineOut.append(temp)

    def selectRect(self):
        global rect
        self.canvas.delete("square")
        self.select_button.configure(relief=RIDGE)
        self.delete_button.configure(relief=RIDGE)
        self.dot_button.configure(relief=RIDGE)
        self.line_button.configure(relief=RIDGE)
        self.clip_button.configure(relief=SUNKEN)
        self.cropOutside_button.configure(relief=RIDGE)
        self.cropInside_button.configure(relief=RIDGE)

        self.canvas.bind('<Button-1>', self.locate_xy_2)
        self.canvas.bind("<B1-Motion>", self.selectime)
        self.canvas.bind("<ButtonRelease-1>", self.releaseevent)

    def selectime(self, event):
        global current_x, current_y
        self.nux, self.nuy = (event.x, event.y)
        self.canvas.coords(self.rect, current_x, current_y, self.nux, self.nuy)

    def releaseevent(self, event):
        self.square.clear()
        new_square = [current_x, current_y, self.nux, self.nuy]
        self.square.append(new_square)
        self.cohen(self.line)
        self.isClip = True
        # print("clip", self.square)

    def onlyline(self):
        self.canvas.delete("square")
        self.select_button.configure(relief=RIDGE)
        self.delete_button.configure(relief=RIDGE)
        self.dot_button.configure(relief=RIDGE)
        self.line_button.configure(relief=SUNKEN)
        self.clip_button.configure(relief=RIDGE)
        self.cropOutside_button.configure(relief=RIDGE)
        self.cropInside_button.configure(relief=RIDGE)

        self.canvas.bind('<Button-1>', self.line_click)
        self.canvas.bind("<B1-Motion>", self.line_drag)
        self.canvas.bind("<ButtonRelease-1>", self.line_release)

    def line_click(self, event):
        global click
        global current_x, current_y
        current_x, current_y = (event.x), (event.y)
        self.line2.append(self.canvas.create_line(current_x, current_y, current_x, current_y, tags="line"))

    def line_drag(self, event):
        global current_x, current_y
        self.nux = event.x
        self.nuy = event.y
        self.canvas.coords(self.line2[-1], current_x, current_y, self.nux, self.nuy)

    def line_release(self, event):
        self.passingLine()
        if self.rect is not None:
            self.cohen(self.line)

    def passingLine(self):
        temp = [current_x, current_y, self.nux, self.nuy]
        self.line.append(temp)


root = Tk()
p = Clipping(root)
root.mainloop()
