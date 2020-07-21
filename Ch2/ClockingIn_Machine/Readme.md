# 打卡机系统 - Clocking-In System
## 需求分析
打卡机系统需要实现的是在世界时钟（计时器）下通过在**一天内**输入上班打卡/下班打卡操作返回当前时间（子输出）的功能，并在**一周后**根据每天的打卡操作（输入）返回相应数据（总输入），包括迟到，早退，缺卡，周平均工作时间。

### 功能分析
根据需求，系统的运行周期为一周，而且具有以天为单位的子系统。
#### 子系统功能模块（一天）
在子系统中，需求为：
> 上班打卡，员工具有编号(首位为 1 的六位编号)，输入编号后，再 输入校验码，校验码生成规则:员工编号除首位反序，再与员工编号 求和，如:员工编号，110086，校验码为 178087。校验码错误即打卡失败。记录打卡时间 。  
> 下班打卡，只需输入员工编号即可。记录打卡时间，显示该人员今天 上班时长，如果上班时长不够，显示早退 xx 分钟。可以更新下班打 卡时间。无下班打卡显示缺卡。  
> 可以设置规定上班时长，如 9 小时。  

对应的功能的模块为：
* punch_In() :  以标准输入 员工ID 以及 校验码 作为输入，打卡成功后输出打卡时间，每次标准输入都有5次机会。
* arriveVerifie() : 以打卡上班时间作为输入，根据上班制度并结合前一天的工作时长判断是否为迟到，并将判断结果记录在周总结中，判断迟到的标准：
	* 打卡时间超过11点的，算为迟到
	* 打卡时间在10点到11点之间的，如果前一天工作超过12小时，不算迟到，否则算为迟到
* punch_Out() : 以标准输入 员工ID 作为输入，打卡成功后输出打卡时间。在更新打卡时间功能中，可以通过判断punchOut_time是否为空来判断是否能够进行打卡下班时间的更新，每次标准输入都有5次机会。
* leaveVerifie() : 以打卡上班时间以及打卡下班时间作为输入， 根据上班制度判断是否为早退，并记录当天的工作时长，并将判断结果记录和工作时长在周总结中。早退的标准：当日工作时长小于9小时，都当作早退。（即便是8:59分）
* 在一天记录完成后，刷新打卡上班和下班的时间。
* 	缺卡判断 absence_times：由于一天的有效打卡次数最多为两次，不妨设置一个数值为2的变量，在每次打卡后进行递减，并在一天结束后将缺卡次数记录到周总结中。
#### 子系统之间的切换
* 一天结束后，需要将打卡时间 reset 来保证下一天的功能不受影响。
#### 总系统
* 在总系统（一周）中，需求如下：
> 每次测试，输入指令后，开启 打卡机，打卡机开启模拟时间为:周一早上七点。程序运行结束为周五晚12点。   
> 打卡机运行结束之前，每周该打卡机会生成每周考勤周报，显示周平   
> 均上班时长，周迟到，早退，缺卡次数等。   

对应功能模块为：
* timer(): 用于实现模拟时钟，在程序运行过程中不断刷新当前时间，并在打卡操作是将当前时间输出到打卡时间中。**时钟不应受到除打卡操作外任何功能的影响导致程序进入阻塞态。** 
* 通过标准输入来激活打卡机（进入运行状态），时间初始值为周一 7:00 AM
* 以一周为单位，根据时钟时间判断打卡系统何时休眠（不可进行打卡操作），何时运行（可以进行打卡操作）
* 在根据时钟时间，在打卡机进入休眠状态前，返回并输出周总结数据。并 reset 周总结数据

#### 数据结构
* simulate Clock: 含有星期（周一  ～ 周日）、时间（时分秒）
* Weekly Resume: 含有 早退次数，迟到次数，缺卡次数，以及周工作时长。

