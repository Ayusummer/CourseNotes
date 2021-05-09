<!--
 * @Author: your name
 * @Date: 2021-04-10 14:41:47
 * @LastEditTime: 2021-04-28 14:44:20
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \junior-lessons_second-term\DigitalImageProcessing\Experiment.md
-->
<!--
 * @Author: your name
 * @Date: 2021-04-10 14:41:47
 * @LastEditTime: 2021-04-10 16:04:54
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \junior-lessons_second-term\DigitalImageProcessing\Experiment.md
-->

----
# 第2次实验


---
## 实验目的
- 熟悉基于基于单像素空域增强方法，理解并掌握直方图均衡化和规定化实现图像增强

---
## 实验内容
1. 对一幅低对比度分辨率的图像采用除直方图处理方法之外的灰度级变换方法实现图像增强。（图自选）
2. 对一幅低对比度分辨率的图像采用直方图均衡化和规定化方法（单映射或组映射）实现图像增强，分别采用系统函数和自己编写函数实现相应用功能。（图自选）
3. 写出实验报告。报告要求：有实验目的，实验内容，实验过程，实验小结和较详细的图文说明。

---
## 实验过程

---
### 平滑处理
- 对一幅低对比度分辨率的图像采用除直方图处理方法之外的灰度级变换方法实现图像增强

    ---
