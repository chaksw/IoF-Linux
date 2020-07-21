/*
 * @Author: Runsheng WU 
 * @Date: 2020-07-18 10:56:27 
 * @Last Modified by: Runsheng WU
 * @Last Modified time: 2020-07-21 12:17:57
 */

#include "../header/includes.h"
#include "../header/StaffInfor_Manage.h"

// For test
// Staff Staffs[NUMBEROFSTAFF] = {{"Sponge.Bob@krusty.com", "Sponge Bob", "unkown", 11, 100001, 8081, 0, 0, 0, 0, 0, 0},
//                             {"Patrick.Star@krusty.com", "Patrick Star", "unkown", 12, 100002, 8082, 0, 0, 0, 0, 0, 0},
//                             {"karbs@krusty.com", "Mr.Krabs", "unkown", 13, 100003, 8083, 0, 0, 0, 0, 0, 0},
//                             {"Squidward.Tentacles@krusty.com", "Squidward Tentacles", "unkown", 14, 100004, 8084, 0, 0, 0, 0, 0, 0},
//                             {"Sandy.Cheeks@krusty.com", "Sandy Cheeks", "unkown", 15, 100005, 8085, 0, 0, 0, 0, 0, 0},
//                             {"Tom.Kenny@krusty.com", "Tom Kenny", "unkown", 16, 100006, 8086, 0, 0, 0, 0, 0, 0}};

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


int punchIn(simu_Clock cur_t, Staff *staffs_buf)
{
    int try_Time = 5;
    int inv_Id = 0;
    int id = 0, id_code = 0;          // Id et Id code
    Staff *pStaff = staffs_buf;

    // Entre ID
    printf("Please entre your 6 number employee ID:\r\n");
    scanf("%d", &id);

    if ((id / 100000) != 1)
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
    }else
    {
        for (int i = 0; i < NUMBEROFSTAFF; i++)
        {
            if (id == pStaff->id)
            {
                inverse_Id(id, &inv_Id);        // Get the inverse Id
                // Entre ID code
                printf("Please entre your 6 number ID code:\r\n");
                scanf("%d", &id_code);
                try_Time = 5;
                while((id + (inv_Id % 100000)) != id_code)
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
                // s->punchIn_time = cur_t;
                // pStaff->punchIn_time = cur_t;
                memcpy(&(pStaff->punchIn_time), &cur_t, sizeof(cur_t));
                // memcpy(&(s->punchIn_time), &cur_t, sizeof(cur_t));
                printf("Punch succeed !\n");
                printf("Name: %s\tID: %d\n", pStaff->name, pStaff->id); 
                printf("Your punch in time is : %s  %02d:%02d:%02d\r\n", pStaff->punchIn_time.days, pStaff->punchIn_time.hours, pStaff->punchIn_time.minute, pStaff->punchIn_time.seconds);
                arriveVerifie(pStaff);
                (pStaff->punchTimes)++;
                return 0;
            }else
            {
                pStaff++;
            }
        } 
    }
    printf("Could not find a corresponding ID, Please try again later\n");
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


int punchOut(simu_Clock cur_t, Staff *staffs_buf)
{
    float min = 0;
    int try_Time = 5;
    int id = 0;         // Id
    Staff *pStaff = staffs_buf;
    // Entre ID
    printf("Please entre your 6 number employee ID:\r\n");
    scanf("%d", &id);
    
    if ((id / 100000) != 1)
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
    }else
    {
        for (int i = 0; i < NUMBEROFSTAFF; i++)
        {
            if (id == pStaff->id)
            {
                memcpy(&(pStaff->punchOut_time), &cur_t, sizeof(cur_t));
                printf("Punch succeed !\n");
                printf("Name: %s\tID: %d\n", pStaff->name, pStaff->id);
                printf("Your punch out time is : %s  %02d:%02d:%02d\r\n", pStaff->punchOut_time.days, pStaff->punchOut_time.hours, pStaff->punchOut_time.minute, pStaff->punchOut_time.seconds);
                if (pStaff->punchTimes == 1)       // have punched in 
                {
                    leaveVerifie(pStaff);
                    (pStaff->punchTimes)++; 
                }else if((pStaff->punchTimes) == 0)                      // haven't punched in
                {
                    (pStaff->punchTimes)++;
                }else
                {
                    printf("You have punched today...");
                    return 0;
                }
                return 0;
            }else
            {
                pStaff++;
            }
        } 
    }
    printf("Could not find a corresponding ID, Please try again later\n");
    return 0;
}


