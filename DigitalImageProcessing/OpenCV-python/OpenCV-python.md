<!--
 * @Author: your name
 * @Date: 2021-04-01 09:59:17
 * @LastEditTime: 2021-04-28 14:37:14
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


---
## 6.阈值分割
- [原文链接](http://codec.wang/#/opencv/start/06-image-thresholding)

---
- ![20210418105241](http:cdn.ayusummer233.top/img/20210418105241.png)

---
### 目标
- 使用固定阈值、自适应阈值和Otsu阈值法"二值化"图像
- OpenCV函数：`cv2.threshold()`, `cv2.adaptiveThreshold()`

---
### 教程

---
#### 固定阈值分割
- 固定阈值分割很直接，一句话说就是像素点值大于阈值变成一类值，小于阈值变成另一类值。  
  ![20210418105405](http:cdn.ayusummer233.top/img/20210418105405.png)
- ```python
  import cv2
  import os
  import numpy as np

  # 原图路径定义
  file_path_rice_Ear = os.path.abspath(os.path.join(os.path.dirname(__file__),
                                                    '../../../resource/pic/riceEar/RiceEar1.png'))

  # 灰度图读入
  img = cv2.imread(file_path_rice_Ear, 0)

  # 阈值分割
  ret, th = cv2.threshold(img, 127, 255, cv2.THRESH_BINARY)

  # 两张图片横向合并（便于对比显示）
  tmp = np.hstack((img, th))

  cv2.imshow("RiceEarFixedThresholding", tmp)
  cv2.waitKey(0)
  ```
  ![20210418221015](http:cdn.ayusummer233.top/img/20210418221015.png)
- `cv2.threshold()`用来实现阈值分割，ret是return value缩写，代表当前的阈值，暂时不用理会。函数有4个参数：
  - 参数1：要处理的原图，一般是灰度图
  - 参数2：设定的阈值
  - 参数3：对于`THRESH_BINARY`、`THRESH_BINARY_INV`阈值方法所选用的最大阈值，一般为255
  - 参数4：阈值的方式，主要有5种，详情：ThresholdTypes
  
  ---
- 下面结合代码理解下这5种阈值方式：
  ```python
  # 应用5种不同的阈值方法
  ret, th1 = cv2.threshold(img, 127, 255, cv2.THRESH_BINARY)
  ret, th2 = cv2.threshold(img, 127, 255, cv2.THRESH_BINARY_INV)
  ret, th3 = cv2.threshold(img, 127, 255, cv2.THRESH_TRUNC)
  ret, th4 = cv2.threshold(img, 127, 255, cv2.THRESH_TOZERO)
  ret, th5 = cv2.threshold(img, 127, 255, cv2.THRESH_TOZERO_INV)

  titles = ['Original', 'BINARY', 'BINARY_INV', 'TRUNC', 'TOZERO', 'TOZERO_INV']
  images = [img, th1, th2, th3, th4, th5]

  # 使用Matplotlib显示
  for i in range(6):
      plt.subplot(2, 3, i + 1)
      plt.imshow(images[i], 'gray')
      plt.title(titles[i], fontsize=8)
      plt.xticks([]), plt.yticks([])  # 隐藏坐标轴
  plt.show()
  ```
- ![20210418221152](http:cdn.ayusummer233.top/img/20210418221152.png)
> - 很多人误以为阈值分割就是二值化。从上图中可以发现，两者并不等同，阈值分割结果是两类值，而不是两个值
- ![20210418221340](http:cdn.ayusummer233.top/img/20210418221340.png)

---
#### 自适应阈值
- 看得出来固定阈值是在整幅图片上应用一个阈值进行分割，_它并不适用于明暗分布不均的图片_。 `cv2.adaptiveThreshold()`自适应阈值会每次取图片的一小部分计算阈值，这样图片不同区域的阈值就不尽相同。它有5个参数，其实很好理解，先看下效果：
  ```python
  # 自适应阈值对比固定阈值
  img = cv2.imread(file_path_rice_Ear, 0)

  # 固定阈值
  ret, th1 = cv2.threshold(img, 127, 255, cv2.THRESH_BINARY)
  # 自适应阈值
  th2 = cv2.adaptiveThreshold(
      img, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY, 11, 4)
  th3 = cv2.adaptiveThreshold(
      img, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY, 25, 6)

  titles = ['Original', 'Global(v = 127)', 'Adaptive Mean', 'Adaptive Gaussian']
  images = [img, th1, th2, th3]

  for i in range(4):
      plt.subplot(2, 2, i + 1), plt.imshow(images[i], 'gray')
      plt.title(titles[i], fontsize=8)
      plt.xticks([]), plt.yticks([])
  plt.show()
  ```
- ![20210418223251](http:cdn.ayusummer233.top/img/20210418223251.png)
- 参数1：要处理的原图
- 参数2：最大阈值，一般为255
- 参数3：小区域阈值的计算方式
  - `ADAPTIVE_THRESH_MEAN_C` : 小区域内取均值
  - `ADAPTIVE_THRESH_GAUSSIAN_C` : 小区域内加权求和，权重是个高斯核
- 参数4 : 阈值方法，只能使用`THRESH_BINARY`, `THRESH_BINARY_INV`
- 参数5：小区域的面积，如11就是11*11的小块
- 参数6：最终阈值等于小区域计算出的阈值再减去此值

----
#### Otsu阈值
- [参考链接](https://blog.csdn.net/jzwong/article/details/106954097)
  
  ---
- 在前面固定阈值中，我们是随便选了一个阈值如127，那如何知道我们选的这个阈值效果好不好呢？答案是：不断尝试，所以这种方法在很多文献中都被称为经验阈值。Otsu阈值法就提供了一种自动高效的二值化方法
- ```python
  import cv2
  import os
  import numpy as np

  # 原图路径定义
  file_path_rice_Ear = os.path.abspath(os.path.join(os.path.dirname(__file__),
                                                    '../../../resource/pic/riceEar/RiceEar1.png'))

  # TRIANGLE阈值处理
  src = cv2.imread(file_path_rice_Ear, cv2.IMREAD_GRAYSCALE)

  triThe = 0
  maxval = 255
  triThe, dst_tri = cv2.threshold(src, triThe, maxval, cv2.THRESH_OTSU + cv2.THRESH_BINARY)
  triThe1, dst_tri1 = cv2.threshold(src, triThe, maxval, cv2.THRESH_OTSU + cv2.THRESH_BINARY_INV)
  print(triThe)
  print(triThe1)

  # 3张图片横向合并（便于对比显示）
  tmp = np.hstack((src, dst_tri, dst_tri1))
  cv2.imshow("OTSUThresholding", tmp)
  cv2.waitKey(0)
  cv2.destroyAllWindows()
  ```
  ![20210418224039](http:cdn.ayusummer233.top/img/20210418224039.png)

----
#### 最大熵阈值分割
- [参考链接](https://blog.csdn.net/u011939755/article/details/88550948)

  ---
```python
import numpy as np
import cv2
import os

# 原图路径定义
file_path_rice_Ear = os.path.abspath(os.path.join(os.path.dirname(__file__),
                                                  '../../../resource/pic/riceEar/RiceEar1.png'))


def segment(img):
    """
    最大熵分割
    :param img:
    :return:
    """

    def calculate_current_entropy(hist, threshold):
        data_hist = hist.copy()
        background_sum = 0.
        target_sum = 0.
        for i in range(256):
            if i < threshold:  # 累积背景
                background_sum += data_hist[i]
            else:  # 累积目标
                target_sum += data_hist[i]
        background_ent = 0.
        target_ent = 0.
        for i in range(256):
            if i < threshold:  # 计算背景熵
                if data_hist[i] == 0:
                    continue
                ratio1 = data_hist[i] / background_sum
                background_ent -= ratio1 * np.log2(ratio1)
            else:
                if data_hist[i] == 0:
                    continue
                ratio2 = data_hist[i] / target_sum
                target_ent -= ratio2 * np.log2(ratio2)
        return target_ent + background_ent

    def max_entropy_segmentation(img):
        channels = [0]
        hist_size = [256]
        prange = [0, 256]
        hist = cv2.calcHist(img, channels, None, hist_size, prange)
        hist = np.reshape(hist, [-1])
        max_ent = 0.
        max_index = 0
        for i in range(256):
            cur_ent = calculate_current_entropy(hist, i)
            if cur_ent > max_ent:
                max_ent = cur_ent
                max_index = i
        ret, th = cv2.threshold(img, max_index, 255, cv2.THRESH_BINARY)
        return th

    img = max_entropy_segmentation(img)
    return img


if __name__ == "__main__":
    img = cv2.imread(file_path_rice_Ear)
    img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    res = segment(img)
    cv2.imshow("max_entropy_segmentation", res)
    cv2.waitKey()
```
- ![20210418224435](http:cdn.ayusummer233.top/img/20210418224435.png)

----
### 小结
- `cv2.threshold()`用来进行固定阈值分割。固定阈值不适用于光线不均匀的图片，所以用`cv2.adaptiveThreshold()`进行自适应阈值分割。
- 二值化跟阈值分割并不等同。针对不同的图片，可以采用不同的阈值方法。


----
# 其他随笔

---
## 中文支持

----
### freetype
- 安装`freetype-py`
  ```
  pip install freetype-py
  ```

> - 2021.4.28-锚点 : 重新思考了这分文档的必要性,认为不应当将其与主课程分离开来,因此将其合并到数字图像处理的主笔记上,该文档不打算再更新了