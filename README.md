# SA and HCS Optimization Project

一个使用模拟退火算法和登山算法解决流水车间调度问题的最优化实验。

基于`C++ 17`标准库。

![](https://img.shields.io/badge/author-Gaozih-%2366ccff)
![](https://img.shields.io/github/license/Gzh0821/Optimization_project)
![](https://img.shields.io/github/stars/Gzh0821/Optimization_project)


## 简介
- 本项目来源于最优化方法课程的大作业。

- 本项目实现了使用`HCS`（登山算法）和`SA`（模拟退火算法）解决流水车间调度问题。

- 仅使用C++17标准库，可使用`gnu-g++`,`MSVC`等编译器直接编译运行。

- 代码重要处均附有注释，易于复现和修改。

## 项目结构
- `Optimization.h`为项目头文件，包含解决方案类声明，算法参数格式声明和随机数生成器。
- `Optimization.cpp`为项目解决方案文件，包含`SA`算法，`HCS`算法的实现及文件预处理方法。
- `main.cpp`为主文件，包含项目入口`main`函数和调用算法的`cal_func`函数。

## 选择数据集
- 本项目使用给出的数据集`flowshop-test-10-student.txt`，包含11组原始数据。
- 执行程序时，需输入数字0-10选择要处理的数据组。
- 或调用程序时直接输入数字参数。

## 简易的复现
- 可任选以下方法进行复现。
- 若程序运行结束后直接退出，可使用`getchar()`或`system("pause")`等方法暂停程序。
### 直接运行
- 本项目已使用默认参数（SA算法，起始温度=250,温度阈值=5,退火速度=0.95,允许相同数=2），重复20次,
构建了`exe`可执行文件（`Windows`平台），可在`project`目录下，打开`cmd`命令行窗口，输入`.\project.exe`运行程序。

### 使用CLion构建（建议）
- 在`CLion`中打开本目录，在文件-设置中，使用`CLion`捆绑的`mingw`工具链，在`Cmake`中，增加`Release`配置文件，构建并运行即可。

### 使用GNU-g++构建

#### 下载gnu编译器套件
- **若您已部署`gcc`，`g++`（GNU编译器套件）或`windows`平台的`mingw-gcc`组件，可跳过本步骤**
- 本项目未在`MSVC`平台下验证。
- ***以下教程为`windows`平台部署教程，`Linux`及其它平台请自行安装`GNU`编译器套件。
- 下载`mingw64-gcc-8.1.0`，
  可在[sourceforge](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/8.1.0/threads-posix/seh/x86_64-8.1.0-release-posix-seh-rt_v6-rev0.7z/download)中下载。

- 解压压缩包，并解压出的`mingw64`目录置于合适的目录下：如:`C:\`下。
- 打开`windows`系统的环境变量设置，在系统变量中的`Path`变量中添加`C:\mingw64\bin`（对应上一步的目录名）。
- 打开`cmd`命令行窗口，输入`g++`，查看是否部署成功。
-
#### 编译并运行

- 打开本项目目录，在本目录下打开`cmd`命令行窗口，输入以下命令来编译文件。
```
g++ main.cpp Optimization.cpp -O3 -std=c++17 -o Test.exe
```
- 将生成的`Test.exe`置入项目的`project`目录下，并在`project`目录下打开`cmd`命令行窗口，输入`.\Test.exe`运行程序。

## 计算结果
- 程序会打印每次算出的最优（最短时间）结果，仅需查看最后一次输出的结果即可。
- 输出结果格式如下（以第0组数据为例）：
```
7038
7,4,8,2,6,1,0,3,10,9,5,
Time:59
```
- 第一行为计算出的最短时间，即工件最优顺序的总加工时间为7038。
- 第二行为此时间对应的工件加工顺序。工件编号按原始数据顺序。从0号开始。
- 第三行为此次计算所耗费的时间，单位为毫秒（ms）。

## 修改算法和参数
- 若需修改每次执行程序时算法的执行次数，只需修改`main.cpp`中的`main`函数：
```cpp
    for (int i = 0; i < 20; ++i) {
        Solution s(sol);//复制构造Solution对象
        last_ans = cal_func(move(s), last_ans);//计算
    }
```
- 将`i < 20`中的20修改为需要的值即可。
---------
- 若需修改使用的算法或参数，只需修改`main.cpp`中的`cal_func`函数：
```cpp
    int ans = s.SA(make_tuple(250, 5, 0.95, 25));//SA算法,参数设置分别为起始温度,温度阈值,退火速度和允许相同数
    //int ans = s.HCS();//HCS算法
```
- 若需修改`SA`算法的参数，修改`make_tuple()`内的四个参数即可。
- 若需使用`HCS`算法，将`s.SA`所在行注释掉，并解除`s.HCS`所在行注释即可。