int punchOut_Update(simu_Clock cur_t, Staff *staffs_buf)
{
    float min = 0;
    int try_Time = 5;
    int id = 0;         // Id
    Staff *pStaff = staffs_buf;
    // Entre ID
    printf("Please entre your 6 number employee ID:\r\n");
    scanf("%d", &id);
    
    if ((id / 100000) != 1)
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
    }else
    {
        for (int i = 0; i < NUMBEROFSTAFF; i++)
        {
            if (id == pStaff->id)
            {
                if (pStaff->punchTimes == 0)
                {
                    printf("You can not upgrade punch out time cause you did not punch out/in before\n");
                    return 0;;
                }else if ((pStaff->punchTimes) == 2)
                {
                    memcpy(&(pStaff->punchOut_time), &cur_t, sizeof(cur_t));
                    leaveVerifie(pStaff);
                    printf("Upgrade punch out time succeed !\n");
                    printf("Name: %s\tID: %d\n", pStaff->name, pStaff->id);
                printf("Your punch out time is : %s  %02d:%02d:%02d\r\n", pStaff->punchOut_time.days, pStaff->punchOut_time.hours, pStaff->punchOut_time.minute, pStaff->punchOut_time.seconds);
                }else if(((pStaff->punchTimes) == 1) && (pStaff->punchIn_time.hours != 0))                      // haven't punched in
                {
                    memcpy(&(pStaff->punchOut_time), &cur_t, sizeof(cur_t));
                    printf("Upgrade punch out time succeed !\n");
                    printf("Name: %s\tID: %d\n", pStaff->name, pStaff->id);
                printf("Your punch out time is : %s  %02d:%02d:%02d\r\n", pStaff->punchOut_time.days, pStaff->punchOut_time.hours, pStaff->punchOut_time.minute, pStaff->punchOut_time.seconds);
                } 
                return 0;
            }else
            {
                pStaff++;
            }
        } 
    }
    printf("Could not find a corresponding ID, Please try again later\n");
    return 0;
}

// case for late 
//// 1: punchIn after 11AM
//// 2: punchIn after 10AM & before 11AM but did not work over 12 hours yesterday
void arriveVerifie(Staff *s)
{
    if ((s->punchIn_time.hours > 10) && (s->punchIn_time.hours < 11))
    {
        if (s->yesterday_Work_Time < 12.00)
        {
            s->weekly_resume.late_times++;
        }
    }else if (s->punchIn_time.hours > 11.00)
    {
        s->weekly_resume.late_times++;   
    }
}


void leaveVerifie(Staff *s)
{
    float min = 0;
    float hour = 0;
    hour = (s->punchOut_time.hours - s->punchIn_time.hours);
    if (s->punchOut_time.minute < s->punchIn_time.minute)
    {
        min = (float)(s->punchIn_time.minute - s->punchOut_time.minute);
        min = (60 - min) / 60;
        hour -= 1.0;
        s->today_Work_Time = hour + min;
    }else
    {
        min = (s->punchOut_time.minute - s->punchIn_time.minute);
        min /= 60;
        s->today_Work_Time += hour + min;
    }

    if (s->today_Work_Time < WORIKING_HOURS)
    {
        s->weekly_resume.le_times++;
    }
    printf("you have worked for %.2f hours today\n", s->today_Work_Time);
    s->yesterday_Work_Time = s->today_Work_Time;
    s->today_Work_Time = 0; 
}


void printf_menu()
{
    printf("Niubility Company Punched-Card Machine System\r\n");
    printf("Welcome back ! Please choose your service...\r\n");
    printf("********** 1: Punch In ***********\n");
    printf("********** 2: Punch Out **********\n");
    printf("****** 3: Upgrade Punch Out ******\n");
    printf("********** 4: Exit ***************\n");
}


