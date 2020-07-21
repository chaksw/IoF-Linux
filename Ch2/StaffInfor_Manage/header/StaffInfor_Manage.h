/*
 * @Author: Runsheng WU 
 * @Date: 2020-07-18 10:56:43 
 * @Last Modified by: Runsheng WU
 * @Last Modified time: 2020-07-21 11:57:54
 */


#ifndef STAFFINFOR_MANAGE
#define STAFFINFOR_MANAGE


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
    unsigned int tel;
    float today_Work_Time;        
    float yesterday_Work_Time;
    unsigned int punchTimes;
    Weekly_resume weekly_resume;           // Clocking in Information
    simu_Clock punchIn_time;
    simu_Clock punchOut_time;
}Staff;

Staff Staffs[NUMBEROFSTAFF];        // 20 Staff in a company
// extern Staff Staffs[NUMBEROFSTAFF];    // for test

/**
 * a simulate timer
 * @param t : current time updated
*/
int timer(simu_Clock *t);

/**
 * punchIn : verifie empolyee ID and record the punch-in time
 * @param cur_t input, current time
 * @param punchIn_time output, punch in time
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

#endif