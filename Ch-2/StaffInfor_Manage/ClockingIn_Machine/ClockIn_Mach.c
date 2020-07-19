/*
 * @Author: Runsheng WU 
 * @Date: 2020-07-12 19:55:22 
 * @Last Modified by: Runsheng WU
 * @Last Modified time: 2020-07-18 10:53:02
 */

#include "includes.h"
#include "ClockIn_Mach.h"


int timer(simu_Clock *t)
{
    usleep(ONE_SECOND);
    // fflush(stdout);
    t->seconds++;
    if (t->seconds == 60)
    {
        t->minute++;
        t->seconds = 0;
    }
    if (t->minute == 60)
    {
        t->hours++;
        t->minute = 0;
    }
    if (t->hours == 24)
    {
        t->days_c++;
        t->hours = 0;
    }
    if (t->days_c == 8)
    {
        t->days_c = 1;
    }
    switch (t->days_c)
    {
        case 1:
            strcpy(t->days, "Mon");
            break;
        case 2:
            strcpy(t->days, "Tue");
            break;
        case 3:
            strcpy(t->days, "Wed");
            break;
        case 4:
            strcpy(t->days, "Thu");
            break;
        case 5:
            strcpy(t->days, "Fri");
            break;
        case 6:
            strcpy(t->days, "Sat");
            break;
        case 7:
            strcpy(t->days, "Sun");
            break;
        default:
            break;
    }
    return 0; 
}


int punchIn(simu_Clock cur_t ,simu_Clock *punch_Time)
{
    int try_Time = 5;
    int inv_Id = 0;
    int id = 0, id_code = 0;          // Id et Id code
    

    // Entre ID
    printf("Please entre your 6 number employee ID:\r\n");
    scanf("%d", &id);

    while ((id / 100000) != 1)
    {
        if (try_Time != 0)
        {
            printf("Invalid ID, please try again, you still have %d times..\r\n", try_Time--);
            
            scanf("%d", &id);
        }else
        {
            printf("Invalid ID, please try again later or contact administration.\r\n");
            return 0;
        }
    }

    inverse_Id(id, &inv_Id);        // Get the inverse Id
    // Entre ID code
    printf("Please entre your 6 number ID code:\r\n");
    scanf("%d", &id_code);
    try_Time = 5;
    while(id + (inv_Id % 100000) != id_code)
    {
        
        if (try_Time != 0)
        {
            printf("Wrong ID code, please try again,, you still have %d times..\r\n", --try_Time);
            scanf("%d", &id_code);
        }else
        {
            printf("Invalid ID code, please try again later or contact administration.\r\n");
            return 0;
        }
        
    }
    
    *punch_Time = cur_t;
    printf("Punch succeed, Your punch time is : %s  %02d:%02d:%02d\r\n", punch_Time->days, punch_Time->hours, punch_Time->minute, punch_Time->seconds);
    return 0;
}


void inverse_Id(int Id, int *inv_Id)
{
    int i = 100000;
    int Id_buf = Id % i;       // get the last 5 number
    // printf("%d\n", Id_buf);
    while (i > 0)
    {
        i /= 10;
        *inv_Id += (Id_buf % 10) * i;
        Id_buf /= 10;
    }
    // printf("%d\n", *inv_Id);
}


int punchOut(simu_Clock cur_t, simu_Clock *punchOut_time)
{
    int try_Time = 5;
    int id = 0;         // Id

    // Entre ID
    printf("Please entre your 6 number employee ID:\r\n");
    scanf("%d", &id);

    while ((id / 100000) != 1)
    {
        if (try_Time != 0)
        {
            printf("Invalid ID, please try again, you still have %d times..\r\n", --try_Time);
            scanf("%d", &id);
        }else
        {
            printf("Invalid ID, please try again later or contact administration.\r\n");
            return 0;
        }
    }
    *punchOut_time = cur_t;
    printf("Punch succeed, Your punch time is : %s  %02d:%02d:%02d\r\n", punchOut_time->days, punchOut_time->hours, punchOut_time->minute, punchOut_time->seconds);
    return 0;    
}

// case for late 
//// 1: punchIn after 11AM
//// 2: punchIn after 10AM & before 11AM but did not work over 12 hours yesterday
void arriveVerifie(simu_Clock punchIn_time, Weekly_resume *wr)
{
    if ((punchIn_time.hours > 10) && (punchIn_time.hours < 11))
    {
        if (yesterday_Work_Time < 12.00)
            wr->late_times++;
    }else if (punchIn_time.hours > 11)
        wr->late_times++;   
}


