# Linux 嵌入式开发 - Resume(C&Linux)
[CMAKE](https://www.hahack.com/codes/cmake/#%E5%90%8C%E4%B8%80%E7%9B%AE%E5%BD%95%EF%BC%8C%E5%A4%9A%E4%B8%AA%E6%BA%90%E6%96%87%E4%BB%B6)
# 1. Linux开发环境搭建
## 1.1 Linux操作 - vim编辑器
Vim编辑器分为三个模式，命令模式、插入模式和编辑模式，同一时间只能在一种模式下工作
### 编辑模式
打开vim后的默认模式，进行复制粘贴保存光标定位等操作，此模式下无法修改已有代码，在插入模式下按’esc’退出插入模式（系统自动转换为编辑模式）
#### 编辑模式下的操作
插入模式下。按“ESC”进入编辑模式
	* u  撤销
	* control r 反撤销
	* 数字n+x 删除光标后n个字符
	* 数字n+X 删除光标前n个字符
	* 数字n+dd 剪切当前行开始n行
	* 数字n+yy 复制当前行开始的n行
	* p 把黏贴板上的内容插入到当前行

### 插入模式
在命令模式下按 ’a i o ’ 进入，可对已有代码进行编辑，区别是插入的位置不同
	* 按"i" 在光标后面开始编辑
	* 按“a”在光标前开始编辑
	* 按“o”在光标下另起新行进行编辑
#### 插入模式下的操作

### 命令模式（最后一行模式）
只能通过编辑模式进入，shift  :进入，用于保存，退出，另存文件
#### 命令模式下的操作
	* :w 保存文件
	* :wq 保存文件并退出vi
	* :x 保存文件并退出vi
	* :q! 不保存文件，强制退出vi
	* :w filename 另存为filename

- - - -
## 1.2 常用服务介绍
远程终端控制，允许远程客户端对Linux系统（服务端）进行访问和操作，调用其提供的服务和功能
实用性: 以后可以将虚拟机安装在另外的电脑，然后通过sshd（ScureCRT）进行远程访问和操作
### sshd ssh: Secure Shell d : 服务
	1. ScureCRT客户端
		* 命令，字符串传递和交互
		* 实现文件传输 rz (receive from client)  sz (send to client)
	2. SSHD服务端（Linux中下载）
### samba服务 server message block in Linux - smbd & nmbd
提供远程访问Linux系统的共享文件夹的功能
	* 安装 sudo apt-get install samba
	* 配置 
		* [rocky_share]
        		comment = My share
       	 		path = /Home/Documents
        		writable = yes
        		browseable = yes 
	* 用户权限
		* sudo smbpasswd -a username 
	* 重启 
		* sudo /etc/init.d/smbd restart
		* sudo /etc/init.d/nmbd restart 
	* 连接 command + K - 输入Linux IP地址 - 输入d samba 用户名及密码
- - - -
## 1.3 VMtools
为ubuntu提供远程访问和编辑主机系统特定共享文件夹的功能 	
共享文件夹设置 虚拟机 - 设置 - 共享 -  添加或删除需要共享给Ubuntu的文件夹
在Ubuntu的Linux系统中访问共享文件所在目录:  cd /mnt/hgfs/
- - - -
## 1.4 代码编辑器 IDE（集成开发环境） = 编辑 + 编译器 + 调试器
问题 : 嵌入式开发平台很多 ARM STM32 51单片机 不同平台对应不同的编译器和调试器
思路 : 但编辑器的选择可以统一，只要找到符合开发平台的编译器和调试器即可
### Understand编辑器使用
……

# 2. 嵌入式C语言开发
Gcc - GNU GNU C Compiler
## 2.1gcc用法
gcc -o 输出的文件名（变异后输出的文件） 输入的文件名（需要编译的文件）
**文件名的后缀设置要注意是特定的文件（.c 或是 .cpp 等等），目的是让翻译器能够识别并调用对应的翻译者，但目前gcc版本已经可以自动识别c和c++了**

###  C语言的编译过程
	1. 预处理
	在编写大型程序时，预处理可以帮助我们省时省力
	Cpp 生成预处理文件 -o a.i 011.c
	预处理就是替换 将define设定的宏体替换成宏名 #define ABC 10 : 将ABC替换成10
	2. 编译
	/usr/lib/gcc/x86_64-linux-gnu/7/cc1 -o a.s 011.c
	将011.c文件编译成 a.s文件 这个操作相当于 `gcc -S`
	3. 汇编 生成目标文件 .o
	As -o a.o a.s 想当于 `gcc -c`
	4. 链接系统标准库
	/usr/lib/gcc/x86_64-linux-gnu/7/collect2  -o build a.o+…
	相当于 `gcc -o build 011.c`
	在编译过程中，关键字的处理是在编译中进行的，而include和define在预	处理阶段已经处理完了，所以这两者都不是关键字
	5. *编译常用命令：
```
	gcc filename.c -o filename  
	gcc -o filename filename.c 
	//filename.c可以放在gcc后面或是命令最后，但 -o filename 必须看作一个整体
```

### C语言常见错误举例
* 预处理错误
#include "name’’
#include<name>
Not find
解析，预处理中调用头文件的格式，<>只会找系统中的头文件而不会找当前目录下的头文件，而’’ ‘’只会找当前目录下的头文件，而不会找系统头文件
解决方法: gcc -I 跟查找头文件目录

* 编译错误 - 语法错误
* 链接错误 - 
原材料不够 (undefined) 
undefined reference to ‘’ ‘’
寻找标签是否实现
或者多了 
multiple definition of `fun' 多次实现标签，只保留一个标签的实现即可

## 2.2 预处理的使用
### 常用预处理手段
* #include 	包含头文件
* #define	宏	替换
	#define  宏名 宏体 加括号
	`#define  ABC (5+3)`
	printf(‘’ the %d\n’’, ABC*5); (5+3)*5
	宏函数
	`#define  ABC(x)  (5+(x))`
	**注意，宏定义只会做简单的替换，而不会计算优先级，为了避免运算符优先级的影响，一般在定义宏函数时，需要对替换单元加上括号，保证优先级计算**

* #ifdef  #else  #endif	  条件编译
* 预定义宏
__FUNCTION__: 函数名
__LINE__: 行号
__FILE__: 文件名
printf("the %s, %s, %d\n", __FUNCTION__, __FILE__,__LINE__);
//标示出所在的函数的函数名，文件名，以及函数所在行号

### 条件预处理
在实际开发过程中，一般分有测试版本 and 发行版本，在测试版本中，会对代码进行一定的预处理以便debugger 但在发行时，我们不希望之前定义的预定义宏出现在发行版本中，为此，我们使用条件预处理。例如我们有代码:                                                                           

```
#include<stdio.h>
int main()
{
#ifdef  ABC
        printf("the %s, %s, %d\n", __FUNCTION__, __FILE__,__LINE__);
#endif
        printf("hello world !\n »);
        return 0;
}
```
#ifdef + #endif 表示如果在代码中定义了ABC 则编译时运行条件框架下的代码，一般来说，我们在实际代码中不会定义ABC，但在调试过程中，为了方便debugger，我们会用到 -D命令使得ABC得到定义。

* gcc -D ABC 等价于 #define ABC
这样，在调试中就会运行条件预处理框架下的代码
对于 003.c文件 有: gcc -DABC -o build 003.c

### 另外一些关于宏定义的指令
```
#include <stdio.h>

#define TEST

// 取消已经定义的宏
#undef TEST

//#开头 以if开头 必须以endif结尾
// #ifdef if defined如果已经定义
// #ifndef if not defined 如果尚未定义
#ifndef TEST
void print_message()
{
    printf("这里是定义的\n");
}
#else
void print_message()
{
    printf("这里是未定义的\n");
}
#endif

#define TEST 8
// 这里是条件起始 必须加上条件 否则会导致预编译错误 其实是预编译语法错误
#if TEST == 1
int a = 100;
// 如果前一个条件不成立，才会处理到elif 此时如果没有规定成立条件，会导致报错
#elif TEST < 100
int a = 1000;
#else
int a = 10000;
#endif

// 一般来说，对于代码当中尚未开发完成的代码，而又可能会导致一些不可预见的问题
// 但是又不想让程序无法执行 可以加上这样一个预处理指令，代表代码仍需处理
#warning 这里会出现什么内容

// 直接抛出一个预编译错误
#error 这里会出现错误么？

// 这个指令功能非常强大
// 非致命性警告，只有添加了 -Wall 才可发现 - W警告 all所有 显示所有的警告
#pragma warning("这是什么？")

// 显示一段信息
#pragma message("这是一段信息")

// 内存对齐方式，括号内指定内存对齐的字节数
#pragma pack(2)

int main(int argc, char const *argv[])
{
    print_message();
    return 0;
}
```


### 宏展开下的#, ##
* # 字符串化
* ## 连接符号
```
#define ABC(x)			#x 
#define ABC(x)			day##x 
```

示例代码: 
```
#include<stdio.h>
  
#define ABC(x)          #x
#define DAY(x)          myday##x		
int main()
{
        int myday1 = 10;
        int myday2 = 20;
        printf(ABC(ab\n));
        printf("the day is %d\n",DAY(1));
        return 0;
}
输出结果：
ab
the day is 10
```

- - - -
## 2.3 C语言关键字
### 数据类型
> 	C语言的操作对象：资源/内存（内存类型的资源，LCD、LED灯）  
> 	C语言通过数据类型描述这些资源的属性（大小  
> 	比如 int(a) ; sizeof(a) = 4 bytes（字节） = 32bits（比特）;  
> 	硬件芯片操作的最小单位： bit 1 and 0  
> 	软件操作的最小单位：1byte（字节） = 8 bits（比特）  
> 	而 sizeof(char)  = 1 byte  = 8 bits	  
> 	嵌入式的应用场景：硬件处理的最小单位  
	
	* int
		1. 大小：根据编译器来决定 可能是32bits，也可能是16bits
		2. 编译器最优的处理大小：系统一个周期，所能接受的最大处理单位，int：32 bits = 4B 也可能是 16 bits = 2B
	* 整型常量：数字构成的字符串
	* 八进制和十六进制赋值规则： 
		1. 八进制 int a = 012 	// a = 10 = 1*8 + 2*1
		2. 十六进制 int a = 0x1A		// a = 26 = 1*16 + (A=10)*1
	* long、short：特殊长度限制符，整型类型的组合
	* unsigned（无符号数）— 数据 、signed（有符号）— 数字 
		决定了内存空间的最高字节是符号位还是数据
	* float、double 浮点数 
		浮点数在内存中的表示形式跟整型是完全不同的
		大小  float ：4B	double ：8B
		浮点型常量 	1.0 为 double类型
					1.0f 为 float
![](Readme/%E6%88%AA%E5%B1%8F2020-04-2214.58.26.png)

					 
	* void 声明标准
	 
	* 格式说明符：格式说明由“％”和格式字符组成，如％d％f等。它的作用是将输出的数据转换为指定的格式输出。格式说明总是由“％”字符开始的。 
	* 输出格式说明符（format）定义
		1. ％d：整型输出，％ld：长整型输出， 
		2. ％o：以八进制数形式输出整数，
		3. ％x/%X：以十六进制数形式输出无符号整数，或输出字符串的地址。%x输出小写，%X输出大写
		4. ％p：是以16进制的形式输出内存地址
		5. ％u：以十进制数输出unsigned型数据(无符号数)。注意⚠️：%d与%u有无符号的数值范围，也就是极限的值，不然数值打印出来会有误。%lu ：长unsigned型数据。
		6. ％c：用来输出一个字符，
		7. ％s：用来输出一个字符串，
		8. ％f：用来输出实数，以小数形式输出，默认情况下保留小数点6位。 
		9. %.100f：用来输出实数，保留小数点100位。
		10. ％e：以指数形式输出实数，
		11. ％g：根据大小自动选f格式或e格式，且不输出无意义的零。
	
	* 输入 格式说明符（format）与输出的基本相同，但输入不能是地址，所以没有地址说明符，同时多了一个格式说明符 %i：
		* 	%i/%I ： 输入一个整数，可以是10进制数，带前导0为八进制，前导0x的为16进制数。

### C 语言常用库函数
	* math.h 
		* double sqrt(double x) - 平方根
		* double fabs(double x)  - 绝对值
		* double pow(double x, double y) - 指数函数
		* double log(double x)  - ε为底的对数函数log
		* double 1og10(double x)  - 10位底
		* double sin(double x) - sin函数
		* double cos(double x) - cos函数
	* stdlib.h
		* int rand(void) - 产生一个0 到 4字节之间的随机正数
		* void srand (unsigned a) - 随机数发生器
		* exit(int a ) - 退出程序
```
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	srand(time(NULL));	// 以当前时间为基础初始化一个随机数发生器，可以让后面产生的随机数不断更新，而不是固定在一个值
	int num = rand() % 10;
	printf("%d\n", num);

	int num2 = rand() % 10;
	printf("%d\n", num2);
}
```

	* unistd.h
		* sleep(unsigned seconds)  - 睡眠/等待（秒）
		* usleep(int micro_seconds); - 睡眠/等待（微秒）
	
- - - -

### 自定义数据类型
#### struct - 结构体：结构体类型中的成员名可以与程序中的变量名相同，二者并不代表同一个对象，编译程序可以自动对他们进行区分，初始化时并不分配空间，只有在它定义变量时才分配空间

	 语法形式： 
```
struct my_struct {
		//成员列表
		unsigned int a;
		unsigned int b;
		unsigned int c;
		unsigned int d;
};		//定义结构体名称,变量顺序有要求

* struct my_struct mybuf;
```

	实例
```
#define N 20
struct student{
	int no;
	char name[N];
	float score;
}s3 = {3,"s3",90}, s4{4,"s4",80}; // 创建结构体对象同时初始化，⚠️注意，这种初始化方式只能在这里使用，不能在其他地方使用，见下
为了使用上的方面，通常用一个宏定义代表一个结构体类型
#define WORKER struct worker // 这样在程序中，WORKER 与 struct worker等效
WORKER{
	long number;
	char name[N]
	char sex;
	int age;
	float salary;
 	char address[80]
	char phone[20]
}worker3;	// 定义结构体类型的同时定义变量

WORKER worker1,worker2;	// 创建结构体变量
s3 = {3,"s3",90};	// 错误，这里定义结构体只能一项一项定义
```
		*  结构体嵌套
```
#define N 20
struct birthday{
	int year;
	int month;
	int day;
};

struct student{
	int no;
	char name[N];
	struct birthday date;
	float score;
}s1 = {1,"s1",{1992,9,9},89}

int main()
{
	struct student s2;
	s2.no = 2;
	strcpy(s2.name,"s2");
	s2.date.year = 1993;	//结构体内嵌结构体的变量初始化
	s2.date.month = 10;
	s2.date.day = 10;
	s2.score = 99
}

// 当内嵌结构体只在某一个结构体中会用到，可以直接在结构体内部直接定义结构体
struct student{
	int no;
	char name[N];
	struct birthday 
	{
		int year;
		int month;
		int day;
	}date;
	float score;
}s1 = {1,"s1",{1992,9,9},89}
	
```
	* 结构体数组和结构体指针
```
// 结构体数组
struct student
{
	int no;
	char name[20]
	float score;
}stu[3];

// 也可以在定义完成后另外定义结构体数组
struct student stu1[4];
struct student stu2[] = {{1,"s1",99},{2,"s2".88},{3,"s3",99}};	//定义结构体数组同时初始化各个结构体的变量

// 同类型结构体可以直接赋值
stu1[0] = stu2[0];
stu1[1] = stu2[1];
// 遍历结构体数组时，要注意一个结构体数组的大小为单个结构体大小*结构体数组内结构体个数；所以要遍历结构体数组的每个结构体需要用sizeof(s1)/sizeof(struct student)
for (i = 0; i<sizeof(s1)/sizeof(struct student); i++)
{
	printf("%d,%s,%f\n",stu1[i].no,stu1[i].name,stu1[i].score);
}

```

```
// 结构体指针
// 结构体指针的初始化规定了它的数据特性（指针），并为结构体指针本身分配了一定的内存空间。但是指针的内容尚未确定，它可以指向随机的对象

struct student *pstu; //	结构体指针初始化

pstu = stu1; //指针指向了结构体数组的首地址，即stu1[0],通过对指针进行为运算p++，可以让指针指向结构体数组内其他结构体,当然与普通指针一样，实际上pstu指向的是stu1结构体数组

// 结构体指针可以作为函数的形参，用来调用已初始化的结构体数组
void print_into(struct student *p, int n)
{
	for(i = 0; i<n; i++)
	{
	printf("%d,%c,%f",pstu->no,p->name,(*p).score);	//访问结构体指针内部变量的形式
	pstu++; // 位运算，让指针指向结构体数组内的其他结构体，实现遍历
	// printf("%d,%c,%f",pstu[i]->no,pstu[i]->name,psut[i].score); 也可以用数组形式对结构体指针进行遍历

	}
}

int main()
{
	struct student stu2[] = {{1,"s1",99},{2,"s2".88},{3,"s3",99}};
	print_into(stu2,sizeof(stu2)/sizeof(stu2[0]))
	return 0;
}
```

#### union  共同体 使得不同数据类型的数据可以使用共用的存储区域，这种数据构造类型称为共用体，共用体的定义，说明和使用形式上与结构体相似。两者本质上的不同仅在于使用内存的方式上
		应用场景；技巧性代码
```
union my_union{
		char a;
		short b;
		int c;
};

int main()
{
	union my_union abc;
	printf("%d \n", sizeof(union my_union));	//输出结果时4，这my_union中，char short int时共用一段内存的，所以整个机构体的内存大小等于结构体内部最大的类型数据的大小（int）
	abc.a ='A';
	abc.b = 20;
	abc.c =0x12345678;
	printf("%#x %c\n",abc.a abc.a);		// 输出结果。0x78 x 
	// 分析，由于共用体内部的数据时共用内存的，所以在对各项数据进行复制初始化时，后者的赋值会直接将内存中的值覆盖，所以本来存放‘A’的内存会被int c变量中第一个字节的内存（78）所覆盖，所以输出时0x78  x（#%x表示以16进制输出，加上前缀，%c表示以字符常量形式输出78对应ASCII码的x）
	return 0;
}


```

#### enum - enumerate ：枚举 表示被命名的整型常数的集合
例如：
```
#define MON 0
#define TUE 1
#define WED 2
```
可以打包为： `enum abc{ MON =0, TUE = 1, WED = 2};`
```
enum week{
		Monday = 0, Tuesday = 1, Wednesday = 2,
		Thursday, Friday,	
		Saturday, Sunday	//默认情况以0开始累加，除非特殊定义
		//如果MON是100，TUE为101，以此类推
};
```
主要功能和用法，能够更好地描述对象集合，让人与人之间的代码交流更加容易理解

####  typedef 数据类型的别名，能够更加准确的表示数据表达的意思，增加可读性
		* C语言中经常在定义结构体类型时使用typedef
#### 用struct和typedef构建链表
```
#include <stdio.h>
//链表
typedef struct node{
	int data;
	struct node *next;
}listnode *linklist;	//初始化结构体类型的别名,这样对于结构体node多了两个结构体类型的别名，node listnode 和 node *linklist

int main()
{
	// struct node n1,n2,*p;
	listnode n1,n2,n3;	//这里n1,n2,n3的类型不是 struct node 而是 struct listnode node
	linklist p; //	由于定义了类型为指针结构体别名linklist,所以创建结构体指针时，不需要在加*

	n1.date = 10;
	n1.nextt = NULL;
	n2.data = 20;
	n2.next = NULL;
	n3.data = 40;
	n3.next = NULL；
	p = &n1;
	return 0;

}

```
	语法： `typedef int a_t; //a_t 是int类型的外号`
	xxx_t  是不成文的对于typedef类型的命名方法

#### 位段（位域）
对于一个144bit [18位]的模块，将第98位使能（置1）
```
n = 98/8;
config[n] |= (1<<(98%8))
```
但这种使能的方法十分不直观，C语言存在一种方法，能以位为单位对内存空间进行命令和赋值，这种方法叫位段（位域），位域一般是以结构体为单位，对物理模块的位进行定义，尤其是当模块中每个功能的使能所用位段不同时，位段的定义就尤为重要且方便
```
/********位段 bit-field********/

#include<stdio.h>
#include<string.h>
#include<termios.h>
#include<unistd.h>

typedef unsigned char BYTE; //位域是无符号位，所以定义时一定用unsigned

struct date{
    BYTE rs:1;  // :后的数字表示定义的变量存储的位数，这里rs表示存储1位，freq表示存储7位   
    BYTE dbm:2;
    BYTE    :2; // 无意义位段，当需要在特定位段进行定义而前面的位段尚未被定义时，可以通过定义无意义位段来跳过前面的位段
    BYTE fosc:3;    // 5-7位表示晶振频率
    BYTE freq:7; 
};

int main()
{
    struct date b;
    b.rs = 1;   
    b.freq = 100;
    b.dbm = 3;
    
    printf("b.rs = %x\n", b.rs);
    printf("b.freq = %x\n", b.freq);
    printf("b.dbm = %x\n", b.dbm);

}

```
* 注意⚠️：
	* 对于计算机来说，任何数据类型的内存分配都是以字节为最下单位的，所以对于以结构体为基础的位段定义，一旦总位段超过了一个字节，则计算机会开辟新的内存空间存储
	* 

- - - -

### 逻辑结构
	* if else
	* switch(a - 整型数){
		case 1;
			break
		case 2;
	}
	* do, while, for 
	* continue, break, goto
	goto 跳转

### 类型修饰符
	
### 杂项
		* return
		返回的概念
		* sizeof
		sizeof 并非函数，而是C语言中设定好的执行特定功能的关键字，是编译器给我们查看内存空间容量的一个工具
- - - -
### 类型修饰符
对内存资源存放位置的限定、对资源属性中位置的限定
内存的分类：可读、可写、以及可读可写
内存（存储器）（访问速度相对满）、寄存器（位于CPU中）（访问速度相对快）
* auto：默认情况下实现的关键字（一般情况不用书写说明）、分配的内存位置都是可读可写的区域、如果是在定义{}中定义，则为栈空间
```
{
auto int a 	//等价于 int a
}
```

* register：定义一些快速访问变量，编译器会尽量CPU的寄存器去描述定义值，但如果寄存器不足时，定义值还是放在存储器中
	* 引用符 &对register不起作用，因为寄存器的地址名称为R0、R2等而非类似0x100的可以引用的地址名称
```
register int a 		//限制变量定义在寄存器上的修饰符 
```

* static：静态修饰符
	* 应用场景（修饰3种数据）：
		1. 函数内部的变量
```
int fun()
{
	int a; ====> static int a;
}		
```
		2. 函数外部的变量
```
int a; =====> static int a;
int fun() {}
```
		3. 函数的修饰符
```
int fun(); ====> static int();
```

* extern：外部声明
* const：常量的定义
* volatile：告知编译器编译方法的关键字，不优化编译
```
int a =100;

while (a == 100);

mylcd();
——————————
[a]：a的地址
f1: LDR R0, [a]	//将[a] 读取到R0中
f2: CMP R0, #100	//比较R0和100
f3: JMPeq f1
f4: mylcd();		//
```
- - - -

## 运算符
### 算数操作运算-加减乘除求模
注意⚠️：CPU中只有加法器，所有算数操作运算都是通过加法器的组合来完成的
	* 模的使用：n%m = res [0 m-1]
		1. 取一个范围的数：
		eg：给一个任意的数字，得到一个1到100内的数字？
				(m%100) +1
		2. 得到M进制的一个个位数

### 逻辑运算：返回结果为1或0（目前统一为0为假，非零为真）
	注意⚠️：A || B  != B || A
```
#include<stdio.h>

int main()
{
		int a = 10;
		int res;
		res = (a == 10) || printf(“=========\n”);
		printf(‘’the res is %d\n’’,res);
		return 0;
		输出结果为 the res is 1

		若改为：res = (a != 10) || printf(“=========\n”);
		输出结果为：===========
					the res is 1
```

### 链表详解-管理动态内存
对于一般的数组，它的大小时静态分配的，就是说数组的大小必须时常量而不是变量，不能用变量来定义数组的大小。
#### 单向链表
```
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// 链表
// 1.链表的创建
typedef struct student
{
    int num;
    char name[20];
    struct student *next;
}STU;

// 2.链表的遍历输出
void link_printf(STU *head)
{
    while (head != NULL)
    {   
        printf("%d %s\n",head->num,head->name);
        head = head->next;
        
    }
}
// 3.1. 链表的插入，头插法在链表插入数据
STU *link_insert(STU *head, STU *pnew)
{
    if (head == NULL)
    {
        head = pnew;
        head->next = NULL;
    }else if(pnew != NULL)
    {
        pnew->next = head;
        head = pnew;
    }
    return head;
}
// 3.2.链表插入，尾插法插入数据
STU *link_insert_end(STU *head, STU *pnew)
{
    STU *pb = head;
    if (head == NULL)
    {
        head = pnew;
        head->next = NULL;
    }else if(pnew != NULL)
    {
        while (pb->next != NULL)
        {
            pb = pb->next;
        }
        pb->next = pnew;
        pnew->next = NULL;
    }
    return head;
}
// 4.链表内数据的查找
STU *link_find(STU *head, char *name)
{
    while (head != NULL)
    {   
        if(strcmp(head->name, name) == 0)
            break;
        printf("%d %s\n",head->num,head->name);
        head = head->next;
    }
    return head;
}
// 5.链表的内存释放
STU *link_free(STU *head)
{
    STU *ps;    //建立缓存
    while (head != NULL)
    {   
        // 先找到头节点的下一个节点，再将头节点释放，然后将下一个节点定义位头节点，继续寻找
        ps = head->next; 
        free(head);
        head = ps;
            
    }
    return head;
}

// 6.链表任意节点的删除
STU *link_delete(STU *head, char *name)
{
    STU *ps = head,*pf = head;
    while (pf != NULL)
    {   
        if(strcmp(pf->name, name) == 0){
            if (pf == head)
            {
                // 如果头节点就时要删除的节点，直接通过将头节点改为下个节点来解除关系
                head = head->next;
            }else
            {
                // 查找，找到后先接触将被删除节点与其他节点的关系
                // ps节点本身时指向要被删除的节点，这是需要将这个指向改为要被删除节点的下个节点            
                ps->next = pf->next;
            }
            free(pf);
            break;  // 退出while循环
            
        }
            
    // 由于链表的单向性，删除节点后，被删除的节点的前一个节点无法指向下下一个节点，为此，在查找时必须先建立缓存节点存放被删除节点的前一个节点
        ps = pf;
        pf = pf->next;
    }
    return head;
}

// 7.链表排序-升序
// 定义交换节点函数
void swap(STU *pf,STU *pb)
{
    STU temp;
    temp = *pf;
    *pf = *pb;
    *pb = temp;
    // 将指向交换
    temp.next = pf->next;
    pf->next = pb->next;
    pb->next = temp.next;
    //在此，pf就会作为两次比较后的最小值不断跟后面的节点进行比较
}
// 定义排序函数
STU *link_order(STU *head)
{
    STU *pf = head,*pb;
    while (pf->next != NULL)    // 外循环，决定了产生了多少个最少值
    {
        pb = pf->next;
        while (pb != NULL)  // 内循环，将外循环得到的当前最小值和后面的节点数据一一比较
        {
            if (pf->num > pb->num)
                swap(pf,pb);
            else if (pf->num == pb->num){
                if (*(pf->name) > *(pb->name))  // 取字符串首地址，也就是首字母，这里比较的是ascII码
                    swap(pf,pb);
            }
            pb = pb->next;
        }
        // 当内循环进行了一次之后，首节点就会获得整个链表的最小值，至此，pf往后移一位，在剩下的节点中找到最小值
        pf = pf->next;
    }
    return head;
}

// 8.链表逆序
// 思路。将所有节点的指向反转，同时原来的头节点指向NULL，尾节点作为头节点
STU *link_reverse(STU  *head)
{
    STU *pf = head, *pb,*ps;
    if (head == NULL)
        return head;
    pb = pf->next;
    while (pb != NULL)  //因为pb在循环中时最后改变指向的结构体指针，所以只需要判读pb是否指向NULL
    {
        ps = pb->next;  // 先将pb的下个节点进行保存
        pb->next = pf;  // 改变pb->next的指向
        pf = pb;    // 然后将pf后移
        pb = ps;    // 最后将pb后移
    }
    // 当所有指向都改变后，而此时pf指向尾节点，需先现将head->next指向该会NULL,在将head指向pf
    head->next = NULL; 
    head = pf;
    return head;
}



// 查看帮助信息
void print_help(void)
{
    puts("************");
    puts("1.插入学生信息到头部");
    puts("2.插入学生信息到尾部");
    puts("3.遍历学生信息");
    puts("4.查找学生信息");
    puts("5.删除学生信息");
    puts("6.按学号排序");
    puts("7.逆序排列");
    puts("8.查看帮助信息");
    puts("9.退出管理系统");
    puts("************");
}
int main()
{
    STU *pnew,*p,*head = NULL,*pb;
    int i,len = 3,ops; char name[18];
    print_help();
    while (1)
    {
        puts("请输入操作码：");
        scanf("%d",&ops);
        switch(ops){
            case 1: //插入学生信息到头部
                pnew = malloc(sizeof(STU));
                puts("请输入学号和姓名：");
                scanf("%d%s",&(pnew->num),pnew->name);
                head = link_insert(head,pnew);
            break;
            case 2: // 插入学生信息到尾部
                
            break;
            case 3: //打印学生信息
                if (head == NULL)
                    puts("列表为空\n");
                else
                    link_printf(head);
            break;
            case 4: //查找学生信息
                puts("请输入要查找的姓名：");
                scanf("%s",name);
                p = link_find(head,name);
                if (p != NULL)
                {
                    printf("找到：%d %s\n", p->num,p->name);
                }else
                {
                    printf("找不到对应姓名\n");
                }
            break;
            case 5: //删除学生信息
                puts("请输入要删除的姓名：");
                scanf("%s",name);
                head = link_delete(head,name);
            break;
            case 6: //按学号排序
                head = link_order(head);
            break;
            case 7: //逆序排列
                head = link_reverse(head);
            break;
            case 8: //查看帮助
                print_help();
            break;
            case 9: //退出管理系统
                return 0;
            break;
        }
    }
    // head = link_free(head);
    return 0;
}

```

#### 双向链表
* 双向链表与链表的不同在于节点的不仅可以指向后面的节点，也可以指向前面的节点
* 双向链表一般都是循环结构，就是说head->front指向最后一个节点，而尾节点->next指向head
```
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// 双向链表-循环结构
// 双向链表与链表的不同在于节点的不仅可以指向后面的节点，也可以指向前面的节点
// 双向链表一般都是循环结构，就是说head->next指向最后一个节点，而尾节点->next指向head
// 1.双向链表的创建
typedef struct student
{
    int num;
    char name[20];
    struct student *front;  // 新增一个front指向当前节点的上一个节点
    struct student *next;
}STU;

// 2.链表的遍历输出
void link_printf(int line, STU *head,char flag)
{
    // 由于双向链表的循环结构，链表中任何节点都不会指向NULL
    // 但因为head是确定的，所以只需要新增一个临时指向节点，通过判断节点是否指向head来确定遍历是否完成
    STU *pb = head;
    if (head == NULL)
    {
        return; //如果链表本身为空，则直接退出
    }
    if (flag == 1)
    {
        while (pb->next != head)
        {   
            printf("%d:%d %s\n",line,pb->num,pb->name);
            pb = pb->next;
        }
    }else   //逆序打印
    {
        pb = pb->front; // 从尾部开始反向打印
        while (pb != head)
        {
            printf("%d:%d %s\n",line,pb->num,pb->name);
            pb = pb->front;
        }
    } 
    printf("%d:%d %s\n",line,pb->num,pb->name);
}
// 3.1. 双向链表的插入，以head作为参考头节点，从head->front也就是尾节点后面插入新的节点
STU *link_insert(STU *head, STU *pnew)
{
    STU *pb = head;
    if (head == NULL)
    {
        // 双向链表对于首个插入的数据，pnew->front和pnew->next必须指向本身，以满足循环结构
        head = pnew;
        head->next = head;
        head->front = head;        
    }else if(pnew != NULL)
    {
        // 以head为首，在尾节点后插入新节点
        pb = head->front;   // 找到最后一个节点
        pnew->next = pb->next;  // pb->next指向头节点，将pnew->next指向头节点
        pb->next = pnew;    
        pnew->front = pb;
        pnew->next->front = pnew;
        
    }
    return head;
}

// 4.链表内数据的查找
STU *link_find(STU *head, char *name)
{
    STU *pb = head;
    if (head == NULL)
    {
        return NULL; //如果链表本身为空，则直接退出
    }
    while (pb->next != head)
    {   
        if(strcmp(pb->name, name) == 0)
            break;
        pb = pb->next;
    }
    if(strcmp(pb->name, name) == 0)
        return pb;
    else
        return NULL;
}
// 5.链表的内存释放
STU *link_free(STU *head)
{
    STU *ps = head;    //建立缓存
    if (head == NULL)
    {
        return NULL;
    }
    while (ps->next != head)
    {   
        // 先找到头节点的下一个节点，再将头节点释放，然后将下一个节点定义位头节点，继续寻找
        ps = ps->next; 
        free(ps->front);
    }
    free(ps);
    return NULL;
}

// 6.链表任意节点的删除
STU *link_delete(STU *head, char *name)
{
    STU *pb = head;
    if (head == NULL)
    {
        return NULL; //如果链表本身为空，则直接退出
    }
    while (pb->next != head)    //在头节点到倒数第二个节点中查找
    {   
        if(strcmp(pb->name, name) == 0) // 找到就break，准备删除
            break;  
        pb = pb->next;
    }
    // 分两种情况，1是在前面已经找到了，准备删除，这时pb对应要被删除的节点，2是前面没找到，这时pb对应最后一个节点
    if(strcmp(pb->name, name) == 0)
    {
        if (pb == head)
            head = pb->next;
        pb->front->next = pb->next;
        pb->next->front = pb->front;
        free(pb);
    }
    return head;
}

// 7.链表排序-升序
// 定义交换节点函数
void swap(STU *pf,STU *pb)
{
    STU temp;
    temp = *pf;
    *pf = *pb;
    *pb = temp;
    // 将指向交换
    temp.next = pf->next;
    temp.front = pf->front;
    pf->next = pb->next;
    pf->front = pb->front;
    pb->next = temp.next;
    pb->front = temp.front;
    //在此，pf就会作为两次比较后的最小值不断跟后面的节点进行比较
}
// 定义排序函数
STU *link_order(STU *head)
{
    STU *pf = head,*pb;
    while (pf->next != head)    // 外循环，决定了产生了多少个最少值
    {
        pb = pf->next;
        while (pb != head)  // 内循环，将外循环得到的当前最小值和后面的节点数据一一比较
        {
            if (pf->num > pb->num)
                swap(pf,pb);
            else if (pf->num == pb->num){
                if (*(pf->name) > *(pb->name))  // 取字符串首地址，也就是首字母，这里比较的是ascII码
                    swap(pf,pb);
            }
            pb = pb->next;
        }
        // 当内循环进行了一次之后，首节点就会获得整个链表的最小值，至此，pf往后移一位，在剩下的节点中找到最小值
        pf = pf->next;
    }
    return head;
}

// 查看帮助信息
void print_help(void)
{
    puts("************");
    puts("1.插入学生信息到尾部");
    puts("2.遍历学生信息");
    puts("3.查找学生信息");
    puts("4.删除学生信息");
    puts("5.按学号排序");
    puts("6.逆序排列");
    puts("7.查看帮助信息");
    puts("8.退出管理系统");
    puts("************");
}
int main()
{
    STU *pnew,*p,*head = NULL,*pb;
    int i,len = 3,ops; char name[18];
    print_help();
    while (1)
    {
        puts("请输入操作码：");
        scanf("%d",&ops);
        switch(ops){
            case 1: //插入学生信息到头部
                pnew = malloc(sizeof(STU));
                puts("请输入学号和姓名：");
                scanf("%d%s",&(pnew->num),pnew->name);
                head = link_insert(head,pnew);
            break;
            case 2: //打印学生信息
                if (head == NULL)
                    puts("列表为空\n");
                else
                    link_printf(__LINE__,head,1);
            break;
            case 3: //查找学生信息
                puts("请输入要查找的姓名：");
                scanf("%s",name);
                p = link_find(head,name);
                if (p != NULL)
                {
                    printf("找到：%d %s\n", p->num,p->name);
                }else
                {
                    printf("找不到对应姓名\n");
                }
            break;
            case 4: //删除学生信息
                puts("请输入要删除的姓名：");
                scanf("%s",name);
                head = link_delete(head,name);
            break;
            case 5: //按学号排序
                head = link_order(head);
            break;
            case 6: //逆序排列打印
                link_printf(__LINE__,head,0);
            break;
            case 7: //查看帮助
                print_help();
            break;
            case 8: //退出管理系统
                link_free(head);
                return 0;
            break;
            default:
                puts("输入有误，请输入正确的操作码！");
        }
    }
    return 0;
}

```
### 位运算符
[关于位运算的使用](https://blog.csdn.net/weixin_42233791/article/details/107433643)
		1. 左移<<、右移>> 
		左移：二进制下的左移位、相当于 *2 
		eg: m<<1 == m*2 m<<n == m*2ˆn
			int a = b*32 =====> b<<5
			* 符号与补码 [数据、符号]
			* 负数的表达方式： 对于一个8bits
				* -1 的 二进制表达方式：1 0 0 0 0 0 0 1 	
					* 它的补码为： 1 1 1 1 1 1 1 0  	//符号位不变，其他取反	
					* 而负数在计算机内存的表示方式为补码+1，而-1即：1 1 1 1 1 1 1 1 
		2. 右移：二进制下的右移位，相当于 /2，由于右移涉及最高位（符号位），所以右移符号是严格遵许符号位的操作，否则容易陷入死循环
			* int a; a>>n		//有符号数，如果a是负数，最高位补1，如果是正数，补0
			* unsigned int a; a>>n		//无符号数，最高位补0

		3. 与或非 & |  ~
			* &：屏蔽（清零器 clr） A & 0 —> 0
				* eg： int a = 0x1234      a & 0xff00 === a = 0x1200  //屏蔽低8位

			* |：A | 0 = A ===>保留      A | 1 = 1 ===>设置为高电平（设置器 set） 	
		
		设置器用法例子：设置一个资源的bit5位高电平，其位不变
```
int a;
a = (a | (0x1<<5))  ====== a | (0x1<<n)	//将第五位置1，其余为全为0，然后与原本的a去或，这样除了第5位肯定为1外，其他位保持不变
```
		
		清零器用法例子：清除第五位
```
int a;
a = a & (～(0x1<<5)) =======第n位  a & (～(0x1<<5))	//先将第五位置1，去后取非，此时除第五位是0，其余位全为1，最后与a取与（&），这样a除第五位为0外，其他保持不变
```
		
		* 异或 ^、取反 ~ 逐位操作
		^ ： 相同取0，相反取1
		1 ^ 1 = 0;       1 ^ 0 = 1;
		小技巧：在不引入第三个数的情况下交换两个数
```
int fun() 	 		
{
		int a = 20;
		int b = 30;
		a = a^b;	//取出两个数之前不同的二进制赋值给a
		b = a^b;	//新a和b异或，就能恢复到原来的a = 20 再赋值给b
		a = a^b;	//新b = 20, 抑或新a,就能恢复原来的b = 30赋值给a = 30
```

		4. 内存访问符号： ()、[]、{}、->、. 、&、*

## 2.4 C语言内存空间的使用
C语言的最终操作对象就是资源，在操作这些资源之前，我们需要进行寻址操作，而这就会运用到pointer（指针）—访问内存空间最核心的关键词。

### 指针概述
	内存类型资源地址，门牌号的代名词。
	指针变量：存放指针这个概念的盒子。
	C语言编译器对指针这个特殊的概念，有两个疑问
		1. 分配一个盒子，盒子要多大？
		2. 盒子里存放的地址，所指向内存的读取方法是什么？
			1. 通常一个盒子大小为1Byte = 8bits（可以描述256个状态），而对于1GB的内存，它会有2^30个盒子。（2ˆ10Byte  = 1KByte、2ˆ20Byte = 1MByte、2ˆ30Byte  = 1GByte），在32位系统中（2ˆ32Byte = 4GB）中，需要2ˆ32中状态来描述内存，所以指针大小就是4Byte（字节）
			2. 指针的读取移动单位为一个存储单元，而不是一个字节，所以指针指向的内存的读取方式有定义它的数据类型来决定，比如：
```
char *p;		//定义为char，所以他的储存单元为1B，p一次只读1个B
int *p;		//定义为int，储存单位为4B，p一次读4个B							//p为地址值，*p为所指向的对象的值（地址存储的值）
```

举例：
```
#include<stdio.h>
  
int main()
{
        int *p1;
        char *p2;
        printf("the p1 is %lu, the p2 is %lu\n", sizeof(p1), sizeof(p2));
        return 0;
}

输出结果：the p1 is 8, the p2 is 8	//代表64位系统指针大小位8B
```

指针指向的内存空间，一定要保证合法性
```
#include <stdio.h>
  
int main()
{
        int a = 0x12345678;
        char *p1;		//指针位char类，一次只读一个字节
        p1 = &a;		//a的最小位地址赋给p1
        printf("the p1 is %x\n",*p1);
        return 0;
}
输出结果：the p1 is 78
```

* 浮点数的存储形式
```
#include <stdio.h>
  
int main()
{
        float a = 1.2;  //float大小为4B
        int *p1;
        p1 = &a;
        printf("the p1 is %x\n",*p1);
        return 0;
}
输出结果为：the p1 is 3f99999a
```

```
#include <stdio.h>
  
int main()
{
        float a = 1.2;  //float大小为4B
        unsigned char *p1;
        p1 = &a;
        printf("the p1 is %x\n",*p1);
        return 0;
}
输出结果为：the p1 is 9a
```

### 指针+修饰符
	1. const：常量、只读性质的关键字
		* 常量指针：`const int *p` 地址本身可以变，但所指向的对象的数值不能变 
		* 指针常量：`int * const p` 地址本身不能变，但所指向的对象的数值可以变，跟硬件资源关系比较大
		* 常量指针常量：`const char * const p ` 地址本身以及指向的对象的数值（地址存储值）均不可以变 ，用于ROM设备
```
int nValue1 = 10;
int nValue2 = 20;
int * const p = &nVlaue1;		//定义指针常量
p = &nValue2;		//错误，指针常量不能地址本身的值
*p = 40;		//正确，指针常量可以改变所值对象的值，此时nValue1=40

int nConstValue1 = 5;
int nConstValue2 = 15;
const int *p2 = &nConstValue1		//定义常量指针
p2 = &nConstValue2;		//正确，常量指针地址本身的值，此时p2邦定的是nConstValue2的值，p2位nConstValue2的地址
*p2 = nConstValue2;		//错误，不能改变所指对象的值

const int * const p3;		//定义常量指针常量
p3 = &nConstValue2;		//错误；不能改变地址本身的值
*p3 = nConstValue2;		//错误，也不能改变所值对象的值
```

	2.  volatile：防止优化指向内存的地址
	3. typedef：将复杂的声明别名化，增加代码可读性
```
char *name_t;		//name_t是一个指针，指向了一个char类型的内存
typedef char *name_t	//name_t是一个指针类型的名称，指向一个char类型的内存
name_t abc;	//abc是一个指针，属于name_t指针类型，指向一个char类型的内存
```

### 指针+运算符
	1. 加减运算
```
int *p = 0x12;
p+1 = 0x12 + 1*(sizeof(*p))		//指针的加减法；实际上是加（减）的是一个指针变量读内存大小单位（存储单元）
```
	
	2. ++、--
```
int *p = 0x12;
p++;		//同样是加减法，但++和--更新p的值（地址）	
```
	
	3. 变量名[n]  地址内容的标签非线性访问方式 - n：ID 标签
```
int *p = 0x12;	//p[n]访问的是所指对象的值
```

* 举例
	* 	要点：数据的分配是从高往低分配的。按代码顺序，先定义的数据会放在高位，而指针加法（减法）是指向更高位（低位）的地址
```
#include <stdio.h>
  
int main()
{
        int a = 0x12345678;
        int b = 0x99991199;
        int *p1 = &b;

        char *p2 = (char *)&b;  //强制类型转换
        printf("the p1+1 is %x,%x\n", *(p1+1),p1[1]);   //p1[1],以p1为基地址，往上偏移一个标签得到&a

        printf("the p2+1 is %x\n",p2[1]);
        return 0;
}	
输出结果：the p1+1 is 12345678,12345678
		   the p2+1 is 11
```
	
	4. 指针越界访问 举例
```
#include <stdio.h>
  
int main()
{
        const int a = 0x12345678;
        int b = 0x11223344;
        int *p = &b;
        //*(p+1) = 0x100;
        p[1] = 0x100;
        printf("the a is %x\n", a);
}
输出结果：the a is 100
const是只读限制符，但对于const修饰的数据， 可以通过一些强制手段进行数据更改，所以在C语言中，const修饰的数据只是只读常量，而是只读变量
```

	5. 指针逻辑运算符操作（>=、<=、==、!=）
	指针逻辑运算中常用的是 == 和 !=
		* 跟一个特殊值比较   0x0：地址的无效值，结束标志
			`if(p == 0x0)` 
	或者		`if(p == NULL)`    NULL  = 0x0
		* 	指针必须是同类型比较才有意义
	
	6. 多级指针概述 - 存放地址的地址空间 `int **p；`
	主要用于描述内存与内存之间的关系，让本来不连续的指针有了线性关系。
	*  举例
```
#include<stdio.h>
  
int main(int argc, char **argv) //argc：传递参数的个数 **argv：输入参数
{
        int i = 0;
        while(argv[i] != NULL){
                printf("the argv[%d] is %s\n", i, argv[i]);
                i++;
        }
        return 0;
}
输入参数：./build hello 123 456
输出结果：the argv[0] is ./build
		  the argv[1] is hello
		  the argv[2] is 123
		  the argv[3] is 456	
```

### 数组 - 内存分配的其中一种形式
	1. 定义：定义一个空间的：
		1. 大小
		2. 读取方式
定义方式：数据类型 数组名[m]  	//m的作用域只在申请的时候起作用
```
int a[100];	//a是一个常量，定义后就不能再修改
例如：
char buf[100]
buf = "hello world"	//错误
```
	
	2. 空间的赋值（初始化）-  按标签逐一赋值
```
int a[10];
a[0] = xx;	//按照标签逐一赋值
a[1] = yy;	
#自动化赋值 ---->空间定义时，就告诉编译器初始化情况
int a[10] = {10,20,30}；	//C语言本身，CPU内部不支持空间和空间的拷贝 

char buf[10] = {'a', 'b', 'c', '\0'};	//buf作为字符串时，根据字符串的重要属性，结果一定要有\0

char buf[10] = {"abc"}；	//最合理的写法，用“”定义会自动添加“”
char buf[10] = "abc";		//buf是变量，可以更改
char *p = "abc";			//p是地址，他所指向的是“abc”常量，常量地址无法更改，所以p无法更改
```
注意⚠️：数组空间的初始化和变量的初始化本质不同，尤其在嵌入式的裸机开发中，空间的初始化往往需要库函数的辅助

		* 数组的第二次“初始化”只能逐一处理，但当一块空间是字符空间时，C语言提供了一套字符拷贝拷贝函数，实现内存空间和内存空间的逐一赋值的功能的一个封装体，但一旦空间中出现了0这个特殊值，函数就即将结束。
		* 实现函数：strcpy{}、strcpy
```
char buf[10] = "abc";
strcpy(buf,"hello world");
//但strcpy函数没有限制拷贝大小，这容易导致拷贝过程中的内存溢出问题，所以在工程中不使用，替而用strncpy{}
```

	3. 字符空间与非字符空间的区别
			* 	字符空间，ASCII码编码来解码的空间
				* %s
				* \0作为结束标志
			* 	非字符空间 - 数值，数据
				* 	数据定义默认方式 ：unsigned char but[]
				*  所以一般定义 char buf[10] ，buf都是string
			* 	memcpy{} 的使用		
```
int buf[10];
int sensor_buf[100];
memcpy(buf,sensor_buf,10*sizeof(int));	//memcpy函数中，拷贝个数是以一个字节为单位，所以对于int等大小为4字节的空间拷贝，需要在n*size(int)保证拷贝正确

unsigned char buf[10];
unsigned char sensor_buf[10];
memcpy(buf,sensor_buf,10);
```

	4. 指针与数组 - 指针数组
			* 	定义方式： char *a[100]; sizeof(a) = 400  32位系统中，一个指针大小位4 type，所以a大小位100*4 = 400
			* 指针保存：
```
int a[10];
int b[5][6];

int *p1 = a;		//正确
int **p2 = b;		//错误，二维数组跟二维指针不是一个概念
int (*p)[6];		//正确
```
			* 指针数组与二维指针作用相同，是创建一个数组存储指向某个数据类型的指针。也就是说，数组内部存储的是多个指针，通过这种原理，我们可以利用指针数组来存储一个字符串列表
```
#include <stdio.h>
 
const int MAX = 4;
 
int main ()
{
   const char *names[] = {
                   "Zara Ali",
                   "Hina Ali",
                   "Nuha Ali",
                   "Sara Ali",
   };
   int i = 0;
 
   for ( i = 0; i < MAX; i++)
   {
      printf("Value of names[%d] = %s\n", i, names[i] );
   }
   return 0;
}
输出结果：
Value of names[0] = Zara Ali
Value of names[1] = Hina Ali
Value of names[2] = Nuha Ali
Value of names[3] = Sara Ali		
```

### 结构体的字节对齐
	1. 字节对齐：在C语言中，结构体是种复合数据类型，其构成元素既可以是基本数据类型(如int、long、float等)的变量，也可以是一些复合数据类型(如数组、结构体、联合等)的数据单元。编译器为结构体的每个成员按照其自然边界(alignment)分配空间。各成员按照它们被声明的顺序在内存中顺序存储，第一个成员的地址和整个结构的地址相同。
		* 	四个基本概念
			1. 数据类型自身的对齐值：char型数据自身对齐值为1字节，short型数据为2字节，int/float型为4字节，double型为8字节 
			2. 结构体或类的自身对齐值 = 其成员中自身对齐值最大的那个值，一般位4字节
			3. 指定对齐值：#pragma pack (value)时的指定对齐值value。
			4. 数据成员、结构体和类的有效对齐值：自身对齐值和指定对齐值中较小者，即有效对齐值=min{自身对齐值，当前指定的pack值}。
```
#include <stdio.h>

struct abc{
		char a;		
		short c;
		int b;
};

struct my{
		char a;
		int b;
		short c;
}
int main()
{
		struct abc buf;
		struct my buf1;
		printf("the buf is %lu, %lu\n", sizeof(abc),sizeof(my));
}

输出结果：the buf is 8, 12	//最终结构体大小一定是4的倍数
```
	* 分析：由于打包时结构体里数据成员顺序不同，结构体的大小也不同。第一个结构体定义中，结构体的对齐值位4字节，而char 和 short的连续定义占的空间不超过4字节，所以char 和 short 存放在头4个字节中。结构体大小位8字节。而第二个结构体中，char 和 int的连续定义占的空间超过4个字节，所以char 、int 、short 分别被放在了3个4字节内存空间中，所以第二个结构体大小为12
	* 
	* 结构体字节对齐的细节和具体编译器实现相关，但一般而言满足三个准则：
			1. 结构体变量的首地址能够被其最宽基本类型成员的大小所整除；
			2. 结构体每个成员相对结构体首地址的偏移量(offset)都是成员大小的整数倍，如有需要编译器会在成员之间加上填充字节(internal adding)；
			3.  结构体的总大小为结构体最宽基本类型成员大小的整数倍，如有需要编译器会在最末一个成员之后加上填充字节{trailing padding}。
	         对于以上规则的说明如下：
>      第一条：编译器在给结构体开辟空间时，首先找到结构体中最宽的基本数据类型，然后寻找内存地址能被该基本数据类型所整除的位置，作为结构体的首地址。将这个最宽的基本数据类型的大小作为上面介绍的对齐模数。  
>      第二条：为结构体的一个成员开辟空间之前，编译器首先检查预开辟空间的首地址相对于结构体首地址的偏移是否是本成员大小的整数倍，若是，则存放本成员，反之，则在本成员和上一个成员之间填充一定的字节，以达到整数倍的要求，也就是将预开辟空间的首地址后移几个字节。  
>      第三条：结构体总大小是包括填充字节，最后一个成员满足上面两条以外，还必须满足第三条，否则就必须在最后填充几个字节以达到本条要求。  

	2. 位域 [字节对齐与位域](https://www.cnblogs.com/clover-toeic/p/3853132.html)

### 内存分布
	1. C/C++ 定义了 内存分布 - 代码空间、全局变量与静态变量区、栈空间、堆空间
		* 静态存储区 存放全局变量和静态变量，只读空间、代码段）：存储在系统运行之前就分配的数据，生存周期最长
		* 栈空间：存储局部变量的空间，能提供出栈、入栈的操作，对临时变量进行替换，会在函数运行时在栈空间上将函数内局部变量进行创建和存储，并调用内部存储的变量，函数一旦返回，就释放不再存在。**ps:C++中的类存储在栈空间中的**
		* 堆空间：动态内存空间，运行时可以自由、自我管理分配和释放的空间，生存周期是由程序猿来决定，用malloc申请堆空间，free进行内存释放
			* mallc函数本身并不识别要申请的内存是什么类型，只关系内存的总字节数
			* malloc申请到的是一块连续的内存，有时可能申请到比所需内存更大的内存空间，有事会申请不到，直接返回NULL
			* malloc返回值类型是void *，所以在调用malloc时要显示地进行类型转换，将void *转换成所需要的指针类型
			* 如果free的参数时NULL的话，没有任何效果
			* 释放一块内存中的一部分时不被允许的
```
#include <stdio.h>

int main()
{
	char *p;
  p = (char *)mallc(10 * sizeof(char	)); //申请10个字节的空间,转换类型为类型为char匹配指针
	if(p == NULL){	//如果malloc的返回值是NULL，说明申请不到内存
		printf("malloc failed\n");
		return 0;
	}
	printf("p = %p\n",p);
	free(p);	//释放内存 实际是删除了p所指的目标（变量或对象），释放了它所占的堆空间，而不是删除p本身，释放堆空间后，p成了空悬指针
	printf("%p\n",p); //从输出结果可以看到，free(p)后，指针依然指向了之前分配的地址，这样是很危险的
	p = NULL;  // 为了防止上面的情况，可以在释放内存后将p指针设为NULL
	//free(p+2) 错误，不能释放部分内存空间
	return 0;
}			
```

	* 	在函数中建立的动态对象在函数返回后仍可使用，我们将这个动态对象所在的空间称为堆空间的自由空间。所以需要在在函数内部堆建立的动态对象进行释放，在函数外释放是很容易失控的是，往往会出错。
```
#include <stdio.h>
char *get_string(){
	//char []s = "welcome"; //这样初始化会产生错误。局部变量，函数执行结束后就会被释放，如果用它作为返回值会导致错误
	// static char []s = "welcome"; //正确，将s定义为静态变量，存放在静态区中，生命周期与整个程序相同，即使函数执行结束变量也不会被释放
	// char *s = "welcome" //正确，这里设置了一个常量 “welcome”，并用指针指向这个常量，常量和静态变量一样存储在静态区中。
	//*s = 'W' //错误，指针指向的是字符串常量，常量地址中的内容不允许被修改
	// 申请动态内存 正确，动态内存需要用free释放，释放前一直存在，所以我们可以在函数外部对动态内存进行释放
	char *s;
	s = (char *)mallc(10 * sizeof(char	))
	if(s == NULL){	//如果malloc的返回值是NULL，说明申请不到内存
		printf("malloc failed\n");
		return 0;
	}
	printf("input: ")
	scanf("$s",s);
	printf("s = %p\n",s);

 // s = "welcome"; //错误。虽然能输出结果，但是s作为一个动态内存地址，不能用来指向静态区中的字符串常量(welcome)，这样会出现段错误（访问了不该访问的地址-静态区）

	return s; 
}
int main()
{
	char p;
	p = get_string();	。
	printf("%s\n",p);	
	free(p)
	p = NULL;
	return 0;
} 
```

	* 野指针。也指针不是NULL指针，是指向“垃圾”内存的指针，它的出现原因主要有两个：
			* 指针没有被初始化
			* 指针p被free之后，没有设置为NULL
			* 指针操作超过了变量的作用范围（给指针赋值时，赋值量超过了指针本身的指向范围）
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char *p;	////错误 p没有被初始化
	//strcpy(p,"welcome");	//出现段错误，原因是p没有被初始化，所以无法被访问
	char s[] = "well" //存放的是 w ε l \0 四个字节
	p = s;	
	strcpy(p,"welcome");	//错误，非法访问，原因 p 原本指向了4个字节的空间，但welcome有7个字节，超过了p指针的作用范围
	return 0;
}		`

```

```
实例 为结构体分配动态内存空间
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 20
typedef struct student{
	int no;
	char name[N];
	float score;
}Stu;

Stu *get_info()	//结构体指针作为返回值
{
	Stu *p;
	if ((p = (Stu *)malloc(sizeof(Stu)) == NULL){
		printf("malloc failed\n");
		return NULL;
	}
	p->no = 1;
	strcpy(p->name, "Tom");
	p->score = 90;
	return p;
	
}

int main()
{
	Stu *s;
	if((s = get_info()) == NULL)
	{
		return 0;
	}
	printf("Student info: $d %s $.2f\n",s->no,s->name, s->score);
	free(s);
	s = NULL;

	return 0;
}
```
		
内存分布及相应内容存放
- - - -
内核空间	应用程序不许访问
- - - -
栈空间		局部变量
- - - -
运行时的堆空间		malloc申请堆空间，free进行内存释放
- - - -
静态空间 - 全局数据空间（静态数据 data 、bss）		已初始化和未初始化的空间（可读可写）
- - - -
静态空间 - 只读数据段（属于TEXT）			字符串常量（只读）
- - - -
静态空间 - 代码段（属于TEXT）				代码存放（只读）

		* 可以terminal中输入：size build（.o文件名）查看各个空间数据大小
		* 只读空间
			* 	代码段和只读空间的数据无法修改，否则会出现断错误
```
#include<stdio.h>
  
int b = 100;
int fun()
{
        static int a = 100;	//存储在全局变量静态空间中
        return a++;
}
int main()
{
        static int a;		//存储在全局变量静态空间中
        unsigned char *p;
        char *p1 = "helao world";
        a = 0x10;

        printf("the p1 is %s\n", p1);
        printf("the string address is %p\n", "helao world");
        p1[3] = 'l';		//p1指向的是字符串常量，位于只读空间，无法修改，否则会出现断错误
        printf("the p1 is %s\n", p1);
        printf("the is a %p\n",&a);     //%p 看地址
        printf("this is %p\n", main);

        p = (unsigned char *)main;
        printf("the p[0] is %d\n", p[0]);
        p[0] = 0x12;
        printf("++++ ths p[0] is %x\n", p[0]);
        return 0;
}
```

	2. 各种数据段的内存存储位置
		* 全局变量（数据段）一般存储在data或者bss等静态数据段存储空间中，其中bss存储未初始化（未被赋值）数据段，data存储已初始化（已被赋值）的数据段
		* 只读数据段（常量）和代码段存储在TEXT中
		* 局部变量（结构体、函数内的变量）存储（数据段）存储在栈空间中，但如果局部变量用static修饰，则该变量的存储地址会发生改变，变量会存储在bss或data中
		* 可用 nm (.o文件) 查看静态空间中的各个数据段的属性（地址，数据类型，数据名称）
	9. 堆空间
		* 	分配：使用malloc()函数，一旦分配成功，返回分配好的地址给程序猿只需要接受，对于新地址的操作方法，有程序猿把握。输入参数指定分配的大小，单位就是B（字节）
		* 释放：free()
```
void fun()
{
char *p;
p = (char *)malloc(100);	//分配地址及大小
if(p == NULL){ error }
}
free(p);	//释放

int a[5];
a = malloc(5*sizeof(int));	
```
	
附：[内存(RAM或ROM)和FLASH存储的真正区别总结](https://blog.csdn.net/liangkaiyang/article/details/5955653)

## 函数-由数据结构和算法组成的实现特定功能的结构
### 函数概述
	1. 基本概念：实现特定功能并能提供复用化的代码的集合
	函数3要素：在定义函数时，必须将3要素告知编译器
		1. 函数名 - 地址
		2. 输入参数
		3. 返回值
```
int fun(int, int, char){	----代码----		} 	//定义函数方式
```

	2. 用指针保存函数：`int (*p)(int, int, char);`
	3. 调用函数：`fun(10,2);`
	
### 函数定义举例
	1. 查看man手册中的函数（printf）；`man 3 printf`
```
//用指针访问函数名（地址）
#include <stdio.h>

int main()
{
		int (*myshow)(const char *, ...);
		printf("hello world\n");
		myshow = printf;
		myshow("==========\n");
		return 0;	
}
输出结果：hello world 
		  ===========
```

	2. 指针函数：用类似指针数组的方式存放多个函数
	 `int (*p[7])(int, int);`

### 函数输入参数
	1. 函数使用过程中，调用者通过将实参传递给被调者（函数）的形参实现函数的功能并返回特定值。输入参数的传递形式称为拷贝，拷贝的方式包括值传递、地址传递以及连续空间传递。
	2. 值传递
```
#include <stdio.h>
  
void myswap(int a, int b)        //buf为形参
{
        a = a^b;
        b = a^b;
        a = a^b;
}
 
int main()
{
        int a = 20;
        int b = 30;
        printf("the a is %d,the b is %d\n", a,b);
        myswap(a,b);
        printf("after swapm the a is %d,the b is %d\n", a,b);
        return 0;
}
输出结果：the a is 20,the b is 30
		  after swapm the a is 20,the b is 30	
并没有实现值互换
```
	* 分析：值传递是在调用子函数时将实惨的值拷贝到函数的形参中，函数通过形参去进行实施函数内部的命令，但在函数执行完后，形参数值便会消失，所以整个函数调用过程并没有改变实参的数值。总结来说，对于值传递，函数的调用不会更改实参的数值
	
	3. 地址传递
```
#include <stdio.h>
  
void myswap(int *a, int *b)     //buf为形参
{
        *a = (*a)^(*b);
        *b = (*a)^(*b);
        *a = (*a)^(*b);
}
 
int main()
{
        int a = 20;
        int b = 30;
        printf("the a is %d,the b is %d\n", a,b);
        myswap(&a,&b);
        printf("after swapm the a is %d,the b is %d\n", a,b);
        return 0;
}
输出结果：the a is 20,the b is 30
		  after swapm the a is 30,the b is 20	
数值成功调换
```
	* 地址传递中，主函数通过让将实参地址传递给子函数，让子函数修改对应地址空间中的值，从而在子函数执行完后，被拷贝的主函数实参的地址没有改变，但地址对应的数值改变了。
	
	* 注意⚠️：值传递和地址传递的根本区别在于调用函数后输入参数是否发生改变！！
```
//对于函数
void fun2(int *p);
int main()
{
	int *p;
	fun2(p);	//这是值传递，不是地址传递，虽然它传递的是一个地址值，但调用函数执行完后，输入参数的值（地址值）并没有发生改变。
	return 0;
} 

拓展：通过地址传递修改地址值
void fun2(int **p);
int main()
{
	int p;
	fun2(&p);	//输入参数输入p的地址，然后通过地址传递改变p的存储地址值
	return 0;
}
```
	4. 连续空间的传递 - 数组、结构体的传递
		1. 对于数组、结构体这样的空间，函数与函数之间的调用时，多用地址传递
	对于数组：`void fun(*p);`
	对于结构体：`void fun(struct 结构名 *p;)`
		* 	在连续空间的传递中，如果调用者不希望定义的实惨被修改，则实惨需要被定义为只读（const），同样的，函数的形参如果被定义成只读，那么函数内部不允许出现有修改形参的操作。
```
void fun(const int *p);	//只查看，不允许修改
void fun(char *p);	//可以查看修改
```
		2. 连续传递空间可以分为字符空间传递和非字符空间传递，对于空间传递，我们最主要关注的是需要传递的空间的地址以及传递结束标志
			* 对于字符空间传递，由于字符串的地址本身自带结束标志NULL（0x00），所以在函数进行空间传递时，只需要加入以NULL为条件的循环
```
在terminal中，输入man 函数名 可以查看函数信息
//以 strlen为例
int strlen(const char *p)
{
	//错误处理:判断输入参数是否合法
	if(p == NULL)
	{
		//出错处理
		return...
	}
	//内存处理，加入循环，从头到位逐一处理
	while(p[i] != NULL)
	{
		数据处理
		i++;
	}
}

//以 strcpy为例
void strcpy(char *dest, const char *src)
{
}
```
		* 对于非字符空间（数据、数值），由于可定义的数据类型过多，在调用函数时为了能够让函数适配多种类型实参的传递，我们用 *void定义形参。同时非字符类型数据的地址没有自带的结束标志，所以在函数定义时，需要添加表示数据长度的形参
```
//以 memcpy为例	
void memcpy(void *destm const void *src, size_t n)；	//n 表示传递参数长度

//以 recv函数为例
ssize_t recv(int sockfd, void *buf, size_t len, int flags);
```

### 返回值
	1. 基本语法： 返回类型 函数名称（输入列表）{  return } return 的类型就是返回的类型，返回类型可以是1. 基本数据类型（int char float 等）、指针（int *, char *），2. 连续空间类型（数组，结构体）
	2. 返回基本数据类型 - 输入参数与返回值在调用时的情况
```
//假设有以下函数
int fun1(void);	//返回值类型为int
void fun2(int *p);	//输入参数为指针传递
int fun(int *p);		//承上启下，指针传递和返回数据
int *fun1(void);		//返回指针
int *fun(int *p)		//指针传递，返回指针


int main()
{
	int a = 0;
	a = fun1();	
	fun2(&a);

	int *p;
	p = fun1();
}
1 调用函数时，输入指针参数和函数返回值都会改变调用者对应参数的数值

```

	3. 返回连续空间类型：对于连续空间类型（数组，结构体），C语言中无法直接返回整个结构体或是数组，而是用指针作为空间返回的唯一数据类型。也就是返回地址
		* 在返回地址中，必须保证函数返回的地址所致的空间是合法的（地址所指向的变量不在栈空间中（不是局部变量））
		* 为此，我们在函数内部将变量存放在静态区（static修饰）、堆空间（malloc()）
```
#include <stdio.h>
#include <string.g>	//strcpy使用库
#inlcude <stdlib.h>	//堆空间使用库	
char *fun(void)
{
		⚠️//char buf[] = "hello world!";	//buf位于函数中，是局部变量（位于栈空间）
		//static char buf[] = "hello world!";	//用static 静态化 将变量存储在静态区中（全局变量）
		char *s = (char *)malloc(100);	//用malloc将局部变量放到堆区中
		strcpy(s, "hello world!");	//用strcpy对s进行赋值
		return s;		
}

int main()
{
		char *p;
		p = fun();
		printf("the p is %s\n", p) //以%s输出p地址指向的字符串
		free(p);	//释放堆空间
		return 0;
}
```

### Main函数传参
main函数传参实际应用于linux系统中的管理命令（可执行程序），如`cp t1.c t2.c`实际上在执行cp中的main函数时，会将t1.c t2..c两个文件作为参数传入到main函数，完成拷贝操作
```
#include <stdio.h>
//main函数的参数是程序编译时，在terminal中自定义的参数
//例如 ./test9.c zhangsan lisi 包括test9.c在内，main函数参数共有3个。//argc表示main函数参数个数,argv指针数组存储每个传入参数的首地址
int main(int argc, char *argv[]) 
{
	int i;
	printf("argc=%d\n",argc)
	for(i = 0; i < argc; i++)
	{
		printf("argv[%d] = %s\n", i, argv[i]);
	}

	return 0;
}
```

### 各类函数
#### 字符串追加函数 strcat() 、strncat()
```
头文件：#include<string.h>
函数定义：
   char *strcat(char *dest, const char *src);
   char *strncat(char *dest, const char *src, size_t n)；
函数功能：
strcat函数追加src字符串到dest指向的字符串的后面。追加的时候会加'\0'
strncat 追加src指向的字符串前n个字符，到dest指向的字符串的后面，如果n大于src字符个数，则strcat和strncat等效
使用时需要注意保证dest指向的内存空间足够大

#include<stdoi.h>
#include<string.h>
int main()
{
	char str[20] = "aa\0aaaaaaaaaaaa";
	char *src = "hello";
	strcat(str,src);	//追加时，src会先识别str中的\0，并从str中的\0后开始追加，并在最后加上\0，所以追加后\0后的内容都会消失。
	printf("%s\n",str);
	return 0;
}

输出结果 aahello
```

#### 比较函数 strcmp() 、strncmp()
```
头文件： #include<string.h>
函数定义：
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2 size_t n);
函数说明：
     比较s1和s2指向的字符串大小
     比较的方法：逐个字符去比较ascII码。一旦比较处大小就返回对应返回值
     如果所有字符都一样。返回0
返回值：
     如果s1指向的字符串大于s2指向的字符串，返回1
     如果s1指向的字符串小雨s2指向的字符串，返回-1
	   如果相等返回0
注意⚠️：在逐个比较过程中，一旦某个字符比较出现了不同的情况，函数立即结束并返回对应值

#include<stdoi.h>
#include<string.h>

int main()
{
	char *s1 = "hello world";
	char *s2 = "hello ketty";

	if(strcmp(s1,s2) == 0)
		printf("s1 == s2\n");
	else if(strcmp(s1,s2) > 0)
		printf("s1 > s2\n");
	else
		printf("s1 < s2\n");
}
```

#### 查找字符函数 strchr()
```
头文件：#include<string.h>
函数定义：
    strchr(const char *s, int c);
    strrchr(const char*s, int c);
函数说明：
    在字符指针s指向的字符串中，找ascII码为c的字符
注意⚠️：strchr查找是首次匹配，一旦匹配到一个字符，即使字符串中有多个匹配字符，函数也会立即结束并返回值。
       strrchr查找是末位开始匹配，从字符串最后开始查找，找到后函数结束并返回值
    如果找到，返回对应字符的地址。
    如果找不到，返回NULL
```

#### 字符串匹配函数
```
#include<string.h>
char strstr(const char *haystack, sont char *needle);

函数说明：在haystack指向的字符串中查找needle指向的字符串。也是首次匹配
找到了返回字符串的首地址
找不到返回NULL
```

#### 字符串转换数值 atoi、atol、atof
```
#include<>stdlib.h>
函数定义： 
    int atoi(const char *nptr);
    long atol(const char *nptr);
	  double atof(const char *nptr);
功能：
    将nptr指向的字符串转换成整数并返回,前提是字符串是由数字组成
```

#### 字符串切割函数 strtok()
```
头文件：#include<string.h>
函数定义：char strtok(char *str. const char *delim);
函数功能：按照delim指向的字符串中的字符，切割str指向的字符串，就是在str指向的字符串中国呢发现了delim字符串中的字符，就将其变成“\0”，在stc中有多个匹配delim字符串中的字符的情况下，每次strtok的调用只切割一次，再次切割会接上次切割的位置继续切.如果没找到匹配字符就返回NULL

#inlcude<stdio.h>
#inclcude<string.h>
int main()
{
	char str[100] = "lucy:yuxin,hanping,xiaoyang:xueyang;zhanghu:yongheng";
  char *p[8];
	int i = 0,j;
  p[i] = strtok(str, ",:;");
	//printf("p[%d]:%s\n",i,p[i]);
输出结结果： lucy //调用strtok后，函数会将在str中第一个匹配到的字符变成\0，此时str字符串就会变成lucy\0hanping,xiaoyang:xueyang;zhanghu:yongheng，p[0]则是指向str的指针。
//继续切割并打印后续的内容的方法
	while(p[i] != NULL) //如果p[i]为NULL，说明找不到匹配项
	{
		i++;
		p[i] = strtok(NULL,",:;");
	}
	for(j=0,j<i;j++)
	{
		printf("p[%d]:%s\n",j,p[j]);
	}
	return 0;
}
```

#### 格式化字符串操作函数 sprintf()、sscanf()
```
int sprintf(char *buf, const char* format,...);
	//输出数据到buf指定的内存区域
char buf[20];
sprintf(buf, %d:%d:%d, 2013,10,1);
printf("buf=%s\n",buf);

int sscanf(const char *buf, const char *format, ...);
	//从buf指定的内存区域中读入信息
int a,b,c;
sscanf("2013:10:1","%d:%d:%d",&a,&b,&c);
printf("a=%d,b=%d,c=%d\n",a,b,c);

```

#### sscanf高级用法
```
1:跳过数据
#include<stdio.h>
int main()
{
	char buf[20];
	sscanf("1234 5678","%*d %s",buf); //%*d表示跳过数据，这里会跳过1234,然后各一个空格以字符串形式获取5678，存放在buf当中
}

2:指定宽度获取数据： %[width]s
sscanf("12345678","%*2d%4s",buf);	//跳过前2个字节字符。从字符串中获取4个字节字符串，存放在buf中

3:从字符串中匹配某个集合的字符串 %[a-z],只支持获取字符串
char buf[20];
sscanf("agcd32DajfDdFF"."%[a-z]",buf);	//从字符串中获取输入只要‘a‘到'z'之间的字符，一旦匹配到不在这之间的，即使后面还有匹配项，函数也终止。
其他规则：
%[aBc] 匹配a B c中的一员，同样遵守首次非匹配就结束函数的原则
%[^aFc] 匹配非a F c的所有字符
%[^a-z] 匹配非a-z的字符

练习：
使用sscanf获得 abc#def@ghi 中 # 和 @ 之间的字符
#include<stdio.h>
int main()
{
	char buf[100];
	sscanf("abc#def@ghi",%*[^#]%*c%[^@],buf);	//%*[^#] 跳过非#的所有字符，然后%*c跳过一个字符，这里指#，最后获取所有非@的字符。
	return 0;
}
```

# 嵌入式工程师必备0x10道题目
[嵌入式工程师必备0x10道题目](https://blog.csdn.net/taowenyin/article/details/4080475)

### 宏定义 - 预处理
* 用预处理指令#define声明一个常数，用以表明1年中有多少秒（忽略闰年问题）
`#define 宏名（大写） 宏体 format`
`#define SECONDS_PER_YEAR (60 * 60 * 24 * 365)UL`

要点：
	1. #define语法的基本知识（例如：不能以分号结束、括号的使用，等等）
	2. 懂得预处理器将为你计算常数表达式的值，因此，直接写出你是如何计算一年中有多少秒而不是计算出实际的值，是更清晰而没有代价的。
	3. 意识到这个表达式将使一个16位机的整型数溢出，因此要用到长整型符号L，告诉编译器这个常数是的长整型数。
	4. 如果你在你的表达式中用到UL（表示无符号长整型），那么你有了一个好的起点。记住，第一印象很重要。

### 数据声明
* 用变量a给出下面的定义
	1. 一个整型数（An integer）==== ` int a;`
	2. 一个指向整型数的指针（A pointer to an integer）`int *a`;
	3. 一个指向指针的的指针，它指向的指针是指向一个整型数（A pointer to a pointer to an integer） ====  `int **a;`
	4. 一个有10个整型数的数组（An array of 10 integers） int a[10];
	5. 一个有10个指针的数组，该指针是指向一个整型数的（An array of 10 pointers to integers） ==== ` int *a[10];`
	6. 一个指向有10个整型数数组的指针（A pointer to an array of 10 integers）====  `int (*a)[10];`
	7. 一个指向函数的指针，该函数有一个整型参数并返回一个整型数（A pointer to a function that takes an integer as an argument and returns an integer）====  `int (*a)(int;)`
	8. 一个有10个指针的数组，该指针指向一个函数，该函数有一个整型参数并返回一个整型数（ An array of ten pointers to functions that take an integer argument and return an integer ）
	====  `int (*a[10])(int);`

### 关键字 static 的作用
* 关键字static的作用是什么？
	1. 修饰局部变量（位于栈空间 - 函数体内）
	2. 修饰全局变量（模块内函数体外）
	3. 修饰全局函数（模块内）
* 这个简单的问题很少有人能回答完全。在C语言中，关键字static有三个明显的作用：

	1. 在函数体，一个被声明为静态的变量（局部静态化）在这一函数被调用过程中维持其值不变；
	2. 在模块内（但在函数体外），一个被声明为静态的变量可以被模块内所用函数访问，但不能被模块外其它函数访问。它是一个本地的全局变量；
	3. 在模块内，一个被声明为静态的函数只可被这一模块内的其它函数调用。那就是，这个函数被限制在声明它的模块的本地范围内使用。

### 关键字 const 的作用
* 只读，在想C语言中，但只是建议性，不具备强制性，用const修饰的变量不是常量而是只读变量，但在C++中const修饰的变量就是常量

### 关键字 volatile 的作用
* 防止C语言编译器的优化
	1. 一个定义为volatile的变量是说这变量可能会被意想不到地改变，这样，编译器就不会去假设这个变量的值了。精确地说就是，优化器在用到这个变量时必须每次都小心地重新读取这个变量的值，而不是使用保存在寄存器里的备份。下面是volatile变量的几个例子：
		* 并行设备的硬件寄存器（如：状态寄存器）；
		* 一个中断服务子程序中会访问到的非自动变量（Non-automatic variables）；
		* 多线程应用中被几个任务共享的变量
* 回答不出这个问题的人是不会被雇佣的。我认为这是区分C程序员和嵌入式系统程序员的最基本的问题。嵌入式系统程序员经常同硬件、中断、RTOS等等打交道，所用这些都要求volatile变量。不懂得volatile内容将会带来灾难。 假设被面试者正确地回答了这是问题（嗯，怀疑这否会是这样），我将稍微深究一下，看一下这家伙是不是直正懂得volatile完全的重要性。
		1. 一个参数既可以是const还可以是volatile吗？解释为什么。
		* 是的。一个例子是只读的状态寄存器。它是volatile因为它可能被意想不到地改变。它是const因为程序不应该试图去修改它；
		2. 一个指针可以是volatile 吗？解释为什么。
		* 是的。尽管这并不很常见。一个例子是当一个中服务子程序修该一个指向一个buffer的指针时；
### 位操作
* 给定一个整型变量a，写两段代码，第一个设置a的bit 3，第二个清除a 的bit 3。
```
#define BIT3 (0x1 << 3)
static int a;
a |= BIT3;		//设置a的bit3
a &= ˜BIT3;		//清楚a的bit3
```


### 访问某特定的内存位置
* 在某工程中，要求设置绝对地址为0x67a9的整型变量的值为0xaa66。
```
int *p = (int *)0x67a9;	//设置绝对地址
*p = 0xaa66;	//访问0xaa66;
```

### 其他面试题
#### ISR（中断服务程序）
* 中断是嵌入式系统中重要的组成部分，这导致了很多编译开发商提供一种扩展—让标准C支持中断。具代表事实是，产生了一个新的关键字__interrupt。下面的代码就使用了__interrupt关键字去定义了一个中断服务子程序(ISR)，请评论一下这段代码的。

```
__interrupt double compute_area (double radius)
{
	double area = PI * radius * radius;
	printf(" Area = %f", area);
	return area;
}
```

这个函数有太多的错误了，以至让人不知从何说起了：
	1. ISR 不能返回一个值。如果你不懂这个，那么你不会被雇用的；
	2. ISR 不能传递参数。如果你没有看到这一点，你被雇用的机会等同第一项；
	3. 在许多的处理器/编译器中，浮点一般都是不可重入的。有些处理器/编译器需要让额处的寄存器入栈，有些处理器/编译器就是不允许在ISR中做浮点运算。此外，ISR应该是短而有效率的，在ISR中做浮点运算是不明智的；
	4. 与第三点一脉相承，printf()经常有重入和性能上的问题。如果你丢掉了第三和第四点，我不会太为难你的。不用说，如果你能得到后两点，那么你的被雇用前景越来越光明了。

#### 存在有符号类型和无符号类型时所有的操作数都自动转换为无符号类型。
* 下面的代码输出是什么，为什么？

```
void foo(void)
{
	unsigned int a = 6;
	int b = -20;
	(a+b > 6) puts("> 6") : puts("<= 6");
}
```
这个问题测试你是否懂得C语言中的整数自动转换原则，我发现有些开发者懂得极少这些东西。不管如何，这无符号整型问题的答案是输出是“>6”。原因是当表达式中存在有符号类型和无符号类型时所有的操作数都自动转换为无符号类型。 因此-20变成了一个非常大的正整数，所以该表达式计算出的结果大于6。这一点对于应当频繁用到无符号数据类型的嵌入式系统来说是丰常重要的。如果你答错了这个问题，你也就到了得不到这份工作的边缘。

#### 评价下面的代码片断：
```
unsigned int zero = 0;
unsigned int compzero = 0xFFFF;
/*1's complement of zero */
```

对于一个int型不是16位的处理器为说，上面的代码是不正确的。应编写如下：
unsigned int compzero = ~0;	(提高兼容性，避免在非32位处理器下出错)
这一问题真正能揭露出应试者是否懂得处理器字长的重要性。在我的经验里，好的嵌入式程序员非常准确地明白硬件的细节和它的局限，然而PC机程序往往把硬件作为一个无法避免的烦恼。


# 3. Linux操作系统基础
## Linux操作系统结构组成（KERNEL、SHELL、USER APPLICATION）
1. kernel：内核，包围在硬件之上，管理设备、进程、内存、交换空间、文件系统、精灵进程，控制系统程序与硬件打交道的功能。
2. SHELL：提供人机交互界面，用户与内核之间打交道的功能
	* 分类：Bourne shell(sh), Korn hell (ksh), Cshell (csh), Bourne-again shell (bash), tcsh. 不同的shell的命令提示符不一样
		* 	sh, bash #root, $user
		* zsh, csh, #root %user
3. FileSystem：文件系统、管理文件、目录

## 特性
* 多用户、多任务（进程、线程处理）、多平台、图像化界面（x-window）、硬件支持（低配置），通信与联网、应用程序支持（编辑器、编程工具、数据库、办公软件、图形处理、Internet应用、游戏）

## 文件系统
	1. 文件系统分类
		* 硬盘文件系统： NTFS、coda、Ext（扩展文件系统）、Ext3、Ext4、VFAT 、ISO9660、UFS、FAT
		* 闪存文件系统：JFFS2、YAFFS
		* 数据库文件系统：BFFS、WINFS
		* 网络文件系统：NFS Samba
		* 虚拟文件系统：VFS（Proc）、TMPFS（临时文件系统）、PROCFS（进程文件系统）、LOOPBACKFS（回送文件系统）
		* 可以使用du df 命令查看系统内部文件系统的情况
	2. 文件系统功能
		* 能定义文件组织方式，文件结构
		* 提供建立和存取文件的环境、目录和文件
		* 能对文件存储空间进行组织和分配
		* 负责文件存储并对存入的文件进行保护和检索
		* 负责建立文件、存入、读出、修改、转存文件、控制文件的存取、撤销文件等
##  Linux文件系统及特点
	1. EXT3
		* EXT3是基于日志方式的文件系统
		* 系统中每个文件都是有索引的，用户对文件的每一个操作都会记录成日志，形成一个任务队列排着执行
	2. SWAP
		* swap是交换分区的文件系统，类似windows的虚拟内存
		* 虚拟内存的实现：两种方式
		* 第一种是进行内存的排列，像内存池一样，进行优化
		* 第二种是把硬盘上的空间模拟成内存
## Linux系统常见命令
	1. SHELL命令行格式
		* $command [option(s)] [argument(s)]
		* 每个命令行两个部分之间有空格分隔
		* 命令区分大小写
		* 不同的命令提示符，使用分隔符为;
		* 如果要输入的命令太多，可以用\来标明该条命令未结束
		* 补齐命令 连续按两下TAB键用于命令补齐，按一下TAB键用于文件名补齐
		[Linux命令大全](https://man.linuxde.net/)

## 软件包管理命令
### dpkg软件包管理器相关命令
	dpkg没有考虑软件包的依赖关系，比如在安装gcc时，它并不会自动安装gcc依赖的相关软件，在没有网络的情况下会用到，所以在用dpkg时，我们首先要知道安装的软件和那些软件有依赖关系，然后将这些软件逐个事先下载好放在系统当中，最后逐个安装上。而apt会考虑依赖关系，同时也会自动调用互联网，所以用apt安装软件时，apt会从网上下载软件以及其他有依赖关系的软件然后一并安装上
	* 	dpkg -i <软件包名>  安装一个在本地文件系统上存在的Debian软件包
	* dpkg -r <安装的软件名> 移除一个已经安装的软件包
	* dpkg -P <软件名> 移除已安装软件包及配置文件
	* dpkg -L <软件名> 列出安装的软件包清单
	* dpkg -s <软件名> 显示软件包的安装状态 
### apt软件包管理器
	APT工作原理：Ubuntu采用集中式的软件仓库机制，在系统中使用软件配置文件/etc/apt/sources.list 列出最合适访问的镜像站点地址。而APT软件包管理器就是为这些软件资源建立索引文件，以便本季主机查询，提高软件资源的索引效率
	APT文件管理命令：通常使用 apt-get命令管理软件包，只需要告知软件包名字，就可以自动完成软件包的获取、安装、编译和卸载，以及检查软件包以来关系
	* apt-get subcommands [-d | -f | -m | -q | —purge | -reinstall | -b | -s | -y | -u | -h | -v ] pkg
	* 例子：如果由于故障而中断软件安装过程，可能会造成关联的软件包只有部分安装。之后，用户会发现该软件既不能重装又不能删除。
	* 作为组合命令，下面前者会用于检查软件包依赖关系，后者用于修复想依赖关系。
```
	apt-get check 
	apt-get -f install
	// 在处理关系上，apt-get会自动下载并安装具有依赖关系的软件包，但不会处理与安装存在推荐和建议关系的软件包
```

## shell命令
shell是Linux内核的一个外层保护工具，负责完成用户与内核之间的交互
### SHELL的特殊字符
	1. 通配符 *. ?, []
		1. *：匹配任意长度的字符
		2. ?：匹配单个字符
		3. [s]：通配某个范围内的任意一个字符
	* 举例
			1. * === 所有文件
　　2. g*  === 文件名以“g”开头的文件
　　3. b*.txt  === 以”b” 开头，中间有零个或任意多个字符，并以”.txt” 结尾的文件
　　4. Data??? === 以“Data”开头，其后紧接着 3 个字符的文件
　　5. [abc]* === 文件名含有”a”,”b”, 或”c” 的文件
　　6. BACKUP.[0-9][0-9][0-9] === 以”BACKUP.” 开头，并紧接着 3 个数字的文件
　　7. [[:upper:]]*  === 以大写字母开头的文件
　　8. [![:digit:]]* === 不以数字开头的文件
　　9. *[[:lower:]123] === 文件名以小写字母结尾，或以“1”，“2”，或“3”结尾的文件　

	2. 重定向[SHELL重定向](https://www.runoob.com/linux/linux-shell-io-redirections.html)
### 管道
管道可以把一系列命令连接起来，意味着第一个命令的输出将作为第二个命令的输出，通过管道传递给第二个命令，第二个命令的输出又将作为第三个命令的输入，以此类推。通过 ｜ 符实现这个功能
例如：
```
ls usr/bin | wc -w 
// 以上操作中，借助管道 | 将ls的输出直接作为wc命令的输入，得到/usr/bin目录下文件的个数

cat /etc/passwd | grep "Linux"
打印 /etc/passwd 目录下的文件，然后显示该目录中Linux的信息
```

### 输入输出重定向
	* 输入输出重定向是改变shell命令或默认程序的标准输入/输出目标，重新定向到新的目标
	* Linux中默认的标准输入定义为键盘，标准输出定义为终端窗口
	* 用户可以为当前操作改变输入输出，迫使某个特定命令的输入或输出来源作为外部文件
		1. >file 将file文件重定向为输出源，新建模式
```
ls -l /etc >file1
ls -ls /etc 会显示 /etc目录下的所有文件名这个信息输出到终端显示，而>file1会将file1重定向为输出源，即将所有文件名这个信息写进file1文件中
```
		2.  >>file 与1类似，但为追加模式，即在不改变file内容情况下追加新的重定向输出
		3. <file 重定向输入 将file中的内容作为输入传给某个命令
		4. 2> 或 &> 将由命令产生的错误信息重定向为输出源，输出到某个文件中，2>为新建模式，2>>为追加模式
```
ls -l filew.txt 2>wrong.txt
// 因为目录下没有filew.txt这个文件，所以系统会显示错误信息，而2>wrong.txt就会将这个错误信息输出到wrong.txt文件中		
```

### 命令置换
	将一个命令的输出作为另一个命令的参数。多用于shell脚本当中格式如下：
```
command1 'command2'
command1 $(command2)
例子：
echo "Today is 'date'"
echo 会打印信息到终端上，而date是现实目前日期，上面的命令就是将date的输出（日期信息）作为echo的参数，这样就能打印日期信息
```

### shell基本系统管理维护命令
看mininode
### Linux基本系统文件
	* /etc/passwd 显示系统能够识别的用户清单，用户登陆时，系统查询这个文件，确定用户的UID并验证用户口令，信息包含：用户名，经过加密的口令，UID，默认的GID，个人信息，主目录，登陆shell
	* /etc/group 包含了UNIX组的名称和每个组中成员列表
	* /etc/skel 目录时被 /usr/sbin/useradd 使用，把想要的新用户拥有的配置文件从/etc/skel目录拷贝。
		* 常用的文件：.bash_profile .bashrc  .bash_logout dircolors .inputrc .vimrc
### 进程
	* 进程的概念：程序的一次执行就是一个进程
	* ps 进程显示命令，显示进程的各项信息，包括：进程号（PID），占用的CPU使用率，占用的记忆体使用率及大小，占用的虚拟记忆体大小，**进程状态**，进程开始时间及执行时间
	* 进程状态分类：
		* R: 正在执行中
		* S: 阻塞状
		* T: 暂停执行
		* Z: 不存在但暂时无法消除
		* D: 不可中断的紧致
		* <: 高优先级的进程
		* N: 低优先级的继承
		* L: 有内存分页分配并锁在内存中
```
ps aux | grep a.out
通过管道组合可以显示特定进程项目		
```
	* top 监视进程 显示各项进程信息，并会随着进程状态变化不断更新
	* pstree 将所有进程以树状图显示，树状体将会以pid（进程号）或事以init这个基本进程为根，如果有指定使用者id,则树状图会只显示该使用者所拥有的进程
		* kill 终止进程 kill -signal PID 向指定的进程发出一个signal 默认情况下，kill命令向指定进程发出信号15，将杀死那些不捕捉或不忽略这个信号的进程
			* signal  在终端输入 kill -l 查看各种信号
### 网络配置基础
	* 用户既可以通过命令行的方式，也可以通过图形界面完成网络配置，实现网络配置的唯一目标就是修改系统中众多的网络配置文件，如 /etc/interfaces /etc/hosts /etc/resolv.conf 等等
	* 通常，用户可能使用普通以太网卡，无线网卡，调制解调其等不同类型的设备接入网络。不同类型的网络设备在主机中被映射为相应的网路接口，如以太网卡映射为eth，无线网卡映射为wlan。我们可以通过为每个网络接口分配一个全世界范围内唯一的32bits（IPv4）的标识符。这个标识符就是IP地址
	* IP地址
		* IP地址包括三个部分：Internet网络号（Net-ID）、子网号（Subnet-ID）和主机号（Host-ID）如 192.186（网络号）.1（子网号）.10（主机号）
		* 配置：接入网络的计算机主机依靠IP地址，唯一地标示其在网络中的身份，因此为主机配置IP地址时接入网络的关键，配置IP地址的方法有两种：
			* 配置静态IP，在主机进入网络之前，实现为主机设置固定的IP地址
			* 配置动态IP，选择DHCP网络服务，在主机进入网络后，动态随机获取IP地址
		* 无论是静态IP还是动态IP，计算机都将IP信息保存在 /etc/network/interfaces 中 
```
可以通过修改 /etc/network/interfaces 文件内容修改interfaces配置文件信息，为系统配置静态或者动态IP地址
sudo vi /etc/network/interfaces //打开配置文件
auto lo // 不变
iface lo init loopback // 不变
#配置动态IP
添加或修改：
#The primary network interface
auto eth0	//需要根据系统网卡类型配置，如我这边ens33而非eth0
iface eth0 inet dhcp

#配置静态IP
添加或修改
#The primary network interface
iface eth0 int static
	address 192.168.182.1.128
	netmask 255.255.255.0
	gateway 192.168.182.2


```
	* 除了修改IP地址，我们还需要对运营服务器的指定 DNS客户端配置文件-reslov.conf 进行修改，然后用相关命令使得IP地址和DNS配置文件的修改生效
		* 	DNS服务器地址保存在配置文件 /etc/resolv.conf 中
```
cat /etc/resolv.conf //查看DNS配置文件
sudo vi /etc/resolv.conf //打开配置文件
修改配置文件
sudo /etc/init.d/networking restart //使得修改的配置文件生效
```

### Shell脚本编程
	1. 相对C/C++等编译型语言，shell脚本语言是解释型语言，他的本质是系统管理操作命令的有序集合，他不需要编译器的支持，只需要在运行之前赋予执行权限
	2. shell编程的基本过程
		* 建立shell文件，shell脚本文件一般以.sh结尾指包含多行操作系统命令或shell命令的文本文件
		* 赋予shell文件执行权限。建立的初始脚本文件无执行权限，需要用chmod命令修改权限`chmod u+x 脚本名.sh`
		* 执行shell文件。直接在命令行上调用shell程序` ./文件.sh`
	3. shell变量
		* 	shell 允许用户建立变量存储数据，但不支持数据类型（整型，字符，浮点），**将任何赋给变量的值都解释为一串字符，而且赋值过程中不能有空格**
		* Bourne Shell 有四种类型的变量
			* 用户自定义变量
			* 位置变量，即命令行参数
			* 预定义变量
			* 环境变量
	4. shell功能语句
		* 说明性语句(注释) # 开头 
		* 常用功能性语句
		* 结构性语句 
	1. 	功能性语句
		1. read var1 var2 var3 ：var1 2 3 为用户自定义变量，脚本执行时，会把输入参数按顺序赋给这些变量，如果执行read时标准输入无数据，则程序会等候，知道数据的到来或者程序被终止
		2. expr 命令 主要用于进行简单的整数运算（+ - \*  / %）
```
A='expr 12 + 5 \* 3' #算数运算中，每个数以及运算操作符必须用空格隔开，这与赋值操作要求相反，且对于赋值运算结果的直接赋值，必须用'‘进行转意
echo $A
```
		3. test测试语句
```
#!/bin/bash

A=“how”
B="how"
test $A = $B #测试两个字符串是否一样 测试会区分大小写
echo $? #输出上一条命令的结果
输出结果：0 # 0为真 非0为假 与C语言判断相反

pwd
echo $?	#输出为0 因为pwd时正确的命令

ls file
echo $?	#输出为2 非零为假 file不存在与当前目录中

A=99
B=90
test $A -ne $B #测试A是否不等于B
echo $? #输出为0 

test $A -lt $B	#测试A是否小于B
echo $? #输出为1

test -d /home/runshengwu/shelldemo/expr.sh #测试文件是否为一个目录
echo $? #输出为1 被测试文件只是一个文件

test -r /home/runshengwu/shelldemo/expr.sh #测试文件是否可读
echo $? 

```

	2. 条件循环语句
		1. for
```
for I in 1 3 5 7 9
do 
		echo "$I"
done	#打印 1 3 5 7 9

for I in 'ls /etc'
do 
		echo "$I"
done	#打印 /etc目录下的所有文件

for I in 'seq 1 2 10'	 #seq提供生成1到10中以2为间隔的所有数
do 
		echo "$I"
done #输出结果 1 3 5 7 9

SUM=0
for I in 'seq 1 100' #当没有设定间隔是，默认间隔是1
do
		SUM='expr #SUM + $SUM + $I'
done
echo $SUM #输出结果：5050

for((I = 1; I <= 10; I++))
do 
		echo "I=$I"
done	#输出1-10

实例：
# The statament of for…do..done
# 拷贝当前目录下（ls）的所有文件到backup子目录下，使用语法为： ./prog5.sh [filename]
if [ ! -d $HOME/backup ]
then
	mkdir $HOME/backup	#如果没有backup文件就创建一个
fi		#fi if终止语句
flist='ls'
for file in $flist	#遍历ls目录下的所有文件
do
	if [ $# = 1]	#当命令行有一个参数时
	then
			if [ #1 = $file] #验证输入参数（文件名）是否存在与ls目录下
			then
					echo "$file found"; exit
			fi
	else	#当命令行中没有参数
			cp $file $HOME/backup
			echo " $file copied"
	fi
done
echo ***Backup Completed***
					
```
	
		2. while and case
```
#!/bin/bash
#输入5个成绩分数并根据成绩进行评级
I=0
while [ $I -lt 5]
do
	I='expr $I + 1'
	echo -n "input score:" #-n 提示不换行
	read S	#将输入参数赋值给S
	case 'expr $S / 10' in 
		10|9)	#如果 S/10 属于10-9之间
			echo "A"
			;;
		6|7|8) #如果S/10属于 6 7 8 之间
			echo "B"
			;;
		*）
			echo "C"
			;;
	esac	#case结束语句
	echo "$I"
done		

#在当前目录下批量创建文件FILE1 FILE2…
I=0

echo -n "input number:"
read S
while [ $I -lt $S]
do
	I='expr $I + 1'
	>FILESI #>用法，在当前目录下创建文件，文件名为FILEI，I为数字
```
		3. 循环控制语句 break continue
在建议死循环的情况下，可以看control+C退出死循环
	5. shell 函数
```
  1 grep_user()
  2 {
  3         R='grep "$1" /etc/passwd | wc -l'
  4         echo $R
  5         return $R
  6 }
  7 
  8 echo -n "input username:"
  9 read USER
 10 grep_user $USER
 11 echo "-$?-"	 
```

# 4. GNU开发环境(ww.gnu.org)
## GNU源码下载
GNU 软件的安装过程都是：
	1. 解压源代码包
	2. ./configure    //配置文件，生成makefile文件
	3. make    //生成可执行文件
	4. make install    //安装文件

## 编译过程参数
	* -c ：只编译不链接，生成目标文件 .o
	* -S：只编译不汇编，生成汇编代码
	* -Ε：只预编译
	* -g：包含调试信息 debugger时要加上 `gcc -g hello.c -o hello` 调出调试信息
	* -o file：指定目标输出文件
	* -l dir：搜索头文件路径 当头文件（.h）不是定义在系统文件中时，用-I+头文件路径搜索头文件。当只输入-I.时，默认为当前文件夹
	`gcc -I. hello.c -o hello`
	* 编译常用命令：
```
	gcc filename1.c filename2.c -o filename  
	gcc -o filename filename.c 
	//filename.c可以放在gcc后面或是命令最后，但 -o filename 必须看作一个整体
```
	* 

## 库选项
1. Linux系统下静态链接库和动态链接库格式 
	* 静态链接库：编译时会将相应的文件都包含到可执行文件中 [libname.a]
	* 动态链接库：运行时会调用，位于/usr/lib 文件中  [libname.so [主版本号.次版本号.发行号]] eg: libnetpbm.so.10
	* 静态链接库和动态链接库的区别只是在链接的时候
	1. 编写链接库文件
		1. -static 静态链接编译,编译时会将系统相应的文件包含在内，使得可执行文件非常大，正常情况下不会使用
		2. -share 生成动态库文件，进行动态编译（编译在默认情况下就是动态链接）
		3. -L dir  库文件搜索中添加路径
		4. -fPIC  生成使用相对位置无关的目标代码（position independent code），然后通常用于使用gcc的 -static选项从该PIC目标文件生成动态库文件
2. 编译静态链接库和动态链接库
	* 静态链接库编译
		1. 先生成目标文件 .o  `gcc -c filename.c`
		2. ar crv [*.a][*.o]    //将目标文件打包成 .a 静态库文件  
			* `ar crv filename.a filename.c` 
	* 	调用静态链接库 `gcc -o [file] [file.c] -L path filename.a（要调用的库文件及路径）`

举例：自定义一个静态链接库文件：countlib.c
```
#include <stdio.h>
  
unsigned long count(unsigned int a, unsigned int b)
{
        return a*b;
}
在shell中：
生成目标文件： gcc -c countlib.c
打包文件：   ar cru countlib.a countlib.c

在count.c文件编译时中调用上述静态链接库
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
        unsigned int x,y;
        sscanf(argv[1],"%u",&x);
        sscanf(argv[2],"%u",&y);
        printf("result is :%u\n",x*y);
        return 0;
}
 
在shell中： gcc -o count count.c -L./ count lib.a
执行：./count 12 3
输出结果： result is :36
```

	* 编译动态链接库（同样以countlib.c 和 count.c为例）
		1. 生成位置无关的目标代码 `gcc -fPIC -c countlib.c`
		2. 打包成动态库文件.so`gcc -shared -o countlib.so countlib.o`
	* 	调用动态链接库（与静态链接库类似）
	`gcc -o count count.c -L./ countlib.so`

## 警告选项
	1.  -w 关闭所有警告选项
	2. -Wall 发出gcc提供的所有有用警告
	3. -pedantic 发出ansi c的所有警告

## 优化选项 -Olevel (1、2、3)
优化选项是为了提升效率，只有在代码确定不会再修改是才会使用

## gdb调试
debug模式编译


## Makefile
	1. Makefile·作用：工程文件组织，编译成复杂的程序，并安装及卸载程序
Makefile 由若干条的规则构成：
```
targets（目标文件）：prerequisites（依赖文件.o）
	command（命令）
```
 
	2. Makefile变量
		* 用户自定义变量
		* 预定义变量
		* 自动变量及环境变量
举例：假设有3个函数main.c, func1.c, func2.c，通过make生成可执行文件hello
```
#create makefile
MObj = main.o func1.o func2.o		//用户自定义变量
CFLAGS = -g -c	//预定义变量：C编译器选项
CC = gcc
CXX = g++
@.o: $(MObj)	//用$符号调用自定义变量
	$(CC) $^ -o $@	//$^ 表示上一行定义的目标的所有依赖文件$(OMbj)  $@ 表示输出文件(hello)
	//$(CC) $(MObj) -o $@

main.o: main.c 
	$(CC) $(CFLAGS) main.c

func1.o: func1.c
	$(CC) $(CFLAGS) func1.c

func2.o: func2.c
	$(CC) $(CFLAGS) func2.c
.PHONY: clean		//声明为伪目标，防止文件夹下有同名的clean文件导致错误
clean:	//输入 make clean 调用
	rm $(MObj) hello		//清除已生成文件
.PHONY: install
install:	//输入 sudo make install 调用
	cp hello /usr/local/hello	//将文件拷贝到具体路径下
.PHONY: uninstall
uninstall:	//输入 sudo make uninstall 调用
	rm /usr/local/hello
```

	3. make工作流程
		* make会在当前目录下找名字叫做“Makefile” 或 “makefile” 的文件,makefile是make读入的唯一配置文件
		* 如果找到，他会找文件中的第一个目标文件（target）并把这个文件作为最终目标文件
		* 根据时间戳生成目标文件
		* 递归区寻找目标文件的对应依赖文件，并且递归生成（同样有时间戳问题）
	
	4.  引用其他makefile及makefile嵌套
	5. 条件判断
```
ifeq(a,b)	//如果a与b相等
	…
else
	…
endif
```

	6. makefile管理命令
	7. makefile主体基本格式
```
main	
```
	9. Makefile模版，这个模版是适用于所有源文件都处在同一个目录的情况
```
#Makefile

#自定义变量
MAKE    = make
CXX     = g++
#编译选项，生成所有警告、不优化、采用c++20标准、输出调试信息、只编译并生成目标文件
CFLAGS  = -Wall -O0 -std=c++2a -g -c
#最终目标文件main
EXES    = main
#wildcard为Makefile模式匹配关键字，获取目标目录符合匹配模式的所有文件名
SRCS    = $(wildcard ./*.cpp)
#patsubst为Makefile模式替换关键字，查找字符串SRCS中按空格分开的单词，并将符合模式%.cpp的字符串全部替换成%.o，作为main的依赖文件
OBJS    = $(patsubst ./%.cpp, ./%.o, $(SRCS))

RM      = rm -f

#默认任务
default:
#默认任务要执行的命令，按上面的变量名替换为变量值后执行，前面必须有一个Tab符
    $(MAKE) $(EXES)
#makefile主体
#模式匹配,冒号前者为目标项，冒号后面为依赖项，这里最终生成的可执行文件是main
$(EXES): $(OBJS)
#$^表示规则中所有的依赖项，$@表示规则中的目标
    $(CXX) $^ -o $@

# %模式自动匹配符
%.o: %.cpp
# $<表示规则中的第一个依赖项
    $(CXX) $(CFLAGS) $< -o $@

#伪目标，声明clean为伪目标或标签，为了避免该清理任务与文件名相同而被错识别
.PHONY: clean
#清理之前的目标文件，以便下次完整的重新编译
    $(RM) $(OBJS) $(EXES) *.o


	
```
	10. Makefile隐含规则
		* 	编译C程序时，n.o的目标的依赖目标会自动推到为n.c，并且其生成命令时` $(CC) -c $(CPPFLAGS) $(CFLAGS)`
		* 隐含规则2: 链接Object文件的隐含规则，n目标依赖于n.o 通过运行C的编译器来运行链接程序生成，其生成命令时 `$(CC) $(LDFLAGS) n.o`
		* `$(LOADLIBES) $(LDLIBS)` 这个规则不仅对于只有一个源文件的工程有效，对多个Object文件（由不同源文件生成的）也有效，例如：
```
#假设x.c y.c z.c都存在
#目标文件名必须是和依赖文件名中的其中一个同名，否则会出错
x:x.o y.o z.o
#当makefile文件只有这条命令时，根据隐含规则他会自动执行如下命令
cc -c x.c -i x.o 		
cc -c y.c -i y.o 
cc -c z.c -i z.o 
cc x.o y.o z.o -o x
```

### Makefile的VPATH
	* VPATH：虚路径
		* 在一些大的工程中，有大量的源文件一般被分类存放在不同的目录中，所以当make需要区找寻文件的依赖关系时，你可以子文件前加上路径，告诉make其自动找
		* Makefile文件中的特殊变量“VPATH”的定义可以让make到所指定的目录中找寻文件
		* 一般格式：VPATH = src:…/headers 这里指定的两个目录 “src” 和 “../headers”，make会按照这个顺序进行搜索，不同目录由冒号进行分隔。当然，当前目录永远是最高优先搜索的地方
### Makefile的嵌套
```
#假设有多个目录存放着源文件，且存放源文件的目录都有一个makefile
#声明变量
cc = gcc
SUBDIRS = f1 \
			f2 \
			main \
			obj
OBJS = f1.o f2.o main.o
BIN = myapp
OBJS_DIR = obj
BIN_DIR = bin
#让定义的变量可以被子目录下的makefile调用
export CC OBJS BIN OBJS_DIR BIN_DIR	

all: CHECK DIR $(SUBDIRS)
CHECK_DIR:
		#建立文件夹，放到bin目录下
		mkdir -p $(BIN_DIR)
$(SBUDIRS):ECHO
		#对SUBDIRS（这里是:f1/ f2/ main/目录下的所有源文件进行make），并将最后生成的可执行文件存放到bin/下。注意这里的依赖是ECHO
		make -C $@	#make -C 调取某个目录下的makefile
ECHO:
		#ECHO将make的信息根据定义的目录变量逐个打印出来
		@echo $(SUBDIRS)
		@echo begin compile
CLEAN:
		#清除各个目录下的.o文件以及bin/下的可执行文件
		@$(RM) $(OBJS_DIR)/*.o
		@rm -rf $(BIN_DIR)
```
## Autotools
在使用大型程序时，手动编写makefile非常麻烦
	1. 组成工具
		1. autoscan：用于扫描源代码目录，生成 configure.scan 文件。configure.scan 文件包含了系统配置的基本选项，里面都是一些宏定义。我们需要将它改名为 configure.in
		2. aclocal：一个perl叫门程序，根据 configure.in 文件的内容，自动生成 aclocal.m4 文件。生成的 aclocal.m4 文件是宏展开文件
			* aclocal 的定义：
	 `*aclocal -create aclocal.m4 by scanning configure.ac`

		3. autoconf：用来产生 configure 文件，configure.in文件的内容是一些宏，这些宏经过autoconf处理后会变成检查系统特性，环境变量，软件必须的参数shell脚本
		4. autoheader：自动生成configure.in
		5. automake：使用automake -add-missing 来产生 makefile.in makefile.am是用来生成makefile.in的，需要手动书写

		2. configure 的生成
Files used in preparing a software package for distribution, when using just Autoconf:
     your source files —> [autoscan*] —> [configure.scan] —> configure.ac
     
     configure.ac —.
            		        |   .———> autoconf* ——> configure
     [aclocal.m4] ——+—+
          		        |   `——> [autoheader*] ——> [config.h.in]
     [acsite.m4] —'
     
     Makefile.in
Additionally, if you use Automake, the following additional productions come into play:
     [acinclude.m4] —.
                     		    |
     [local macros] —+—> aclocal* —> aclocal.m4
                      		   |
     configure.ac ——'
     
     configure.ac ——.
                  		 +——> automake* ——> Makefile.in
     Makefile.am ——'

Files used in configuring a software package:
                          		 .——————> [config.cache]
     configure* ——————+——————> config.log
                         		|
     [config.h.in] -.          v            			    .-> [config.h] -.
                    	    +——————> config.status* -+           	    +——————> make*
     Makefile.in —'                			            `-> Makefile —'
 

##  autotools用法、具体流程（以hello.c为例）
```
#include <stdio.h>
  
int main()
{
        printf("hi configure\n");
        return 0;
}	
```

	1. `autoscan //扫描生成 configure.scan文件`
	2. `mv configure.scan configure.ac  //将configure.scan 更改为 configure.ac 或 configure.in`
	3.  修改configure.ac文件内容
```
#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
# 修改要生成的文件名，版本号，错误信息发送地址（邮箱）
AC_INIT([hello, 1.0, runsheng.wu@outlook.com)
AC_CONFIG_SRCDIR([hello.c])
AC_CONFIG_HEADERS([config.h])
# 最后使用automake生成文件 AM_INIT_AUTOMAKE(hello,1.0)	
# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_OUTPUT(Makefile)	//配置程序输出为Makefile
```
	4. 生成 config.h.in `autoheader`
	5. 生成 aclocal.m4 文件 `aclocal`
	6. 创建 Makefile.am 文件
```
bin_PROGRAMS = hello		//bin_PROGRAMS = 目标文件名
hello_SOURCES = hello.c	//目标文件名_SOURCES = 文件名.c
```
	6. 生成 Makefile.in 文件 `automake —add-missing`
	7. 建立一些空文件表示工程信息
	`touch NEWS README AUTHORS ChangeLog `
	8. 生成 Makefile `./configure`
	9. 执行make相关命令 
```
make	//生成可执行文件
sudo make install		//安装
make dist	//生成压缩包
make clean	//清理
```

# 5. Lunix高级编程 
	上面4点关于Linux的课程是关于嵌入式系统体系下应用层的学习，并没有涉及Linu内核。所以接下来就要通过学习Linux高级编程来了解Linux内核的强大
	* Linux内核主要功能
		1. 文件管理
		2. 进程管理
		3. 设备管理
		4. 内存管理
		5. 网络管理
	* 	在一般的编程工作中，我们总是通过编写代码程序在硬件中实现特定功能，在嵌入式系统体系中，代码程序是在应用层，硬件是在硬件层，而在应用层和硬件层之间，是用过系统内核层来完成代码程序到功能的转换的，就是说，我们是将写好的代码写入内核当中，通过内核的驱动程序将相关指令和功能写入硬件当中，而Linux高级编程，属于实现应用层和内核层之间交流的语言。
	* 而事实上，代码编写当中，我们许多指令和变量的使用都调用到库函数，实际上指令和变量的使用都会调用到库函数中相应的结构函数，而我们学习的高级编程，就是通过应用层，直接在内核中使用相应的结构函数，
	* LInux下高级编程的特点：设计到内核想用户空间提供的接口：内核本身是一个稳定的代码，需要为同时为多个用户空间的应用程序服务，为了防止某些用户的应用层的代码错误导致内核代码崩溃或产生其他问题，就需要为用户提供相应的接口（函数），并在这些接口函数中加上一些保护，就可以让符合接口函数的应用提供安全的服务，同时保护内核

## 文件I/O
* 文件的概念：文件是动态管理磁盘数据的结构
* 文件的分类：
	* 磁盘文件：指一组相关数据的有序集合，通常存储在外部介质（如磁盘）上，使用时才调如内存。
	* 设备文件：操作系统中与主机相连的输入、输出设备看作是一个文件、这些设备文件的输入、输出看作是对磁盘问价你的读和写。例如、键盘（标准输入文件）、屏幕（标准输出文件）
在Linux操作系统中，每一个外部设备都在/dev目录下对应一个设备文件，要通过程序操作设备，就必须对与其对应的/dev目录下的设备文件进行操作。在Linux操作系统中，一切数据都以文件的形式存在，大部分设备硬件也称为设备文件。
* 而一切文件数据处理程序运行都是在内存中完成的

### 标准I/O
在系统进行文件数据的输入输出操作过程中，文件数据必须先进入文件缓冲区然后在进入内存，进行程序运行，等识别到程序运行完成或其他标志时，才会刷新缓冲区

文件缓冲分类：
	1. 行缓冲：就是缓冲区碰到换行符才刷新缓冲区，例如输出函数printf函数就是标准的I/O库函数，是行缓冲的，当数据进入缓冲区中，没有识别到换行符“\n”，函数在程序结束之前是不会将数据输出到屏幕上的。另外，在也可以通过fflush(NULL)函数刷新缓冲区。
	2. 全缓冲：标准I/O函数，想普通文件读写数据的，都是全缓冲。全缓冲不识别换行符，只会在缓冲区满了或者用fflush函数时才会刷新缓冲区。否则，只有在程序正常结束时，才会刷新缓冲区。
	3. 无缓冲：读写文件的时候通过系统调用I/O（read/wirte）对文件进行读写数据，这时候是无缓冲的，写数据会立马进入文件，读数据会立马进入内存。
	
### 磁盘文件的分类
* 之前说到，文件是动态管理磁盘数据的机构，也就是磁盘上一段命名的存储区。计算机的存储在物理上是二进制的，所以物理上所有的磁盘文件本质都是一样的，数据在文件->磁盘上以字节为单位进行顺序存储
* 从用户或者操作系统的角度上，可以把文件分为：
	* 文本文件：基于字符编码的文件 ，字符编码，常见的有ASCII，UNICODE等。文本文件一般可以用文本编辑器打开
	* 二进制文件：基于值编码的文件，也称作非文本文件，这里说的二进制并非直接的01构成的文件，而是根据特定的应用（音频、图片等）以特定的编码形式来存储。
	
### 文件指针
	* 文件指针在程序中用来标示（代表）一个文件的
	* 在定义中，文件指针的一般形式为：
		* *FILE 指针变量标识符，在库函数<stdio.h>中。
#### 补充：
c语言中有三个特殊文件指针无需定义，在程序中可以直接使用
	* stdin:标准输入 默认为当前终端（键盘）
		* scanf、getchar函数默认从此终端获得数据
	* stdout:标准输出 默认为从终端（屏幕）
		* printf、puts函数默认输出信息到终端
	* stderr：标准错误输出设备文件 默认为当前终端（屏幕）
		* 当程序出错使用 peeror函数使错误信息打印在此终端
![](Readme/84F4149C-00FB-4D7A-B7BD-BA5E3D7E4BD4.png)

#### 文件I/O接口实现 看vscode
```
// 文件I/O接口
// 读写文件fopen(),fgetc(),fputc()，并利用读写操作实现文件（文本、音乐、视频等）拷贝
#include<stdio.h>
int main(int argc, char *argv[])    // main函数参数用于实现文件拷贝
{
    FILE *fp = NULL,*fp2 = NULL; char ch;
    char buf[1024];
    if (argc != 3)  // 如果main参数不满足拷贝文件数量，直接退出
    {  
        return 0;
    }
    fp = fopen(argv[1],"rt"); // 第一个参数为文件指针,表示文件路径，第二个参数为规定文件操作类型："r"表示只读，"b"表示二进制文件,"p"表示文本文件,先后有规定，返回值为文件指针
    fp2 = fopen(argv[2],"wt");    // 可以打开一个不存在的文件，系统会创建一个，“w”表示文件可写，会在无论当前目录是否存在同名文件都新建一个文件（如已有就覆盖）“a”表示追加一个新的可写文件，如果文件以存在，“a+”，追加新的可读可写文件
    // 但“a”或者“a+”会在文件内容最后追加内容，如果此时调用fgetc()调用信息，则会从文件开头调用信息，导致无法指显示追加的内容

    if (fp == NULL)
    {
        perror("log");  // 输出错误信息，错误信息可以自己设置，但一般会打印出系统给出的错误信息
        return 0;
    }
    if (fp2 == NULL)
    {
        perror("log");  // 输出错误信息，错误信息可以自己设置，但一般会打印出系统给出的错误信息
        return 0;
    }
    while (feof(fp) == 0)   // feof函数检查文件流是否读到了文件尾，没读一个文件数据都会返回非零值，知道检查到文件尾返回0
    {
        // printf("%c",ch);
        // 实现文件复制
        // ch = fgetc(fp); // 以1个字节为单位逐次打印文件信息
        // fputc(ch,fp2);  // 以1个字节为单位写入数据，第一个参数为写入的数据，第二个参数的写入的文件指针（目标文件）
        
        // fgets(buf,1023,fp); //fgets()按字符串读取，遇到换行符或者读到size-1个字节停止读取，会在读取的内容后面加一个“\0”，作为字符串结尾
        // fputs(buf,fp2); // 以字符串为单位写入数据，不需要规定size，会识别字符串中的“\0”作为结束输入标志，输入完成后会把“\0”删除
        // 但对于音乐、视频、图片等二进制文件中，无法通过这种方法读取，具体原因不清楚，可能因为二进制文件内容存在零

        // 以上的文件读写非常少用，一般文件读写用下面的方法，可以读写任何类型的文件
        int len = fread(buf,1,1023,fp); // fread()这里定义从文件中读取1023块数据，一块是1个字节，共1023块，返回指是块数
        if (len > 0)
        {   
            fwrite(buf,1,1023,fp2); // fwrite()这里定义在文件中写入1023块数据，一块是1个字节，共1023块
        }

    }

    fclose(fp);   // 关闭文件
    fclose(fp2);
    
    return 0;
}
```

#### 结合双向链表的文件读写实现
```
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
// 结合链表，通过链表将输入的信息数据存入文件

    // prinrf():将内存数据结构格式化成字符串，输出到标准输出
    // sprinf():将内存数据结构格式化成字符串。输出到目标内存
    // fprintf()：将内存数据结构格式化成字符串，输出到目标文件
    // scanf()；将标准输入的字符串格式化成数据结构存储到指定内存
    // sscanf()：将指定内存的字符串格式化成数据结构存储到指定内存
    // fscanf()：将指定文件的字符串格式化成数据结构存储到指定内存
#define BLOCK 0 //定义读取方式是块读写还是文本读写,0表示文本，1表示二进制
#define BLOCK_NAME "data.bin"
#define TXT_NAME "data.txt"
// 双向链表-循环结构
// 双向链表与链表的不同在于节点的不仅可以指向后面的节点，也可以指向前面的节点
// 双向链表一般都是循环结构，就是说head->next指向最后一个节点，而尾节点->next指向head
// 1.双向链表的创建
typedef struct student
{
    int num;
    char name[20];
    struct student *front;  // 新增一个front指向当前节点的上一个节点
    struct student *next;
}STU;

// 2.链表的遍历输出
void link_printf(int line, STU *head,char flag)
{
    // 由于双向链表的循环结构，链表中任何节点都不会指向NULL
    // 但因为head是确定的，所以只需要新增一个临时指向节点，通过判断节点是否指向head来确定遍历是否完成
    STU *pb = head;
    if (head == NULL)
    {
        return; //如果链表本身为空，则直接退出
    }
    if (flag == 1)
    {
        while (pb->next != head)
        {   
            printf("%d:%d %s\n",line,pb->num,pb->name);
            pb = pb->next;
        }
    }else   //逆序打印
    {
        pb = pb->front; // 从尾部开始反向打印
        while (pb != head)
        {
            printf("%d:%d %s\n",line,pb->num,pb->name);
            pb = pb->front;
        }
    } 
    printf("%d:%d %s\n",line,pb->num,pb->name);
}
// 3.1. 双向链表的插入，以head作为参考头节点，从head->front也就是尾节点后面插入新的节点
STU *link_insert(STU *head, STU *pnew)
{
    STU *pb = head;
    if (head == NULL)
    {
        // 双向链表对于首个插入的数据，pnew->front和pnew->next必须指向本身，以满足循环结构
        head = pnew;
        head->next = head;
        head->front = head;        
    }else if(pnew != NULL)
    {
        // 以head为首，在尾节点后插入新节点
        pb = head->front;   // 找到最后一个节点
        pnew->next = pb->next;  // pb->next指向头节点，将pnew->next指向头节点
        pb->next = pnew;    
        pnew->front = pb;
        pnew->next->front = pnew;
        
    }
    return head;
}

// 4.链表内数据的查找
STU *link_find(STU *head, char *name)
{
    STU *pb = head;
    if (head == NULL)
    {
        return NULL; //如果链表本身为空，则直接退出
    }
    while (pb->next != head)
    {   
        if(strcmp(pb->name, name) == 0)
            break;
        pb = pb->next;
    }
    if(strcmp(pb->name, name) == 0)
        return pb;
    else
        return NULL;
}
// 5.链表的内存释放
STU *link_free(STU *head)
{
    STU *ps = head;    //建立缓存
    if (head == NULL)
    {
        return NULL;
    }
    while (ps->next != head)
    {   
        // 先找到头节点的下一个节点，再将头节点释放，然后将下一个节点定义位头节点，继续寻找
        ps = ps->next; 
        free(ps->front);
    }
    free(ps);
    return NULL;
}

// 6.链表任意节点的删除
STU *link_delete(STU *head, char *name)
{
    STU *pb = head;
    if (head == NULL)
    {
        return NULL; //如果链表本身为空，则直接退出
    }
    while (pb->next != head)    //在头节点到倒数第二个节点中查找
    {   
        if(strcmp(pb->name, name) == 0) // 找到就break，准备删除
            break;  
        pb = pb->next;
    }
    // 分两种情况，1是在前面已经找到了，准备删除，这时pb对应要被删除的节点，2是前面没找到，这时pb对应最后一个节点
    if(strcmp(pb->name, name) == 0)
    {
        if (pb == head)
            head = pb->next;
        pb->front->next = pb->next;
        pb->next->front = pb->front;
        free(pb);
    }
    return head;
}

// 7.链表排序-升序
// 定义交换节点函数
void swap(STU *pf,STU *pb)
{
    STU temp;
    temp = *pf;
    *pf = *pb;
    *pb = temp;
    // 将指向交换
    temp.next = pf->next;
    temp.front = pf->front;
    pf->next = pb->next;
    pf->front = pb->front;
    pb->next = temp.next;
    pb->front = temp.front;
    //在此，pf就会作为两次比较后的最小值不断跟后面的节点进行比较
}
// 定义排序函数
STU *link_order(STU *head)
{
    STU *pf = head,*pb;
    while (pf->next != head)    // 外循环，决定了产生了多少个最少值
    {
        pb = pf->next;
        while (pb != head)  // 内循环，将外循环得到的当前最小值和后面的节点数据一一比较
        {
            if (pf->num > pb->num)
                swap(pf,pb);
            else if (pf->num == pb->num){
                if (*(pf->name) > *(pb->name))  // 取字符串首地址，也就是首字母，这里比较的是ascII码
                    swap(pf,pb);
            }
            pb = pb->next;
        }
        // 当内循环进行了一次之后，首节点就会获得整个链表的最小值，至此，pf往后移一位，在剩下的节点中找到最小值
        pf = pf->next;
    }
    return head;
}


// 查看帮助信息
void print_help(void)
{
    puts("************");
    puts("1.插入学生信息到尾部");
    puts("2.遍历学生信息");
    puts("3.查找学生信息");
    puts("4.删除学生信息");
    puts("5.按学号排序");
    puts("6.逆序排列");
    puts("7.查看帮助信息");
    puts("8.保存并退出管理系统");
    puts("************");
}

STU *loader_data(STU *head) // 从文件读取数据到链表
{
    STU *pnew = NULL;
    FILE *fp = NULL;
#if BLOCK
    fp = fopen(BLOCK_NAME,"rt");
#else
    fp = fopen(TXT_NAME,"rt");
#endif
    if (fp == NULL)
    {
        perror("");
        return NULL;
    }
    printf("%d:len = %ld\n",__LINE__,ftell(fp));    // ftell() 定位当亲文件指针的位置
    fseek(fp,sizeof(pnew)*2,SEEK_SET);   // fssek() 文件定位，这里表示将文件指针从文件开头跳到两个链表大小后的位置
    while (feof(fp) == 0)
    {
        pnew = malloc(sizeof(STU));
#if BLIOCK
        fread(pnew,sizeof(pnew),1,fp);   // 用二进制读取方式从文件中读取数据，一次读取一个链表大小的数据
#else
        fscanf(fp,"%d%s",&(pnew->num),pnew->name);  // 将指定文件的字符串格式化成数据结构存储到指定内存
#endif  
        head = link_insert(head,pnew);
    }
    fclose(fp);
    return head;
}

void save_to_file(STU *head)    // 将链表数据存储到文件
{
    STU *pb = head;
    FILE *fp = NULL;
    if (head == NULL)
        return;
#if BLOCK
    fp = fopen(BLOCK_NAME,"w");
#else
    fp = fopen(TXT_NAME,"w");
#endif
    if (fp == NULL)
    {
        perror("");
        return;
    }
    while (pb->next != head)
    { 
#if BLOCK  
        fwrite(pb,sizeof(pb),1,fp); // 一次写入一个链表大小的数据，从pb写入fp，fwrite决定了写入方式是二进制（块）
#else
        fprintf(fp,"%d\t %s\n",pb->num,pb->name);   // 将内存数据结构格式化成字符串，输出到目标文件
#endif        
        pb = pb->next;
    }
#if BLOCK
    fwrite(pb,sizeof(pb),1,fp); // 一次写入一个链表大小的数据，从pb写入fp，fwrite决定了写入方式是二进制（块）   
#else
    fprintf(fp,"%d\t %s",pb->num,pb->name);
#endif
    fclose(fp);
}
int main()
{
    STU *pnew,*p,*head = NULL,*pb;
    int i,len = 3,ops; char name[18];
    print_help();
    head = loader_data(head);
    while (1)
    {
        puts("请输入操作码：");
        scanf("%d",&ops);
        switch(ops){
            case 1: //插入学生信息到头部
                pnew = malloc(sizeof(STU));
                puts("请输入学号和姓名：");
                scanf("%d%s",&(pnew->num),pnew->name);
                head = link_insert(head,pnew);
            break;
            case 2: //打印学生信息
                if (head == NULL)
                    puts("列表为空\n");
                else
                    link_printf(__LINE__,head,1);
            break;
            case 3: //查找学生信息
                puts("请输入要查找的姓名：");
                scanf("%s",name);
                p = link_find(head,name);
                if (p != NULL)
                {
                    printf("找到：%d %s\n", p->num,p->name);
                }else
                {
                    printf("找不到对应姓名\n");
                }
            break;
            case 4: //删除学生信息
                puts("请输入要删除的姓名：");
                scanf("%s",name);
                head = link_delete(head,name);
            break;
            case 5: //按学号排序
                head = link_order(head);
            break;
            case 6: //逆序排列打印
                link_printf(__LINE__,head,0);
            break;
            case 7: //查看帮助
                print_help();
            break;
            case 8: //保存退出管理系统
                save_to_file(head);
                link_free(head);
                return 0;
            break;
            default:
                puts("输入有误，请输入正确的操作码！");
        }
    }
    return 0;
}
```

#### 文件加密解密
```
// **************************************** //
// ***********文件加密/解密-对称加密体制******* //
/* 对称加密体制是即加密方A和解密方B共享一个密钥Key。
加密方A使用该密钥jkey对要保密的文件进行加密操作，从
而生成密文；解密方B同样使用该密钥key对加密生成的加密文件
试试解密操作，从而生成明文 */
// 对称机密体制格式：密文+密码 = 明文 明文-密码 = 密文
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
// 本程序实现对文件内容的加密和解密
// 加解密文件函数
char *file_text_encrypt(char *src_file_text,unsigned long int length,unsigned int password)
{
    for (int i = 0; i < length; i++)
    {
        src_file_text[i] ^= password;
    }
    return src_file_text;
    
}

// 从键盘获取源文件和目的文件名
void get_file_name(char *dest_file_name,char *src_file_name)
{
    puts("请输入源文件名：");
    gets(src_file_name);
    puts("请输入目标文件名：");
    gets(dest_file_name);
}

// 读取源文件
char *read_src_file(unsigned long int *file_length, char *src_file_name)
{
    FILE *fp = NULL;
    char *buf;
    fp = fopen(src_file_name,"r");
    if (fp == NULL)
        return NULL;
    // 获取文件大小
    fseek(fp,0,SEEK_END);   // 这里文件指针会指向文件末位，需要在后面重新定位文件指针
    *file_length = ftell(fp);
    // 将文件指针定位到文件头
    rewind(fp);
    buf = malloc(*file_length); // 为字符串指针申请空间，空间大小与文件大小一致
    fread(buf,1,*file_length,fp);   // 读取格式，以一个字节为文件块单位，一共有file_length块
    fclose(fp);
    return buf;

    
}

// 将某个字符串保存到文件
void save_file(char *text,unsigned long int length, char *file_name)
{
    FILE *fp = NULL;
    fp = fopen(file_name,"w");
    if (fp == NULL)
        return;
    fwrite(text,1,length,fp);
    free(text);
    fclose(fp);
    
}

void print_help()
{
    printf("**********1:加密文件**********\n");
    printf("**********2:解密文件**********\n");
    printf("**********3:退出程序**********\n");
}

int main()
{
    char *buf;
    unsigned int pwd,ops;
    char dest_file_name[30],src_file_name[30];
    unsigned long int file_length;
    while(1)
    {
        print_help();
        puts("请输入操作吗：");
        scanf("%d",&ops);
        getchar();
        switch (ops)
        {
        case 1: // 加密文件
        case 2: // 解密文件
            get_file_name(dest_file_name,src_file_name);
            buf = read_src_file(&file_length,src_file_name);    // 获取文件内容
            puts("请输入密码：");
            scanf("%d",&pwd);
            file_text_encrypt(buf,file_length,pwd); // 对文件内容进行加密
            break;
        case 3: // 退出程序,
            save_file(buf,file_length,dest_file_name);
            return 0;
            break;
        
        default:
            puts("输入有误，请输入正确的操作数！");  
        }
    }
    return 0;
}
```

#### 链表歌词播放-缺歌词数据文件
```
// 歌词链表，结合链表实现歌词的存储和播放
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>  // usleep函数头文件

// 双向链表-循环结构
// 双向链表与链表的不同在于节点的不仅可以指向后面的节点，也可以指向前面的节点
// 双向链表一般都是循环结构，就是说head->next指向最后一个节点，而尾节点->next指向head
// 1.双向链表的创建
typedef struct lrc
{
    int m_time;
    char lrc_buf[200];
    struct lrc *front;  // 新增一个front指向当前节点的上一个节点
    struct lrc *next;
}LRC;

// 2.链表的遍历输出
void link_printf(int line, LRC *head,char flag)
{
    // 由于双向链表的循环结构，链表中任何节点都不会指向NULL
    // 但因为head是确定的，所以只需要新增一个临时指向节点，通过判断节点是否指向head来确定遍历是否完成
    LRC *pb = head;
    if (head == NULL)
    {
        return; //如果链表本身为空，则直接退出
    }
    if (flag == 1)
    {
        while (pb->next != head)
        {   
            printf("%d:%d %s\n",line,pb->m_time,pb->lrc_buf);
            pb = pb->next;
        }
    }else   //逆序打印
    {
        pb = pb->front; // 从尾部开始反向打印
        while (pb != head)
        {
            printf("%d:%d %s\n",line,pb->m_time,pb->lrc_buf);
            pb = pb->front;
        }
    } 
    printf("%d:%d %s\n",line,pb->m_time,pb->lrc_buf);
}
// 3.1. 双向链表的插入，以head作为参考头节点，从head->front也就是尾节点后面插入新的节点
LRC *link_insert(LRC *head, LRC *pnew)
{
    LRC *pb = head;
    if (head == NULL)
    {
        // 双向链表对于首个插入的数据，pnew->front和pnew->next必须指向本身，以满足循环结构
        head = pnew;
        head->next = head;
        head->front = head;        
    }else if(pnew != NULL)
    {
        // 以head为首，在尾节点后插入新节点
        pb = head->front;   // 找到最后一个节点
        pnew->next = pb->next;  // pb->next指向头节点，将pnew->next指向头节点
        pb->next = pnew;    
        pnew->front = pb;
        pnew->next->front = pnew;
        
    }
    return head;
}

// 4.链表内数据的查找
LRC *link_find(LRC *head, int time)
{
    LRC *pb = head;
    if (head == NULL)
    {
        return NULL; //如果链表本身为空，则直接退出
    }
    while (pb->next != head)
    {   
        if(pb->m_time == time)
            break;
        pb = pb->next;
    }
    if(pb->m_time == time)
        return pb;
    else
        return NULL;
}
// 5.链表的内存释放
LRC *link_free(LRC *head)
{
    LRC *ps = head;    //建立缓存
    if (head == NULL)
    {
        return NULL;
    }
    while (ps->next != head)
    {   
        // 先找到头节点的下一个节点，再将头节点释放，然后将下一个节点定义位头节点，继续寻找
        ps = ps->next; 
        free(ps->front);
    }
    free(ps);
    return NULL;
}



// 7.链表排序-升序
// 定义交换节点函数
void swap(LRC *pf,LRC *pb)
{
    LRC temp;
    temp = *pf;
    *pf = *pb;
    *pb = temp;
    // 将指向交换
    temp.next = pf->next;
    temp.front = pf->front;
    pf->next = pb->next;
    pf->front = pb->front;
    pb->next = temp.next;
    pb->front = temp.front;
    //在此，pf就会作为两次比较后的最小值不断跟后面的节点进行比较
}
// 定义排序函数
LRC *link_order(LRC *head)
{
    LRC *pf = head,*pb;
    while (pf->next != head)    // 外循环，决定了产生了多少个最少值
    {
        pb = pf->next;
        while (pb != head)  // 内循环，将外循环得到的当前最小值和后面的节点数据一一比较
        {
            if (pf->m_time > pb->m_time)
                swap(pf,pb);
            pb = pb->next;
        }
        // 当内循环进行了一次之后，首节点就会获得整个链表的最小值，至此，pf往后移一位，在剩下的节点中找到最小值
        pf = pf->next;
    }
    return head;
}

// 将歌词数据切割成以一个歌词为单位的字符串数组。
int msg_deal(char *msg_src,char *msg_done[],char *str)
{
    int i = 0;
    msg_done[i] = strtok(msg_src,str);  // 切割函数
    while (msg_done[i] != NULL)     
    {
        i++;
        msg_done[i] = strtok(NULL,str);
    }
    return i;
    
}

int main()
{
    char *str = "[03:30.68][02:39.34][01:10.71]爱能不能够永远单纯没有悲哀";
    int time_buf[5];
    int i=0,j,s=0,len;
    int min,sec;
    LRC *pnew, *p, *head = NULL;
    char *q[100];
    char lrc_buf[];
    len = msg_deal(lrc_buf,q,"\r\n");
    // 将歌词数据放入链表
    for (int k = 0; k < len; k++)
    {
        str = q[k];
        while (*str == '[')
        {
            // 获取歌词时间
            time_buf[i++] = atoi(str+1)*60+atoi(str+4); // 将每个时间数据存储在time_buf[i]中，一共有3个
            str = str+10;
        }
        for (j = 0; j < i; j++)
            {
                pnew = malloc(sizeof(LRC));
                pnew->m_time = time_buf[j]; // 在链表中放入时间数据
                strcpy(pnew->lrc_buf,str);  // 在链表中放入歌词数据
                head = link_insert(head,pnew);
            }
    }
    
    
    link_printf(__LINE__,head,1);
    // 结合模拟时钟程序播放歌词
    while(1)
    {
        usleep(100*1000);   // usleep函数能把线程挂起一段时间， 单位是微秒（千分之一毫秒）。
        printf("%02d:%02d\r",s/60,s%60);    // 显示计时
        fflush(stdout);

        p = link_find(head,s);
        if (p != NULL)
        {
            printf("%02d:%02d:%s\n",p->m_time/60,p->m_time%60,p->lrc_buf); //打印链表中的歌词
        }
        s++;
    }
	return 0;
}
```

# Linux C/C++ Development
* 程序生成：人类语言->机器语言（编程语言->汇编语言->二进制）
	* 编程语言（代码文件）->通过编译（包含预处理/编译/汇编）生成目标文件->链接，将单个或多个目标文件组合链接，生成可执行文件。具体：
		* 预处理 - 头文件，宏定义
		* 编译，语法检查，翻译成汇编语言
		* 汇编，汇编语言翻译成二进制代码（目标文件）
		* 单个或多个目标文件链接生成可执行文件


	

