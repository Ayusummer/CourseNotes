<!--
 * @Author: your name
 * @Date: 2021-04-01 09:59:17
 * @LastEditTime: 2021-04-10 12:09:58
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \junior-lessons_second-term\DigitalImageProcessing\OpenCV-python\OpenCV-python.md
-->
> - 注:本篇笔记另有[JupyterLab版本](https://gitee.com/ayusummer233/res_-daily-notes/blob/master/Jupyter/OPenCV/Note.ipynb)
>   - JupyterLab的食用记录可在[此文档](https://github.com/Ayusummer/DailyNotes/blob/main/BigDataMicroMajor/Python/Note.md)的JupyterLab标题下找到
> - **实质**:本篇笔记实际上是以[此文档](http://codec.wang/#/opencv/)为基本框架进行学习的个人记录


---
# 入门篇
## 1.基本元素:图片

---
### 1.1加载图片显示图片
```python
import cv2

lena = cv2.imread('../resource/pic/lena.jpg')
cv2.imshow('lena', lena)
cv2.waitKey(0)  # 等待窗口关闭
```
- ![20210401112101](http:cdn.ayusummer233.top/img/20210401112101.png)

- `参数2`:读入方式(默认为彩色图)
  - `cv2.IMREAD_COLOR`：彩色图，默认值(1)
  - `cv2.IMREAD_GRAYSCALE`：灰度图(0)
  - `cv2.IMREAD_UNCHANGED`：包含透明通道的彩色图(-1)
  ```python
  # 先定义窗口，后显示图片
  cv2.namedWindow('lena2')
  # 加载灰度图
  lena = cv2.imread('../../resource/pic/lena.jpg', 0)
  cv2.imshow('lena2', lena)
  cv2.waitKey(0)  # 等待窗口关闭
  ```
  ![20210410120330](http:cdn.ayusummer233.top/img/20210410120330.png)

  ---
- `cv2.waitKey(0)`:等待窗口关闭
  - 是让程序暂停的意思，参数是等待时间（毫秒ms）。时间一到，会继续执行接下来的程序，传入0的话表示一直等待。等待期间也可以获取用户的按键输入
  - 能起到"显示"图像窗口的作用
  - 不加此句的话窗口会一闪而过(类似于刚写C++不加system("pause)时dos窗口闪一下就没了一样)
  - 但是`cv2.waitKey(0)`不能代替`time.sleep()`,后者也不能替代前者的作用;前者只有有图形界面才起效

    ---
- 我们也可以先用`cv2.namedWindow()`创建一个窗口，之后再显示图片：
    ```python
    import cv2

    # 先定义窗口，后显示图片
    cv2.namedWindow('lena2', cv2.WINDOW_NORMAL)
    lena = cv2.imread('../resource/pic/lena.jpg')
    cv2.imshow('lena2', lena)
    cv2.waitKey(0)  # 等待窗口关闭

    ```
    - ![20210401112317](http:cdn.ayusummer233.top/img/20210401112317.png)
  - `参数1` : 窗口的名字
  - `参数2` : 默认是`cv2.WINDOW_AUTOSIZE`，表示窗口大小自适应图片;也可以设置为`cv2.WINDOW_NORMAL`，表示窗口大小可调整。图片比较大的时候，可以考虑用后者。

---
### 1.2保存图片
- `cv2.imwrite()`用于保存图片，参数1是包含后缀名的文件名：
  ```python
  import cv2

  # 先定义窗口，后显示图片
  cv2.namedWindow('lena2')
  # 加载灰度图
  lena = cv2.imread('../../resource/pic/lena.jpg', 0)
  cv2.imshow('lena2', lena)
  cv2.imwrite('../../resource/pic/lena_gray.jpg', lena)
  cv2.waitKey(0)  # 等待窗口关闭
  ```
  ![20210410120958](http:cdn.ayusummer233.top/img/20210410120958.png)