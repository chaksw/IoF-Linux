# Staff Information Management - Combining with Clocking-In System
## 需求分析
之前的打卡机系统实现的是在实时功能（模拟时钟）下对打卡操作（输入ID）进行相应的判断（参数）并获得打卡时间（输出），他能完成一个打卡机该做的事（某个ID作为输入时能通过一系列判断并输出相应的输出（打卡时间）），但对于一个打卡机，它存在一个关键的问题 —— 给谁用？（OO）
而本次需求，是为了实现实现**员工考勤管理**。相当于明确了这个问题，也相当于是一个输入的扩展（将原本的“ 某个ID输入” 变为 “ 一个具体ID输入（也就是员工））

> 某公司采用了之前公司生产的打开机产品，**加入到本来的员工信息管理系统中**，现需要对员工信息管理系统基础功能进行升级，主要升级一下功能:   
> 1. 将打卡机产生的数据和员工信息绑定  
> 2. 员工原先具有以下信息:姓名，年龄，性别，工号，手机号，邮箱地 址，现需添加考勤信息。  
> 3. 每周需统计工作时长排名前三的员工(且未出现考勤异常，无迟到， 早退，旷工，缺卡等)进行奖励，对考勤异常的员工进行惩罚   

### 思路
上述的分析是从一个现有的打卡机（面向功能）能给谁用为出发点展开的，现在不妨从应用场景出发去分析（面向对象），以此为出发点的话，打卡机不过是一个应用对象的其中一个功能模块（需要变为一个库文件以便工功能的调用），而这里的应用对象就是一个公司的员工们（员工管理系统）。

> 1. 将上一任务卡升级为固定库(可采用静态库、动态库或头文件+源文   
> 件)  
> 2. 创建员工信息结构体，创建考勤信息结构体(工号，工作时长，迟到次数，早退次数，旷工次数，缺卡次数等)  
> 3. 创建员工结构体数组(假设员工20人)，打卡机运行期间，采集员工   
> 数据  
> 4. 每周五上报各员工考勤周报(写入结构体数组对应成员中)，给出每   
> 周奖励名单，每周惩罚名单，惩罚原因(如:共迟到 2 次，本周三，   
> 本周四)  

也就是说，在一个公司中，有20个员工可以使用这个打卡机功能，而且每个员工的打卡操作（输入）都会产生不同的输出（无论是以天还是以周为单位）。而最终，以20个员工的20个输出作为输入，会有一个统计性输出。
> 每周需统计工作时长排名前三的员工(且未出现考勤异常，无迟到， 早退，旷工，缺卡等)进行奖励，对考勤异常的员工进行惩罚 。  

## 功能分析
> 	个人理解：所有的程序的目的都是为了满足一个应用场景（需求），而程序就是根据需求实现的多个功能模块的一个”体“，而功能模块都是建立在两个基本东西上的——数据结构和算法（函数）。其中数据结构构成了函数的输入输出，算法构成了输入到输出之间的参数部分。  

员工信息管理本身比较核心的部分就是员工信息，对于这里，构建一个满足需求的功能，首要的是构建一个员工信息的数据结构（结构体）。这个结构体要满足对于一个员工的规范性（也就是说，适用于任何一个员工），同时要保证每个员工的独立性（结构体数组）。

### 员工结构体数组初始化
由于员工管理系统中的每一个成员（员工结构体）包含的信息比较多。我们需要定义一个函数来对20个员工进行初始化（当然，直接在结构体数组初始化时对每个员工结构体中的每个信息进行初始化也可，但我这里更喜欢调用标准输入或者文件IO），先定义一个大小为20的结构体数组，再通过标准输入（读取文件）来对每个信息进行初始化（在其中不妨加一些限定来保证每个数据的一般性）。
```
Staff Staffs[NUMBEROFSTAFF];        // 20 Staff in a company

/**
 * staffsIniit Initilize staff information of each from standard input
 * @param pStaff input pointer struct staff
  */
void staffsInit(Staff *pStaff);

```

### 结构体定义注意事项 - 字节对齐
在C语言中，结构体是种复合数据类型，其构成元素既可以是基本数据类型(如int、long、float等)的变量，也可以是一些复合数据类型(如数组、结构体、联合等)的数据单元。编译器为结构体的每个成员按照其自然边界(alignment)分配空间。各成员按照它们被声明的顺序在内存中顺序存储，第一个成员的地址和整个结构的地址相同。

