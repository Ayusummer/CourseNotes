# 考前复习

---
## 题型
- 选择题($26*1.5'=39'$)
- 判断题($20*1'=20'$)
> 选择题+判断题应该占60'
- 简答题($7题20'$)
- 综合题($3题20'$)

---
# 软件工程复习提纲、
## A卷
1. 选择26*1.5=39
2. 判断20
3. 简答7*3=21
4. 综合20 3道

### 选择题
---
- 12.软件的集成测试工作
- 软件的集成测试工作最好由（不属于该软件开发组的软件设计人员）承担，以提高集成测试的效果（五）
- 1.软件的集成测试工作最好由（）承担，以提高集成测试的效果
  - Answer：不属于该软件开发组的软件设计人员
- 2.集成测试的主要方法有两个，一个是（）另一个是（）
  - Answer：渐增式测试方法、非渐增式测试方法
----
- 13.白盒测试
- 白盒测试法是根据程序的（内部逻辑）来设计测试用例的方法（五）
- 1.黑河测试是从（）观点的测试，白盒测试是从（）观点的测试
  - Answer：用户、开发人员
- 2.使用白盒测试方法时确定测试数据应根据（）和指定的覆盖标准
  - Answer：程序的内部逻辑
- 3.白盒测试时通过结构测试，主要以程序的内部逻辑为基础设计测试用例。
- 4.*此段描述是错误描述：白盒法是一种静态测试方法，主要用于模块测试
- 白盒法的定义：
  - 白盒法是在软件测试过程中，由详细设计提供的文档，从软件的具体的逻辑结构和执行路径出发，设计测试用例，完成测试的目的.白盒法测试主要用于测试，程序内部逻辑。
- 白盒法的概念：
  - 白盒测试也称为结构测试或者是逻辑驱动测试，是一种测试用例设计方法，它从程序的控制结构导出测试用例。
测试用例由测试输入数据以及与之相对应的输出结果组成。测试用例设计的好坏直接决定了测试的效果和结果。所以说在软件测试活动中最关键的步骤就是设计有效的测试用例。
白盒测试适用于被测单元内部如何工作的信息，允许测试人员对程序内部逻辑结构以及有关信息来设计和选择测试用例，对程序的逻辑路径进行测试，基于一个代码的内部逻辑知识，测试时基于覆盖全部代码、分支、路径、条件。
--- 
- 14.验收测试的任务
- 验收测试的任务是验证软件的（有效性）（五）
- 1.验收测试的任务是验证软件的（）
  - Answer：有效性
- 2.成功的测试时指运行测试用例后（）
  - Answer：发现了程序的错误
- 3.软件测试的目的是尽可能发现软件中的错误，通常（）是代码编写阶段可进行的测试，它是整个测试工作的基础
  - Answer：单元测试
---- 
- 15.()是()
- （封装）是把对象的属性结合在一起，构成一个独立的对象，其内部消息对外界是隐藏的，外界只能通过有限的接口与对象发生联系（六）
--- 
- 16.应用执行对象的操作
- 应用执行对象的操作可以改变该对象的（属性）（六）
- 1.应用执行对象的操作可以改变该对象的（）
  - Answer：属性
--- 
- 17.对象类
- 所有的对象可以成为各种对象类，每个对象类都定义了一组（方法）（六）
- 面向对象的主要特征除了对象唯一性、封装性、继承性外，还有（ 多态性 ）。
- 所有的对象可以成为对象类，每个对象类都定义了一组（ 方法 ）。
--- 
- 18./19.面向对象分析
- 面向对象分析的首要工作是建立（问题的对象模型）（七）
- 面向对象的分析方法主要是建立三类模型，即（ 对象模型、动态模型、功能模型 ）。
- 软件开发过程中，抽取和整理用户需求并建立问题域精确模型的过程叫（ 面向对象分析 ）。
- 面向对象分析是对系统建立的3个模型中，核心的模型是（ 对象 ）模型。
- 面向对象分析是对系统进行（ 需求建模 ）的一种方法。
- 应该在（ 建立动态模型和功能模型之后 ）,确定对象类中应有的服务。
- 面向对象的动态模型中，每张状态图表示（ 某一个类 ）的动态行为。
- 在考察系统的一些涉及时序和改变的状况时，要用动态模型来表示。动态模型着重于系统的控制逻辑，它包括两个图；一个是事件追踪图，另一个是（ 状态图 ）。
--- 
- 20.动态模型
  - 动态模型的描述工具是`状态图`（七）
    - A. 设计图 B. 结构图 状态图 D. 对象图
---
- 21.软件设计的原则
  - 只有类的共有界面的成员才能成为使用类的操作，这是软件设计的（B）原则
    - A. 过程抽象 B. 信息隐藏 功能抽象 共享性
---
- 22. 面向对象设计的特点
- 下面所列的性质中，(D)不属于面向对象程序设计的特性
   A. 继承性 B. 重用性 封装性 D. 可视化
- 面向对象设计中，基于父类创建的子类具有父类的所有特性（属性和方法），这一特点称为类的（继承性）（八）
---
- 23.面向对象的实现
  - 面向对象的实现主要包括`把面向对象设计用某种程序设计语言书写为面向对象程序，测试并调试面向对象的程序`（九）
  - 面向对象程序设计语言不同于其他语言的最主要特点是`继承性`
  - 面向对象的测试与传统测试方法的主要区别是`测试对象不同`
  - 面向对象设计的结果，既可以用面向对象语言，也可以用非面向对象语言实现
  - 一般来说，应该尽量选用面向对象语言来实现面向对象分析、设计的结果。
  - 良好的面向对象程序设计风格，既包括传统的程序设计风格准则，也包括为适应面向对象方法所特有的概念（如继承性）而必须遵循的一些新准则。
  - 与传统软件测试（测试用例的设计由软件的输入—处理—输出视图或单个模块的算法细节驱动）不同，面向对象测试关注于设计适当的操作序列以检查类的状态。
  - 面向对象系统的确认测试也是面向黑盒的，可以应用传统的黑盒方法完成测试工作。
  - (B)意味着一个操作在不同的类中可以有不同的实现方式
    - A. 多继承 B. 多态性 C. 消息 D. 封装
---
- 24.(B)的作用是为有效地定量地进行管理，把握软件工程过程的实际情况和它所产生的产品质量
      - A. 估算 B.度量 C. 风险分析 D. 进度安排
---
- 25.风险管理
  - 风险管理的过程
    - 风险规划,风险识别,风险评估
    - 风险收集**不是**风险管理的过程
      - 谁会去收集风险呢.jpg
  - 按照软件管理的原始指导思想,受控制的对象应当是`软件配置项` 
--- 
- 26.软件可维护性
  - 影响软件可维护性的因素不包括`可用性`
  - `软件的可维护性`是用来衡量对软件产品进行维护的难易程度的标准，它是软件质量的主要特征之一。影响软件可维护性的因素有很多，如可理解性、可测试性、可修改性等。
  - 文档是影响软件可维护性的决定因素
  - 适应性维护是指为使软件产品在改变了的环境下仍能使用而进行的维护。
  - 软件维护内容中,占维护活动工作量比例最高的是`适应性维护`
  - 使用软件时提出增加新功能就必须进行`完善性`维护
  - 软件维护的副作用是指`因修改软件而造成的错误`
  - 软件文档是软件工程实施的重要成分;它不仅是软件开发各阶段的重要依据,而且影响软件的`可维护性`

---
### 简答题
- 1.请简述软件过程的目标、过程和原则。（第一章 简答题 7）
- 目标：
  - 降低成本、及时交付高质量的软件产品（高质量、高效率、高效益）
- 过程：
  - 基本过程、支持过程和组织过程  
- 原则：
  - 原则就是过程中的轨道约束，包括：选取适宜的开发范型、采用合适的设计方法、提供高质量的工程支持、重视开发过程的管理
---
- 2.XP是一种什么样的模型?（第二章 简答题 5）
- XP是现代版的增量模型，特点是客户参与、适应变化、测试驱动、以代码为核心。实行XP的条件如下：
  - 企业具有较高的能力成熟度，具有团队开发环境和配套的测试工具。
  - 软件结构是开放的，增量可随意整合。
  - 开发团队拥有“系统隐喻”。
---
- 3.为什么说需求过程是一种迭代过程?（第三章 简单题 9）
   - 由于人们对客观事物的认识是不断深化的，因此需求过程是一个迭代过程，每次迭代都可提供更高质量和更详细内容的软件需求 这种迭代会给项目带来一定的风险，上 次迭代的设计实现可能会因为需求不足而被推翻
  - 在很多情况下，对需求的理解会随着设计过程和实现过程的深入而不断深化，这也会导致在软件生命周期的后期，重新修订软件需求原因可能来自于错误的分析，客户环境和业务流程的改变，市场趋势的变化等。无论是什么原因，软件分析师应认识到需求变化的必然性，并采取相应的措施，减少需求变更对软件系统的影响。
--- 
- 4.请简述如何准备事件跟踪图。（第七章 简答题 六） 
   - 事件跟踪图能形象、清晰地表示事件序列以及事件与对象的关系。在事件跟踪图中，一条竖线代表一个类和对象，每个事件用一条水平的箭头线表示，箭头方向从事件的发送对象指向接受对象。事件按照先后顺序排列，时间从上向下递增。
--- 
- 5.请简述软件工程与软件项目管理的区别与联系。（第十一章 简答题 2)
   - 软件项目管理和软件工程的区别和关系如下。
     - 目标相同：软件共产与软件项目都是围绕软件产品开发的管理。
     - 作用不同，件工程是件开发方法论，是关于如何开发出好的软件产品；获件项目管理是软件产品的生产管理形式，项目目标是项目的绩效。
     - 两者关系：软件工程对于任何软件项目具有指导性，软件项目管理是落实软件工程思想的载体。
----
- 6.什么是配置项?什么是配置管理?
- [`第13章-控制, 13.3-配置管理, P143习题T3-5`]
  - 软件配置管理中的基本单元，称为`软件配置项`。
  - 在开发过程中，将软件的文档、程序、数据进行分割与综合，以利于软件的定义、标识、跟踪、管理，使其最终形成受控的软件版本产品，这一管理过程称为`软件配置管理`。
---
- 7.面向对象的时代如何进行软件维护
- (`第14章-软件维护及软件文档, 14.1-软件维护, P147习题T3-4,7,8`)
  - 软件维护的工作程序
    - 软件维护的工作程序与软件开发的工作程序相仿。具工作程序是∶ 维护的需求分析、维护的设计、修改程序代码、维护后的测试、维护后的试运行、维护后的正式运行、维护过程的评审和审计。
  - `面向缺陷的维护`∶该软件产品能够正常运行，可以满足用户的功能、性能、接口需求，只是维护前在个别地方存在缺陷，用户不是非常满意。克服缺陷的方法是修改程序，也就是通常说的只修改程序，不修改数据结构。
  - `面向功能维护`∶该软件产品在功能、性能、接口上存在某些不足，不能满足用户的某些需求，因此需要增加某些功能、性能、接口。解决这些不足的方法是，不但要修改设计，而且也要修改程序，也就是通常说的，既要修改数据结构，又要修改编码。
-----
- 8.面向对象部分（可能考第七章 简答题2、5）
- [`第3篇-面向对象方法学包括第6章-面向方法学导论~第10章-统一建模语言`]
- [`第7章-面向对象分析, P88习题T3-2,5`]?
  - 2.类间的外部关系有几种类型?每种关系表达什么语义? 
  - 3.请简述面向对象分析的过程。 
  - 4.什么是动态模型? 
  - 5.请简述如何准备脚本。

---
### 综合题
- 1.测试用例(等价类划分)
- [`第5章-结构化实现, P62T4-2`]
- 现有一段判定三角形类型的程序，可以根据输入的三角形的三边长来判定可构成的三角形是否为等腰三角形。请用等价类划分法来为此段代码设计测试用例。
- ![测试用例](https://images.gitee.com/uploads/images/2021/0103/073911_0dac49f4_7703072.png "屏幕截图.png")

---
- 2.数据流图(分析系统画出数据流图,给出实例作图分析)
- [`第3章-结构化分析, 3.5-数据流图, P27习题T4-2,3`]
- 某银行计算机储蓄系统的工作流程大致如下：储户填写的存款单或取款单由业务员输人系统。如果是存款，则系统记录存款人的姓名、住址（或电话号码）、身份证号码、存款类型、存款日期、到期日期、利率及密码〔可选）等信息，并打印出存款单给储户；如果是取款且存款时留有密码，则系统首先核对储户密码，若密码正确或存款时未留密码，则系统计算利息并打印出利息清单给储户。请用数据流图描绘本系统的功能。
- ![银行系统数据流图](https://images.gitee.com/uploads/images/2021/0102/224459_26730a4c_7965824.png "屏幕截图.png")
- 有如下一个学生选课系统：教师提出开课计划，系统批准后给教师下发开课通知。学生可向系统提出选课申请，系统批准后给学生下发选课申请结果通知。课程结束后，系统还可以帮助教师录入学生成绩，同时把成绩单发送给学生。请画出该系统顶层的数据流图。
- ![选课系统数据流图](https://images.gitee.com/uploads/images/2021/0102/224647_22bcefe5_7965824.png "屏幕截图.png")

---
- 3.功能模型(给定功能分析设计)
- [`第7章-面向对象分析-P89T4-3`]
- 现在有一个医院病房监护系统，用户提出的系统功能要求如下。
  - 在医院病房监护系统中，安置在每个病房的病症监视器将病员的病症信号实时传送到中央监视系统进行分析处理。在中心值班室里，值班护士使用中央监视系统对病员的情况进行监控，根据医生的要求随时打印病员的病情报告，系统定期自动更新病历。
  - 当病症出现异常时，系统会立即自动报警，通知值班医生及时进行处理，同时打印病员的病情报告和更新病历。
  - 请建立医院病房监护系统的功能模型。
- 在本题中，动作对象主要包括病员、医生和护士 3类。
  - 病员的病症信号会被局部监视系统采集，并传递到中央监视系统中。中央监视系统会读入病员的相关信息，并在必要的时候进行报警。
  - 护士会按照要求对病员的情况进行报告，该报告会与病员日志数据一并传递给医生。
  - 中央监视系统会对病员的病症信号进行分析处理，并根据病员日志数据对日志进行更新。医院病房监护系统的功能模型如图 7.3 所示。
  - ![图 7.3 ](https://images.gitee.com/uploads/images/2021/0103/065042_9a99de3f_7703072.png "屏幕截图.png")


---
### 判断题
- 1.原型化(开放化?)划分方法
- 原型化开发方法包括生成原型和实现原型两个步骤（X）
- 1.关于原型化方法的描述：
  - 正确的是：
①原型化方法适用于需求不明确的软件开发
②在开发过程中可以废弃不用早期结构的软件原型
③原型化方法利于确定各项系统服务的可用性
  - 错误描述：
原型化方法可以直接开发出最终产品
--- 
- 2.软件工程改进
- 软件过程改进也是软件工程的范畴 T
--- 
- 3.需求分析的主要目的
- 需求分析的主要目的主要目的是解决软件开发的具体方案（X）
- 需求分析的主要目的是：
①了解客户的需求
②挖掘客户的利益点
③强化客户的需求
--- 
- 4.需求分析的软件工具
- 用于需求分析的软件工具，应该能保证需求的正确性，即验证需求的一致性、完整性、现实性和有效性（√）
- 需求分析的软件工具：
①结构化英语
②判定表
③判定书
  - 关于软件需求分析，
    - 正确的说法有：
软件需求分析需要创建软件的逻辑模型
    - 错误的说法有：
①按照软件生命周期划分，需求分析属于软件定义阶段
②流程图、层次图、IPO图都是软件需求分析的常用工具
③对于一些小型软件，没有必要编写数据字典
--- 
- 5.判定表的优缺点
- 判定表的优点是容易转换为计算机实现，缺点是不能够描述组合条件（X）
- 优点：能间接而又无歧义地描述处理规则
- 缺点：并不适用于作为一种通用的设计工具，没有一种简单的方法使他能同时清晰的表示顺序和重复等处理特性

--- 
- 6.程序设计语言
- 程序设计语育是指编程时表现出来的特点、习惯、逻辑思维等。（×）
  - 解析：程序设计语言是人和计算机通信的基本工具，它的特点不可避免地会影响人思维和解决问题的方式，会影响人和计算机通信的方式和质量，也会影响其他人阅读和理解程序的难易程度。
- 进行程序设计语言的选择时，首先考虑的是应用领域。（√）
- 好程序的一个重要标准是源程序代码的逻辑简明清晰、易读易懂。（√）
- 程序语言的特性包括（ 算法特性 ）。
---
- 7.测试用例
- 测试用例由输入数据和预期的输出结果两部分组成（√）
--- 
- 8.模块
- 发现错误多的模块，残留在模块中的错误也多（√）
- 白盒法是一种静态测试方法，主要用于模块测试（X）
--- 
- 9.关于程序设计语言的选择，考虑因素
- 进行程序设计语言的选择时，首先考虑的是应用领域（√）
--- 
- 10.面对对象，类对象封装
- 类封装比对象封装更具体、更细致。`错`
---
- 11.面对对象，继承
- 继承性是父类和子类之间共享数据结构和消息的机制，这是类之间的一种关系。`错`
- 面向对象的继承性是子类自动共享父类数据结构和方法的机制（√）
--- 
- 12.面对对象，类的设计过程
- 类的设计过程包括 确定类、确定关联类、确定属性和识别继承关系。`对`
---
- 13.用例需求分析方法
- 用例需求分析方法采用的是一种结构化的情景分析方法，即基于场景建模的方法。`错`
---- 
- 14.面向对象分析设计活动（方法用于？）
- 一般来说，应该尽量选用面向对象语言来实现面向对象分析设计的结果。`对`
- 面向对象分析和设计活动是一个多次反复迭代的过程（√）
---- 
1.  面向对象用例
- 面向对象测试用例的设计由软件的输入——处理——输出视图或单个模块的算法细节驱动。`错`
- 面向对象设计是在分析模型的基础上，运用面向对象技术生成软件实现环境下的设计模型（√）
---
- 16.面向对象面向对象测试用例设计
- [`第9章-面向对象实现, 9.4-设计测试用例, 习题T1-4`]
- 面向对象测试用例的设计由软件的输入—处理—输出视图或单个模块的算法细节驱动。`✖`
  - 与传统软件测试（测试用例的设计由软件的输入—处理一输出视图或单个模块的算法细节驱动）不同，面向对象测试关注于设计适当的操作序列以检查类的状态。

---
- 17.代码行技术
- [`第11章-计划, 11.1.1代码行技术, P132习题T1-1`]
- 代码行技术是比较简单的定量估算软件规模的方法。`✔`
---
- 18.主程序员组
- [`第12章-组织, 12.2-主程序员组, P137T1-2`]
- 主程序员组的两个关键特性是专业化和层次性。`✔`
---
- 19.软件质量保证
- [`第13章-控制, 13.2-质量保证, P142习题T1-3`]
- 软件质量保证的措施主要有，基于非执行的测试（也称为复审）、基于执行的测试和程序正确性证明。`✔`
---
- 20.文档
- `第14章-软件维护及软件文档, 14.2-软件文档, P147习题`
- 文档是影响软件可维护性的决定因素。`✔`
## B卷
1. 选择3*6
2. 填空2*9
3. 判断2*12
4. 简答5*4
5. 综合2*10