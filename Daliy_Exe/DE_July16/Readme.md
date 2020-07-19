# DE_July16
#Daliy_Exe

## 题目&Function
```
// 1.数组倒序
void inverse_array(int *array, int size);

// 2.统计标准输入字符串中有多少个大写字母、小写字母、 数字
void statistic(char *str, int len);

// 3. 找出随机数组中的最大数或最小数、计算总和、平均值
void random_array();

// 4. 求5个评分平均分
void average(float *grade);
```


## 输出结果
### inverse_array()
```
原数组：
int array[] = {1,2,3,4,5,6,7,8};

结果：
8   7   6   5   4   3   2   1 
```

### statistic()
```
输入：
123abcABC123
结果：
there are 6 number, 3 capital, 3 lowercase
```

### random_array()
```
10 random value is: 16807	282475249	1622650073	984943658	1144108930	470211272	101027544	1457850878	1458777923	2007237709	

minimum value = 16807
Sum of ten random values is: 939365451

Average of ten random values is: 93936545
```

### average()

```
数组：
float grade[5] = {90.0, 89.0, 99.0, 91.0, 75.0};

结果：
Average is 55.80
```

## 关于问题2出现断错误的分析

> ….令人很不爽的是，段错误除了只有一个简单的错误信息之外，没有任何额外的提示，并且有的段错误不是每次都会出现。  


### 问题2函数 - void statistic(char **str*, int *len*)
```
void statistic(char *str, int len)
{
    int num = 0, cap = 0, low = 0;
    for (int i = 0; i < len; i++)
    {
        if ((str[i] >= '0') && (str[i] <= '9'))
            num++;
        else if((str[i] >= 'a') && (str[i] <= 'z'))
            low++;
        else if((str[i] >= 'A') && (str[i] <= 'Z'))
            cap++;
    }
    printf("there are %d number, %d capital, %d lowercase\n", num, cap, low);
    printf("==============================================================\n");

```

### main函数
```
int main(int argc, char **argv)
{
    char *str;
    scanf("%s", str);
    // getchar();
    // printf("%lu", strlen(str));
    statistic(str, strlen(str));
}
```