2. 自然对齐的概念
对齐跟数据在内存中的位置有关。如果一个变量的内存地址正好位于它长度的整数倍，他就被称做自然对齐。比如在32位cpu下，假设一个整型变量的地址为0x00000004，那它就是自然对齐的。

3. 为什么需要定义字节对齐 - ` #pragma pack (value)`
需要字节对齐的根本原因在于CPU访问数据的效率问题。假设上面整型变量的地址不是自然对齐，比如为0x00000002，则CPU如果取它的值的话需要访问两次内存，第一次取从0x00000002-0x00000003的一个short，第二次取从0x00000004-0x00000005的一个short然后组合得到所要的数据，如果变量在0x00000003地址上的话则要访问三次内存，第一次为char，第二次为short，第三次为char，然后组合得到整型数据。而如果变量在自然对齐位置上，则只要一次就可以取出数据。
在设计不同CPU下的通信协议时，或者编写硬件驱动程序时寄存器的结构这两个地方都需要按一字节对齐。即使看起来本来就自然对齐的也要使其对齐，以免不同的编译器生成的代码不一样.

> 现代计算机中内存空间都是按照byte划分的，从理论上讲似乎对任何类型的变量的访问可以从任何地址开始，但实际情况是在访问特定类型变量的时候经常在特定的内存地址访问，这就需要各种类型数据按照一定的规则在空间上排列，而不是顺序的一个接一个的排放，这就是对齐。  
> 对齐的作用和原因：各个硬件平台对存储空间的处理上有很大的不同。一些平台对某些特定类型的数据只能从某些特定地址开始存取。比如有些架构的CPU在访问一个没有进行对齐的变量的时候会发生错误,那么在这种架构下编程必须保证字节对齐.其他平台可能没有这种情况，但是最常见的是如果不按照适合其平台要求对数据存放进行对齐，会在存取效率上带来损失。比如有些平台每次读都是从偶地址开始，如果一个int型（假设为32位系统）如果存放在偶地址开始的地方，那么一个读周期就可以读出这32bit，而如果存放在奇地址开始的地方，就需要2个读周期，并对两次读出的结果的高低字节进行拼凑才能得到该32bit数据。显然在读取效率上下降很多  

4. 如何正确处理字节对齐 - 四个基本概念
	1. 数据类型自身的对齐值：char型数据自身对齐值为1字节，short型数据为2字节，int/float型为4字节，double型为8字节 
	2. 结构体或类的自身对齐值 = 其成员中自身对齐值最大的那个值，一般为4字节
	3. 指定对齐值：#pragma pack (value) 时的指定对齐值value。
	4. 数据成员、结构体和类的有效对齐值：自身对齐值和指定对齐值中较小者，即有效对齐值=min{自身对齐值，当前指定的pack值}。
按照上面的需求，我们定义了这么一个结构体
```
typedef struct 
{
    char email[30];         // email
    char name[20];          // name
    char sexy[6];           // sexy
    int age;                // age
    int id;                 // staff Id
    int tel;                // telephone
    Weekly_resume resume;   // Clocking in Information
}Staff, Staffs[20];

其中内嵌结构体
typedef struct
{
    float aver_Work_t;          // Weekly average working time
    int late_times;             // times of late-for-work
    int le_times;               // times of leave early
    int lack_times;             // times of lack of punch
}Weekly_resume;
```

分析一下，定义的三个数组都是char类型，按照基本数据类型对齐即可，第一个对齐了后面的自然也就对齐了。而其他定义的基本数据类型为 int 和 float 为 4个字节，内嵌结构体内部也是只有int 和 float， 所以结构体的自身对齐值是4个字节，属于自然对齐位置，同时与系统默认的对齐值相同，我们不妨直接调用这个缺省值。
- - - -
### 输出输入分析
在建立好数据结构后，要实现的算法的功能就是为了能够让每一个特定输入，在打卡操作后输出对应的输出并存储在对应的结构体中。

在之前的打卡机系统中，我们对“某一个ID”的打卡操作执行了一系列算法（函数）流程，并在以天为单位输出打卡时间以及以周为单位输出（周总结），而这个输入事实上任意的，而在结合员工管理系统之后（20 名员工各自有对应的ID），这个输入就变成了一个确定的数（即以实参形式来说，它是一个被初始化的变量，以形参形式来说，除了格式要求（6位数）之外，它还必须是被初始化的多个变量中的一个（需要判断））。所以在执行打卡操作时，除了判断ID的规范性，我们还需要判断从ID是都为结构体数组中的一员。
1. 修改punch_In() punch_Out() 函数，添加关于ID是否属于员工管理系统的判断。