// case for leave-early: today's working time < 9 hours
// case for over time: today's workng time > 12 hous;
void leaveVerifie(simu_Clock punchIn_time, simu_Clock punchOut_time, Weekly_resume *re)
{
    float min = 0;
    today_Work_Time = (punchOut_time.hours - punchIn_time.hours);
    if (punchOut_time.minute - punchOut_time.minute < 0)
    {
        min = (punchOut_time.minute + punchOut_time.minute);
        min /= 100;
        today_Work_Time += min;
        today_Work_Time--;
    }else
    {
        min = (punchOut_time.minute - punchOut_time.minute);
        min /= 100;
        today_Work_Time += min;
    }
    if (today_Work_Time < WORIKING_HOURS)
        re->le_times++;
    printf("you have worked for %.2f hours today\n", today_Work_Time);
    yesterday_Work_Time = today_Work_Time;
    today_Work_Time = 0; 
}


void print_menu()
{
    printf("Niubility Company Punched-Card Machine System\r\n");
    printf("Welcome back ! Please choose your service...\r\n");
    printf("********** 1: Punch In ***********\n");
    printf("********** 2: Punch Out **********\n");
    printf("****** 3: Upgrade Punch Out ******\n");
    printf("********** 4: Exit ***************\n");
}


void print(Weekly_resume wr)
{
    printf("Here is your clocking-in repoet this week, check it out !\r\n");
    printf("In this week, your had: \r\n");
    printf("worked %.2f hours per day\n", wr.aver_Work_t);
    printf("late for work %02d times\n", wr.late_times);
    printf("leave early for work %02d time\n", wr.le_times);
    printf("Lack of punch for %02d times\n", wr.lack_times);
}


int clockin_machine_handler(simu_Clock current_Time, simu_Clock *punchIn_time, simu_Clock *punchOut_time, Weekly_resume *weekly_resume)
{
    int ops = 0;
    // start working
    
    if(scanf("%d", &ops) >= 0)
    {   
        // 关闭非阻塞IO
        if(fcntl(STDIN_FILENO, F_SETFL, flags) < 0) // 将flags = O_NONBLOCK 赋给(F_SETLF)标准IO输入，此时标准IO输入为非阻塞状态
        {
            perror("fcntl");
            return -1;
        }
        switch (ops)
        {
        case 1:
            {
                // timer(&current_Time);
                if (current_Time.hours > 5 && current_Time.hours < 15)
                {
                    if(0 == punchIn(current_Time, punchIn_time))
                    {
                        arriveVerifie(*punchIn_time, weekly_resume);
                        absence_times--;
                    }else
                    {
                        printf("Problem PunchIn appear..\n");
                        return 1;
                    }
                }else
                {
                    printf("current time is :%s  %02d:%02d:%02d\r\n", current_Time.days, current_Time.hours, current_Time.minute, current_Time.seconds);
                    printf("your can't punch in at the moment.\r\n");
                }
            }
            break;
        case 2:
            {   
                // timer(&current_Time);
                if (current_Time.hours > 12)
                {
                    if (absence_times == 1)       // have punched in 
                    {
                        if(0 == punchOut(current_Time, punchOut_time))
                        {
                            leaveVerifie(*punchIn_time, *punchOut_time, weekly_resume);
                            absence_times--;
                        }else
                        {
                            printf("Problem PunchOut appear..\n");
                            return 1;
                        }
                        
                    }else if(absence_times == 2)                      // haven't punched in
                    {
                        if(0 == punchOut(current_Time, punchOut_time))
                            absence_times--;
                        else
                        {
                            printf("Problem PunchOut appear..\n");
                            return 1;
                        } 
                    }else
                    {
                        printf("your have punched today...");
                        break;
                    }
                    
                }else
                {
                    printf("current time is :%s  %02d:%02d:%02d\r\n", current_Time.days, current_Time.hours, current_Time.minute, current_Time.seconds);
                    printf("you can't punch out at the moment.\r\n");
                }  
            }
            break;
        case 3:
            {
                // timer(&current_Time);
                if (punchOut_time->hours == 0)
                {
                    printf("you can not upgrade punch out time cause you did not punch out before\n");
                    break;
                }else if (current_Time.hours > 12)
                {
                    if (absence_times == 0)
                    {
                        if(0 == punchOut(current_Time, punchOut_time))
                        {
                            leaveVerifie(*punchIn_time, *punchOut_time, weekly_resume);
                            printf("Upgrade punch out time succeed !\n");
                        }
                    }else if(absence_times == 1)                      // haven't punched in
                    {
                        if(0 == punchOut(current_Time, punchOut_time))
                            printf("Upgrade punch out time succeed !\n");
                    } 
                }else
                {
                    printf("current time is :%s  %02d:%02d:%02d\r\n", current_Time.days, current_Time.hours, current_Time.minute, current_Time.seconds);
                    printf("you can't punch out at the moment.\r\n");
                }  
            }
            break;
        case 4:
            exit(0);
            // return 0;
            break;
        default:
            break;
        }
    }
    return 0;
}


