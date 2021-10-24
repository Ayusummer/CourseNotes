# 实验 2 - Hadoop + MapReduce

## 实验要求与内容

- [Hadoop 官网](http://hadoop.apache.org/)
  - 读文档并跟着文档的步骤进行部署
- 使用两个虚拟机或 1 个虚拟机

> 建议不要装在实验 1 安装 CloudStack 的虚拟机里
>
> 也不打算装在那里面, 一个 CloudStack 已经几乎把服务器性能吃完了(, 远程通信搞崩了几次

- 选一个不是特别新的 `Hadoop` 版本进行安装

- 安装完 Hadoop 后对其性能进行测试

  - 要求使用多于一个性能测试工具
    - 测试 I/O 及其他性能
    - 测试 DFSIO, DFSIOTest 及其他
  - 测试内容要与其他同学不同
  - 需要些报告, 报告中测试性能结果也不能一样, 雷同则都无效

- 在 Hadoop 上编写并运行一个应用程序

  - Hadoop 上有个例子是统计词频, 但是不能直接用原版, 要修改
  - 新建一个文本文件
    - 文件中有若干字符
  - 将文件存储在 Hadoop 中
    - single node mode
  - 实现应用
    - 统计文档中各单词的数量
    - 使用 MapReduce 框架
  - 运行应用
    - 给出词频统计结果以及 overhead
    - 时间开销及其他

  > Linux 中有 run 指令, 加载执行命令前可以统计运行时间等等

---

## 实验设备与环境





---

## 设计正文



---

### 分析与设计思路

---

#### Hadoop 简介

> [原文链接:深入浅出大数据：到底什么是Hadoop？ - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/54994736)

- 2003年，Google 发表了一篇技术学术论文，公开介绍了自己的谷歌文件系统 **GFS（Google File System）**。这是 Google 公司为了存储海量搜索数据而设计的专用文件系统。

  2004年，Doug Cutting 基于 Google 的 GFS 论文，实现了**分布式文件存储系统**，并将它命名为 **NDFS（Nutch Distributed File System）**。

- 2004年，Google 又发表了一篇技术学术论文，介绍自己的 **MapReduce编程模型**。这个编程模型，用于大规模数据集（大于1TB）的并行分析运算。

  2005年，Doug Cutting又基于MapReduce，在 Nutch 搜索引擎实现了该功能。

  2006年，当时依然很厉害的 **Yahoo（雅虎）公司**，招安了 Doug Cutting。加盟 Yahoo 之后，Doug Cutting 将 NDFS 和 MapReduce 进行了升级改造，并重新命名为 **Hadoop**（NDFS 也改名为 HDFS，Hadoop Distributed File System）。

  > Hadoop这个名字，实际上是Doug Cutting他儿子的黄色玩具大象的名字。所以，Hadoop的Logo，就是一只奔跑的黄色大象。
  >
  > ![img](http://cdn.ayusummer233.top/img/202110241443334.jpeg)

- 2006年，Google 又发论文介绍了自己的 **BigTable**。这是一种分布式数据存储系统，一种用来处理海量数据的非关系型数据库。

  Doug Cutting 在自己的 hadoop 系统里面，引入了 BigTable，并命名为 **HBase**。
  
- ![img](http://cdn.ayusummer233.top/img/202110241445071.jpeg)

- 2011 年 11 月，Hadoop 1.0.0 版本正式发布，意味着可以用于商业化。

  但是，1.0 版本中，存在一些问题：

  - 扩展性差，JobTracker 负载较重，成为性能瓶颈。
  - 可靠性差，NameNode 只有一个，万一挂掉，整个系统就会崩溃。
  - 仅适用 MapReduce 一种计算方式。
  - 资源管理的效率比较低。

- 2012 年 5 月，Hadoop 推出了 **2.0 版本** 。

  2.0 版本中，在 HDFS 之上，增加了 **YARN（资源管理框架 Yet Another Resource Negotiator）** 层。它是一个资源管理模块，为各类应用程序提供资源管理和调度。

  > [Hadoop 系列YARN：资源调度平台（YARN介绍） - palyer - 博客园 (cnblogs.com)](https://www.cnblogs.com/mtime2004/p/10025032.html)
  >
  > YARN是 Hadoop 2.x 中的资源管理系统，它是一个通用的资源管理模块，可为各类应用程序进行资源管理和调度。YARN 不仅限于 MapReduce 一种框架使用，也可以供其他框架使用，比如 Hive、Spark、Storm 等。由于 YARN 的通用性，下一代 MapReduce 的核心已经从简单的支持单一应用的计算框架 MapReduce 转移到通用的资源管理系统 YARN。

  ![img](http://cdn.ayusummer233.top/img/202110241528567.png)

  此外，2.0 版本还提升了系统的安全稳定性。

  所以，后来行业里基本上都是使用 2.0 版本。目前 Hadoop 又进一步发展到 3.X 版本。

- Hadoop 3.x 是基于 JDK1.8 开发的，较其他两个版本而言，在功能和优化方面发生了很大的变化，其中包括 HDFS 可擦除编码、多Namenode 支持、MR Native Task 优化等。

  > [一文带你了解Hadoop3.x - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/367318462)

- 经过时间的累积，Hadoop 已经从最开始的两三个组件，发展成一个拥有 20 多个部件的生态系统。
  
  ![img](http://cdn.ayusummer233.top/img/202110241537138.jpeg)
  
  ![img](http://cdn.ayusummer233.top/img/202110241537283.jpeg)
  
- Hadoop 的优点和应用
  
  **高可靠性**
  
  **高扩展性**: Hadoop 是在可用的计算机集群间分配数据并完成计算任务的，这些集群可以方便地进行扩展。
  
  **高效性**：Hadoop 能够在节点之间动态地移动数据，并保证各个节点的动态平衡，因此处理速度非常快。
  
  **高容错性**：Hadoop 能够自动保存数据的多个副本，并且能够自动将失败的任务重新分配。这个其实也算是高可靠性。
  
  **低成本**：Hadoop 是开源的，依赖于社区服务，使用成本比较低。
  
  基于这些优点，Hadoop适合应用于大数据存储和大数据分析的应用，适合于服务器几千台到几万台的集群运行，支持PB级的存储容量。
  
  Hadoop的应用非常广泛，包括：**搜索、日志处理、推荐系统、数据分析、视频图像分析、数据保存等**，都可以使用它进行部署。
  
- Spark 同样是 Apache 软件基金会的顶级项目。它可以理解为在 Hadoop 基础上的一种改进。

  **MapReduce是面向磁盘的**。因此，受限于磁盘读写性能的约束，MapReduce在处理迭代计算、实时计算、交互式数据查询等方面并不高效。但是，这些计算却在图计算、数据挖掘和**机器学习**等相关应用领域中非常常见。

  **Spark是面向内存的**。这使得 Spark 能够为多个不同数据源的数据提供近乎实时的处理性能，适用于需要多次操作特定数据集的应用场景。

  在相同的实验环境下处理相同的数据，**若在内存中运行，那么Spark要比MapReduce快100倍**。其它方面，例如处理迭代运算、计算数据分析类报表、排序等，Spark都比MapReduce快很多。

  此外，Spark在易用性、通用性等方面，也比Hadoop更强。

  所以，Spark的风头，已经盖过了Hadoop。

---

#### 配置一个 `Single Node Cluster`(单一结点集群)



---

### 各模块流程图

- Hadoop 的核心，说白了，就是 HDFS 和 MapReduce。HDFS 为海量数据提供了**存储**，而 MapReduce 为海量数据提供了**计算框架**。

  ![img](http://cdn.ayusummer233.top/img/202110241452093.jpeg)

#### **HDFS**


- HDFS 有三个重要角色：**NameNode**（名称节点）、**DataNode**（数据节点）和**Client**（客户机）。

  ![img](http://cdn.ayusummer233.top/img/202110241453247.jpeg)

  **NameNode：**是 Master 节点（主节点），可以看作是分布式文件系统中的管理者，主要负责管理文件系统的命名空间、集群配置信息和存储块的复制等。NameNode 会将文件系统的 Meta-data 存储在内存中，这些信息主要包括了文件信息、每一个文件对应的文件块的信息和每一个文件块在 DataNode 的信息等。

  **DataNode：**是 Slave 节点（从节点），是文件存储的基本单元，它将 Block 存储在本地文件系统中，保存了 Block 的 Meta-data，同时周期性地将所有存在的 Block 信息发送给 NameNode。

  **Client：**切分文件；访问 HDFS；与 NameNode 交互，获得文件位置信息；与 DataNode 交互，读取和写入数据。 

  **Block（块）**：Block 是 HDFS 中的基本读写单元；HDFS 中的文件都是被切割为 block（块）进行存储的；这些块被复制到多个 DataNode 中；块的大小（通常为 64 MB）和复制的块数量在创建文件时由 Client 决定。

- **HDFS** 的写入流程

  ![img](http://cdn.ayusummer233.top/img/202110241457573.jpeg)

  1. 用户向 Client（客户机）提出请求。例如，需要写入 200 MB 的数据。
  2. Client 制定计划：将数据按照 64 MB 为块，进行切割；所有的块都保存三份。
  3. Client 将大文件切分成块（block）。
  4. 针对第一个块，Client 告诉 NameNode（主控节点），请帮助我，将 64 MB 的块复制三份。
  5. NameNode 告诉 Client 三个 DataNode（数据节点）的地址，并且将它们根据到 Client 的距离，进行了排序。
  6. Client 把数据和清单发给第一个 DataNode。
  7. 第一个 DataNode 将数据复制给第二个 DataNode。
  8. 第二个 DataNode 将数据复制给第三个 DataNode。
  9. 如果某一个块的所有数据都已写入，就会向 NameNode 反馈已完成。
  10. 对第二个 Block，也进行相同的操作。
  11. 所有 Block 都完成后，关闭文件。NameNode 会将数据持久化到磁盘上。

- **HDFS** 读取流程(简化描述)

  ![img](http://cdn.ayusummer233.top/img/202110241502137.jpeg)

  1. 用户向 Client 提出读取请求。
  2. Client 向 NameNode 请求这个文件的所有信息。
  3. NameNode 将给 Client 这个文件的块列表，以及存储各个块的数据节点清单（按照和客户端的距离排序）。
  4. Client 从距离最近的数据节点下载所需的块。

---

#### **MapReduce**

MapReduce 其实是一种编程模型。这个模型的核心步骤主要分两部分：**Map（映射）**和 **Reduce（归约）**。

当用户向 MapReduce 框架提交一个计算作业时，它会首先把计算作业拆分成若干个 **Map 任务**，然后分配到不同的节点上去执行，每一个 Map 任务处理输入数据中的一部分，当 Map 任务完成后，它会生成一些中间文件，这些中间文件将会作为 **Reduce 任务**的输入数据。 Reduce 任务的主要目标就是把前面若干个 Map 的输出汇总到一起并输出。

![img](http://cdn.ayusummer233.top/img/202110241508993.jpeg)

以词频统计任务为例:

![img](http://cdn.ayusummer233.top/img/202110241509474.jpeg)

1. Hadoop 将输入数据切成若干个分片，并将每个 split（分割）交给一个 map task（Map 任务）处理。
2. Mapping 之后，相当于得出这个 task 里面，每个词以及它出现的次数。
3. shuffle（拖移）将相同的词放在一起，并对它们进行排序，分成若干个分片。
4. 根据这些分片，进行 reduce（归约）。
5. 统计出 reduce task 的结果，输出到文件。


---

### 主要算法源码



---

### 改进或拓展



---

## 课程实验结果与分析



---

## 参考文献