### 难点：
1. [结构体的深拷贝和浅拷贝](https://www.cnblogs.com/qinguoyi/p/10186219.html)
2. 通过调用O_NONBLOCK开启和关闭非阻塞状态来控制程序，让时钟不受到除打卡操作外任何功能的影响导致程序进入阻塞态。** 
```
		//使用非阻塞io
    	// int flags, flags2;
    	if((flags = fcntl(STDIN_FILENO, F_GETFL, 0)) < 0)   		// 获取(F_GETFL)标准IO输入(STDIN_FILENO)目前的状态，赋给flags
    	{
        	perror("fcntl");
        	return -1;
    	}
    	flags2 = flags | O_NONBLOCK;        // O_NONBLOCK非阻塞赋给flags 
    	if(fcntl(STDIN_FILENO, F_SETFL, flags2) < 0) // 将flags = O_NONBLOCK 赋给(F_SETLF)标准IO输入，此时标准IO输入为非阻塞状态
    	{
        	perror("fcntl");
        	return -1;
    	}

	  	// 在需要进行打卡操作前，关闭非阻塞态，避免打卡时调用scanf()无法通过标准IO输入相关数据
    	// 关闭非阻塞IO
    	if(fcntl(STDIN_FILENO, F_SETFL, flags) < 0) // 将flags = O_NONBLOCK 赋给(F_SETLF)标准IO输入，此时标准IO输入为非阻塞状态
    	{
        	perror("fcntl");
        	return -1;
    	}

	  	// 在打卡操作结束后，重新开启非阻塞态，让时钟继续运行的同时能随时进行打卡操作
        //打卡操作完成后，重新开启非阻塞IO
        if(fcntl(STDIN_FILENO, F_SETFL, flags2) < 0) // 将flags = O_NONBLOCK 赋给(F_SETLF)标准IO输入，此时标准IO输入为非阻塞状态
        {
            perror("fcntl");
             eturn -1;
        }
```


## 功能模块及数据（结构）-Function&data(struct)
PS: 新增 set_fcntl(int fd, int flags) & int clear_fcntl(int fd, int flags)
```
#define WORIKING_HOURS      (9.00)             // Daliy Working Hours
#define ONE_SECOND          (278)        // define 1 hours = 6 second -> 1 seconds  = 1/3600 seconds = 278 us


// return 
// 0 success
// error
typedef struct
{
    int days_c;
    char days[20];      // punched date
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

float today_Work_Time = 0;        
float yesterday_Work_Time = 0;
int absence_times = 2;

/**
 * a simulate timer
 * @param t : current time updated
*/
int timer(simu_Clock *t);

/**
 * punchIn : verifie empolyee ID and record the punch-in time
 * @param cur_t input, current time
 * @param punchIn_time output, punch in time
 */
int punchIn(simu_Clock cur_t, simu_Clock *punch_Time);

/**
 * punchOut: display the punch-Out time and the information about daliy working
 * @param Icur_t input, current time
 * @param punchOut_time output punch out time
  */
int punchOut(simu_Clock cur_t, simu_Clock *punchOut_time);

/**
 * inverse_Id: get the last 5 ID number in format inverse
 * @param Id empolyee Id
 * @param inv_Id inverse employee Id except the frist number 
  */
void inverse_Id(int Id, int *inv_Id);

/**
 * arriveVerifie: verifie late times
 * @param punchIn_time input time of punch-In
 * @param re output Weekly resume
  */
void arriveVerifie(simu_Clock punchIn_time, Weekly_resume *re);

/**
 * leaveVerifie: verifie leave-early times and working hours
 * @param punchIn_time input1 time of punch-In
 * @param punchOut_time input1 time of punch-Out
 * @param re output Weekly resume
  */
void leaveVerifie(simu_Clock punchIn_time, simu_Clock punchOut_time, Weekly_resume *re);


/**
 * clockin_machine_handler: execute punch-In or punch-Out base on options and return punch time and the information about 
 * @param current_Time input
 * @param punchIn_time output1
 * @param punchOut_time output2
 * @param weekly_resume output3
  */
int clockin_machine_handler(simu_Clock current_Time, simu_Clock *punchIn_time, simu_Clock *punchOut_time, Weekly_resume *weekly_resume);

// Mainly program
int clockin_machine_start();

/** Set NON_BLOCK  IO
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

	






