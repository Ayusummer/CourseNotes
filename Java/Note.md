# 前言

## 实验环境

- 软件:
  - IDEAU2020.2
- 编码方案
  - 没有特殊声明的情况下都是 UTF-8

---

# 考试相关

- 单选
- 多选
- 判断
- 程序写结果(从题库里的编程题摘的)
- 简答题
- 编程题

---

# API 文档

- [在线文档链接](https://www.matools.com/api/java8)

# 各种类的介绍

- Week4

## 任务

- 常用类
- 容器类
- 异常类

## 实验课任务

- 字符串相关类(String StringBuffer)
- 基本数据类型包装类
- Math 类
- File 类
- 枚举类

## 常用类

### String 类

java.lang.String

```java
public final class String
extends Object
implements Serializable, Comparable<String>, CharSequence
```

---

#### 实现了以下接口

- Serializable
- CharSequence
- Comparable< String >

---

#### 概述

- String 类代表字符串。  
  Java 程序中的所有字符串文字（例如"abc" ）都被实现为此类的实例。
- 字符串不变; 它们的值在创建后不能被更改。
- 字符串缓冲区支持可变字符串。 因为 String 对象是不可变的，它们可以被共享。 例如：

```java
 String str = "abc";
```

相当于：

```java
     char data[] = {'a', 'b', 'c'};
     String str = new String(data);
```

---

#### String 类型与其他类型的转换

- [原文链接](https://www.cnblogs.com/mingbai/p/intToString.html)
- 其他类型转 String
  ```Java
  String s = String.valueOf( value); // 其中 value 为任意一种数字类型。
  ```
- String 转其他类型
  ```Java
  String s = "169";
  byte b = Byte.parseByte( s );
  short t = Short.parseShort( s );
  int i = Integer.parseInt( s );
  long l = Long.parseLong( s );
  Float f = Float.parseFloat( s );
  Double d = Double.parseDouble( s );
  ```

---

## 随笔

# JavaGUI

- Week5

## 内容包括

- AWT(Abstract Window Toolkit)
- 组件和容器
- 布局管理器
- 事件处理
- Java 图形
- Window 事件

---

## AWT

- 使用 AWT 所涉及的类一把在 java.awt 包及其子包中;
- Container 和 Component 是 AWT 中的两个核心类;
  ![](R./../res/awtclass.png)

## Component&Container

- java 图形界面最基本的组成成分是 Component,该类及其子类对象是可视化的可交互的 GUI 元素;
- 而 Component 不能独立存在,要放在 Container 中存在
- Container 子类对象可以容纳其他 Component 对象
- Container 对象使用 add 方法添加其他 Component 对象
  - Container 作为 Component 的子类自然地一个 Container 对象也可添加到另一个 Container 对象中
- 有两种常用的 Container
  - Window  
    其对象表示自由停泊的顶级窗口
  - Panel  
    其对象作为可容纳其他 Container 的对象不能独立存在,需要放在其他 Container 中(如 Window 或 Applet)

## Frame&JFrame

- Frame 是 Window 的子类,由 Frame 或其子类创建的对象为一个窗体
- 常用构造方法
  - 空参
  - Frame(String s) //创建标题栏为字符串 s 的窗口
  -

---

## JTextField

文本输入框

- 获取文本输入框内容
  ```Java
  textField.getText();
  ```
  - 获取到的内容判空
  ```Java
  if(textField.getText().equals(""))
  ```

---

## 本周作业:记事本

### 任务

用 javaGUI 完成记事本的程序功能。

### 具体要求：

- 具有以下菜单项：文件、编辑、设置、版本
- 文件菜单中有：打开、保存、退出的功能，其中涉及到流操作可以只将文件的路径答应出来。
- 编辑菜单中有拷贝、黏贴、剪切功能。
- 设置菜单中可以设置文档文字大小、颜色。
- 版本菜单能够显示版本信息。
- 文本域中提供右键菜单功能。

### 提交方式

项目文件打包作为答案上传

---

### 要求解构分析

- 结构分析

  - 不采用分层结构 JLayeredPane 仅采用一层结构就够用了
    - 毕竟记事本做得太臃肿也不是什么好事
  - > 下面自下而上将 GUI 分层
  - JFrame baseFrame(采用默认的 BorderLayout)

    - baseFrame.add(菜单栏)
    - 菜单栏:Menubar
    - 因为菜单栏可能后续会有扩展,所以将菜单栏的创建封装成一个函数
    - 文件菜单中有：打开、保存、退出的功能，其中涉及到流操作可以只将文件的路径答应出来。
      - 文件菜单 file
        - 打开 open
        - 新建 newFile
        - 保存 save
        - 退出
    - 编辑菜单
      - 拷贝 copy
      - 粘贴 paste
      - 剪切 cut
    - 设置菜单
      - 设置文档文字大小 setTextSize
      - 设置文字颜色 setTextColor
    - 版本 version

      - 显示版本信息

    - baseFrame.add(文本区域)
    - 文本区域始终不改变形态,设置成一个静态对象
      - static TextArea textArea;
    - 文本区域也要添加功能,所以添加文本区域也封装成一个函数
    - 可以右键菜单

---

### 实验随笔

- JTextField
  - 获取内容
    ```Java
    textField.getText();
    ```
    - 判空
      ```Java
      if(textField.getText().equals(""))
      ```
- 界面构建好之后重新设置组件大小或者加入新的组件应当重载面板
  ```Java
  containerName.revalidate();
  ```
- 弹出简单的提示对话框
  ```Java
  JOptionPane.showMessageDialog(baseFrame, "请输入特殊点纵坐标");
  ```
  - ![](R./../res/简单的提示对话框.png)

---

## 随笔

- 不等列的二维数组
  - java 中可以使用不等长的二维数组
    ```java
        public static void main(String[] args){
          int a[][]=new int[5][];
          a[0]=new int[4];
          for(int i=0;i<a.length;i++){
            System.out.println(a[i]);
          }
        }
    ```
  - 输出结果:
    ```
    [I@1b6d3586
    null
    null
    null
    null
    ```
- JFrmae 默认布局模式为 BoarderLayout

---

# 流

- Week6

## 本节内容

---

## Java 流输入输出原理

![](R./../res/Java流式输入输出原理.png)

- 在 java 程序中,对于数据的输入/输出操作以"流"(stream)方式进行;
- J2SDK 提供了各种各样的"流"类,用以获取不同种类的数据;
- 程序中通过**标准**的方法输入或输出数据

---

- java.io 包中定义了多个流类型(类或抽象类)来实现输入/输出功能;  
  可以从不同的角度对其进行分类:
  - 按数据流的方向不同可以分为输入流和输出流
  - 按数据单位不同可以分为字节流和字符流
  - 按照功能不同可以分为节点流和处理流

---

- J2SDK 所提供的所有流类型位于包 java.io 内部分别继承自一下四种抽象流类型
  | | 字节流 | 字符流 |
  | - | - | - |
  | 输入流 | InputStream | Reader |
  | 输出流 | OutputStream | Writer |

---

- 节点流为可以从一个特定的数据源(节点)读写数据(如:文件,内存)
  ![](R./../res/节点流.png)
- 处理流是"连接"在已存在的流(节点流或处理流)之上,通过对数据的处理为程序提供更为强大的读写功能;
  ![](R./../res/处理流.png)

---

## InputStream

- 继承自 InputStream 的流都是用于向程序输入数据,且数据的单位为字节(8 bit):  
  下图中深色为节点流,浅色为处理流
  ![](R./../res/InputStream.png)

```Java
这里应当有一个示例
```

---

## OutputStream

- 继承自 OutputStream 的流适用于程序中输入数据,且数据的单位为字节(8 bit);  
  下图中深色为节点流,浅色为处理流
  ![](R./../res/OutputStream.png)

```Java
// 向输出流中写入一个字节数据,该字节数据为参数b的低8位
void write(int b) throws IOException

// 将一个字节类型的数组中的数据写入输出流
void write(byte[] b) throws IOException

// 将一个字节类型的数组中的从指定位置(off)开始的
// len个字节写入到输出流
void write(byte[] b, int off, int len) throws IOException

// 关闭流释放内存资源

```

---

# 线程

- Week7

## 线程概述

- 线程与进程
  - 进程就是一个运行中的程序。
  - 一个进程中可以有多个线程，线程是 CPU 调度和分派的基本单位。
    - 我们可以理解为线程就是程序运行中的一条路径。

---

- 多线程存在的意义
  - 允许多个线程并发执行，提高程序运行效率。
    - 例如：迅雷多线程下载，QQ 多个人同时聊天，凌波多个人同时共享屏幕。

---

- 线程是操作系统的概念，线程也称为轻量级进程（light-weight process，LWP），是 CPU 的基本使用单元，它的轻量级名称是和进程相关的。
  - 线程由线程 ID、程序计数器、寄存器和堆栈组成
  - 多个线程可以共享代码段、数据段和诸如打开的文件等系统资源。
    - 而传统的进程其实就是单线程控制程序，每个进程都有自己的代码段、数据段和其他系统资源。
      - 这无疑使得每个进程管理更多的内容，从而称为重量级进程。
      - “轻量”是指线程没有独自的存储空间，而是和同一个进程的多个线程共享存储空间。

---

## 线程的使用

- Java 的多线程机制提供了两种方式实现多线程编程：
  - 一种是通过继承 java.long.Thread 类来实现，
  - 另一种是通 过实现 Runnable 接口实现。

---

### 继承 Thread 类创建线程

- Thread 类为 Java 实现多线程提供了简单的方法。
  - Thread 类已经具备了运行多线程所需要的资源，
    - 用户只需要重载该类的 run()方法，把需要使用多线程运行的代码放入该方法。这样这些代码就可以和 其他线程“同时”存在，
    - 创建线程对象并用该对象调用 start()方法则线程开始运行。
      - start()方法提供了启动线程和线程运行所需要的框架。

---

## 加锁

- 关键字:
  ```Java
  synchronized
  ```

### 给代码段加锁

```Java
        // 对类的当前对象加锁
        synchronized(this){
            temp = count;
            temp = temp - 500;
            count = temp;
            System.out.println("kids:The current count is:"+count);
        }
```

---

## 线程随笔

- ```Java
  object.wait();
  ```
  - 该对象执行该操作后,该对象释放占用资源的占有权
  - 该对象进入深睡眠状态直至被唤醒
- ```java
  Object.notify();    // 只能通知一个沉睡的对象
  Object.notifyAll(); // 通知所有沉睡的对象
  ```
  唤醒需要占用该对象占用资源的深睡眠状态的对象
- > 需要注意的是无论是 wait 还是 notify,都需要放在 synchronized 代码块中

  - > 毕竟要限制资源访问嘛

- ```Java
  Math.random();
  ```
  生成一个 0-1 之间的数据

---

### 给函数加锁

- 锁加在了当前函数所在类的当前实例上
  - 即与之前加在 this 上的效果是一致的

---

# 网络编程

- 网络编程与网站编程
  - 网络编程
    - 构建多台电脑之间的通信
    - 主(Server)从(Client)
      - C/S 架构
  - 网站编程
    - 构建一台电脑与多台电脑之间的通信
      - 主(Server)和 Browser
        - B/S 架构

---

## Socket 编程

- 电脑端口
  - 65535 个端口
    - 1-1024 基本上都被系统使用

---

### 案例分析 1 UDPTest

#### UDP

- Internet 协议集支持一个无连接的传输协议，
- 该协议称为用户数据报协议（UDP，User Datagram Protocol）。
- UDP 为应用程序提供了一种无需建立连接就可以发送封装的 IP 数据包的方法。
- Internet 的传输层有两个主要协议，互为补充。
  - 无连接的是 UDP，它除了给应用程序发送数据包功能并允许它们在所需的层次上架构自己的协议之外，几乎没有做什么特别的事情。
  - 面向连接的是 TCP，该协议几乎做了所有的事情。

---

#### 功能

---

#### 发送端定义

```Java
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class UDPSender {
    public static void main(String[] args) throws Exception {
        // 定义一个指定端口号为3000的发送端DatagramSocket对象
        DatagramSocket client = new DatagramSocket(3000);
        // 定义要发送的数据
        String str = "hello world";
        // 定义一个DatagramPacket数据报对象，封装发送端信息以及发送地址
        DatagramPacket packet = new DatagramPacket(str.getBytes(),
                str.getBytes().length,
                InetAddress.getByName("localhost"),
                8900);
        System.out.println("开始发送信息...");
        client.send(packet); // 发送数据
        byte[] buff = new byte[1024];
        DatagramPacket receivepacket =
                new DatagramPacket(buff,buff.length);
        client.receive(receivepacket);
        String string = new String(receivepacket.getData(),0,receivepacket.getLength());
        System.out.println(string);
        client.close();      // 释放资源
    }
}
```

- Datagram 数据报
- Socket 套接字
  - 所谓套接字(Socket)，就是对网络中不同主机上的应用进程之间进行双向通信的端点的抽象。
  - 一个套接字就是网络上进程通信的一端，提供了应用层进程利用网络协议交换数据的机制。
  - 从所处的地位来讲，套接字上联应用进程，下联网络协议栈，是应用程序通过网络协议进行通信的接口，是应用程序与网络协议根进行交互的接口

---

- DatagramSocket
  - 此类表示用于发送和接收数据报数据包的套接字。
  - 数据报套接字是分组传送服务的发送或接收点。
    - 在数据报套接字上发送或接收的每个数据包都被单独寻址和路由。
      - 从一个机器发送到另一个机器的多个分组可以不同地路由，并且可以以任何顺序到达。
  - send(DatagramPacket p)
    - 返回类型
      - void
    - 功能
      - 从此套接字发送数据报包。
  - ```Java
    public void receive(DatagramPacket p)
             throws IOException
    ```
    - 从此套接字接收数据报包。
    - 当此方法返回时， DatagramPacket 的缓冲区将填充接收到的数据。

---

- DatagramPacket
  - 该类表示数据报包
  - 数据报包用于实现无连接分组传送服务。
  - 仅基于该数据包中包含的信息，每个消息从一台机器路由到另一台机器。
  - 从一台机器发送到另一台机器的多个分组可能会有不同的路由，并且可能以任何顺序到达。
  - 包传送不能保证。
- InetAddress
  - 此类表示 Internet 协议（IP）地址。
  - IP 地址是由 IP 使用的 32 位或 128 位无符号数字，构建 UDP 和 TCP 协议的低级协议。
  - InetAddress 的一个实例由一个 IP 地址和可能的相应主机名组成（取决于它是用主机名构造还是已经完成了反向主机名解析）。
  - getByName(String host)
    - 返回类型
      - static InetAddress
    - 功能
      - 确定主机名称的 IP 地址。

---

```Java
import java.net.DatagramPacket;
import java.net.DatagramSocket;

public class UDPReceiver {
    public static void main(String[] args) throws Exception {
        // 定义一个指定端口号为8900的接收端DatagramSocket对象
        DatagramSocket server = new DatagramSocket(8900);
        // 定义一个长度为1024的字节数组，用于接收数据
        byte[] buf = new byte[1024];
        // 定义一个DatagramPacket数据报对象，用于封装接收的数据
        DatagramPacket packet = new DatagramPacket(buf, buf.length);
        System.out.println("等待接收数据...");
        while (true){
            // 等待接收数据报数据，在没有接收到数据之前会处于阻塞状态
            server.receive(packet);
            // 调用DatagramPacket的方法获得接收到的信息,并转换为字符串形式
            String str = new String(packet.getData(),
                    0, packet.getLength());
            System.out.println(packet.getAddress()+ ":"
                    + packet.getPort()+"发送消息："+str);
            DatagramPacket returnpacket = new DatagramPacket(
                    "I get it".getBytes(), "I get it".length()
                    ,packet.getAddress(),packet.getPort());
            server.send(returnpacket);
        }
    }
}
```

---

# Java 基础备课笔记学习

## 1.2 Java 开发环境搭建

### jdk 与 jre

- JDK(Java Development Kit)  
  Java 开发工具，包含开发 Java 程序的所有组件，**包含 JRE**
- JRE(Java Runtime Environment)  
  Java 运行环境，如果要运行 Java 程序，就需要 JRE 的支持
- 常用组件
  - src.zip  
    Java 是一门开源的语言，其源代码都在这个压缩包中
  - rt.jar <br/>
    Java 的基础核心类库，我们编写 Java 程序时使用的 class 都在这个 jar 包中
  - javac.exe  
    编译器，将.java 源代码编译为.class 文件
  - java.exe <br/>
    虚拟机，运行 Java 程序的工具
  - jar.exe <br/>
    将 class 文件打成 jar 包的工具
  - javadoc.exe  
    生成帮助文档的工具

---

### 环境变量

- 环境变量是指在操作系统中用来指定操作系统运行环境的一些参数

#### path

- 如果想在任意目录下运行一个程序，我们就需要将程序所在的路径配置在 path 环境变量中。
- 通常我们会将 javac.exe 所在目录配置到 path 中，因为我们需要在任意目录下都能编译 Java 源文件。
- 配置完成之后可以在命令行输入 javac 测试，如果显式帮助信息则是配置成功。

---

#### classpath

- Java 虚拟机运行时加载类的路径。JDK5 之后不配置默认为当前目录“.”。如使用 JDK1.4 或以下版本时需要人工配置。
- 暂时不需要配置，默认加载当前目录下的所有 class 文件。
  > 环境变量删除:
  >
  > - CLASSPATH
  > - .;%JAVA_HOME%\lib\dt.jar;%JAVA_HOME%\lib\tools.jar

---

#### 配置方式

- 命令行
  - 点击屏幕左下角开始 – 运行 – 输入 cmd – 在命令行中直接输入命令进行修改
  - 查看变量值：set 变量名
  - 设置变量值：**set 变量名=变量值**，
    - 多个值之间使用分号“;”分割，引用变量时使用“%变量名%”形式
  - 注意：此种方式**仅适用于当前窗口**
- 我的电脑(此电脑)
  - 鼠标右键点击我的电脑 – 属性 – 高级 – 环境变量
  - 找到要修改的变量将其值修改，此种方式永久有效
- 注意：
  - 配置环境变量之后可以查看编译器(javac.exe)和虚拟机(java.exe)版本，**虚拟机版本不能低于编译器**。
  - 使用哪个版本的编译器和虚拟机取决于 path 环境变量，如果虚拟机版本过低，可以通过环境变量来修改。
  - 编译器版本查看方式：javac –version
  - 虚拟机版本查看方式：java –version
    > 由此方法发现了我的虚拟机版本低于我的编译器版本
    >
    > - 原因是我装了两个 jdk,配置环境变量的时候配置串了
    > - 于是我把 jdk 配置改成了 openjdk

---

## 1.3 第一个 Java 程序

### 编写源代码

- 新建文本文档，扩展名改为.java，在文件中写入代码。
  ![](https://codimd.s3.shivering-isles.com/demo/uploads/upload_942861dae43922f9044eda4adef7ab6d.png)
- 注意：
  - windows 操作系统默认是隐藏已知文件扩展名的。
  - 请测试新建一个文本文档，如果看到的文件名是“新建 文本文档”而不是“新建 文本文档.txt”，那么说明你的扩展名被隐藏了。
  - 请选择菜单栏中的 工具 – 文件夹选项 – 查看 – 下拉滚动条找到“隐藏已知文件扩展名” – 取消掉这一项。

---

### 编译字节码文件

- 左键单机屏幕左下角开始 – 运行 – 输入 cmd 启动命令行窗口
  - > 或 Win+R,输入 cmd 并回车
- 使用 DOS 命令进入源代码所在目录
  - cd 目录路径
- 使用编译器（javac.exe）编译源代码
  - javac 文件名.java
  - 编译后在该目录中会出现扩展名为 class 的字节码文件
  - > 这里我编译报错" 编码 GBK 的不可映射字符",因为我的项目设置里编码类型选的是 UTF-8,所以这里的编码命令应当是
    >
    > ```
    > javac -encoding UTF-8 文件名
    > ```

---

## 3.21 包

- 如果一个类被声明为**public**，那么必须和文件名同名
- 导入类的时候
  - 直接导入该类所属包的全部类
    - 优先匹配当前包中的类,若无再匹配导入包中的类
  - 导入具体类名
    - 不论当前包中是否有同名类都匹配导入的类
- 无包的类可以使用有包的类，有包的类不能使用无包的类。

---

# MyBatis

## 下载

- [下载链接](https://github.com/mybatis/mybatis-3/releases")

---

# 第 1 章 Spring 的基本应用

---

## 1.1 Spring 概述

- Spring 是当前主流的 Java Web 开发框架，它是为了解决企业应用开发的复杂性问题而产生的;

---

### 1.1.1 什么是 Spring

- 一个分层的 Java SE/EE full-stack (一站式)轻量级开源框架
  - 以 IOC,AOP 为内核，使用基本的 JavaBean 来完成以前只可能由 EJB 完成的工作，取代了 EJB 的靡肿 低效的开发模式
  - loC ( Inversion of Control ，控制反转)
  - AOP ( Aspect Oriented Programming , 面向切面编程)
  - EJB ( Enterprise Java Beans , Java 企业 Bean)
- Spring 致力于 Java EE 应用各层的解决方案
  - 在表现层它提供了 Spring MVC 以及与 Struts 框架的整合功能;
  - 在业务逻辑层可以管理事务 记录日志等;
  - 在持久层可以整合 $MyBatis$,$Hibernate$,$JdbcTemplate$ 等技术
  - 因此，可以说 Spring 是企业应用开发很好的"一站式"选择;
  - 虽然 Spring 贯穿于表现层 业务逻辑层和持久层，但它并不想取代那些已有的框架，而是以高度的开放性与它们进行无缝整合

---

### 1.1.2 Spring 框架的优点

- Spring 具有简单、可测试和松耦合等特点，从这个角度出发， Spring 不仅可以用于服务器端开发，也可以应用于任何 Java 应用的开发中;
- 关于 Spring 框架优点的总结，具体如下
  - 非侵入式设计
    - Spring 是一种非侵入式 ( non-invasive )框架，它可以使应用程序代码对框架的依赖最小化
  - 方便解耦, 简化开发
    - Spring 就是一个大工厂，可以将所有对象的创建和依赖关系的维护工作都交给 Spring 容器管理，大大地降低了组件之间的搞合性
  - 支持 AOP
    - Spring 提供了对 AOP 的支持，它允许将一些通用任务，如安全,事务,日志等进行集中式处理，从而提高了程序的复用性;
  - 支持声明式事务处理
    - 只需要通过配置就可以完成对事务的管理，而无须手动编程
  - 方便程序的测试
    - Spring 提供了对 Junit4 的支持，可以通过注解方便地测试 Spring 程序
  - 方便集成各种优秀框架
    - Spring 不排斥各种优秀的开源框架，其内部提供了对各种优秀框架的直接支持
      - 如 Struts Hibernate MyBatis Quartz 等
  - 降低 Java EE API 的使用难度
    - Spring 对 Java EE 开发中非常难用的一些 API (如 JDBC JavaMail 等)，都提供了封装，使这些 API 应用难度大大降低

---

### 1.1.3 Spring 的体系结构

- Spring 框架采用的是分层架构，它一系列的功能要素被分成 20 个模块，这些模块大体分为
  - Core Container
  - Data Access/lntegration
  - Web
  - AOP (Aspect Oriented Programming)
  - Instrwmentation
  - Messaging
  - Test

<!-- ![Spring的体系结构](../res/img/Java/Spring的体系结构.png) -->

![20220328185602](http://cdn.ayusummer233.top/img/20220328185602.png)

- 在上图中，包含 Spring 框架的所有模块
  - 灰色背景模块为本书中所涉及的主要模块
- 接下来分别对体系结构中的模块作用进行简单介绍

---

#### 1.Core Container (核心容器)

- Spring 的核心容器是其他模块建立的基础，它主要由 Beans 模块、 Core 模块, Context 模块, Context- support 模块和 SpEL 模块组成
  - Beans 模块
    - 提供了 BeanFa tory ，是工厂模式的经典实现， Spring 将管理对象称为 Bean
  - Core 核心模块:
    - 提供了 Spring 框架的基本组成部分，包括 loC 和 DI 功能
  - Context 上下文模块
    - 建立在 Core 和 Beans 模块的基础之上，它是访问定义和配置的任何对象的媒介;
    - 其中 ApplicationContext 接口是上下文模块的焦点
  - Context-support 模块
    - 提供了对第三方库嵌入 Spring 应用的集成支持,比如:
      - 缓存( EhCache Guava JCache)
      - 邮件服务 (JavaMail)
      - 任务调度( CommonJ Quartz)
      - 模板引擎( FreeMarker, JasperReports, 速率)
  - SpEL 模块:
    - 是 Spring 3.0 后新增的模块，它提供了 Spring Expression Language 支持，是运行时查询和操作对象图的强大的表达式语言;
    - SpEL( Spring Expression Language , Spring 表达式语言)

---

#### 2. Data Access/lntegration (数据访问/集成)

- 数据访问/集成层包括 JDBC, ORM,OXM,JMS 和 Transactions 模块，具体介绍如下
  - JDBC 模块
    - 提供了一个 JDBC 的抽象层，大幅度地减少了在开发过程中对数据库操作的编码
  - ORM 模块
    - 对流行的对象关系映射 API ，包括 JPA, JDO 和 Hibernate 提供了集成层支持
  - OXM 模块
    - 提供了一个支持对象/XML 映射的抽象层实现
      - 如 JAXB, Castor, XMLBeans, JiBX 和 XStream
  - JMS 模块
    - 指 Java 消息传递服务，包含使用和产生信息的特性，自 4.1 版本后支持与 Spring-message 模块的集成;
  - Transactions 事务模块
    - 支持对实现特殊接口以及所有 POJO 类的编程和声明式的事务管理

---

#### 3. Web

- Spring 的 Web 层包括 WebSocket, Servlet, Web 和 Portlet 模块，具体介绍如下
  - WebSocket 模块
    - Spring 4.0 以后新增的模块，它提供了 WebSocket 和 SockJS 的实现，以及对 STOMP 的支持
  - Servlet 模块
    - 也称为 Spring-webmvc 模块，包含了 Spring 的模型一视图一控制器(MVC) 和 REST Web Services 实现的 Web 应用程序
  - Web 模块
    - 提供了基本的 Web 开发集成特性
      - 例如:多文件上传功能,使用 Servlet 听器来初始化 loC 容器以及 Web 应用上下文
  - Portlet 模块
    - 提供了在 Portlet 环境中使用 MVC 实现，类似 Servlet 模块的功能

---

#### 4. 其他模块

- Spring 的其他模块还有 AOP, Aspects, Instrumentation 以及 Test 模块，具体介绍如下:
  - AOP 模块
    - 提供了面向切面编程实现，允许定义方法拦截器和切入点，将代码按照功能进行分离，以降低搞合性
  - Aspects 模块
    - 提供了与 AspectJ 的集成功能
      - AspectJ 是一个功能强大且成熟的面向切面编程 (AOP) 框架
  - Instrumentation 模块
    - 提供了类工具的支持和类加载器的实现，可以在特定的应用服务器中使用
  - Messaging 模块
    - Spring 4.0 以后新增的模块
    - 它提供了对消息传递体系结构和协议的支持
  - Test 模块
    - 提供了对单元测试和集成测试的支持

---

# 第 3 章 Spring AOP

- 学习目标

  - 了解 AOP 的概念和作用
  - 理解 AOP 中的相关术语
  - 了解 Spring 中两种动态代理方式的区别
  - 掌握基于代理类的 AOP 实现
  - 掌握基于 XML 和注解的 AspectJ 开发

- Spring AOP 模块，是 Spring 框架体系结构中十分重要的内容，该模块中提供了**面向切面编程**实现

---

## 3.1 Spring AOP 简介

---

### 3.1.1 什么是 AOP

- AOP 的全称是 Aspect-Oriented Programming ，即面向切面编程(也称面向方面编程)
  - 是面向对象编程 (OOP) 的一种补充，目前已成为一种比较成熟的编程方式
- 在传统的业务处理代码中，通常都会进行事务处理、日志记录等操作 虽然使用 OOP 可以通过组合或者继承的方式来达到代码的重用，
  - 但如果要实现某个功能( 如日志记录)，同样的代码仍然会分散到各个方法中 这样，如果想要关闭某个功能，或者对其进行修改，就必须要修改所有的相关方法 这不但增加了开发人员的工作量，而且提高了代码的出错率
- 为了解决这一问题， AOP 思想随之产生 AOP 采取横向抽取机制，将分散在各个方法中的重复代码提取出来，然后在程序编译或运行时，再将这些提取出来的代码应用到需要执行的地方;
  - 这种采用横向抽取机制的方式，采用传统的 OOP 思想显然是无法办到的，因为 OOP 只能实现父子关系的纵向的重用
- 虽然 AOP 是一种新的编程思想，但却不是 OOP 的替代品，它只是 OOP 的延伸和补充

---

- 在 AOP 思想中，类与切面的关系如图所示

  <!-- ![](../res/img/Java/AOP中类对切面的关系.png) -->

  ![20220328185621](http://cdn.ayusummer233.top/img/20220328185621.png)

  - 通过 Aspect (切面)分别在 Class1 和 Class2 的方法中加入了事务日志、权限和异常等功能

- AOP 的使用，使开发人员在编写业务逻辑时可以专心于核心业务，而不用过多地关注于其他业务逻辑的实现，这不但提高了开发效率，而且增强了代码的可维护性
- 目前最流行的 AOP 框架有两个，分别为 **Spring AOP** 和 AspectJ
  - Spring AOP
    - 使用纯 Java 实现，不需要专门的编译过程和类加载器，在运行期间通过代理方式向目标类织入增强的代码
  - `AspectJ` 是一个基于`Java`语言的`AOP`框架，从`Spring 2.0`开始， `Spring AOP` 引入了对`AspectJ`的支持，
    - `AspectJ`扩展了 Java 语言，提供了一个专门的编译器，在编译时提供横向代码的织入

---

### 3.1.2 AOP 术语

- 在学习使用`AOP`之前，首先要了解一下`AOP`的专业术语,包括`Aspect`,`Joinpoint`,`Pointcut`,`Advice`,`Target Object`,`Proxy`,`Weaving`
  - Aspect (切面)
    - 在实际应用中，切面通常是指封装的用于横向插入系统功能(如事务、日志等)的类，如图 3-1 中的`Aspect`;该类要被 `Spring` 容器识别为切面，需要在配置文件中通过`<bean>`元素指定
  - Joinpoint (连接点)
    - 在程序执行过程中的某个阶段点，它实际上是对象的一个操作，例如方法的调用或异常的抛出 Spring AOP 中，连接点就是指方法的调用

---

# 第 5 章 Spring 的事务管理

- 学习目标
  - 熟悉`Spring`事务管理的 3 个核心接口
  - 了解 Spring 事务管理的两种方式
  - 掌握基于`XML`和`Annotation`的声明式事务的使用

---

- 通过上一章的学习，读者已经掌握了如何使用 Spring 来操作数据库
  - 但是在实际开发中，操作数据库时还会涉及事务管理问题，为此 `Spring`供了专门用于事务处理的`APl`;
- Spring 事务管理简化了传统的事务管理流程，并且在一定程度上减少了开发者的工作量;

---

## 5.1 Spring 事务管理概述

---

### 5.1.1 事务管理的核心接口

- 在`Spring`的所有`JAR`中,包含一个名为`spring-tx-4.3.6 RELEASE`的`JAR`包,该包就是`Spring`提供的用于事务管理的依赖包;

  - 在该`JAR`包的`org.springframework.transaction`包中，我们可以找到 3 个接口文件

    - `PlatformTransactionManager`
    - `TransactionDefinition`
    - `TransactionStatus`
    - 如下图所示

      <!-- ![](../res/img/Java/5.1.1-事务管理核心接口.png) -->

      ![20220328185644](http://cdn.ayusummer233.top/img/20220328185644.png)

      - 方框标注的 3 个接口文件就是`Spring`事务管理所涉及的 3 个核心接口

---

#### 1.`PlatformTransactionManager`

- `PlatformTransactionManager`接口是`Spring`提供的平台事务管理器，主要用于管理事务;该接口中提供了 3 个事务操作的方法，具体如下
  - ```Java
    TransactionStatus getTransaction (TransactionDefinition definition);  // :用于获取事务状态信息
    ```
  - ```java
     void commit ( TransactionStatus status );    // 用于提交事务
    ```
  - ```java
    void rollback ( TransactionStatus status );   // 用于回滚事务
    ```
  - 在上面的 3 个方法中`getTransaction ( TransactionDefinition definition )`方法会根据`TransactionDefinition`参数返回一个 `TransactionStatus`对象
    - `TransactionStatus`对象就表示一个事务，它被关联在当前执行的线程上

---

- `PlatformTransactionManager`接口只是代表事务管理的接口，它并不知道底层是如何管理事务的，它只需要事务管理提供上面的 3 个方法，但具体如何管理事务则由它的实现类来完成
- `PlatformTransactionManager`接口有许多不同的实现类，常见的几个实现类如下
  - `org.springframework.jdbc.datasource.DataSourceTransactionManager`
    - 用于配置 JDBC 据源的事务管理器。
  - `org.springframework.orm. hibernate4. Hibernate T ransactionManager`
    - 用于配`Hibernate`的事务管理器
  - `org.springframework.transaction.jta.JtaTransactionManager`
    - 用于配置全局事务管理器
  - 当底层采用不同的持久层技术时，系统只需使用不同的`PlatformT ransactionManager`实现类即可

---

#### 2.`TransactionDefinition`

- `TransactionDefinition`接口是事务定义(描述)的对象，该对象中定义了事务规则，并提供了获取事务相关信息的方法，具体如下
  - `String getName()`
    - 获取事务对象名称
  - `int getlsolationLevel()`
    - 获取事务的隔离级别
  - `int getPropagationBehavior()`
    - 获取事务的传播行为
  - `int getTimeout()`
    - 获取事务的超时时间
  - `boolean isReadOnly()`
    - 获取事务是否只读
  - 上述方法中，事务的传播行为是指在同一个方法中，不同操作前后所使用的事务;传播行为有很多种，具体如表 5-1 所示

<!-- ![](../res/img/Java/5.1-传播行为的种类.png) -->

![20220328185702](http://cdn.ayusummer233.top/img/20220328185702.png)

- 在事务管理过程中，传播行为可以控制是否需要创建事务以及如何创建事务，通常情况下，数据的查询不会影响原数据的改变，所以不需要进行事务管理，而对于数据的插入、更新和删除操作，必须进行事务管理
- 如果没有指定事务的传播行为,`Spring`默认传播行为是`REQUIRED`

---

#### 3.`TransactionStatus`

- `TransactionStatus`接口是事务的状态，它描述了某一时间点上事务的状态信息 该接口中包含 6 个方法，具体如下
  - `void flush()`
    - 刷新事务
  - `boolean hasSavepoint()`
    - 获取是否存在保存点
  - `boolean isCompleted()`
    - 获取事务是否完成
  - `boolean isNewTransaction()`
    - 获取是否是新事务
  - `boolean isRollbackOnly()`
    - 获取是否回滚
  - `void setRollbackOnly()`
    - 设置事务回滚

---

### 5.1.2 事务管理的方式

- `Spring`中的事务管理分为两种方式:
  - 传统的编程式事务管理
    - 是通过编写代码实现的事务管理，包括定义事务的开始、正常执行后的事务提交和异常时的事务回滚
  - 声明式事务管理
    - 是通过`AOP`技术实现的事务管理，其主要思想是将事务管理作为一个"切面"代码单独编写，然后通过`AOP`技术将事务管理的"切面"代码织入到业务目标类中

---

- 声明式事务管理最大的优点在于开发者无须通过编程的方式来管理事务，只需在配置文件中进行相关的事务规则声明,就可以将事务规则应用到业务逻辑中;
  - 这使得开发人员可以更加专注于核心业务逻辑代码的编写，在一定程度上减少了工作量，提高了开发效率，所以在实际开发中，通常都推荐使用声明式事务管理
  - 本书主要讲解的就是`Spring`的声明式事务管理

---

## 5.2 声明式事务管理

- `Spring`的声明式事务管理可以通过两种方式来实现
  - 基于`XML`的方式
  - 基于`Annotation`的方式
  - 接下来的两个小节中，将对这两种声明式事务管理方式进行详细讲解

---

### 5.2.1 基于`XML`方式的声明式事务

- 基于`XML`方式的声明式事务管理是通过在配置文件中配置事务规则的相关声明来实现的
- `Spring 2.0` 以后, 提供了`tx`命名空间来配置事务, `tx`命名空间下提供了`<tx:advice>`元素来配置事务的通知(增强处理)
  - 当使用`<tx:advice>` 元素配置了事务的增强处理后，就可以通过编写的`AOP`配置，让`Spring`自动对目标生成代理
- 配置`<tx:advice>`元素时，通常需要指定`id`和`transaction-manager`属性

  - `id`属性是配置文件中的唯一标识，
  - `transaction-manager`属性用于指定事务管理器
  - 除此之外，还需要配置一个`<tx:attributes>`子元素;该子元素可通过配置多个`<tx:method>` 子元素来配置执行事务的细节;
  - `<tx:advice>`元素及其子元素如图 5-2 所示

    <!-- ![](../res/img/Java/5.1.2-txadvice元素及其子元素.png) -->

    ![20220328185733](http://cdn.ayusummer233.top/img/20220328185733.png)

- 在图 5-2 中，配置`<tx:advice>`元素的重点是配置`<tx:method>`子元素，图中使用灰色标的几个属性是`<tx:method>`元素中的常用属性
- 关于`<tx method>`元素的属性描述如表 5-2 所示

<!-- ![](../res/img/Java/表5-2.png)   -->

![20220328185754](http://cdn.ayusummer233.top/img/20220328185754.png)

---

### 案例

- 了解了如何在`XML`文件中配置事务后，接下来通过一个案例来演示如何通过`XML`方式来实`Spring`的声明式事务管理;本案例以上一章的项目代码和数据表为基础，编写一个模拟银行转账的程序，要求在转账时通过`Spring`对事务进行控制，其具体实现步骤如下:
- (1)创建一个名为`chapter05`的 Web 项目，在项目的`lib`目录中导入`chapter04`项目中的所有`JAR`包，并将`AOP`所需`JAR`包也导入到`lib`目录中;导入后的`lib`目录如`图5-3`所示

---

# 第 11 章 `Spring MVC` 入门

- 学习目标
  - 了解`Spring MVC`的特点
  - 掌握`Spring MVC`入门程序的编写
  - 熟悉`Spring MVC`的工作流程
- 通过前面章节的学习，读者已经可以掌握`SSM`框架中`Spring`框架和`MyBatis`框架的使用，并学会了如何将两个框架进行整合;从本章开始，将讲解`SSM`中的最后一个框架:`Spring MVC`

---

## 11.1 `Spring MVC`概述

- `Spring MVC`是`Spring`提供的一个实现了`Web MVC`设计模式的轻量级`Web`框架;它与`Struts 2`框架一样，都属于`MVC`框架，但其使用和性能等方面比`Struts 2`更加优异

---

- `Spring MVC`具有如下特点:
  - 是`Spring`框架的一部分，可以方便地利用`Spring`所提供的其他功能
  - 灵活性强，易于与其他框架集成
  - 提供了一个前端控制器`DispatcherServlet`, 使开发人员无须额外开发控制器对象
  - 可自动绑定用户输入，并能正确的转换数据类型
  - 内置了常见的校验器，可以校验用户输入;
    - 如果校验不能通过，那么就会重定向到输入表单
  - 支持国际化 可以根据用户区域显示多国语言
  - 支持多种视图技术;
    - 它支持`JSP`, `Velocity`, `FreeMarker` 等视图技术
  - 使用基于`XML`的配置文件，在编辑后，不需要重新编译应用程序
- 除上述几个优点外, `Spring MVC`还有很多其他优点，由于篇幅有限，这里就不一一列举了;在接下来的学习中，读者会逐渐地体会到`Spring MVC`的这些优点

---

## 11.2 第一个`SPring MVC`应用

- 了解了什么是`Spring MVC`，以及它的一些优点后，接下来本小节将通过一个简单的入门案例，来演示`Spring MVC`的使用，具体实现步骤如下
- 1.创建顶目，引入`JAR`包;

  - 创建一个名称为`chapter11`的`Web`项目，在项目的`lib`目录中添加运行`Spring MVC`程序所需要的 JAR 包，并发布到类路径下，添加后的项目结构如`图 11-1`所示

    <!-- ![](../res/img/Java/图11-1.png)   -->

    ![20220328185827](http://cdn.ayusummer233.top/img/20220328185827.png)

    > [Tomcat 的安装与配置]()
