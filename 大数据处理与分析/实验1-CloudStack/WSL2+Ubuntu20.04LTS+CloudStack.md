# WSL2 + Ubuntu 20.04LTS 安装 Cloudstack 4.15.2.0 [**abandoned**][网络配置有问题, 未完成, 已弃用 🗑️]

先前在`CentOS7.6` 的腾讯云轻量上安装 Cloudstack 遇到了各种各样的问题, 在查资料的过程中发现实际情况是 Ubuntu 的资料要比 CentOS 的资料多得多, 所以就有了这篇文档记录


## 前言

先前的教程太长了而且遇到了诸多问题, 藉着重置系统重新单开一个文档记录在此环境下部署 Cloudstack 的过程

---

部署教程参考: [Quick Installation Guide — Apache CloudStack 4.15.2.0 documentation](http://docs.cloudstack.apache.org/en/latest/quickinstallationguide/qig.html)

---

## 本地环境配置信息

![image-20210920183032515](http://cdn.ayusummer233.top/img/202109201830771.png)

![image-20210920184644952](http://cdn.ayusummer233.top/img/202109201846139.png)

```bash
# 首先切换到管理员模式
sudo su
```

---

## 先决条件

- [x] 至少一台计算机支持并启用了硬件虚拟化

  > ```shell
  > # 查看 CPU 信息
  > lscpu
  > ```
  >
  > ![image-20210920185306360](http://cdn.ayusummer233.top/img/202109201853480.png)
  >
  > > [lscpu命令详解 - 马昌伟 - 博客园 (cnblogs.com)](https://www.cnblogs.com/machangwei-8/p/10398902.html)
  
- [x] Ubuntu 20.04 LTS

  > ```bash
  > lsb_release -a
  > ```
  >
  > ![image-20210920185908809](http://cdn.ayusummer233.top/img/202109201859877.png)

- [x] 一个网关位于 `xxx.xxx.xxx.1`  的 `/24` 网络，，该网络上不应有DHCP，并且任何运行 CloudStack 的计算机都不会具有动态地址。同样，这也是为了简单。


---

## 环境

### 操作系统

```shell
# 更新和升级包
apt update && apt upgrade
```

> ![image-20210920190806611](http://cdn.ayusummer233.top/img/202109201908703.png)
>
> ---
>
> [apt 和 apt-get的区别_憨憨松的博客-CSDN博客](https://blog.csdn.net/liudsl/article/details/79200134)
>
> 简单来说就是：apt = apt-get、apt-cache 和 apt-config 中最常用命令选项的集合。

---
#### 配置网络

```shell
# 安装网桥和网络工具
apt install bridge-utils net-tools
```

> ![image-20210920191102961](http://cdn.ayusummer233.top/img/202109201911082.png)

顺便看下网络信息和路由表

```bash
ifconfig
```

> ![image-20210920191158070](http://cdn.ayusummer233.top/img/202109201911152.png)

```bash
route-n
```

> ![image-20210920191248930](http://cdn.ayusummer233.top/img/202109201912992.png)



以 `root` 身份登录控制台来配置网桥

```shell
# 登入 root 身份
sudo su
```

```bash
vi /etc/network/interfaces
```



---

#### Hostname

```shell
# 查看 hostname
hostname --fqdn
```

> ![image-20210920105944286](http://cdn.ayusummer233.top/img/202109201059448.png)

主机已经有了默认名称, 但是因为后面要用到 `srvr1.cloud.priv`, 所以还是配下

```shell
# 打开并编辑配置
vi /etc/hosts

# 添加该行配置
10.0.4.11 srvr1.cloud.priv
```



---

#### SELinux


> [一文彻底明白linux中的selinux到底是什么_yanjun821126的博客-CSDN博客_selinux](https://blog.csdn.net/yanjun821126/article/details/80828908)
>
> [2.4 SELinux](https://blog.csdn.net/qq_44714521/article/details/109145500#24_SELinux_123)
>
> 安全增强型 Linux（Security-Enhanced Linux）简称 SELinux，它是一个 Linux 内核模块，也是 Linux 的一个安全子系统。
> SELinux 主要作用就是最大限度地减小系统中服务进程可访问的资源（最小权限原则）

```shell
# 查看是否开启了 SELinux
getenforce
```

> ![image-20210920110127348](http://cdn.ayusummer233.top/img/202109201101462.png)
>
> 压根没用

---

#### NTP

NTP 是保证 cloud servers 中所有时钟同步的必要条件。但是 NTP 不是默认安装的;

```shell
# 查看 NTP 是否启用
systemctl status ntpd
```

> ![image-20210920110403732](http://cdn.ayusummer233.top/img/202109201104870.png)
>
> 已经在用了

---

#### 配置 Cloudstack Package Repository


我们需要配置机器使用 Cloudstack package repository

> Apache Cloudstack 的官方 Release 都是 source code 以至于并不存在可用的"官方"二进制文件
>
> [完整的安装指南](http://docs.cloudstack.apache.org/en/4.15.1.0/installguide/index.html)描述了如何获取 source release 并生成 RPMs and  yum repository
>
> > [RPM（Red-Hat Package Manager 软件包管理器）_百度百科 (baidu.com)](https://baike.baidu.com/item/RPM/3794648)
> >
> > [Yum Repository详解_weixin_34055910的博客-CSDN博客](https://blog.csdn.net/weixin_34055910/article/details/92964753)
> > [YUM](http://yum.baseurl.org/)(Yellowdog Updater Modified)是 Fedora、CentOS、RedHat 中的软件包管理器。基于 RPM 包管理，YUM 通过分析 RPM header数据，自动处理依赖关系，从指定服务器自动下载安装所有依赖的软件包。
>
> [快速部署指南](http://docs.cloudstack.apache.org/en/4.15.1.0/quickinstallationguide/qig.html#selinux)试图让配置越简单越好, 因此这里不进行过多描述, 因此这里使用一款 community-provided 的 yum repository

要添加 CLoudstack repository, 需要创建 `/etc/yum.repos.d/cloudstack.repo` 并输入如下信息:

```shell
# 创建边编辑配置
vi /etc/yum.repos.d/cloudstack.repo
```



```shell
[cloudstack]
name=cloudstack
baseurl=http://download.cloudstack.org/centos/$releasever/4.15/
enabled=1
gpgcheck=0
```

> ```shell
> name=cloudstack    # yum仓库名字
> baseurl=http://download.cloudstack.org/centos/$releasever/4.15/    # 仓库的位置
> enabled=1     # 开启yum功能
> gpgcheck=0    # 关闭完整性检查
> ```
>
> `.repo` 配置文件里不要打注释
>
> ![image-20210920110650042](http://cdn.ayusummer233.top/img/202109201106164.png)

---

### NFS

> 网络文件系统，Network File System, 是一种使用于分散式文件协定，功能是通过网络让不同的机器、不同的操作系统能够分享个人数据，让应用程序通过网络可以访问位于服务器磁盘中的数据的系统
>
> [Linux下部署NFS服务 (*￣︶￣)_Ever~z 的博客！-CSDN博客_nfs](https://blog.csdn.net/sinat_41075146/article/details/80800812)

我们的配置将 NFS 用于 主存储 与 二级存储 (前文 [Cloudstack 概述](#Cloudstack 概述)时有提到)

使用如下命令安装 `nfs-utils`

```shell
yum -y install nfs-utils
```

> ![image-20210920111102858](http://cdn.ayusummer233.top/img/202109201111020.png)

配置 NFS 提供两个不同的 share

```shell
# 打开配置文件
vi /etc/exports

# 填入如下内容
/export/secondary *(rw,async,no_root_squash,no_subtree_check)  
/export/primary *(rw,async,no_root_squash,no_subtree_check)
```

你应该会注意到这两个路径目前并不存在, 因此我们将继续创建这些目录并用如下命令为它们配置适当的权限

```
mkdir -p /export/primary
mkdir /export/secondary
```

> [Linux mkdir 命令 | 菜鸟教程 (runoob.com)](https://www.runoob.com/linux/linux-comm-mkdir.html)
>
> ---
>
> `-p` 确保目录名称存在, 不存在就创建一个
>
> ![image-20210916212430637](http://cdn.ayusummer233.top/img/202109162124784.png)

默认情况下, CentOS 7.x  release 使用 NFSv4; NFSv4 要求在所有客户端上都设置匹配的域; 在本例中 domain 是 `cloud.priv` ; 所以请确保 `/etc/idmapd.conf` 目录下 `Domain = cloud.priv`

```shell
vi /etc/idmapd.conf

# 修改如下配置:
Domain = cloud.priv
```



> ![image-20210916213927112](http://cdn.ayusummer233.top/img/202109162139208.png)
>
> 这里我没取消注释并修改而是直接在原有注释下加了一行, 主要是我看到后面有两处用到了原有注释里的 `local.domain.edu`
>
> ![image-20210916214044901](http://cdn.ayusummer233.top/img/202109162140989.png)

在 `/etc/sysconfig/nfs` 中添加如下配置, 或者取消原本的注释并进行设置

```shell
vi /etc/sysconfig/nfs
```

```shell
LOCKD_TCPPORT=32803
LOCKD_UDPPORT=32769
MOUNTD_PORT=892
RQUOTAD_PORT=875
STATD_PORT=662
STATD_OUTGOING_PORT=2020
```

> 有一说一这个 nfs 是个隐藏文件, 差点误修改 nfs.conf 去了
>
> [后面也有很多配置文件都是隐藏文件,用VSCode编辑的话注意别开错文件了]
>
> ![image-20210916214813349](http://cdn.ayusummer233.top/img/202109162148482.png)
>
> 如下图所示, 原文件中几处配置隔开了
>
> ![image-20210916214935117](http://cdn.ayusummer233.top/img/202109162149261.png)
>
> 所以我索性讲配置加在文件末尾了
>
> ![image-20210916215100821](http://cdn.ayusummer233.top/img/202109162151915.png)

接下来关掉防火墙以防止其阻断连接

```shell
systemctl stop firewalld
systemctl disable firewalld
```

> [iptables、firewall和SELinux的区别及CentOS6.5、7关闭/开启防火墙的方法_theworldofxiej的专栏-CSDN博客](https://blog.csdn.net/theworldofxiej/article/details/103652136)
>
> [CentOS查看端口防火墙状态 - 刀锋93 - 博客园 (cnblogs.com)](https://www.cnblogs.com/hebiao/p/12966000.html)

用如下命令查看下防火墙状态

```shell
firewall-cmd --state
```

> ![image-20210916215701825](http://cdn.ayusummer233.top/img/202109162157968.png)

现在开始配置 nfs 服务在主机启动时启用并实际启用 nfs

```shell
systemctl enable rpcbind
systemctl enable nfs
systemctl start rpcbind
systemctl start nfs
```

> - [2.7 NFS](https://blog.csdn.net/qq_44714521/article/details/109145500#27_NFS_180)
>
> rpcbind 是一个 RPC 服务，主要是在 nfs 共享时候负责通知客户端服务器的 nfs 端口号的。简单理解 rpc 就是一个中介服务。
>
> ![image-20210916220118599](http://cdn.ayusummer233.top/img/202109162201695.png)
>
> 这里我遇到了一处比较奇怪的地方

使用 `showmount` 命令查看共享目录

```shell
showmount -e srvr1.cloud.priv
```



> [Linux showmount命令查看NFS共享目录信息-Linux实验室 (wanyunshuju.com)](https://idc.wanyunshuju.com/cym/1728.html)
>
> 使用showmount命令可以显示NFS服务器的挂载信息。比如查看NFS服务器上有哪些共享目录，这些共享目录可以被哪些客户端访问，以及哪些共享目录已经被客户端挂载了。
>
> `showmount [选项] [NFS服务器]`
>
> `-e` 显示 NFS 服务器的导出列表
>
> ---
>
> ![image-20210920113408957](http://cdn.ayusummer233.top/img/202109201134183.png)

---

## 安装 Management Server

### 数据库的安装与配置

安装并配置 MySQL

首先, CentOS 7 不再提供 MySQL 二进制文件, 我们需要添加一个 MySQL 社区仓库, 其可提供 MySQL Server(以及 Python MySQL connector)

首先在 `/root` 目录创建了一个 `CloudstackStash` 文件夹用来放置 `CloudStack` 部署过程中下载的文件并使用 `cd` 命令切换到此目录

![image-20210920113657062](http://cdn.ayusummer233.top/img/202109201136324.png)

```shell
wget http://repo.mysql.com/mysql-community-release-el7-5.noarch.rpm
rpm -ivh mysql-community-release-el7-5.noarch.rpm
```

> ![image-20210918104710063](http://cdn.ayusummer233.top/img/202109181047325.png)
>
> ![image-20210918104743300](http://cdn.ayusummer233.top/img/202109181047463.png)
>
> [Linux rpm命令 | 菜鸟教程 (runoob.com)](https://www.runoob.com/linux/linux-comm-rpm.html)
>
> ```shell
> -i 　显示套件的相关信息。
> -v 　显示指令执行过程。
> -h或--hash 　套件安装时列出标记。
> ```

使用如下命令安装 MySQL:

```shell
yum -y install mysql-server
```

> ![image-20210918105200080](http://cdn.ayusummer233.top/img/202109181052287.png)
>
> 可以使用如下命令查看安装的 MySQL 版本
>
> ```shell
> mysql -V
> ```
>
> ![image-20210918105331967](http://cdn.ayusummer233.top/img/202109181053123.png)
>
> ```shell
> rpm -qa | grep mysql
> ```
>
> ![image-20210918110222751](http://cdn.ayusummer233.top/img/202109181102916.png)
>
> ```shell
> -q 　使用询问模式，当遇到任何问题时，rpm指令会先询问用户。
> -a 　查询所有套件。
> ```
>
> 可以看到这里的 `MySQL` 版本为 `5.6.51`

修改 `/etc/my.cnf`, 在 [mysqld] 部分添加如下配置

```shell
# 编辑 /etc/my.cnf
vi /etc/my.cnf

# 添加配置
innodb_rollback_on_timeout=1
innodb_lock_wait_timeout=600
max_connections=350
log-bin=mysql-bin
binlog-format = 'ROW'
```

> 需要注意的是, 如果使用 `Ubuntu 16.04` 及更高版本, 那么请指定一个 `server-id`: 在 `my.cnf` 的 [mysqld] 中多加一句
>
> ```shell
> server-id=master-01
> ```
>
> ---
>
> [MySQL my.cnf配置文件详解 (biancheng.net)](http://c.biancheng.net/view/7618.html#:~:text=Linux 操作系统中 MySQL 的配置文件是 my.cnf，一般会放在 %2Fetc%2Fmy.cnf 或 %2Fetc%2Fmysql%2Fmy.cnf,rpm 包安装 MySQL 找不到 my.cnf 文件，可参考《 在linux下通过rpm安装的mysql找不到my.cnf解决方法 》。)
>
> [mysql之my.cnf详解 - 百衲本 - 博客园 (cnblogs.com)](https://www.cnblogs.com/panwenbin-logs/p/8360703.html)
>
> - `innodb_rollback_on_timeout`
>
> 	[MySQL数据库innodb_rollback_on_timeout参数 - 云+社区 - 腾讯云 (tencent.com)](https://cloud.tencent.com/developer/article/1579417)
> 	
> - `innodb_lock_wait_timeout`  
> 		InnoDB 事务在被回滚之前可以等待一个锁定的超时秒数。InnoDB 在它自己的 锁定表中自动检测事务死锁并且回滚事务。 InnoDB 用 LOCK TABLES 语句注意到锁定设置。默认值是 50 秒
> 
> 	> [innodb_百度百科 (baidu.com)](https://baike.baidu.com/item/Innodb/8970025)
>	>
> 	> InnoDB，是MySQL的数据库引擎之一，现为MySQL的默认存储引擎
> 
> - `max_connections`  
>   指定 MySQL 允许的最大连接进程数。如果在访问数据库时经常出现"Too Many Connections"的错误提 示，则需要增大该参数值。
> 
> - `log-bin = mysql-bin`  
>  打开二进制日志功能.在复制(replication)配置中,作为 MASTER 主服务器必须打开此项.如果你需要从你最后的备份中做基于时间点的恢复,你也同样需要二进制日志.这些路径相对于 datadir>	
> 
> - `binlog-format = 'ROW'`
>
>   [关于binary log那些事——认真码了好长一篇 - 苏家小萝卜 - 博客园 (cnblogs.com)](https://www.cnblogs.com/xinysu/p/6607658.html#_lab2_2_1)
>
> ![image-20210918113037715](http://cdn.ayusummer233.top/img/202109181130992.png)

现在 MySQL 的配置完成, 使用如下命令启动 MySQL

```shell
systemctl enable mysqld
systemctl start mysqld
```

> ![image-20210919153846061](http://cdn.ayusummer233.top/img/202109191538290.png)

---

### 安装 MySQL Connector

从 MySQL community repo(上一步添加过) 安装 python MySQL

```shell
yum -y install mysql-connector-python
```

> ![image-20210919161355830](http://cdn.ayusummer233.top/img/202109191613215.png)
>
> 可以看到我这里的 `mysql-connector-python` 的版本号为 `8.0.23`

需要注意的是往前版本所需要的 `mysql-connector-java library` 现在是与 `CloudStack Management server` 捆绑在一起的因此不需要单独安装

### 正式安装 Management Server

通过如下命令安装 `Management server`

```shell
yum -y install cloudstack-management
```

> ![image-20210919162947373](http://cdn.ayusummer233.top/img/202109191629736.png)
>
> 可以看到这里我安装版本是 `4.15.2`, 但是我是看着 `4.15.1` 的文档装的, 有点麻, 不过小版本更新应该问题不大, 不过下面的过程就看 `4.15.2` 的文档吧 (╯﹏╰)b

`CloudStack 4.15` 需要 `Java 11 JRE` 安装 `management servber` 时会自动安装 `Java 11`, 不过还是要看下 `Java 11` 是不是已经处于  `selected/active` 状态:

```shell
alternatives --config java
```

> ![image-20210919163721886](http://cdn.ayusummer233.top/img/202109191637078.png)

确保 当前选定的是 `Java 11`  后继续进行下面的步骤(+ 所在行就是选定行)

安装完 `management server` 后, 我们现在执行如下命令来设置数据库:

```shell
cloudstack-setup-databases cloud:password@localhost --deploy-as=root
```

> ![image-20210919164354269](http://cdn.ayusummer233.top/img/202109191643501.png)

当进程结束时将会显示如下信息:

`CloudStack has successfully initialized the database.`

现在数据库已经创建, 我们可以通过发布如下命令来完成设置 `management server` 的最后一步

```shell
cloudstack-setup-management
```

如果 `servlet container` 是 `Tomcat7` 那么须要加上 `-tomcat7` 参数

>翻了下没找到 `tomcat` 相关的配置所以就没动参数
>
>[Apache Tomcat - 维基百科，自由的百科全书 (wikipedia.org)](https://zh.wikipedia.org/wiki/Apache_Tomcat)
>
>[Java Servlet - 维基百科，自由的百科全书 (wikipedia.org)](https://zh.wikipedia.org/wiki/Java_Servlet)
>
>---
>
>![image-20210919164654314](http://cdn.ayusummer233.top/img/202109191646467.png)
>
>这里显示让我放通 `8080 8250 8443 9090` 端口, 于是就去防火墙把这些端口放通了
>
>![image-20210919165001441](http://cdn.ayusummer233.top/img/202109191650668.png)

---

### System Template 设置

CloudStack 使用许多 `system VM` 提供诸如 `访问虚拟机控制台`, `提供网络服务` 和 `管理存储` 等功能; 此步骤将获取这些 `system image` 以便后续启动云时进行部署

```shell
/usr/share/cloudstack-common/scripts/storage/secondary/cloud-install-sys-tmplt -m /export/secondary -u https://download.cloudstack.org/systemvm/4.15/systemvmtemplate-4.15.1-kvm.qcow2.bz2 -h kvm -F
```

> ![image-20210919171908727](http://cdn.ayusummer233.top/img/202109191719976.png)
>
> 看起来挺大, 下载应该要不少时间
>
> ![image-20210919173447500](http://cdn.ayusummer233.top/img/202109191734775.png)
>
> 下了大概十几分钟的样子

对 `management server` 的配置到此为止. 我们仍需要继续配置 `CloudStack`, 但那需要在配置完 `hypervisor` 之后了

> [Hypervisor - 维基百科，自由的百科全书 (wikipedia.org)](https://zh.wikipedia.org/wiki/Hypervisor)
>
> **Hypervisor**，又称**虚拟机监控器**（英语：virtual machine monitor，缩写为 VMM），是用来创建与运行[虚拟机](https://zh.wikipedia.org/wiki/虛擬機器)的软件、固件或硬件。
>
> 虽然拼写比较像, 但与 `Hyper-V` 并没有关系
>
> [Introduction to Hyper-V on Windows 10 | Microsoft Docs](https://docs.microsoft.com/en-us/virtualization/hyper-v-on-windows/about/) 

---

### 配置与安装 KVM 

`KVM` 是我们将要使用的 `hypervisor` - 我们需要恢复已经在 `hypervisor host` 上完成的初始设置并覆盖掉代理软件的安装;

可以使用相同的步骤为 `Cloudstack` 环境添加额外的 `KVM` 结点

---

#### KVM 安装的先决条件

我们明确使用 `management sevrer` 作为计算结点, 这也就意味着我们我们在设置 `management server` 的同时已经执行了很多先决步骤; 但这里还是列出这些步骤义工明确说明; 这些步骤为:

[配置网络](#配置网络)

[Hostname](#Hostname)

[SELinux](#SELinux)

[NTP](NTP)

[配置 Cloudstack Package Repository](#配置 Cloudstack Package Repository)

现在我们不需要为 `management server` 做上面这些步骤, 但任何额外主机都需要完成上述步骤

---

#### 安装 KVM

安装 `KVM agent` 只需要一个命令就可以完成, 但之后我们需要配置一些东西

```shell
yum -y install epel-release
yum -y install cloudstack-agent
```

> ![image-20210919175345485](http://cdn.ayusummer233.top/img/202109191753869.png)
>
> `pel-release.noarch 0:7-14 `
>
> ![image-20210919175505265](http://cdn.ayusummer233.top/img/202109191755628.png)
>
> `cloudstack-agent.x86_64 0:4.15.2.0-1.el7`

---

#### KVM 配置

该部分又包含两个不同部分: `QEMU` 与 `Libvirt`

> - [4.3 KVM Configuration KVM配置](https://blog.csdn.net/qq_44714521/article/details/109145500#43_KVM_Configuration_KVM_335)
> - [KVM-Qemu-Libvirt三者之间的关系_whatday的专栏-CSDN博客_libvirt qemu](https://blog.csdn.net/whatday/article/details/78445932)
>
> ---
>
> - `KVM` 负责 CPU虚拟化+内存虚拟化，但 KVM 不能模拟其他设备；
>
> - `QEMU` 模拟 IO设备（网卡，磁盘）
>
> `KVM + VEMU` 就能实现真正意义上服务器虚拟化。
>
> 因为用到了上面两个东西，所以一般都称之为 `qemu-kvm`。
>
> - `Libvirt` 则是调用 `KVM` 虚拟化技术的接口用于管理的，用 `Libvirt` 管理方便，直接用 `qemu-kvm` 的接口太繁琐。

---

`QUMU` 配置

`KVM` 配置相对简单只有一个项目; 我们需要编辑 `QEMU VNC` 配置

```shell
vi /etc/libvirt/qemu.conf
```

![image-20210919180258495](http://cdn.ayusummer233.top/img/202109191802714.png)

```shell
vnc_listen=0.0.0.0
```

把上面这行注释取消掉即可

> ![image-20210919180336298](http://cdn.ayusummer233.top/img/202109191803462.png)
>
> ---
>
> [kvm虚拟机vnc配置 - PigDragon - 博客园 (cnblogs.com)](https://www.cnblogs.com/pigdragon/p/9505729.html)
>
> [4.3.1 QEMU Configuration QEMU配置](https://blog.csdn.net/qq_44714521/article/details/109145500#431_QEMU_Configuration_QEMU_343)
>
> ---
>
> - `vnclisten` 默认绑定 `127.0.0.1` ,  在配置文件里指定VNC 绑定`0.0.0.0` IP,就不用在安装 kvm 虚拟机时指定 vnclisten 参数了。
> - 在虚拟主机上有很多个虚拟机的时候，需要指定每个虚拟机的端口，否则将会很乱。

---

`Libvirt` 配置:

`CloudStack` 使用 `Libvirt` 管理虚拟机; 因此正确配置 `Libvirt` 很重要;

`Libvirt` 是 `cloud-agent` 的一个依赖因此应该已经安装好了

1. 为了能够实时迁移, `Libvirt` 需要监听不安全的 `TCP connection`; 我们还需要关闭 `Libvirt` 使用 `多播 DNS 广告` 的尝试

   编辑配置文件:

   ```shell
   vi /etc/libvirt/libvirtd.conf
   ```

   进行如下配置:

   ```shell
   listen_tls = 0
   listen_tcp = 1
   tcp_port = "16509"
   auth_tcp = "none"
   mdns_adv = 0
   ```

   > ![image-20210920124027216](http://cdn.ayusummer233.top/img/202109201240510.png)
   >
   > ![image-20210920124048062](http://cdn.ayusummer233.top/img/202109201240213.png)
   >
   > ![image-20210920124234383](http://cdn.ayusummer233.top/img/202109201242536.png)
   >
   > ![image-20210920124320484](http://cdn.ayusummer233.top/img/202109201243620.png)
   >
   > ![image-20210919182218466](http://cdn.ayusummer233.top/img/202109191822636.png)

2. 在 `libvirtd.conf` 中打开 `listen_tcp` 是不够的, 我们必须改变参数

   编辑配置文件:

   ```shell
   vi /etc/sysconfig/libvirtd
   ```

   取消如下配置的注释:

   ```shell
   LIBVIRTD_ARGS="--listen"
   ```

   > ![image-20210919182516869](http://cdn.ayusummer233.top/img/202109191825033.png)

3. 重启 `libvirt`

   ```shell
   systemctl restart libvirtd
   ```

   > ![image-20210919182559977](http://cdn.ayusummer233.top/img/202109191826168.png)

---

#### KVM 配置完成

为完整起见, 需要检查下 `KVM` 是否在此机器上正常运行:

```shell
# 启用 kvm
modprobe kvm
# 查看 KVM 状态
lsmod | grep kvm
```

> ![image-20210920124640512](http://cdn.ayusummer233.top/img/202109201246642.png)
>
> ---
>
> [Linux lsmod 命令 | 菜鸟教程 (runoob.com)](https://www.runoob.com/linux/linux-comm-lsmod.html)
>
> ---
>
> Linux lsmod（英文全拼：list modules）命令用于显示已载入系统的模块。
>
> ---
>
> ![image-20210919183358309](http://cdn.ayusummer233.top/img/202109191833478.png)
>
> 使用如下命令查看 `libvirt` 运行状态
> 
> ```shell
>service libvirtd status
> ```
>
> ![image-20210919184540644](http://cdn.ayusummer233.top/img/202109191845904.png)
>
> ---
>
> 在 `/dev` 目录下创建一个 `kvm` 文件......
> 
> 虽然显然不合适, 但是没有找到相应的方法
>
> 如果不这么做的话在后面添加 Host 的时候会报错

---

```shell
# 浏览器登入
http://公网ip:8080/client
user: admin
password: password
```

![image-20210920125232811](http://cdn.ayusummer233.top/img/202109201252068.png)

改密码

![image-20210920125325786](http://cdn.ayusummer233.top/img/202109201253019.png)

![image-20210920125353744](http://cdn.ayusummer233.top/img/202109201253008.png)

```shell
Name: Zone1
IPv4 DNS1: 8.8.8.8
IPv4 DNS2: 8.8.8.4
internal DNS1: 180.60.83.19
internal DNS2: 180.60.82.98
Hypervisor: KVM
```

![image-20210919190250733](http://cdn.ayusummer233.top/img/202109191902110.png)

![image-20210919190616158](http://cdn.ayusummer233.top/img/202109191906389.png)

![image-20210919191642295](http://cdn.ayusummer233.top/img/202109191916446.png)

![image-20210919191712120](http://cdn.ayusummer233.top/img/202109191917294.png)

```shell
Pod name: Pod1
Reserved system gateway: 10.0.4.1
Reserved system netmask: 255.255.252.0
Start Reserved system IP: 10.0.4.20
End Reserved system IP: 10.0.4.30
```



![image-20210919192205116](http://cdn.ayusummer233.top/img/202109191922371.png)

```shell
Guest Gateway: 10.0.4.1
Guest Netmask: 255.255.252.0
Guest start IP: 10.0.4.40
Guest end IP: 10.0.4.60
```

![image-20210919192247062](http://cdn.ayusummer233.top/img/202109191922315.png)

```shell
Cluster Name: Cluster1
```

![image-20210920125921449](http://cdn.ayusummer233.top/img/202109201259700.png)

```shell
Host Name: 10.0.4.11	# 内网 ip
Username: root
Password: ********		# root账户密码

```

![image-20210920083238151](http://cdn.ayusummer233.top/img/202109200832411.png)

```shell
Name: Primary1
Protocol: nfs
Server: 10.0.4.11
Path: /export/primary

```

![image-20210920083451631](http://cdn.ayusummer233.top/img/202109200834881.png)

```shell
Provider: NFS
Name: Secondary1
Server: 10.0.4.11
Path: /export/secondary
```



![image-20210920083510007](http://cdn.ayusummer233.top/img/202109200835208.png)

![image-20210919192608219](http://cdn.ayusummer233.top/img/202109191926473.png)

> [CloudStack日志文件路径_kepa520的博客-CSDN博客](https://blog.csdn.net/kepa520/article/details/49126541)
>
> '运行的时候可以在这里查下日志

笑死

```shell
SSH command output:Starting to configure your system:
Configure SElinux ...         [OK]
Configure Network ...         [OK]
Configure Libvirt ...         [OK]
Configure Firewall ...        [OK]
Configure Nfs ...             [OK]
Configure cloudAgent ...      [OK]
CloudStack Agent setup is done!


2021-09-20 13:05:16,499 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-20:ctx-6791d3f9 ctx-ff584ad3) (logid:79f3db61) Sending host added to listener: XcpServerDiscoverer
2021-09-20 13:05:16,499 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-20:ctx-6791d3f9 ctx-ff584ad3) (logid:79f3db61) Sending host added to listener: HypervServerDiscoverer
2021-09-20 13:05:16,499 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-20:ctx-6791d3f9 ctx-ff584ad3) (logid:79f3db61) Sending host added to listener: SecurityGroupListener
2021-09-20 13:05:16,499 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-20:ctx-6791d3f9 ctx-ff584ad3) (logid:79f3db61) Sending host added to listener: SecondaryStorageListener
2021-09-20 13:05:16,499 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-20:ctx-6791d3f9 ctx-ff584ad3) (logid:79f3db61) Sending host added to listener: NetworkOrchestrator
2021-09-20 13:05:16,499 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-20:ctx-6791d3f9 ctx-ff584ad3) (logid:79f3db61) Sending host added to listener: DeploymentPlanningManagerImpl
2021-09-20 13:05:16,499 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-20:ctx-6791d3f9 ctx-ff584ad3) (logid:79f3db61) Sending host added to listener: ClusteredVirtualMachineManagerImpl
2021-09-20 13:05:16,499 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-20:ctx-6791d3f9 ctx-ff584ad3) (logid:79f3db61) Sending host added to listener: VmwareManagerImpl
2021-09-20 13:05:16,499 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-20:ctx-6791d3f9 ctx-ff584ad3) (logid:79f3db61) Sending host added to listener: StoragePoolMonitor
2021-09-20 13:05:16,514 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-20:ctx-6791d3f9 ctx-ff584ad3) (logid:79f3db61) Sending host added to listener: LocalStoragePoolListener
2021-09-20 13:05:16,514 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-20:ctx-6791d3f9 ctx-ff584ad3) (logid:79f3db61) Sending host added to listener: DownloadListener
2021-09-20 13:05:16,514 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-20:ctx-6791d3f9 ctx-ff584ad3) (logid:79f3db61) Sending host added to listener: UploadListener
2021-09-20 13:05:16,514 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-20:ctx-6791d3f9 ctx-ff584ad3) (logid:79f3db61) Sending host added to listener: SshKeysDistriMonitor
2021-09-20 13:05:16,514 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-20:ctx-6791d3f9 ctx-ff584ad3) (logid:79f3db61) Sending host added to listener: VpcVirtualNetworkApplianceManagerImpl
2021-09-20 13:05:16,514 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-20:ctx-6791d3f9 ctx-ff584ad3) (logid:79f3db61) Sending host added to listener: ConsoleProxyListener
2021-09-20 13:05:16,514 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-20:ctx-6791d3f9 ctx-ff584ad3) (logid:79f3db61) Sending host added to listener: BehindOnPingListener
2021-09-20 13:05:16,514 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-20:ctx-6791d3f9 ctx-ff584ad3) (logid:79f3db61) Sending host added to listener: SetHostParamsListener
2021-09-20 13:05:16,514 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-20:ctx-6791d3f9 ctx-ff584ad3) (logid:79f3db61) Sending host added to listener: StorageCapacityListener
2021-09-20 13:05:16,514 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-20:ctx-6791d3f9 ctx-ff584ad3) (logid:79f3db61) Sending host added to listener: ComputeCapacityListener
2021-09-20 13:05:16,514 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-20:ctx-6791d3f9 ctx-ff584ad3) (logid:79f3db61) Sending host added to listener: SshKeysDistriMonitor
2021-09-20 13:05:16,514 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-20:ctx-6791d3f9 ctx-ff584ad3) (logid:79f3db61) Sending host added to listener: VirtualNetworkApplianceManagerImpl
2021-09-20 13:05:16,514 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-20:ctx-6791d3f9 ctx-ff584ad3) (logid:79f3db61) Sending host added to listener: DirectNetworkStatsListener
2021-09-20 13:05:16,532 DEBUG [c.c.a.ApiServlet] (qtp1136768342-20:ctx-6791d3f9 ctx-ff584ad3) (logid:79f3db61) ===END===  114.229.48.144 -- POST  command=addHost&response=json
2021-09-20 13:05:18,860 DEBUG [c.c.s.StatsCollector] (StatsCollector-6:ctx-26b0be2a) (logid:f947c5d9) AutoScaling Monitor is running...
2021-09-20 13:05:18,896 DEBUG [c.c.s.StatsCollector] (StatsCollector-3:ctx-4598fbf2) (logid:23a6ea5a) HostStatsCollector is running...
2021-09-20 13:05:18,907 DEBUG [c.c.s.StatsCollector] (StatsCollector-2:ctx-088bd16a) (logid:982eb1b0) StorageCollector is running...
2021-09-20 13:05:19,066 DEBUG [c.c.a.t.Request] (StatsCollector-3:ctx-4598fbf2) (logid:23a6ea5a) Seq 1-4181029304060084232: Received:  { Ans: , MgmtId: 90520745810660, via: 1(VM-4-11-centos), Ver: v1, Flags: 10, { GetHostStatsAnswer } }
2021-09-20 13:05:20,652 DEBUG [c.c.c.ConsoleProxyManagerImpl] (consoleproxy-1:ctx-a9d0c7a9) (logid:f9ef1325) Skip capacity scan as there is no Primary Storage in 'Up' state
2021-09-20 13:05:25,202 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-13:ctx-5fef8150 ctx-9cfe8943) (logid:b230f191) Sending host added to listener: XcpServerDiscoverer
2021-09-20 13:05:25,202 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-13:ctx-5fef8150 ctx-9cfe8943) (logid:b230f191) Sending host added to listener: HypervServerDiscoverer
2021-09-20 13:05:25,202 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-13:ctx-5fef8150 ctx-9cfe8943) (logid:b230f191) Sending host added to listener: SecurityGroupListener
2021-09-20 13:05:25,202 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-13:ctx-5fef8150 ctx-9cfe8943) (logid:b230f191) Sending host added to listener: SecondaryStorageListener
2021-09-20 13:05:25,202 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-13:ctx-5fef8150 ctx-9cfe8943) (logid:b230f191) Sending host added to listener: NetworkOrchestrator
2021-09-20 13:05:25,202 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-13:ctx-5fef8150 ctx-9cfe8943) (logid:b230f191) Sending host added to listener: DeploymentPlanningManagerImpl
2021-09-20 13:05:25,202 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-13:ctx-5fef8150 ctx-9cfe8943) (logid:b230f191) Sending host added to listener: ClusteredVirtualMachineManagerImpl
2021-09-20 13:05:25,202 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-13:ctx-5fef8150 ctx-9cfe8943) (logid:b230f191) Sending host added to listener: VmwareManagerImpl
2021-09-20 13:05:25,202 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-13:ctx-5fef8150 ctx-9cfe8943) (logid:b230f191) Sending host added to listener: StoragePoolMonitor
2021-09-20 13:05:25,208 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-13:ctx-5fef8150 ctx-9cfe8943) (logid:b230f191) Sending host added to listener: LocalStoragePoolListener
2021-09-20 13:05:25,208 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-13:ctx-5fef8150 ctx-9cfe8943) (logid:b230f191) Sending host added to listener: DownloadListener
2021-09-20 13:05:25,208 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-13:ctx-5fef8150 ctx-9cfe8943) (logid:b230f191) Sending host added to listener: UploadListener
2021-09-20 13:05:25,208 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-13:ctx-5fef8150 ctx-9cfe8943) (logid:b230f191) Sending host added to listener: SshKeysDistriMonitor
2021-09-20 13:05:25,208 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-13:ctx-5fef8150 ctx-9cfe8943) (logid:b230f191) Sending host added to listener: VpcVirtualNetworkApplianceManagerImpl
2021-09-20 13:05:25,208 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-13:ctx-5fef8150 ctx-9cfe8943) (logid:b230f191) Sending host added to listener: ConsoleProxyListener
2021-09-20 13:05:25,208 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-13:ctx-5fef8150 ctx-9cfe8943) (logid:b230f191) Sending host added to listener: BehindOnPingListener
2021-09-20 13:05:25,208 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-13:ctx-5fef8150 ctx-9cfe8943) (logid:b230f191) Sending host added to listener: SetHostParamsListener
2021-09-20 13:05:25,208 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-13:ctx-5fef8150 ctx-9cfe8943) (logid:b230f191) Sending host added to listener: StorageCapacityListener
2021-09-20 13:05:25,208 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-13:ctx-5fef8150 ctx-9cfe8943) (logid:b230f191) Sending host added to listener: ComputeCapacityListener
2021-09-20 13:05:25,208 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-13:ctx-5fef8150 ctx-9cfe8943) (logid:b230f191) Sending host added to listener: SshKeysDistriMonitor
2021-09-20 13:05:25,208 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-13:ctx-5fef8150 ctx-9cfe8943) (logid:b230f191) Sending host added to listener: VirtualNetworkApplianceManagerImpl
2021-09-20 13:05:25,208 DEBUG [c.c.a.m.AgentManagerImpl] (qtp1136768342-13:ctx-5fef8150 ctx-9cfe8943) (logid:b230f191) Sending host added to listener: DirectNetworkStatsListener
2021-09-20 13:05:25,216 DEBUG [c.c.a.ApiServlet] (qtp1136768342-13:ctx-5fef8150 ctx-9cfe8943) (logid:b230f191) ===END===  114.229.48.144 -- POST  command=addHost&response=json
2021-09-20 13:05:33,682 DEBUG [c.c.n.r.VirtualNetworkApplianceManagerImpl] (RouterStatusMonitor-1:ctx-691c5af7) (logid:5fd2fa6b) Found 0 routers to update status. 
2021-09-20 13:05:33,683 DEBUG [c.c.n.r.VirtualNetworkApplianceManagerImpl] (RouterStatusMonitor-1:ctx-691c5af7) (logid:5fd2fa6b) Found 0 VPC's to update Redundant State. 
2021-09-20 13:05:33,684 DEBUG [c.c.n.r.VirtualNetworkApplianceManagerImpl] (RouterStatusMonitor-1:ctx-691c5af7) (logid:5fd2fa6b) Found 0 networks to update RvR status. 
2021-09-20 13:05:38,678 DEBUG [c.c.h.d.HostDaoImpl] (ClusteredAgentManager Timer:ctx-90979f55) (logid:fc046b91) Resetting hosts suitable for reconnect
2021-09-20 13:05:38,679 DEBUG [c.c.h.d.HostDaoImpl] (ClusteredAgentManager Timer:ctx-90979f55) (logid:fc046b91) Completed resetting hosts suitable for reconnect
2021-09-20 13:05:38,679 DEBUG [c.c.h.d.HostDaoImpl] (ClusteredAgentManager Timer:ctx-90979f55) (logid:fc046b91) Acquiring hosts for clusters already owned by this management server
2021-09-20 13:05:38,680 DEBUG [c.c.h.d.HostDaoImpl] (ClusteredAgentManager Timer:ctx-90979f55) (logid:fc046b91) Completed acquiring hosts for clusters already owned by this management server
2021-09-20 13:05:38,680 DEBUG [c.c.h.d.HostDaoImpl] (ClusteredAgentManager Timer:ctx-90979f55) (logid:fc046b91) Acquiring hosts for clusters not owned by any management server
2021-09-20 13:05:38,680 DEBUG [c.c.h.d.HostDaoImpl] (ClusteredAgentManager Timer:ctx-90979f55) (logid:fc046b91) Completed acquiring hosts for clusters not owned by any management server
2021-09-20 13:05:45,444 DEBUG [c.c.a.ApiServlet] (qtp1136768342-19:ctx-d64cba1b) (logid:6eaf1d8a) ===START===  114.229.48.144 -- GET  provider=S3&command=listImageStores&response=json
2021-09-20 13:05:45,449 DEBUG [c.c.a.ApiServer] (qtp1136768342-19:ctx-d64cba1b ctx-462c718a) (logid:6eaf1d8a) CIDRs from which account 'Acct[a868076b-19c5-11ec-9ae2-525400e61ae4-admin]' is allowed to perform API calls: 0.0.0.0/0,::/0
2021-09-20 13:05:45,454 DEBUG [c.c.a.ApiServlet] (qtp1136768342-19:ctx-d64cba1b ctx-462c718a) (logid:6eaf1d8a) ===END===  114.229.48.144 -- GET  provider=S3&command=listImageStores&response=json
2021-09-20 13:05:50,323 DEBUG [c.c.a.ApiServlet] (qtp1136768342-13:ctx-f8c8277c) (logid:288e987e) ===START===  114.229.48.144 -- POST  command=addHost&response=json
2021-09-20 13:05:50,328 DEBUG [c.c.a.ApiServer] (qtp1136768342-13:ctx-f8c8277c ctx-aa11b5f8) (logid:288e987e) CIDRs from which account 'Acct[a868076b-19c5-11ec-9ae2-525400e61ae4-admin]' is allowed to perform API calls: 0.0.0.0/0,::/0
2021-09-20 13:05:50,333 WARN  [c.c.a.d.ParamGenericValidationWorker] (qtp1136768342-13:ctx-f8c8277c ctx-aa11b5f8) (logid:288e987e) Received unknown parameters for command addHost. Unknown parameters : clustertype
2021-09-20 13:05:50,336 INFO  [c.c.r.ResourceManagerImpl] (qtp1136768342-13:ctx-f8c8277c ctx-aa11b5f8) (logid:288e987e) Trying to add a new host at http://10.0.4.11 in data center 1
2021-09-20 13:05:50,338 DEBUG [c.c.h.k.d.LibvirtServerDiscoverer] (qtp1136768342-13:ctx-f8c8277c ctx-aa11b5f8) (logid:288e987e) Skipping host 10.0.4.11 because dce07ff9-8e3d-30dc-ae2c-738aabbb8f1e is already in the database for resource dce07ff9-8e3d-30dc-ae2c-738aabbb8f1e-LibvirtComputingResource with ID c996e972-8efb-44d0-9d42-a8130401608b
2021-09-20 13:05:50,338 WARN  [c.c.h.k.d.LibvirtServerDiscoverer] (qtp1136768342-13:ctx-f8c8277c ctx-aa11b5f8) (logid:288e987e)  can't setup agent, due to com.cloud.utils.exception.CloudRuntimeException: Skipping host 10.0.4.11 because dce07ff9-8e3d-30dc-ae2c-738aabbb8f1e is already in the database for resource dce07ff9-8e3d-30dc-ae2c-738aabbb8f1e-LibvirtComputingResource with ID c996e972-8efb-44d0-9d42-a8130401608b - Skipping host 10.0.4.11 because dce07ff9-8e3d-30dc-ae2c-738aabbb8f1e is already in the database for resource dce07ff9-8e3d-30dc-ae2c-738aabbb8f1e-LibvirtComputingResource with ID c996e972-8efb-44d0-9d42-a8130401608b
2021-09-20 13:05:50,338 WARN  [c.c.r.ResourceManagerImpl] (qtp1136768342-13:ctx-f8c8277c ctx-aa11b5f8) (logid:288e987e) Unable to find the server resources at http://10.0.4.11
2021-09-20 13:05:50,339 INFO  [c.c.u.e.CSExceptionErrorCode] (qtp1136768342-13:ctx-f8c8277c ctx-aa11b5f8) (logid:288e987e) Could not find exception: com.cloud.exception.DiscoveryException in error code list for exceptions
2021-09-20 13:05:50,339 WARN  [o.a.c.a.c.a.h.AddHostCmd] (qtp1136768342-13:ctx-f8c8277c ctx-aa11b5f8) (logid:288e987e) Exception: 
com.cloud.exception.DiscoveryException: Unable to add the host
	at com.cloud.resource.ResourceManagerImpl.discoverHostsFull(ResourceManagerImpl.java:825)
	at com.cloud.resource.ResourceManagerImpl.discoverHosts(ResourceManagerImpl.java:611)
	at java.base/jdk.internal.reflect.NativeMethodAccessorImpl.invoke0(Native Method)
	at java.base/jdk.internal.reflect.NativeMethodAccessorImpl.invoke(NativeMethodAccessorImpl.java:62)
	at java.base/jdk.internal.reflect.DelegatingMethodAccessorImpl.invoke(DelegatingMethodAccessorImpl.java:43)
	at java.base/java.lang.reflect.Method.invoke(Method.java:566)
	at org.springframework.aop.support.AopUtils.invokeJoinpointUsingReflection(AopUtils.java:344)
	at org.springframework.aop.framework.ReflectiveMethodInvocation.invokeJoinpoint(ReflectiveMethodInvocation.java:198)
	at org.springframework.aop.framework.ReflectiveMethodInvocation.proceed(ReflectiveMethodInvocation.java:163)
	at org.springframework.aop.interceptor.ExposeInvocationInterceptor.invoke(ExposeInvocationInterceptor.java:97)
	at org.springframework.aop.framework.ReflectiveMethodInvocation.proceed(ReflectiveMethodInvocation.java:186)
	at org.springframework.aop.framework.JdkDynamicAopProxy.invoke(JdkDynamicAopProxy.java:215)
	at com.sun.proxy.$Proxy192.discoverHosts(Unknown Source)
	at org.apache.cloudstack.api.command.admin.host.AddHostCmd.execute(AddHostCmd.java:142)
	at com.cloud.api.ApiDispatcher.dispatch(ApiDispatcher.java:156)
	at com.cloud.api.ApiServer.queueCommand(ApiServer.java:764)
	at com.cloud.api.ApiServer.handleRequest(ApiServer.java:588)
	at com.cloud.api.ApiServlet.processRequestInContext(ApiServlet.java:321)
	at com.cloud.api.ApiServlet$1.run(ApiServlet.java:134)
	at org.apache.cloudstack.managed.context.impl.DefaultManagedContext$1.call(DefaultManagedContext.java:55)
	at org.apache.cloudstack.managed.context.impl.DefaultManagedContext.callWithContext(DefaultManagedContext.java:102)
	at org.apache.cloudstack.managed.context.impl.DefaultManagedContext.runWithContext(DefaultManagedContext.java:52)
	at com.cloud.api.ApiServlet.processRequest(ApiServlet.java:131)
	at com.cloud.api.ApiServlet.doPost(ApiServlet.java:98)
	at javax.servlet.http.HttpServlet.service(HttpServlet.java:665)
	at javax.servlet.http.HttpServlet.service(HttpServlet.java:750)
	at org.eclipse.jetty.servlet.ServletHolder$NotAsync.service(ServletHolder.java:1443)
	at org.eclipse.jetty.servlet.ServletHolder.handle(ServletHolder.java:791)
	at org.eclipse.jetty.servlet.ServletHandler.doHandle(ServletHandler.java:550)
	at org.eclipse.jetty.server.handler.ScopedHandler.handle(ScopedHandler.java:143)
	at org.eclipse.jetty.security.SecurityHandler.handle(SecurityHandler.java:602)
	at org.eclipse.jetty.server.handler.HandlerWrapper.handle(HandlerWrapper.java:127)
	at org.eclipse.jetty.server.handler.ScopedHandler.nextHandle(ScopedHandler.java:235)
	at org.eclipse.jetty.server.session.SessionHandler.doHandle(SessionHandler.java:1624)
	at org.eclipse.jetty.server.handler.ScopedHandler.nextHandle(ScopedHandler.java:233)
	at org.eclipse.jetty.server.handler.ContextHandler.doHandle(ContextHandler.java:1435)
	at org.eclipse.jetty.server.handler.ScopedHandler.nextScope(ScopedHandler.java:188)
	at org.eclipse.jetty.servlet.ServletHandler.doScope(ServletHandler.java:501)
	at org.eclipse.jetty.server.session.SessionHandler.doScope(SessionHandler.java:1594)
	at org.eclipse.jetty.server.handler.ScopedHandler.nextScope(ScopedHandler.java:186)
	at org.eclipse.jetty.server.handler.ContextHandler.doScope(ContextHandler.java:1350)
	at org.eclipse.jetty.server.handler.ScopedHandler.handle(ScopedHandler.java:141)
	at org.eclipse.jetty.server.handler.gzip.GzipHandler.handle(GzipHandler.java:766)
	at org.eclipse.jetty.server.handler.HandlerCollection.handle(HandlerCollection.java:146)
	at org.eclipse.jetty.server.handler.HandlerWrapper.handle(HandlerWrapper.java:127)
	at org.eclipse.jetty.server.Server.handle(Server.java:516)
	at org.eclipse.jetty.server.HttpChannel.lambda$handle$1(HttpChannel.java:388)
	at org.eclipse.jetty.server.HttpChannel.dispatch(HttpChannel.java:633)
	at org.eclipse.jetty.server.HttpChannel.handle(HttpChannel.java:380)
	at org.eclipse.jetty.server.HttpConnection.onFillable(HttpConnection.java:273)
	at org.eclipse.jetty.io.AbstractConnection$ReadCallback.succeeded(AbstractConnection.java:311)
	at org.eclipse.jetty.io.FillInterest.fillable(FillInterest.java:105)
	at org.eclipse.jetty.io.ChannelEndPoint$1.run(ChannelEndPoint.java:104)
	at org.eclipse.jetty.util.thread.strategy.EatWhatYouKill.runTask(EatWhatYouKill.java:336)
	at org.eclipse.jetty.util.thread.strategy.EatWhatYouKill.doProduce(EatWhatYouKill.java:313)
	at org.eclipse.jetty.util.thread.strategy.EatWhatYouKill.tryProduce(EatWhatYouKill.java:171)
	at org.eclipse.jetty.util.thread.strategy.EatWhatYouKill.run(EatWhatYouKill.java:129)
	at org.eclipse.jetty.util.thread.ReservedThreadExecutor$ReservedThread.run(ReservedThreadExecutor.java:375)
	at org.eclipse.jetty.util.thread.QueuedThreadPool.runJob(QueuedThreadPool.java:773)
	at org.eclipse.jetty.util.thread.QueuedThreadPool$Runner.run(QueuedThreadPool.java:905)
	at java.base/java.lang.Thread.run(Thread.java:829)
2021-09-20 13:05:50,340 INFO  [c.c.a.ApiServer] (qtp1136768342-13:ctx-f8c8277c ctx-aa11b5f8) (logid:288e987e) Unable to add the host
2021-09-20 13:05:50,342 DEBUG [c.c.a.ApiServlet] (qtp1136768342-13:ctx-f8c8277c ctx-aa11b5f8) (logid:288e987e) ===END===  114.229.48.144 -- POST  command=addHost&response=json
2021-09-20 13:05:50,652 DEBUG [c.c.c.ConsoleProxyManagerImpl] (consoleproxy-1:ctx-82b283da) (logid:7151dfdf) Skip capacity scan as there is no Primary Storage in 'Up' state
2021-09-20 13:06:00,866 DEBUG [c.c.a.m.AgentManagerImpl] (AgentManager-Handler-13:null) (logid:) Ping from Routing host 1(VM-4-11-centos)
2021-09-20 13:06:00,867 DEBUG [c.c.v.VirtualMachinePowerStateSyncImpl] (AgentManager-Handler-13:null) (logid:) Process host VM state report from ping process. host: 1
2021-09-20 13:06:00,867 DEBUG [c.c.v.VirtualMachinePowerStateSyncImpl] (AgentManager-Handler-13:null) (logid:) Process VM state report. host: 1, number of records in report: 0
2021-09-20 13:06:00,868 DEBUG [c.c.v.VirtualMachinePowerStateSyncImpl] (AgentManager-Handler-13:null) (logid:) Done with process of VM state report. host: 1
2021-09-20 13:06:03,682 DEBUG [c.c.n.r.VirtualNetworkApplianceManagerImpl] (RouterStatusMonitor-1:ctx-15064511) (logid:20508176) Found 0 routers to update status. 
2021-09-20 13:06:03,683 DEBUG [c.c.n.r.VirtualNetworkApplianceManagerImpl] (RouterStatusMonitor-1:ctx-15064511) (logid:20508176) Found 0 VPC's to update Redundant State. 
2021-09-20 13:06:03,684 DEBUG [c.c.n.r.VirtualNetworkApplianceManagerImpl] (RouterStatusMonitor-1:ctx-15064511) (logid:20508176) Found 0 networks to update RvR status. 
2021-09-20 13:06:18,862 DEBUG [c.c.s.StatsCollector] (StatsCollector-5:ctx-3040c468) (logid:04dcb5c0) AutoScaling Monitor is running...
2021-09-20 13:06:18,908 DEBUG [c.c.s.StatsCollector] (StatsCollector-6:ctx-89536498) (logid:696c1790) StorageCollector is running...
2021-09-20 13:06:19,070 DEBUG [c.c.s.StatsCollector] (StatsCollector-4:ctx-400a538f) (logid:b7de21c3) HostStatsCollector is running...
2021-09-20 13:06:19,126 DEBUG [c.c.a.t.Request] (StatsCollector-4:ctx-400a538f) (logid:b7de21c3) Seq 1-4181029304060084233: Received:  { Ans: , MgmtId: 90520745810660, via: 1(VM-4-11-centos), Ver: v1, Flags: 10, { GetHostStatsAnswer } }
2021-09-20 13:06:20,653 DEBUG [c.c.c.ConsoleProxyManagerImpl] (consoleproxy-1:ctx-cbe70b29) (logid:39729049) Skip capacity scan as there is no Primary Storage in 'Up' state
2021-09-20 13:06:33,682 DEBUG [c.c.n.r.VirtualNetworkApplianceManagerImpl] (RouterStatusMonitor-1:ctx-6ab276a6) (logid:ced19d1d) Found 0 routers to update status. 
2021-09-20 13:06:33,683 DEBUG [c.c.n.r.VirtualNetworkApplianceManagerImpl] (RouterStatusMonitor-1:ctx-6ab276a6) (logid:ced19d1d) Found 0 VPC's to update Redundant State. 
2021-09-20 13:06:33,684 DEBUG [c.c.n.r.VirtualNetworkApplianceManagerImpl] (RouterStatusMonitor-1:ctx-6ab276a6) (logid:ced19d1d) Found 0 networks to update RvR status. 
2021-09-20 13:06:50,652 DEBUG [c.c.c.ConsoleProxyManagerImpl] (consoleproxy-1:ctx-982d8890) (logid:9d932786) Skip capacity scan as there is no Primary Storage in 'Up' state
2021-09-20 13:07:00,865 DEBUG [c.c.a.m.AgentManagerImpl] (AgentManager-Handler-15:null) (logid:) Ping from Routing host 1(VM-4-11-centos)
```

不搞了(