### 分析
[关于段错误的解释和分析手段](https://blog.csdn.net/YSBJ123/article/details/50035169)
在gdb模式下运行代码出现如下错误：
```
Program received signal SIGSEGV, Segmentation fault.
0x00007ffff7a5104d in _IO_vfscanf_internal (s=<optimized out>, format=<optimized out>, 
    argptr=argptr@entry=0x7fffffffdba0, errp=errp@entry=0x0) at vfscanf.c:1103
**1103	vfscanf.c: No such file or directory.**
```
- - - -

虽然不是很懂，但是根据给出的关于vfcanf的信息基本可以推出段错误跟scanf()函数的调用错误有关系。
一般来说，只要按规定格式调用scanf()函数，它是不会出什么问题的。scanf()除获取数组外的基本用法可以看[这里](http://c.biancheng.net/cpp/html/34.html)，而scanf()函数的调用错误原因不妨尝试通过分析函数体内调用的地址是否发生了问题来确定。**系统地址和段错误的关系其实蛮大的。**

引用导致段错误的一般原因（英语显得高大上（俗气）一些）：

> A segmentation fault (often shortened to segfault) is a particular error condition that can occur during the operation of computer software. In short, a segmentation fault occurs when a program attempts to access a memory location that it is not allowed to access, or attempts to access a memory location in a way that is not allowed (ε.g., attempts to write to a read-only location, or to overwrite part of the operating system). Systems based on processors like the Motorola 68000 tend to refer to these events as Address or Bus errors.  
>   
> Segmentation is one approach to memory management and protection in the operating system. It has been superseded by paging for most purposes, but much of the terminology of segmentation is still used, « segmentation fault » being an example. Some operating systems still have segmentation at some logical level although paging is used as the main memory management policy.  
>   
> On Unix-like operating systems, a process that accesses invalid memory receives the SIGSEGV signal. On Microsoft Windows, a process that accesses invalid memory receives the STATUS_ACCESS_VIOLATION exception.  

**一句话总结的话：段错误就是程序的运行过程中，访问了不该访问的地址。**这个被访问的地址在Linux C语言中一般体现为：
1. 可能本身不存在（NULL指针值 ）
2. 可能是受系统保护的地址（零指针常量：0、0L、’\0’、3 - 3、0 * 17 （它们都是“integer constant expression”）以及 (void*)0 ）
3. 可能是只读的内存地址。（常量：关于常量的具体解释，额外总结中有提）。
	**上述的解释只限于目前理解的能力范围，往后应得到补充**

如此，段错误在C语言中与指针息息相关。接下来不妨从定义的指针中进行分析。

程序中，为了通过标准输入获得一个位置大小的字符串，定义了str指针，希望能够通过这个指针构建一个数组。但是指针根据定义的形式，在程序运行中会导致不同的结果（可以查看[链接](https://blog.csdn.net/YSBJ123/article/details/50035169)了解一下，也可以看下面的额外总结）
	程序中，我定义了`char *str;`，很明显，指针被定义成野指针了（没有被正确的赋予大小或者具体的变量值）
	关于指针的更多解释可以看[这里](http://c.biancheng.net/cpp/html/34.html)。

既然现在错误地定义了一个野指针，不妨思考下关于如何正确定义指针，一般而言，指针应该如何定义要结合功能需要来分析，但现在功能需求已经确定了（指向一个未知大小数组-很明显要用malloc()..），不妨拓展下思路，不妨在这里结合下由于指针而出现的段错误进行分析：那么我们之前定义的野指针什么原因导致了段错误
1. 可能本身不存在（NULL指针值 ） **不是**
2. 可能是受系统保护的地址（零指针常量：0、0L、’\0’、3 - 3、0 * 17 （它们都是“integer constant expression”）以及 (void*)0 ） **不是**
3. 可能是只读的内存地址。（常量：关于常量的具体解释，额外总结中有提） **好像也不是**
	
	………
### 野指针
先给出野指针的定义（在额外总结中也可看到）：
野指针。也指针不是NULL指针，是指向“垃圾”内存的指针，它的出现原因主要有两个：
1. 指针没有被初始化
2. 指针p被free之后，没有设置为NULL
3. 指针操作超过了变量的作用范围（给指针赋值时，赋值量超过了指针本身的指向范围）
那么：
1. 我定义的指针被初始化了吗？初始化了，通过scanf()调取标准输入的字符串
2. 被free后，设置成NULL了吗？没有malloc哪来的free
3. **给指针赋值时，赋值量超过了指针本身的指向范围了吗 超！过！了！**
**所以总结来说，我定义了一个指针，这个指针大小为4个字节，他的作用范围是1个字节（指向一个char类型数据），但我需要给它一个字符串，所以它变成了一个野指针。这个指针在通过scanf()方位标准输入的字符串（地址）时，超过了它本身的作用范围（访问了不该访问的地址），所以出现了段错误**

### 解决方案
知道错误原因之后，接下来找解决办法（其实就是用malloc()…）：多想一些，为什么不能定义一个NULL指针（虽然很明显不行）？既然这里不能用NULL指针，那么什么时候应该定义一个NULL指针？
继续引用：
> 系统保证**空指针不指向任何实际的对象或者函数。反过来说，任何对象或者函数的地址都不可能是空指针**。  

也就是说，定义一个空指针的目的是为了保证这个被定义为NULL的指针不会成为一个野指针。而当我们需要用一个指针来在后续操作中指向任意一个具有确定大小的数据时，我们都不妨先定义一个NULL指针，其实在结构体的调用和链表的使用中，空指针的使用十分常见。

回到正题，用malloc定义指针来调用动态内存，定义一个动态大小的指针来指向未知大小的数组。关于malloc的使用和意义在额外总结的堆空间部分有解释。

更改后的代码
```
int main(int argc, char **argv)
{
    char *str = (char*)malloc(20*sizeof(char));     // 初始化成动态数组
    if(str == NULL)                                 //如果malloc的返回值是NULL，说明申请不到内存
    {   
        printf("malloc failed\n");
        return 0;
    }
    scanf("%s", str);
    statistic(str, strlen(str));


    free(str);
    str = NULL;
    return 0;
}
```

至此，问题分析完毕。


### 额外总结 - 内存分布
C/C++ 定义了 内存分布 - 代码空间、全局变量与静态变量区、栈空间、堆空间
* 静态存储区 存放全局变量和静态变量，只读空间、代码段）：存储在系统运行之前就分配的数据，生存周期最长
* 栈空间：存储局部变量的空间，能提供出栈、入栈的操作，对临时变量进行替换，会在函数运行时在栈空间上将函数内局部变量进行创建和存储，并调用内部存储的变量，函数一旦返回，就释放不再存在。**ps:C++中的类存储在栈空间中的**
* 堆空间：动态内存空间，运行时可以自由、自我管理分配和释放的空间，生存周期是由程序猿来决定，用malloc申请堆空间，free进行内存释放
	* mallc函数本身并不识别要申请的内存是什么类型，只关系内存的总字节数
	* malloc申请到的是一块连续的内存，有时可能申请到比所需内存更大的内存空间，有时会申请不到，直接返回NULL
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

* 在函数中建立的动态对象在函数返回后仍可使用，我们将这个动态对象所在的空间称为堆空间的自由空间。所以需要在在函数内部堆建立的动态对象进行释放，在函数外释放是很容易失控的是，往往会出错。
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

* 野指针。也指针不是NULL指针，是指向“垃圾”内存的指针，它的出现原因主要有三个：
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

