<!--
 * @Author: your name
 * @Date: 2021-03-19 08:43:43
 * @LastEditTime: 2021-04-01 08:38:31
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \junior-lessons_second-term\DigitalImageProcessing\Matlab\Matlab.md
-->
# 个人环境
- Matlab2019b

---
# 零散知识点
- 续行符:`...`

---
## 0基础入门推荐视频
- [B站@爱研究的小阿楠](https://www.bilibili.com/video/BV13D4y1Q7RS/?p=5&spm_id_from=pageDriver)

---
## 编码
- [方案来源](https://www.zhihu.com/question/27933621/answer/249429313)

---
- 默认情况下使用GBK,但其并不是一个通用的编码
- 打开Matlab安装目录下的bin目录,将`lcdata_utf8.xml`重命名为`lcdata.xml`并打开该文件
- 删除
  ```
  <encoding name=”GBK”>  
  < encoding_alias name=”936”>  
  </encoding> 
  ```
- 将
  ```
  <encoding name=”UTF-8”>  
  <encoding_alias name=”utf8”/> 
  </encoding>  
  ```
  修改为
  ```
  <encoding name="UTF-8">  
  <encoding_alias name="utf8"/>  
  <encoding_alias name="GBK"/>  
  </encoding>    
  ```
- 重启 matlab 之后在命令行窗口执行
  ```
  slCharacterEncoding
  ```
  即可看到当前编码方案为`UTF-8`

  ---
### 可能存在的问题
- 至此,可以在Matlab中新建脚本默认使用utf-8的编码方案,但是绘图时中文显示会乱码(类似GBK编码打开utf-8文件的乱码效果)
- [参考链接@知乎:当时明月在](https://zhuanlan.zhihu.com/p/353825395)
- [参考链接@CSDN:happyangry](https://blog.csdn.net/happyangry/article/details/86237693?utm_source=app)
  
  ---
- ```Matlab
  feature('DefaultCharacterSet','UTF-8')  % 设置当前字符集为UTF8
  ```
  将此行代码放在脚本首行即可解决绘图乱码问题
  
  - 也可以在`Matlab安装目录\toolbox\local`目录下新建`startup.m`文件写入该行脚本实现启动Matlab自动配置当前字符集


---
## 更改默认工作目录
- [方案来源](https://blog.csdn.net/weixin_43699666/article/details/112506898)
  
  ---
- Matlab的默认工作目录一般是安装目录
- 打开Matlab安装目录下的`toolbox\local\matlabrc.m`文件,在最后加上一行
  ```
  cd 'E:/GithubProject/junior-lessons_second-term/DigitalImageProcessing/Matlab'
  ```
  - `E:/GithubProject/junior-lessons_second-term/DigitalImageProcessing/Matlab`即为想要变更到的目标目录,可以使用`/`来避免转义带来的错误
- 重启Matlab即可发现工作目录已变更

----
## 使用相对目录来访问文件
```Matlab
.       % 当前工作目录
../     % 当前工作目录上级目录
../../  % 当前工作目录上级目录的上级目录
```
- 与python使用相对目录不同的是,Matlab中的相对路径索引起始点并非当前代码所在的文件,**而是当前的工作目录**(就是每次打开Matlab时左侧显示的当前文件夹)
- ![20210401083711](http:cdn.ayusummer233.top/img/20210401083711.png)
- 示例
  ![20210401083830](http:cdn.ayusummer233.top/img/20210401083830.png)



----
## 常用命令
- `clc` : 清除命令窗口的内容，对工作环境中的全部变量无任何影响
- `close`: 关闭当前的Figure窗口
- `close all` : 关闭所有的Figure窗口
- `clear` : 清除工作空间的所有变量
- `clear all` : 清除工作空间的所有变量，函数，和MEX文件
- `doc ***` : ***的帮助文档
- `open 函数名` : 打开该函数的源码文件


-----
## 函数
```Matlab
function [y1,…,yN] = myfun(x1,…,xM)
```
- “myfun”的名称必须和文件名称一致，否则会报错。
- 此处输入变量和输出变量必须有限个且全部罗列。
- 在函数里，对输入变量都要应用，对输出变量都要赋值



---
# 图像处理基本操作
- [matlab灰度化、二值化处理图像@CSDN:苍白的咏叹调](https://blog.csdn.net/kuishao1314aa/article/details/84798625?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522161595308616780271574440%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=161595308616780271574440&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~baidu_landing_v2~default-2-84798625.first_rank_v2_pc_rank_v29&utm_term=matlab%E5%8F%98%E6%8D%A2%E4%B8%BA%E7%81%B0%E5%BA%A6%E5%9B%BE%E5%83%8F)

  ---
## 基操
- 将图像读取为一个矩阵
    ```Matlab
    data = imread('图像绝对路径');
    ```
  ---
- 创建2行2列的子图,并将读取的图在1号位上显示
  ```Matlab
  subplot(221);   
  imshow(data);
  ```
  ---
- 添加总图标题
  ```Matlab
  suptitle('图像处理基本操作')
  ```

<div STYLE="page-break-after: always;"></div>
  
> - 建议总标题放在所有子图都绘制完毕之后,这样不会挡到子图的标题  
>   ![20210320074241](http:cdn.ayusummer233.top/img/20210320074241.png)
> - 如果先定义总标题,则可能会遮挡子图表题
>   ![20210320074257](http:cdn.ayusummer233.top/img/20210320074257.png)

---
- 保存图像
  ```Matlab
  %保存当前窗口的图像
  saveas(gcf,图像绝对路径); 
  ```


---
## 灰度化处理
  ```Matlab
  gdata = rgb2gray(data);
  ```
  - `rgb2gray` : 通过消除图像色调和饱和度信息同时保留亮度实现将将RGB图像或彩色图转换为灰度图像，即灰度化处理的功能

---
## 二值化
  ```Matlab
  n = graythresh(gdata);
  bw=im2bw(data,n);
  ```
  - `graythresh` : 最大类间方差法是一种自适应的阈值确定的方法,又叫大津法,简称`OTSU`。它是按图像的灰度特性,将图像分成背景和目标2部分。在使用`im2bw`函数将灰度图像转换为二值图像时，需要设定一个阈值，这个函数可以帮助我们获得一个合适的阈值。
- `Matlab2019b`推荐用`imbinarize`而非`im2bw`


  ---
### `imbinarize`和`im2bw`的区别
- ```Matlab
  bw = im2bw(g, level);
  bw = imbinarize(g, level);
  ```
- 在`matlab2018`中建议用`imbinarize`来将图片转换为二值图，其**参数必须为灰度图**。
- 在`matlab2016`中,只有`im2bw`函数,其参数可以是灰度图或RGB图。
> - 从上面两句话可以看出二者的主要区别，两者接收的参数类型不同：

<div STYLE="page-break-after: always;"></div>

> - 但是当`im2bw`的`level`省略时，默认为 0.5；而`imbinzrize`的阈值默认值使用OTSU方法来得到的。
> - ![20210319182201](http:cdn.ayusummer233.top/img/20210319182201.png)
> - ![20210319183250](http:cdn.ayusummer233.top/img/20210319183250.png)
- 阈值 level 的作用为：
  - 用值 1 (白色)替换输入图像中亮度大于 level 比例的所有像素
  - 用值 0 (黑色)替换所有其他像素。


---
## 最邻近插值(NearestInterpolation)
- [参考链接@CSDN:kill2013110](https://blog.csdn.net/kill2013110/article/details/108123824)
- Digital Image Processing 4th Edition [Rafael C. Gonzalez] **Section2.4 P91**
- 自定义最邻近插值算法  
  ```Matlab
  function [dst]=NearestInterpolation(src,K)
  % 最近邻法插值
  % 输入：源图像src，放大倍数K
  % 输出：目标图像矩阵dst

  [srcM,srcN,srcC]=size(src);     % 读取源图像元素点的行列数及色板数
  dstM=round(K*srcM);             % 该处仍要确保当放大倍数K非整数时目标图像大小为整数
  dstN=round(K*srcN);
  
  % 使用class将数据类型统一，目标图像初始化
  dst=ones(dstM,dstN,srcC,class(src));
  
  % 逐像素点赋值
  for dstX=1:dstM
      for dstY=1:dstN
          for dstC=1:srcC
              srcX=round(dstX/K);
              srcY=round(dstY/K);
              srcX(srcX>srcN)=srcN; % 防止索引源图像界外位置,该函数很耗时但简洁
              srcX(srcX<1)=1;
              srcY(srcY>srcM)=srcM ;
              srcY(srcY<1)=1;
              dst(dstX,dstY,dstC)=src(srcX,srcY,dstC);
          end
      end
  end
  end
  ```

  ---
- `round`:四舍五入为最近的小数或整数
  - `Y = round(X)`: 将 X 的每个元素四舍五入为最近的整数。在对等情况下，即有元素的小数部分恰为 0.5 时，round 函数会偏离零四舍五入到具有更大幅值的整数。
  - `Y = round(X,N)`: 四舍五入到 N 位数：
    - `N > 0`：舍入到小数点右侧的第 N 位数。
    - `N = 0`：四舍五入到最接近的整数。
    - `N < 0`：舍入到小数点左侧的第 N 位数。

  ---
- `ones` : 创建全部为1的数组
  - `X = ones` : 返回标量 1。
  - `X = ones(n)` : 返回一个 n×n 的全 1 矩阵。
  - `X = ones(sz1,...,szN)` : 返回由 1 组成的 sz1×...×szN 数组，其中 sz1,...,szN 指示每个维度的大小。例如，ones(2,3) 返回由 1 组成的 2×3 数组。
  - `X = ones(sz)` : 返回一个由 1 组成的数组，其中大小向量 sz 定义 size(X)。例如，ones([2,3]) 返回由 1 组成的 2×3 数组。
  - `X = ones(classname)` : 返回标量 1，其中 `classname` 指定数据类型。例如，`ones('int8')` 返回一个 8 位整数标量 1。
  - `X = ones(n,classname)` : 返回一个由 1 组成并且数据类型为 classname 的 n×n 数组。
  - `X = ones(sz1,...,szN,classname)` : 返回一个由 1 组成并且数据类型为 `classname` 的 `sz1×...×szN` 数组。
  - `X = ones(sz,classname)` : 返回一个由 1 组成的数组，其中大小向量 sz 定义 size(X)，classname 定义 class(X)。
  - `X = ones('like',p)` : 返回一个与数值变量 p 具有相同的数据类型、稀疏性和复/实性（实数或复数）的标量 1。
  - `X = ones(n,'like',p)` : 返回一个由 1 组成的如同 p 的 n×n 数组。
  - `X = ones(sz1,...,szN,'like',p)` :  返回一个由 1 组成的如同 p 的 sz1×...×szN 数组。
  - `X = ones(sz,'like',p)` : 返回一个由 1 组成的如同 p 的数组，其中大小向量 sz 定义 size(X)。
> matlab中读取图片后保存的数据是uint8类型(8位无符号整数，即1个字节)，以此方式存储的图像称作8位图像，相比较matlab默认数据类型双精度浮点double（64位，8个字节）可以节省存储空间