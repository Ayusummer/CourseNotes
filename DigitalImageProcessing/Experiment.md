<!--
 * @Author: your name
 * @Date: 2021-04-10 14:41:47
 * @LastEditTime: 2021-04-10 16:42:25
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



---
# 第3次实验

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
- 首先我手里并没有一幅带有噪声的图像


---
## 实验小结



