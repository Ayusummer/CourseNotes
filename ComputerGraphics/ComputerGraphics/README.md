<!--
 * @Author: your name
 * @Date: 2021-05-30 21:52:43
 * @LastEditTime: 2021-05-30 22:12:23
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \JuniorLesson_SecondTerm\ComputerGraphics\ComputerGraphics\README.md
-->
# 项目结构说明
- ComputerGraphics  : 项目根目录
  - curve_fitting   : 曲线拟合模块
  - Graphic_convert_2D  : 二维图形变换模块
  - Graphic_draw_2D : 二维图形绘制模块
  - linesegmentCut  : 线段裁剪模块
  - `basic_draw.py`  : 基本绘制函数模块
  - `GlobalTest.py`  : 随手测试模块
  - `main.py` : 主程序模块
  - `README.md`   : 帮助文档
  - `requirements.txt`    : 项目依赖
  - `test_function.py`    : 随手测试函数模块


----
# 系统开发环境
- win10专业版
- IDE选择 : Pycharm+Anaconda
  - `Pycharm Community 2021.1`
  - `conda 4.10.1`
- python版本 : `python3.9.5`
- 导入第三方库版本
  - numpy==1.20.3
  - turtle==0.0.1
  - matplotlib==3.4.2


---
# 程序运行指南
- 在项目根目录下用命令行使用 `pip ` 命令安装项目依赖
  ```
  pip intsall -r requirements.txt -i https://mirrors.aliyun.com/pypi/simple/
  ```
- 或者从[此处](https://ayusummer-my.sharepoint.com/:f:/g/personal/233_ayusummer_onmicrosoft_com/ErJVJJHS1vpChkWlHIpbkaYB76nehJkwDWJYBiMOsDGdqA?e=KfPzwV)下载项目虚拟环境压缩包并解压到本地纯英文(无空格)的目录下;  
  使用一个自己顺手的 IDE, 将运行环境指向解压后的项目虚拟环境

- 运行项目根目录下的 `main.py` 文件即可