当输入对应的“ 某个特定ID”后，输出理所当然地需要被“特定” ，让程序表达出打卡机实现的是对20个特定数据结构的处理，而同时处理方式也是一样的，只是输入输出不同。
关于打卡机的输出，我的理解是：对于某个员工来说，以天为单位出的是当天的迟到、早退、缺卡数，以周为单位输出当周的周总结。所以我们需要修改的是所有输出为周总结的函数，让“某个输出”变为“特定的输出”。而关于打卡时间，因为打卡时间分为上班和下班，但每个员工的打卡时间都是不同的，而且每天结束后我们需要根据打卡时间计算出当天的工作时长，并最后得出每位员工一天的缺卡次数，所以打卡时间（上下班）应该作为结构体内部数据被保存并在一天结束后清零。而在关于判断迟到和早退以及缺卡次数的的三个函数中，都是以某一个员工打卡时间作为输入，周总结作为输出，这对于以一个包含了上述输入输出数据的结构体来说 ，是不合理的（无法实现特定的输入和特定的输出），所以，我们要么将函数作为以结构体作为输入输出的函数的一部分，要么将它本身的输入输出变为结构体数组。
2. 修改或删除arriveVerifie() 、leaveVerifie() 以及 clockin_machine_handler() 函数，使输出值变为对应ID的周总结数据。同时将打卡时间，相关的全局变量设为结构体数据，同时定义一个函数 resetInfor_Daliy()，在一天结束后将结构体中打卡时间，打卡次数清零（在相关数据都写进Weekly_Resume后）的数据清零 。修改后的结构体为 （为了方便初始化，将原本的用于递减的absence_times（缺卡次数） 改为 punchTimes （打卡次数）

在完成以周为单位完成每一位员工的周总结数据录入后，在最后需要根据每一位员工的周总结输出（在这里作为输入）统计出周奖励名单和乘法名单（工作时长排名前三及没出现考勤异常情况的（先决条件）员工）以及惩罚原因（出现的具体考勤异常）

3. 结合冒泡排序，输入每位员工的考勤情况，根据员工的工作时长(降序)和考勤异常次数（降序）对员工进行排序，最后再根据ID将每位员工进行重新排序（升序），以便在输出奖励和惩罚名单时调用 Staffs[]结构体数组。
```
// bubble sort according to Clocking-In situation
void bubbleSort_CI();

// // bubble sort according to working time
void bubbleSort_WT();

// bubble sort according to ID
void bubbleSort_ID();
```

4. 定义函数 resumeInfor_Weekly()，输入每位员工的考勤情况（也就是结构体数组），输出奖励和惩罚名单。并将每位员工的周总结清零.

最终员工结构体为：
```
typedef struct
{
    char email[40];         
    char name[20];          
    char sexy[8];           
    unsigned int age;                
    unsigned int id;                 
    unsigned int tel;
    unsigned int le_daliy;                  // leave early times in one day
    unsigned int late_daliy;                // late times in one day
    unsigned int punchTimes;                // punch times in one day
    float today_Work_Time;        
    float yesterday_Work_Time;
    Weekly_resume weekly_resume;            // Clocking in Information
    simu_Clock punchIn_time;
    simu_Clock punchOut_time;
    simu_Clock ClockingIn_Stuation;
}Staff;
 
```

### 重提非阻塞IO
不知是之前测试没完整还是这次修改了函数逻辑，非阻塞IO的设置和取消在测试过程中消失了，不过本来之前也是似懂非懂的。现在正好把非阻塞IO的设置和取消设置成函数，这样更方面调用。
1. 新增设置和取消非阻塞IO的函数。
```
int set_fcntl(int fd, int flags)
{
    int cur_flags;
    //使用非阻塞io
    // int flags, flags2;
    if((cur_flags = fcntl(fd, F_GETFL, 0)) < 0)   
    {
        perror("fcntl");
        return -1;
    }
    cur_flags |= flags;     
    if(fcntl(fd, F_SETFL, cur_flags) < 0) 
    {
        perror("fcntl");
        return -1;
    }
    return 0;
}


int clear_fcntl(int fd, int flags)
{
    int cur_flags;
    if((cur_flags = fcntl(fd, F_GETFL, 0)) < 0)   
    {
        perror("fcntl");
        return -1;
    }
    cur_flags &= ~flags;   
    if(fcntl(fd, F_SETFL, cur_flags) < 0) 
    {
        perror("fcntl");
        return -1;
    }
    return 0;
}

```

