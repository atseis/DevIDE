﻿# DevIDE——C集成开发环境

2019年小学期作业

## 技术文档

- [显示行数](./Document/显示行数.md)
- [语法高亮](./Document/语法高亮.md)
- [显示左侧目录树](./Document/显示左侧目录树.md)
- [左右拉伸](./Document/左右拉伸.md)
- [查找](./Document/查找.md)
- [隐藏注释](./Document/隐藏注释.md)
- [多窗口标签](./Document/多窗口标签.md)
- [自动补全](./Document/自动补全.md)

## 开发日志

### 2019.8.30

- 完成了初版最简洁设计
- 实现功能有
    - 打开文件
    - 保存、另存为文件
    - 新建文件
    - 文本框内编辑文件
    - 编译.cpp .c文件
    - 运行.cpp .c文件生成的.exe文件
- 下一步目标
    - 窗体左侧文件所在目录结构显示
    - 多文件编辑
    - 多窗口编辑时文本编辑框上方多个窗口的标签显示

### 2019.8.31

- 删除了代码中之前用来测试的多余输出语句
- 代码编辑框大小适应整个窗体变化
- 代码编辑框左侧增加显示行号功能
- 下一步目标
    - 实现代码高亮
    - 实现代码自动补全
    - 代码编辑框左侧文件目录结构显示
    - 编辑框上方多文件窗口标签显示
    - 编辑框下方编译、运行、调试结果显示
    - 调试功能的实现
    
### 2019.9.3

- 新增了目录树和打开功能
- 下一步目标
    - 实现代码高亮
    - 实现代码自动补全
    - 编辑框上方多文件窗口标签显示
    - 编辑框下方编译、运行、调试结果显示
    - 调试功能的实现

### 2019.9.6

- 补充了点击目录树打开对应文件的功能
- 实现代码高亮
- 下一步目标
    - 实现代码自动补全
    - 编辑框上方多文件窗口标签显示
    - 编辑框下方编译、运行、调试结果显示
    - 调试功能的实现

### 2019.9.9

- 补充了左右拉伸调整大小的功能
- 下一步目标
    - 实现代码自动补全
    - 编辑框上方多文件窗口标签显示
    - 编辑框下方编译、运行、调试结果显示
    - 调试功能的实现

### 2019.9.11

- 添加查找功能
- 下一步目标
    - 实现代码自动补全
    - 编辑框上方多文件窗口标签显示
    - 编辑框下方编译、运行、调试结果显示
    - 调试功能的实现

### 2019.9.12

- 添加代码的显示与隐藏功能
- 下一步目标
    - 实现代码自动补全
    - 编辑框上方多文件窗口标签显示
    - 编辑框下方编译、运行、调试结果显示
    - 调试功能的实现

### 2019.9.13

- 给代码框添加标签，实现多窗口编辑
- 下一步目标
    - 实现代码自动补全
    - 编辑框下方编译、运行、调试结果显示
    - 调试功能的实现
- 发现问题
    - 单行注释部分如果有函数名的格式，还是会按照函数名高亮方式高亮

### 2019.9.14

- 添加自动补全功能
- 下一步目标
    - 调试功能实现
    - 编辑框下方编译、运行、调试结果显示

### 2019.9.16

- 标签处增加关闭图标
- 补充补全样式设置
- 下一步目标
    - 调试功能实现
    - 编辑框下方编译、运行、调试结果显示
