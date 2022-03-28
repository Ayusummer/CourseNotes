# 前言
## 实验题目格式
- 以11.16第五次实验为例,题目应为:
  - 实验五 无线局域网组网实验
    - 也就是说按照第几次实验来写
> 因为实验指导书上的实验1我们拆成了两次实验做的
> - 所以本次实验指导书上是
>   - 实验四 无线局域网组网实验
>   - 而我们报告上应当写:
>      - 实验五 无线局域网组网实验
# 实验4 跨交换机VLAN配置实验
## 实验目标
- 进一步熟悉VLAN配置的方法;
- 掌握通过建立交换路径进行跨交换VLAN的配置方法

---
## 实验内容
- pic
- 创建VLAN
- VLAN指定端口
- 建立交换路径

## CLI配置代码
- 两个VLAN
- SZYF0
```
enable 
conf t
hostname SZYF0
exit
vlan database
vlan 2 name vlan2
vlan 3 name vlan3
exit
conf t
int f0/1
switchport access vlan 2
int f0/2
switchport access vlan 3
int f0/3
switchport access vlan 2
int f0/4
switchport access vlan 3
exit
exit
sh vlan brief
```
- SZYF1
```
enable 
conf t
hostname SZYF1
exit
vlan database
vlan 2 name vlan2
vlan 3 name vlan3
exit
conf t
int f0/1
switchport access vlan 2
int f0/2
switchport access vlan 3
int f0/3
switchport access vlan 2
int f0/4
switchport access vlan 3
exit
exit
sh vlan brief
```
- 配置完成后去PCZYF0测试ping
- pic
- 再去PCZYF1测试ping
- pic


---
# 第6次实验 实验5

---
## 关于本次的计网实验
- 今天的计网实验最迟明天下午78节课之前上交
  - 也就是说在明天**15:30**之前要把压缩包发给我
    - 由于并不知道有多少人要交,所以15:30我上完Java课后就会将收集到的压缩包打包提交给老师
- 压缩包命名格式
  - 学号+姓名
- 压缩包内包括
  - 每个小实验的拓扑图
    - .pkt文件
  - 每个小实验的调试截图文档
    - .docx文件
    - 文件内应包含执行ping命令的截图

# 第7次实验 实验5.2 动态路由器应用实验
- 本次计网实验报告
  - 若是写了RIP的部分
    - 那么老师批改的时候会把RIP部分的分数也填上
      - 因此**不用再重新写**一份RIP的实验报告;
  - 若是没写RIP的部分
    - 那么这次要写一份RIP的实验报告,下次做实验的时候我再收