- [参考链接@CodecWang](http://codec.wang/#/opencv/basic/extra-07-contrast-and-brightness)

    ---
- 首先我手里并没有一幅低对比度分辨率的图像,但是还留有上次实验用的彩色图像也即  
  ![20210410145002](http:cdn.ayusummer233.top/img/20210410145002.png)
  - 首先保存其灰度图像
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
  - 亮度调整是将图像像素的强度整体变大/变小，对比度调整则指的是图像暗处的像素强度变低，亮出的变高，从而拓宽某个区域内的显示精度。
  - OpenCV中亮度和对比度应用这个公式来计算：  
    g</span>(x)=αf</span>(x)+β</span></span>  
    - α(>0)、β常称为增益与偏置值，分别控制图片的对比度和亮度。
    - f(x,y) 代表源图像 x行，y列的像素点的c通道的数值
    - g(x,y) 代表目标图像x行，y列的像素点的c通道的数值
  - 那么对其进行对比度与亮度调整:
    ```python
    np.uint8(np.clip(contrast * img + brightness, 0, 255))
    ```
    - ```python
      numpy.clip(a->array_like, a_min->array_like or none, a_max->array_like or none, out=None->ndarray , **kwargs)
      """
      功能：把数组 a 中的值缩放到 [a_min, a_max] 之间。
      < a_min -> a_min
      > a_max -> a_max

      参数
      --------
      a: numpy 数组。

      a_min: 最小值

      a_max: 最大值

      示例
      -------
      x = np.array([2, 3, 4, 4, 6, 8, 7, 7, 11, 10, 11, 12])
      x = np.clip(x, 5, 9)
      >>> x
      [5,5,5,5,6,8,7,7,9,9,9,9]
      """
      ```
    - 晓得原理之后使用如下代码并手动调整得到合适的图片
        ```python
        import cv2
        import numpy as np


        # 回调函数，暂时无用
        def nothing(x):
            pass


        # img = cv2.imread('lena.jpg')
        img = cv2.imread("../../../resource/pic/lena_gray.jpg")
        cv2.namedWindow('image')

        # 创建两个滑块
        cv2.createTrackbar('brightness', 'image', 0, 100, nothing)
        cv2.createTrackbar('contrast', 'image', 100, 300, nothing)

        temp = img.copy()
        rows, cols = img.shape[:2]

        while True:
            cv2.imshow('image', temp)
            if cv2.waitKey(1) == 27:
                break

            # 得到两个滑块的值
            brightness = cv2.getTrackbarPos('brightness', 'image')
            contrast = cv2.getTrackbarPos('contrast', 'image') * 0.01
            # 进行对比度和亮度调整
            temp = np.uint8(np.clip(contrast * img + brightness, 0, 255))

        ```
        - [执行结果](https://cdn.ayusummer233.top/image/gifDHyqk2N7a2.gif)
        - ![20210410160810](http:cdn.ayusummer233.top/img/20210410160810.png)

        ----
    - 这样就得到了实验用图,相应的反向操作进行图像增强
        ```python
        import cv2
        import numpy as np

        img = cv2.imread('../resource/pic/lena_low_quality.jpg')
        res = np.uint8(np.clip((2 * img + 50), 0, 255))

        # 两张图片横向合并（便于对比显示）
        tmp = np.hstack((img, res))
        cv2.imshow('image', tmp)
        cv2.waitKey(0)

        ```
        ![20210410161121](http:cdn.ayusummer233.top/img/20210410161121.png)
    - 至此,第一部分结束

---
### 直方图处理
- 对一幅低对比度分辨率的图像采用直方图均衡化和规定化方法实现图像增强，分别采用系统函数和自己编写函数实现相应用功能。

    ---
- [参考链接@CodecWang](http://codec.wang/#/opencv/basic/15-histograms)

    ---
- `直方图` : 简单来说，直方图就是图像中每个像素值的个数统计形成的柱状图
- `OpenCV中直方图计算`
  ```python
  cv2.calcHist(images, channels, mask, histSize, ranges)
  ```
  - `images` : 要计算的原图，以方括号的传入，如：[img]
  - `channels` : 类似dims，灰度图写[0]就行，彩色图B/G/R分别传入[0]/[1]/[2]
    - `dims` : 要计算的通道数，对于灰度图dims=1，普通彩色图dims=3
  - `mask` : 要计算的区域，计算整幅图的话，写None
  - `histSize` : 子区段数目，如果我们统计0~255每个像素值histSize=256；如果划分区间，比如0~15, 16~31…240~255这样16个区间，histSize=16
  - `ranges` : 要计算的像素值范围，一般为[0,256)

    ---
- `绘制直方图`
  ```python
    import cv2
    import matplotlib.pyplot as plt

    img = cv2.imread('../resource/pic/lena_low_quality.jpg')
    plt.hist(img.ravel(), 256, [0, 256])
    plt.show()
  ```
  ![20210410155316](http:cdn.ayusummer233.top/img/20210410155316.png)
  - 可以看出,这个图像确实有够糊的

    ---
- 直方图均衡化
  - 一副效果好的图像通常在直方图上的分布比较均匀，直方图均衡化就是用来改善图像的全局亮度和对比度。
    ```python
    import cv2
    import numpy as np
    import matplotlib.pyplot as plt

    img = cv2.imread('../resource/pic/lena_low_quality.jpg', 0)

    # 1.直方图计算
    # 使用OpenCV函数计算
    hist = cv2.calcHist([img], [0], None, [256], [0, 256])  # 性能：0.022158 s

    # 2.绘制直方图
    plt.hist(img.ravel(), 256, [0, 256])
    plt.show()

    # 3.直方图均衡化
    equ = cv2.equalizeHist(img)
    cv2.imshow('equalization', np.hstack((img, equ)))  # 并排显示
    cv2.waitKey(0)

    # 绘制出均衡化后的直方图
    plt.hist(equ.ravel(), 256, [0, 256])
    plt.show()

    ```
    ![20210410162024](http:cdn.ayusummer233.top/img/20210410162024.png)

    ---
- 自己编写函数实现相应用功能
    ```python
    import cv2
    import numpy as np
    import matplotlib.pyplot as plt


    # 直方图均衡化
    def hist_equal(image, z_max=255):
        H, W = image.shape
        S = H * W * 1.
        out = image.copy()
        sum_h = 0.

        for i in range(1, 255):
            ind = np.where(image == i)

            sum_h += len(image[ind])

            z_prime = z_max / S * sum_h

            out[ind] = z_prime

            out = out.astype(np.uint8)

        return out


    img = cv2.imread("../resource/pic/lena_low_quality.jpg", 0).astype(np.float)
    out = hist_equal(img)
    # 显示直方图
    plt.hist(out.ravel(), bins=255, rwidth=0.8, range=(0, 255))
    plt.show()
    # 显示处理后的图像
    cv2.imshow("result", out)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    ```
    ![20210410163952](http:cdn.ayusummer233.top/img/20210410163952.png)


---
## 实验小结
- 熟悉了基于单像素空域增强方法，理解并掌握了直方图均衡化和规定化实现图像增强
- 复习了`Matplotlib`,`numpy`库,进一步学习了`OpenCV-python`库

----
# 分组实验-稻穗分割

----
## 实验要求
- 分割图像中的稻穗，方法自选（传统方法），可以是多种方法的结合，结果图像中稻穗区域以白色显示，其他背景黑色显示。
- 说明：请同学们自由分组，上传解决方案（模板同实验报告），每组仅上传一份即可，在封面处标明小组成员，及成员分工
- 图像
  - ![20210417203034](http:cdn.ayusummer233.top/img/20210417203034.png)
  - ![20210417203202](http:cdn.ayusummer233.top/img/20210417203202.png)
  - ![20210417203224](http:cdn.ayusummer233.top/img/20210417203224.png)
  - ![20210417203239](http:cdn.ayusummer233.top/img/20210417203239.png)
  - ![20210417203253](http:cdn.ayusummer233.top/img/20210417203253.png)

----



---
# 第3次实验-图像增强

---
## 实验目的
- 熟悉空域和频域增强方法，理解并掌握常用平滑和锐化方法

---
## 实验内容
1. 对一幅带有噪声图像采用空域和频域的滤波方法实现平滑处理，选择一种方法自己编写代码实现，并比较、分析不同窗口大小的滤波方法对其结果的影响（图自选）；
2. 对上一步经过平滑处理过后的图像进行锐化处理，要求分别采用空域和频域的滤波方法实现锐化处理，并选择一种方法自己编写代码实现；
3. 写出实验报告。报告要求：有实验目的，实验内容，实验过程，实验小结和较详细的图文说明。

---
## 实验过程

---
### 平滑处理
- 对一幅带有噪声图像采用空域和频域的滤波方法实现平滑处理，选择一种方法自己编写代码实现，并比较、分析不同窗口大小的滤波方法对其结果的影响

    ---
- 首先我手里并没有一幅带有模板噪声的图像,因此要先为现有图像添加噪声,为了方便针对性处理,也为了节约时间

#### 为图像添加椒盐噪声与高斯噪声
- [参考链接](https://www.cnblogs.com/wojianxin/p/12499928.html)

  ---
- 噪声干扰一般是随机产生的，分布不规则，大小也不规则。噪声像素的灰度是空间不相关，`与邻近像素显著不同`
-  在噪声的概念中, 通常采用信噪比（`Signal-Noise Rate, SNR`）衡量图像噪声。SNR越小噪声占比越大。
- 在信号系统中，计量单位为dB，为10lg(PS/PN), PS和PN分别代表信号和噪声的有效功率。在这里，采用信号像素点的占比充当SNR，以衡量所添加噪声的多少。


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

----
#### 平滑处理
- [参考链接](https://blog.csdn.net/weixin_44980490/article/details/107707205)

  ----
- 为图像添加噪声后就获得了有噪声的图像,接下来进行图像平滑处理

  ----
##### 均值滤波
- 均值滤波是典型的线性滤波算法，其采用的主要方法为邻域平均法。它是指在图像上对目标像素给一个模板，该模板包括了其周围的临近像素（以目标像素为中心的周围8个像素，构成一个滤波模板，即包括目标像素本身），再用模板中的全体像素的平均值来代替原来像素值。

```python
import cv2
import numpy as np
import matplotlib.pyplot as plt
import os


# 均值滤波
def meanFiltering1(img, size):      # img输入，size均值滤波器的尺寸，>=3，且必须为奇数
    num = int((size - 1) / 2)       # 输入图像需要填充的尺寸
    img = cv2.copyMakeBorder(img, num, num, num, num, cv2.BORDER_REPLICATE)  # 对传入的图像进行扩充，尺寸为num
    h1, w1 = img.shape[0:2]
    # 高斯滤波
    img1 = np.zeros((h1, w1, 3), dtype="uint8")     # 定义空白图像，用于输出中值滤波后的结果
    for i in range(num, h1 - num):                  # 对扩充图像中的原图进行遍历
        for j in range(num, w1 - num):
            sum = 0
            sum1 = 0
            sum2 = 0
            for k in range(i - num, i + num + 1):  # 求中心像素周围size*size区域内的像素的平均值
                for l in range(j - num, j + num + 1):
                    sum = sum + img[k, l][0]    # B通道
                    sum1 = sum1 + img[k, l][1]  # G通道
                    sum2 = sum2 + img[k, l][2]  # R通道
            sum = sum / (size ** 2)             # 除以核尺寸的平方
            sum1 = sum1 / (size ** 2)
            sum2 = sum2 / (size ** 2)
            img1[i, j] = [sum, sum1, sum2]      # 复制给空白图像
    img1 = img1[(0 + num):(h1 - num), (0 + num):(h1 - num)]  # 从滤波图像中裁剪出原图像
    return img1


# 图像路径定义
lena_with_saltAndPepperNoise = os.path.abspath(os.path.join(os.path.dirname(__file__),
                                                            '../../../resource/pic/pic-with-noise'
                                                            '/lena_with_GaussianNoise.png'))

# 读取图片
img = cv2.imread(lena_with_saltAndPepperNoise)
source = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

# 均值滤波
# result = cv2.blur(source, (5, 5))
result = meanFiltering1(source, 5)


# 显示图像
plt.rcParams['font.family'] = ['SimHei']  # 使用黑体
titles = ['原图', '均值滤波']
images = [source, result]

for i in range(2):
    plt.subplot(1, 2, i + 1), plt.imshow(images[i], 'gray')
    plt.title(titles[i])
    plt.xticks([]), plt.yticks([])
plt.show()
```
![20210425222024](http:cdn.ayusummer233.top/img/20210425222024.png)


---
### 锐化处理
- [参考链接@CSDN-单曲循环鸭-基于opencv（C++）的图像处理（图像锐化）](https://blog.csdn.net/weixin_45801311/article/details/110246869)

  ---
- 对上一步经过平滑处理过后的图像进行锐化处理，要求分别采用空域和频域的滤波方法实现锐化处理，并选择一种方法自己编写代码实现；

  ---
#### 图像锐化的概念
- 图像锐化(image sharpening)是补偿图像的轮廓，增强图像的边缘及灰度跳变的部分，使图像变得清晰，分为空间域处理和频域处理两类。图像锐化是为了突出图像上地物的边缘、轮廓，或某些线性目标要素的特征。这种滤波方法提高了地物边缘与周围像元之间的反差，因此也被称为边缘增强。

---
#### 高通滤波
- [参考链接@知乎-闪电侠的右-https://zhuanlan.zhihu.com/p/162275458]

  ---
- 高通滤波法采用高通滤波器让高频分量通过，使图像的边缘和线条变得清楚，实现锐化。
- 高通滤波器而用空域法和频域法实现，在空间域使用卷积方法，模板如  
  ![20210425223027](http:cdn.ayusummer233.top/img/20210425223027.png)  
  可以看出和拉普拉斯算子基本相同。
```python
import cv2
import matplotlib.pyplot as plt
import os

# 图像路径定义
meanFilter1Img = os.path.abspath(os.path.join(os.path.dirname(__file__),
                                              '../../../resource/pic/Experiment/Ex3-ImageEnhancement/meanFilter1.png'))

plt.subplot(1, 2, 1)
img = cv2.imread(meanFilter1Img, 0)  # 0为灰度图
plt.axis('off')             # 关闭坐标轴
plt.imshow(img, cmap='gray')

plt.subplot(1, 2, 2)
depth = cv2.CV_16S
# 求X方向梯度（创建grad_x, grad_y矩阵）
grad_x = cv2.Sobel(img, depth, 1, 0)
abs_grad_x = cv2.convertScaleAbs(grad_x)

# 求Y方向梯度
grad_y = cv2.Sobel(img, depth, 0, 1)
abs_grad_y = cv2.convertScaleAbs(grad_y)

# 合并梯度
sobel_img = cv2.addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0)

plt.imshow(sobel_img, cmap='gray')
plt.axis('off')             # 关闭坐标轴
plt.show()
```
![20210425223737](http:cdn.ayusummer233.top/img/20210425223737.png)



----
## 调试问题及解决方案记录

----
### plt显示图像的色差问题
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




---
## 实验小结
- 进一步了解了图像增强的方法, 对于图像平滑处理以及锐化处理的方法有了原理及其实现方面的理解
- 进一步熟悉了python的`numpy`,`Matplotlib`, `OpenCV-Python`库的使用方法


-----
# 第4次实验-图像分割

----
## 实验目的 
- 1、理解图像分割的基本概念。
- 2、掌握阈值法、K-means聚类方法、边缘提取及区域增长和分裂方法进行图像分割。

----
## 实验环境
- Matlab等

-----
## 实验内容
- 1、分别采用两种阈值选取方法实现图像分割（如全局阈值、OTSU等），要求根据阈值选取的思想自己写代码。（分割图像可自由选择）

  ----
- 2、采用K-means聚类算法实现图像分割，要求根据K-means的思想自己写代码。（分割图像可自由选择）

  ----
- 3、分别用Roberts,Sobel和拉普拉斯高斯算子对图像进行边缘检测(可使用系统函数)，比较三种算子处理的不同之处。

  ----
- 4、选择适当方法实现肺的分割，结果包括两部分：肺（白色显示）和背景（黑色显示）。  
  ![20210428142537](http:cdn.ayusummer233.top/img/20210428142537.png)

-----
### 分别采用两种阈值选取方法实现图像分割

----
#### Otsu阈值
- [参考链接](https://blog.csdn.net/jzwong/article/details/106954097)
  
  ---
- 在之前固定阈值测试中，阈值是随便选的(如127)，要想知道阈值选取地好不好就只能不断尝试，所以这种方法在很多文献中都被称为经验阈值。
- Otsu阈值法就提供了一种自动高效的二值化方法
  ```python
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