void printf_Wr(Staff *s)
{
    printf("/***************************************************************************************/\n");
    printf("Name: %s\tID: %d\n", s->name, s->id);
    printf("Clocking-in report this week:\r\n");
    printf("Worked %.2f hours per day\n", s->weekly_resume.aver_Work_t);
    printf("Late for work %02d times\n", s->weekly_resume.late_times);
    printf("Leave early for work %02d time\n", s->weekly_resume.le_times);
    printf("Lack of punch for %02d times\n", s->weekly_resume.lack_times);
    printf("Your punch in time is : %s  %02d:%02d:%02d\r\n", s->punchIn_time.days, s->punchIn_time.hours, s->punchIn_time.minute, s->punchIn_time.seconds);
    printf("Your punch out time is : %s  %02d:%02d:%02d\r\n", s->punchOut_time.days, s->punchOut_time.hours, s->punchOut_time.minute, s->punchOut_time.seconds);
    printf("/***************************************************************************************/\n");
}


int clockin_machine_handler(simu_Clock current_Time, Staff *staffs_buf)
{
    int ops = 0;
    // start working 
    if(scanf("%d", &ops) >= 0)
    {   
        // 关闭非阻塞IO
        clear_fcntl(STDIN_FILENO, O_NONBLOCK);
        switch (ops)
        {
        case 1:                 // PunchIn
            {
                printf("\n");
                if (current_Time.hours > 5 && current_Time.hours < 15)
                {
                    if(punchIn(current_Time, staffs_buf) != 0)
                    {
                        // arriveVerifie(s);
                        // (s->punchTimes)++;
                        // // printf_Wr(s);
                        printf("Problem punch-in appear..\n");
                        return 1;
                    }
                }else
                {
                    printf("Current time is :%s  %02d:%02d:%02d\r\n", current_Time.days, current_Time.hours, current_Time.minute, current_Time.seconds);
                    printf("You can't punch in at the moment.\r\n");
                }
            }
            break;
        case 2:                 // PunchOut
            {   
                printf("\n");
                if (current_Time.hours > 12)
                {
                    if(0 != punchOut(current_Time, staffs_buf))
                    {
                        // leaveVerifie(s);
                        // (s->punchTimes)++;
                        printf("Problem punch-out appear..\n");
                        return 1;
                    }
                }else
                {
                    printf("Current time is :%s  %02d:%02d:%02d\r\n", current_Time.days, current_Time.hours, current_Time.minute, current_Time.seconds);
                    printf("You can't punch out at the moment.\r\n");
                }  
            }
            break;
        case 3:                 // Update PunchOut time
            {
                // timer(&current_Time);
                printf("\n");
                if (current_Time.hours > 12)
                {
                    punchOut_Update(current_Time, staffs_buf);
                }else
                {
                    printf("Current time is :%s  %02d:%02d:%02d\r\n", current_Time.days, current_Time.hours, current_Time.minute, current_Time.seconds);
                    printf("You can't punch out at the moment.\r\n");
                }  
            }
            break;
        case 4:
            printf("\n");
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
    simu_Clock current_Time = {0};
    // Staff staff = {0}, *pStaff = NULL;
    int today = 0;

    // Initilize current_Time Monday
    current_Time.days_c = 1;
    strcpy(current_Time.days, "Monday");
    today = current_Time.days_c;
    current_Time.hours  = 6;
    
    while(1)
    {
        while(1)
        {
            timer(&current_Time);       // start clock simulation
            // printf("today: %d    %d\r\n", today, current_Time.days_c);
            if (current_Time.days_c == 6 || current_Time.days_c == 7 || (current_Time.days_c == 1 && current_Time.hours < 7))
            {
                printf("\rcurrent time is :%s  %02d:%02d:%02d", current_Time.days, current_Time.hours, current_Time.minute, current_Time.seconds);
                fflush(stdout);
                // printf("\n");
                // printf("\rIs not a good time for work, enjoy your week-end !");
                // fflush(stdout);
            }else{   
                today = current_Time.days_c;
                printf("\n");
                // printf("=======================================\n");
                printf_menu();
                break;
            }
        }
        while(1)
        {
            timer(&current_Time); 
            printf("\rcurrent time is :%s  %02d:%02d:%02d", current_Time.days, current_Time.hours, current_Time.minute, current_Time.seconds);
            fflush(stdout);
            
            if(0 != clockin_machine_handler(current_Time, Staffs))
            {
                return 1;
            }
            //打卡操作完成后，重新开启非阻塞IO
            set_fcntl(STDIN_FILENO, O_NONBLOCK);

            // record the clocking-in situation of last day and refresh all the data
            if (current_Time.days_c != today)       // one day end
            {
                resetInfor_Daliy();                 // Reset Clocking-In information of each staff           
                today = current_Time.days_c;
            }

            // report weekly clocking-in in every Friday 23:30 PM
            if (current_Time.days_c == 5 && current_Time.hours == 23 && current_Time.minute == 59 && current_Time.seconds == 0)
            {
                // record the friday clocking-in situation and refresh all the data
                resetInfor_Daliy(); 
                // printf("today: %d    %d\r\n", today, current_Time.days_c);
                // today = current_Time.days_c;
                // refresh to next day
                current_Time.days_c++;
                current_Time.hours = 0;
                current_Time.minute = 0;
                // printf("today: %d    %d\r\n", today, current_Time.days_c);
                printf("\n");
                resumeInfor_Weekly();                   // Resume Clocking-In information of Company in analyzing each staff                   
                break;
            }
        }
    }
    return 0;
}


void staffsInit()
{
    Staff *pStaff = Staffs;                // Pointer to Staffs[0]
    int id = 100001, age = 0, tel = 0, k = 0;
    char name[20], email[30], sexy[6];
    for (int i = 0; i < NUMBEROFSTAFF; i++)
    {
        // for each staff
        // name
        printf("Entry your name (Chinese or English):  ");
        scanf("%s", name);
        while(strlen(name) > 20)
        {
            printf("Entry error, Excess of input length, please entry again\n");
            printf("Entry your name (Chinese or English):  ");
            scanf("%s", name);
        }
        for (k = 0; k < strlen(name); k++)
        {
            pStaff->name[k] = name[k];
        }
        // sexy
        printf("Entry your sexy (male or female)  ");
        scanf("%s", sexy);
        while(strlen(sexy) > 8)
        {
            printf("Entry error, Excess of input length, please entry again\n");
            printf("Entry your sexy (male or female)  ");
            scanf("%s", sexy);
        }
        for (k = 0; k < strlen(name); k++)
        {
            pStaff->sexy[k] = sexy[k];
        }
        // age
        printf("Entry your age:  ");
        scanf("%d", &age);
        while(age > 65 || age < 18)
        {
            printf("Entry error, inllegal age, please entry again\n");
            printf("Entry your age:  ");
            scanf("%d", &age);
        }
        pStaff->age = age;

        // telephone
        printf("Entry your tel:  ");
        scanf("%d", &tel);
        while((tel / 10000000000) != 1)
        {
            printf("Entry error, inllegal number, please entry again\n");
            printf("Entry your tel:  ");
            scanf("%d", &tel);
        }
        pStaff->tel = tel;

        // email
        printf("Entry your email:  ");
        scanf("%s", pStaff->email);
        while(strlen(email) > 40)
        {
            printf("Entry error, Excess of input length, please entry again\n");
            printf("Entry your sexy (male or female)  ");
            scanf("%s", email);
        }
        for (k = 0; k < strlen(name); k++)
        {
            pStaff->email[k] = email[k];
        }
        pStaff->id = id;
        memset(&(pStaff->punchIn_time), 0, sizeof(pStaff->punchIn_time));
        memset(&(pStaff->punchOut_time), 0, sizeof(pStaff->punchOut_time));
        memset(&(pStaff->weekly_resume), 0, sizeof(pStaff->weekly_resume));
        pStaff->today_Work_Time = 0;
        pStaff->yesterday_Work_Time = 0;
        id++;
        pStaff++;
    }
}


void resetInfor_Daliy()
{
    Staff *pStaff = Staffs;
    for (int i = 0; i < NUMBEROFSTAFF; i++)
    {
        if ((pStaff->punchTimes) == 2)
        {
            pStaff->weekly_resume.aver_Work_t += pStaff->yesterday_Work_Time;
        }
        pStaff->weekly_resume.lack_times += (2 - (pStaff->punchTimes));
        memset(&(pStaff->punchIn_time), 0, sizeof(pStaff->punchIn_time));
        memset(&(pStaff->punchOut_time), 0, sizeof(pStaff->punchOut_time));
        (pStaff->punchTimes) = 0;
        pStaff++;
    }
}


// bubble sort of Staffs according to Clocking-In situation
void bubbleSort_CIS()
{
    int times = 0, timesNext = 0;
    Staff tempStaff = {0};
    Staff *pStaff = Staffs;
    Staff *pStaffN = ++pStaff;
    for (int i = 1; i < NUMBEROFSTAFF; i++)
    {   
        times = pStaff->weekly_resume.lack_times + pStaff->weekly_resume.late_times + pStaff->weekly_resume.le_times;
        timesNext = pStaffN->weekly_resume.lack_times + pStaffN->weekly_resume.late_times + pStaffN->weekly_resume.le_times;
        for (int k = 0; k < (NUMBEROFSTAFF - i); k++)
        {
            // Compare
            if(times > timesNext)
            {
                // Swap
                tempStaff = Staffs[k];
                Staffs[k] = Staffs[k+1];
                Staffs[k+1]= tempStaff;
            }
        }
        pStaff++;
        pStaffN++;
    }
}


// bubble sort of Staffs according to working time
void bubbleSort_WT()
{
    Staff tempStaff = {0};
    Staff *pStaff = Staffs;
    Staff *pStaffN = pStaff++;
    for (int i = 1; i < NUMBEROFSTAFF; i++)
    {
        for (int k = 0; k < (NUMBEROFSTAFF - i); k++)
        {
            // Compare
            if((pStaff->weekly_resume.aver_Work_t) > (pStaffN)->weekly_resume.aver_Work_t)
            {
                // Swap
                tempStaff = Staffs[k];
                Staffs[k] = Staffs[k+1];
                Staffs[k+1]= tempStaff;
            }
        }
        pStaff++;
        pStaffN++;
    }
}


// bubble sort of Staffs according to ID
void bubbleSort_ID()
{
    Staff tempStaff = {0};
    Staff *pStaff = Staffs;
    Staff *pStaffN = pStaff++;
    for (int i = 1; i < NUMBEROFSTAFF; i++)
    {
        for (int k = 0; k < (NUMBEROFSTAFF - i); k++)
        {
            // Compare
            if((pStaff->id) > (pStaffN->id))
            {
                // Swap
                tempStaff = Staffs[k];
                Staffs[k] = Staffs[k+1];
                Staffs[k+1]= tempStaff;
            }
        }
        pStaff++;
        pStaffN++;
    }
}


void resumeInfor_Weekly()
{
    
    // Resume first
    Staff *pStaff = Staffs;
    int ci_times = 0, count = 1;
    printf("/************* Clocking-In situation of all staffs in this week ***************/\n");
    for (int i = 0; i < NUMBEROFSTAFF; i++)
    {
        printf_Wr(pStaff);
        pStaff->weekly_resume.aver_Work_t = pStaff->weekly_resume.aver_Work_t / 5;
        pStaff++;
    }

    // Gratification List
    pStaff = Staffs;
    printf("/************* The gratification list of this week ****************/\n");
    bubbleSort_WT();
    while(count < 4)
    {
        for (int i = 0; i < NUMBEROFSTAFF; i++)
        {
            ci_times = pStaff->weekly_resume.lack_times + pStaff->weekly_resume.late_times + pStaff->weekly_resume.le_times; 
            if(ci_times == 0)
            {
                printf("Number %d: \n", count);
                printf_Wr(pStaff);
                count++;
                pStaff++;
            }else
            {
                pStaff++;
            }
        }
    }
    pStaff = Staffs;

    // Penalty list
    printf("/*********** The penalty list of this week, hope your are not among.. ************/\n");
    bubbleSort_CIS();
    count = 1;
    while (count < 4)
    {
        printf("Number %d: \n", count);
        printf_Wr(pStaff);
        pStaff++;
        count++;
    }
    
    // Reset in the end
    pStaff = Staffs;
    bubbleSort_ID();
    for (int i = 0; i < NUMBEROFSTAFF; i++)
    {
        memset(&(pStaff->weekly_resume), 0, sizeof(pStaff->weekly_resume));       // refresh struct Weekly Resume before the new week
        pStaff++;
    }
}


int start_staff_manager()
{               
    staffsInit();
    set_fcntl(STDIN_FILENO, O_NONBLOCK);        // 设置非阻塞IO
    clockin_machine_start();
    return 0;
}


int set_fcntl(int fd, int flags)
{
    int cur_flags;
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