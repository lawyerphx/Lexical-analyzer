# Lexical-analyzer
简易的词法分析器
工程结构：

1. analyzer.h，包含了词法分析器与记号流的实现，提供了如下公共接口
       void openfile(string ss)	//初始化词法分析器并打开文件 ss
       void Build_Graph()			//建立 state_trans 图结构
       package getItem()			//读入一个词语并返回其信息
       string getError()			//获取错误信息
2. def_lex.h，包含了词法分析器中用到的一些 define 信息
3. test_flow.cpp，检查输入 c 程序的格式是否有问题
4. main.cpp，主程序
5. src.c，需要词法分析的c语言程序

ANALYZER接口介绍：

特殊类：Token_Flow

	std::void init(void)

	初始化记号流

	std::void Statistic(void)

	获得关于记号流的统计信息

	std::string ask(string nam,string tok)

	尝试返回 (tok,nam) 在记号流中的别名，如果没有则为之分配别名。

private

	std::void F(int x,char y,int z)

	在状态转移图上面加一条从 x 到 z 的 y 转移

	std::char Get_char(void)

	从文件或缓冲序列中得到一个字符

	std::void Back_Push(char ch)

	将ch丢入缓冲序列

	std::string get_Token(void)

	得到当前单词的第一层标记

	std::void Raise_Error(int state)

	触发异常处理，state 表示异常编号

	std:: void move(char ch)

	在状态转移自动机上沿着 ch 行走

public

	std: : void openfile(string ss)

	初始化词法分析器并打开文件 ss

	std: : void Build_Graph(void)

	建立 state_trans 图结构

	std::package getItem(void)	

	读入一个词语并返回其信息

	string getError(void)

	获取错误信息

	更加具体的函数解释见 analyzer.h 代码注释

测试代码分为两份：

src.c为正常的，无错误的代码。

而 error_src.c 为代码中含有三处不同错误的代码。

执行

    .\main.exe
    src
    .\main.exe
    error_src

实验结果产生为文件 src.log, error_src.log

