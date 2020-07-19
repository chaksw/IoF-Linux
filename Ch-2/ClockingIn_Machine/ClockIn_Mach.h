/*
 * @Author: Runsheng WU 
 * @Date: 2020-07-18 10:56:43 
 * @Last Modified by:   Runsheng WU 
 * @Last Modified time: 2020-07-18 10:56:43 
 */


#ifndef CLOCKIN_MACH_H
#define CLOCKIN_MACH_H


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
int flags, flags2;

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


#endif