int clockin_machine_start()
{
    simu_Clock current_Time = {0}, punchIn_time = {0}, punchOut_time = {0};
    Weekly_resume weekly_resume = {0};
    int today = 0;
    // int tomorrow = 0;
    // Initilize current_Time Monday
    current_Time.days_c = 1;
    strcpy(current_Time.days, "Monday");
    today = current_Time.days_c;
    current_Time.hours  = 0;
    
    while(1)
    {
        while(1)
        {
            timer(&current_Time);       // start clock simulation
            // printf("today: %d    %d\r\n", today, current_Time.days_c);
            if (current_Time.days_c == 6 || current_Time.days_c == 7 || (current_Time.days_c == 1 && current_Time.hours < 7))
            {
                memset(&weekly_resume, 0, sizeof(weekly_resume));       // refresh struct Weekly Resume before the new week
                printf("\rcurrent time is :%s  %02d:%02d:%02d", current_Time.days, current_Time.hours, current_Time.minute, current_Time.seconds);
                fflush(stdout);
                // printf("\n");
                // printf("\rIs not a good time for work, enjoy your week-end !");
                // fflush(stdout);
            }else{   
                today = current_Time.days_c;
                printf("\n");
                printf("=======================================\n");
                print_menu();
                break;
            }
        }
        while(1)
        {
            timer(&current_Time); 
            printf("\rcurrent time is :%s  %02d:%02d:%02d", current_Time.days, current_Time.hours, current_Time.minute, current_Time.seconds);
            fflush(stdout);
            
            if(0 != clockin_machine_handler(current_Time, &punchIn_time, &punchOut_time, &weekly_resume))
                return 1;
            //打卡操作完成后，重新开启非阻塞IO
            if(fcntl(STDIN_FILENO, F_SETFL, flags2) < 0) // 将flags = O_NONBLOCK 赋给(F_SETLF)标准IO输入，此时标准IO输入为非阻塞状态
            {
                perror("fcntl");
                return -1;
            }
            // record the clocking-in situation of last day and refresh all the data
            if (current_Time.days_c != today)       // one day end
            {
                if (absence_times == 0)
                {
                    weekly_resume.aver_Work_t += yesterday_Work_Time;
                }
                weekly_resume.lack_times += absence_times;
                memset(&punchIn_time, 0, sizeof(punchIn_time));
                memset(&punchOut_time, 0, sizeof(punchOut_time));
                absence_times = 2;
                today = current_Time.days_c;
            }
            // report weekly clocking-in in every Friday 23:30 PM
            if (current_Time.days_c == 5 && current_Time.hours == 23 && current_Time.minute == 59 && current_Time.seconds == 0)
            {
                // record the friday clocking-in situation and refresh all the data
                if (absence_times == 0)
                {
                    weekly_resume.aver_Work_t += yesterday_Work_Time;
                }
                weekly_resume.lack_times += absence_times;
                memset(&punchIn_time, 0, sizeof(punchIn_time));
                memset(&punchOut_time, 0, sizeof(punchOut_time));
                absence_times = 2;
                // printf("today: %d    %d\r\n", today, current_Time.days_c);
                // today = current_Time.days_c;
                // refresh to next day
                current_Time.days_c++;
                current_Time.hours = 0;
                current_Time.minute = 0;
                // printf("today: %d    %d\r\n", today, current_Time.days_c);
                weekly_resume.aver_Work_t = weekly_resume.aver_Work_t / 5;
                printf("\n");
                print(weekly_resume);
                break;
            }
        }
    }
    return 0;
}