## 功能（函数+数据）模块
```
#define WORIKING_HOURS      (9.00)             // Daliy Working Hours
#define ONE_SECOND          (278)        // define 1 hours = 6 second -> 1 seconds  = 1/3600 seconds = 278 us
#define NUMBEROFSTAFF       (6)


// return 
// 0 success
// error
// #pragma pack(4)      // default
typedef struct
{
    char days[20];      // punched date
    int days_c;
    int hours;          // punched hours
    int minute;         // punched minute
    int seconds;        // punched second  
}simu_Clock;

typedef struct
{
    float aver_Work_t;          // Weekly average working time
    int late_times;             // times of late-for-work
    int le_times;               // times of leave early
    int lack_times;             // times of lack of punch
}Weekly_resume;

// #pragma pack(4)          // default（缺省值）
// Struct staff
typedef struct
{
    char email[40];         
    char name[20];          
    char sexy[8];           
    unsigned int age;                
    unsigned int id;                 
    unsigned long tel;
    unsigned int le_daliy;                  // leave early times in one day
    unsigned int late_daliy;                // late times in one day
    unsigned int punchTimes;                // punch times in one day
    float today_Work_Time;        
    float yesterday_Work_Time;
    Weekly_resume weekly_resume;            // Clocking in Information
    simu_Clock punchIn_time;
    simu_Clock punchOut_time;
    simu_Clock ClockingIn_Stuation;
}Staff;

Staff Staffs[NUMBEROFSTAFF];                // 20 Staff in a company
// extern Staff Staffs[NUMBEROFSTAFF];      // for test

/**
 * a simulate timer
 * @param t : current time updated
*/
int timer(simu_Clock *t);

/**
 * punchIn : verifie empolyee ID and record the punch-in time
 * @param cur_t input, current time
 * @param staffs_buf output Staffs struct array 
 */
int punchIn(simu_Clock cur_t, Staff *staffs_buf);

/**
 * punchOut: display the punch-Out time and the information about daliy working
 * @param cur_t input, current time
 * @param staffs_buf output Staffs struct array 
  */
int punchOut(simu_Clock cur_t, Staff *staffs_buf);


/**
 * punchOut: display the punch-Out time and the information about daliy working
 * @param cur_t input, current time
 * @param staffs_buf output Staffs struct array 
  */
int punchOut_Update(simu_Clock cur_t, Staff *staffs_buf);


/**
 * inverse_Id: get the last 5 ID number in format inverse
 * @param Id empolyee Id
 * @param inv_Id inverse employee Id except the frist number 
  */
void inverse_Id(int Id, int *inv_Id);

/**
 * arriveVerifie: verifie late times
 * @param s output any staff in system
  */
void arriveVerifie(Staff *s);

/**
 * leaveVerifie: verifie leave-early times and working hours
 * @param s output any staff in system
  */
void leaveVerifie(Staff *s);

// Print Menu
void printf_menu();

/**
 *  Print Weekly Resume of one staff
 * @param s output any staff in system
 */
void printf_Wr(Staff *s);

/**
 * clockin_machine_handler: execute punch-In or punch-Out base on options and return punch time and the information about 
 * @param current_Time input
 * @param staffs_buf output Staffs struct array 
  */
int clockin_machine_handler(simu_Clock current_Time, Staff *staffs_buf);

// ClockintIn mainly program
int clockin_machine_start();

// staffsIniit Initilize staff information of each from standard input
void staffsInit();

// Reset Clocking-In information of each staff
void resetInfor_Daliy();

// bubble sort of Staffs according to Clocking-In situation
void bubbleSort_CIS();

// // bubble sort of Staffs according to working time
void bubbleSort_WT();

// bubble sort of Staffs according to ID
void bubbleSort_ID();

// Resume Clocking-In information of Company in analyzing each staff
void resumeInfor_Weekly();

// Staff management mainly program
int start_staff_manager();

/** Set NON_BLOCK IO
 * @param fd API type
 * @param flags IO type
*/
int set_fcntl(int fd, int flags);

/** Clear NON_BLOCK IO
 * @param fd API type
 * @param flags IO type
*/
int clear_fcntl(int fd, int flags);

```






	
	
	
	
	