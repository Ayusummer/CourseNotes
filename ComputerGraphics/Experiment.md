<!--
 * @Author: your name
 * @Date: 2021-04-09 18:04:11
 * @LastEditTime: 2021-04-09 20:39:14
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \junior-lessons_second-term\ComputerGraphics\Experiment.md
-->
# 实验1-二维图形绘制

---
## 1.绘制金刚石图案​
- 金刚石图案的成图规则是：把一个圆周等分成​n份，然后每两点之间连线。当n取奇数时，该图案可一笔连续绘成，即用MoveTo函数确定一个当前点，然后连续用LineTo函数连点成线。​
- 请设计连线规则并编程实现。​

### python绘制金刚石
```python
import turtle
import math
import time


def draw(x, y, r):
    turtle.penup()
    turtle.goto(x, y)
    turtle.pendown()
    turtle.circle(r)


def join(x, y, ex, ey):
    turtle.penup()
    turtle.goto(x, y)
    turtle.pendown()
    turtle.goto(ex, ey)


if __name__ == '__main__':
    rid = int(turtle.textinput('输入', '输入半径'))

    turtle.setup(width=1000, height=1000)
    turtle.speed(50)
    # draw(0,0,300)
    xlist = []
    ylist = []

    for i in range(0, 30):
        xlist.append(rid * math.cos(math.pi / 15 * i));
        ylist.append(rid * math.sin(math.pi / 15 * i));
        # print(12*i,' R == ',i*15);
        draw(0, (i + 1) * -(rid / 30), (i + 1) * (rid / 30));
    for i in range(0, xlist.__len__()):
        for j in range(0, xlist.__len__()):
            join(xlist[i], ylist[i], xlist[j], ylist[j])
```
---
#### turtle

---
##### turtle.speed(speed=None)
- `speed` : 一个 [0,10] 范围内的整型数或速度字符串
  - `fastest`: 0 最快
  - `fast`: 10 快
  - `normal`: 6 正常
  - `slow`: 3 慢
  - `slowest`: 1 最慢

---
##### turtle.circle(radius, extent=None, steps=None)
- `radius` : 一个数值
- `extent` : 一个数值 (或 None)
- `steps` : 一个整型数 (或 None)
    
    ---
- 绘制一个 radius 指定半径的圆。圆心在海龟左边 radius 个单位；extent 为一个夹角，用来决定绘制圆的一部分。如未指定 extent*则绘制整个圆。如果 *extent 不是完整圆周，则以当前画笔位置为一个端点绘制圆弧。如果 radius 为正值则朝逆时针方向绘制圆弧，否则朝顺时针方向。最终海龟的朝向会依据 extent 的值而改变。
- 圆实际是以其内切正多边形来近似表示的，其边的数量由 steps 指定。如果未指定边数则会自动确定。此方法也可用来绘制正多边形。
> - 要注意的是,画笔起始点位置并非圆心,而是圆心垂线与下圆弧的交点
>   ![](https://cdn.ayusummer233.top/image/c4x4voXmXM.gif)


---
## debug

---
### 未找到`graphics.h`
- 原因在于缺少EasyX支持,该库需要手动安装
  - [EasyX官网](https://easyx.cn/easyx)
  - [适用于VS2019的版本]()
- 下载之后运行安装即可
  ![20210409182232](http:cdn.ayusummer233.top/img/20210409182232.png)
- [官中文档](https://docs.easyx.cn/zh-cn/device-func)
  - [离线版](https://ayusummer-my.sharepoint.com/:u:/g/personal/233_ayusummer_onmicrosoft_com/EZU2zHoF049HhFajv8Cyx_ABkPKQli9uYtn__fOdWMkN6A?e=eDekIl)
---


