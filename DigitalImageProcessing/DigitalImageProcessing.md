<!--
 * @Author: your name
 * @Date: 2021-03-12 15:20:33
 * @LastEditTime: 2021-03-24 14:58:19
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
  ![20210320103108](http:qpokg4i30.hn-bkt.clouddn.com/img/20210320103108.png)
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
  2. 对一幅低对比度分辨率的图像采用直方图均衡化和规定化方法（单映射或组映射）实现图像增强，分别采用系统函数和自己编写函数实现相应用功能。（图自选）
  3. 写出实验报告。报告要求：**有实验目的，实验内容，实验过程，实验小结和较详细的图文说明**。



