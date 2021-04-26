<!--
 * @Author: your name
 * @Date: 2021-03-12 15:20:33
 * @LastEditTime: 2021-04-21 22:43:33
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \junior-lessons_second-term\数字图像处理\DigitalImageProcessing.md
-->
# 资料分享(持续更新)
- [英文第四版笔记<iCloud>](https://www.icloud.com/iclouddrive/0n1hoYXE5HSN8I8yj7kkNglMw#Digital_Image_Processing_4th_Edition_%5BRafael_C._Gonzalez%5D)
- [教材笔记<OneDrive>](https://1drv.ms/u/s!Agvl5Ir7iUevllq25QUUhc0-M9MZ?e=g8vsS8)
- [课堂PPT笔记<OneDrive><PDF文件>](https://1drv.ms/b/s!Agvl5Ir7iUevlmClzv3bGbV7SRDA?e=R6BNoB)
- [[课堂PPT笔记<OneDrive><.goodnotes文件>]](https://1drv.ms/u/s!Agvl5Ir7iUevlmEZBUZP263AFXKZ?e=w9c4L4)
> - OneDrive如果实在打不开的话可能需要魔法(
> - 有意向协作编辑的话可以私信我获取编辑权限


---
# 基本概念

## 调色板(Palette)
- [参考链接@CSDN:_古怪](https://blog.csdn.net/shen_gan/article/details/8114285)

  ---
- 真彩图像虽然是目前的主流图像,但在实际应用中仍然有一些其他彩色图像在使用,这些图像的图像数据一般不是像素值,需要查颜色表才能找到真正的像素值;颜色表又称调色板或颜色查找表
- **引入调色板的目的是为早期图像节省显示缓冲区空间**
  ![20210320103108](http:cdn.ayusummer233.top/img/20210320103108.png)
  - `假设`上图是一个长宽各为240个像素,颜色数为16色的彩色图像
    - 每个颜色都用RGB来直接表示的话,由于RGB每个分量都有256个级别,要用8位(bit)即1字节(byte)表示,每个像素用3byte,整个图像需要$240 \times 240 \times 3 \approx 168KB$显示缓存空间
    - 若用调色板的方法,就能用一个16行24位(24=8*3)的表,每行记录一种颜色的RGB值;16种状态可以用4位二进制数表示,所以一个像素用0.5byte(=4bit),整个图像用$240 \times 240 \times 0.5 \approx 28KB$,占用的字节数约为前面的1/6

---
## 2.4 Image Sampling and Quantization
- 图像例举与量化

---
### Image Interpolation(图像插值)
- [参考链接@CSDN:Effend](https://blog.csdn.net/Effend/article/details/82870144)

---
#### Matlab自带插值函数
- 图像缩放函数：
  ```Matlab
  J = imresize(I, rate, method);
  ```
  - `I`:原图像矩阵
  - `rate`:缩放比例;>1为放大，<1为缩小；
  - `method`:选择插值方法;默认为`nearest`（最近邻插值），还有`bilinear`（双线性插值）、`bicubic`（双三次插值）。
  > 双三次插值可能生成在原始范围之外的像素值

---
#### 最邻近插值
- 查找原始图像中最近的像素，并将其灰度分配给网格中的新像素
- `Pixel replication`是最邻近插值的重要步骤
- 当我们想要将图像的大小增加整数倍时，`Pixel replication`是适用的。
- $srcX = dstX \times \frac{srcWidth}{dstWidth} \\ srcY = dstY \times \frac{srcHeight}{dstHeight}$
- 中心对齐(OpenCV也是如此):  
  $SrcX = (dstX + 0.5) \times \frac{srcWidth}{dstWidth} - 0.5 \\ SrcY = (dstY + 0.5) \times \frac{srcHeight}{dstHeight} - 0.5$
- 使用近邻插值的缩放图像具有严重的马赛克、棋盘效果和缩小图像的严重失真


---
#### 双线性插值
- [参考链接@CSDN:Effend](https://blog.csdn.net/Effend/article/details/82996871)
- [参考链接@CSDN:kill2013110](https://blog.csdn.net/kill2013110/article/details/108124737)

  ---
- 使用一个点的四个最近的临近点来确定灰度
- $v(x',y') = ax' + by' + cx'y' +d$
  - `(x',y')` : 放大后的点的坐标
  - `v(x',y')` : 放大后点的灰度 
  - 四个系数由四个未知方程中的四个方程确定，这些方程可以使用点的四个最近的临近点来构造
- 双线性插值通过两个方向上的线性变换来计算待插值像素点的值，而非第最邻近插值中直接插入相同的值。在双线性插值中，一般先对水平/垂直方向上进行线性插值，再合并两个线性插值来得到最终插入的像素值。
  - 计算量和复杂度较最邻近插值方法大
  - 然而由于是以4个相邻映射像素点作为计算参考，使得新像素点的颜色能具有不同于最近邻插值算法的简单颜色变化,很大程度上消除了明显的锯齿，图像效果较好，避免了像素不连续的情况
  - 然而，双线性插值算法仍然具有其短板，简单线性变化会带来边缘模糊化，在颜色变化程度大的边缘处，会明显发现插值的数据在边缘显得不符。另外由于增加了线性权重与像素值相乘，会存在一定的低通滤波性，高频分量会被削弱，在颜色变化程度大的地方可能无法得到正确的像素值。


---
#### 双三次插值
- 该方法较前两种方法更为复杂，在考虑4个相邻映射像素点的同时，还要考虑到像素的变化率。在双线性插值的基础上，选取待插入点周围更大范围的像素值作三次插值，以克服上面两种方法的不足，计算精度更高，计算量也更大，但图像效果更好。


---
#### 三种插值方法原理总结
- 三种插值方法从原理上，算法复杂程度递增，后者是基于前者算法的增强和改善，计算量也随之增加。




## 3.3 Histogram Processing
- 直方图处理

### 实验
- `实验目标`：熟悉基于基于单像素空域增强方法，理解并掌握直方图均衡化和规定化实现图像增强
  
  ---
- `实验要求`:
  1. 对一幅低对比度分辨率的图像采用除直方图处理方法之外的灰度级变换方法实现图像增强。（图自选）
  2. 对一幅低对比度分辨率的图像采用直方图均衡 化和规定化方法（单映射或组映射）实现图像增强，分别采用系统函数和自己编写函数实现相应用功能。（图自选）
  3. 写出实验报告。报告要求：**有实验目的，实验内容，实验过程，实验小结和较详细的图文说明**。

----
# 第3章-亮度变换与空间滤波

---
## 3.5 平滑滤波器
- [参考链接@博客园-极客挖掘机-Python图像处理OpenCV(7):图像平滑(滤波)处理](https://www.cnblogs.com/babycomeon/p/13053617.html)

  ----
### 概念
- `图像平滑`技术通常也被称为`图像滤波`技术
- 图像在获取、传输过程中，受干扰的影响，会产生`噪声`，噪声是一种错误的信号，干扰正常信号。造成图像毛糙，需对图像进行`平滑处理`。
- 图像去噪是一种信号滤波的方法，目的是`保留有用信号，去掉噪音信号`。
- 每一幅图像都包含某种程度的噪声，噪声可以理解为由一种或者多种原因造成的灰度值的随机变化，如由光子通量的随机性造成的噪声等等。
- 而图像平滑技术就是用来处理图像上的噪声

----
### 目的
- 1.`模糊`：在提取较大目标前,去除太小的细节，或将目标内的`小间断连接`起来。
- 2.`消除噪声` : 改善图象质量，降低干扰。
  - 平滑滤波对图像的`低频分量`增强，同时削弱高频分量，用于`消除图像中的随机噪声`，起到`平滑`作用



----
# 第5章-图像复原


----
## 5.2 噪声模型
- `2021.4.21锚点` : **测试图像增强方法是需要噪声所以临时学习了添加噪声的方法,没有深入理解**

  ---
- [参考链接-为图像添加高斯噪声与椒盐噪声-python-@博客园-我坚信阳光灿烂](https://www.cnblogs.com/wojianxin/p/12499928.html)

  ---
- 噪声干扰一般是随机产生的，分布不规则，大小也不规则。噪声像素的灰度是空间不相关，`与邻近像素显著不同`
-  在噪声的概念中, 通常采用信噪比（`Signal-Noise Rate, SNR`）衡量图像噪声。SNR越小噪声占比越大。
- 在信号系统中，计量单位为dB，为10lg(PS/PN), PS和PN分别代表信号和噪声的有效功率。在这里，采用信号像素点的占比充当SNR，以衡量所添加噪声的多少。



-----
### 椒盐噪声


---
##### 椒盐噪声
- 椒盐噪声又称为脉冲噪声，它是一种随机出现的白点（盐噪声）或者黑点（椒噪声）。

  ----
- 为图像添加椒盐噪声
```python
# -*- coding: utf-8 -*-
# @Time    : 2021/4/21 9:41
# @Author  : 咸鱼型233(引自https://www.cnblogs.com/wojianxin/p/12499928.html)
# @File    : 5.2-Salt-and-PepperNoise.py
# @Software: PyCharm
# @Function: 椒盐噪声
import numpy as np
import random
import cv2
from matplotlib import pyplot as plt


def sp_noise(image, prob):
    """

    添加椒盐噪声

    prob:噪声比例

    """

    output = np.zeros(image.shape, np.uint8)
    thres = 1 - prob

    for i in range(image.shape[0]):
        for j in range(image.shape[1]):
            rdn = random.random()
            if rdn < prob:
                output[i][j] = 0
            elif rdn > thres:
                output[i][j] = 255
            else:
                output[i][j] = image[i][j]
    return output


# ========= 函数测试 ======= #
# 读取图像
img = cv2.imread("../../../resource/pic/lena.jpg")
img_plt = img[:, :, ::-1]   # 重新拼合适用于plt显示的图像

# 添加椒盐噪声，噪声比例为 0.02
out1 = sp_noise(img_plt, prob=0.02)

# 显示图像
plt.rcParams['font.family'] = ['SimHei']  # 使用黑体
plt.figure(1)
plt.subplot(121)
plt.axis('off')  # 关闭坐标轴
plt.title('原图')
plt.imshow(img_plt)

plt.subplot(122)
plt.axis('off')
plt.title('添加椒盐噪声')
plt.imshow(out1)

plt.show()


```
![20210421141721](http:cdn.ayusummer233.top/img/20210421141721.png)

---
##### 高斯噪声
- 高斯噪声是指它的概率密度函数服从高斯分布（即正态分布）的一类噪声。

  ---
- 为图像添加高斯噪声
```python
# -*- coding: utf-8 -*-
# @Time    : 2021/4/21 9:40
# @Author  : 咸鱼型233
# 引自https://www.cnblogs.com/wojianxin/p/12499928.html
# @File    : 5.2-GaussianNoise.py
# @Software: PyCharm
# @Function: 高斯噪声
import numpy as np
import random
import cv2
from matplotlib import pyplot as plt


def gasuss_noise(image, mean=0, var=0.001):
    """
    添加高斯噪声

    mean : 均值

    var : 方差
    """

    image = np.array(image / 255, dtype=float)
    noise = np.random.normal(mean, var ** 0.5, image.shape)
    out = image + noise
    if out.min() < 0:
        low_clip = -1.
    else:
        low_clip = 0.
    out = np.clip(out, low_clip, 1.0)
    out = np.uint8(out * 255)
    # cv.imshow("gasuss", out)
    return out


# ========= 函数测试 ======= #
# 读取图像
img = cv2.imread("../../../resource/pic/lena.jpg")
img_plt = img[:, :, ::-1]  # 重新拼合适用于plt显示的图像

# 添加高斯噪声，均值为0，方差为0.001
out2 = gasuss_noise(img_plt, mean=0, var=0.001)

# 显示图像
plt.rcParams['font.family'] = ['SimHei']  # 使用黑体
plt.figure(1)
plt.subplot(121)
plt.axis('off')  # 关闭坐标轴
plt.title('原图')
plt.imshow(img_plt)

plt.subplot(122)
plt.axis('off')
plt.title('添加高斯噪声')
plt.imshow(out2)

plt.show()

```
![20210421142458](http:cdn.ayusummer233.top/img/20210421142458.png)





---
### debug记录

----
#### plt显示图像的色差问题
- [参考链接-@CSDN-善良995](https://blog.csdn.net/weixin_45954454/article/details/114707888)
-   [本节测试代码文件](./OpenCV-python/Test/abnormal_img_show.py)

  ----
- 首先我们来看看`彩色图像`的cv显示-plt显示-原图
  ![20210421102254](http:cdn.ayusummer233.top/img/20210421102254.png)
  ```python
  import cv2
  from matplotlib import pyplot as plt

  # 读取图像
  img = cv2.imread("../../resource/pic/lena.jpg")

  # cv显示图像
  cv2.imshow("cv-show", img)
  cv2.waitKey(0)  # 等待窗口关闭

  # plt显示图像
  plt.rcParams['font.family'] = ['SimHei']    # 使用黑体
  plt.axis('off')  # 关闭坐标轴
  plt.title('plt显示原图')
  plt.imshow(img)
  plt.show()
  ```
- 使用`cv2.imread()`读取图像时，默认彩色图像的三通道顺序为`B、G、R`，这与我们所熟知的RGB中的R通道和B通道正好互换位置了。
- 而使用`plt.imshow()`函数却默认显示图像的通道顺序为`R、G、B`，导致图像出现色差发蓝。
- 解决方案1:cv读取图像后提取通道并按照RGB顺序重新组合图像  
  ```python
  # plt显示图像-cv读取图像后提取通道并按照RGB顺序重新组合图像
  b, g, r = cv2.split(img)            # 分别提取B、G、R通道
  img_new1 = cv2.merge([r, g, b])     # 重新组合为R、G、B
  plt.axis('off')  # 关闭坐标轴
  plt.title('plt显示原图\n-cv读取图像后提取通道并按照RGB顺序重新组合图像\n方案一提取并重组通道')
  plt.imshow(img_new1)
  plt.show()

  # img[:,:,0]表示图片的蓝色通道，对一个字符串s进行翻转用的是s[::-1]，同样img[:,:,::-1]就表示BGR通道翻转，变成RGB
  img_new2 = img[:, :, ::-1]
  plt.axis('off')  # 关闭坐标轴
  plt.title('plt显示原图\n-cv读取图像后提取通道并按照RGB顺序重新组合图像\n方案2-类字符串翻转')
  plt.imshow(img_new2)
  plt.show()

  ```

---
- 除了彩色图像外,plt显示灰度图像也存在色差问题
  - `plt.imshow()`函数默认显示三通道图像，把灰度图当作彩色图显示出来了，所以也会有色差。  
  ![20210421140950](http:cdn.ayusummer233.top/img/20210421140950.png)
  ```python
  # ============ 灰度图像显示 ============ #
  img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
  plt.axis('off')             # 关闭坐标轴
  plt.title("plt显示灰度图像")
  plt.imshow(img_gray)
  plt.show()
  ```

  ---
- 要想正常显示灰度图像只需要在调用`plt.imshow()`时设置`cmap`属性为`'gray'`即可
  ```python
  # plt正常显示灰度图像
  plt.axis('off')             # 关闭坐标轴
  plt.title("plt正常显示灰度图像")
  plt.imshow(img_gray, cmap='gray')
  plt.show()
  ```  
  ![20210421141352](http:cdn.ayusummer233.top/img/20210421141352.png)







