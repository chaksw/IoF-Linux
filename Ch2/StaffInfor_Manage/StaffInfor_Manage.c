/*
 * @Author: Runsheng WU 
 * @Date: 2020-07-18 10:56:27 
 * @Last Modified by: Runsheng WU
 * @Last Modified time: 2020-07-18 18:04:02
 */

#include "includes.h"
#include "ClockingIn_Machine/ClockIn_Mach.h"

// Struct staff
typedef struct 
{
    char name[20];          // name
    char sexy[6];           // sexy
    char email[30];         // email
    int age;                // age
    int id;                 // staff Id
    int tel;                // telephone
    Weekly_resume resume;   // Clocking in Information
}Staff;


int main(int argc, char **argv)
{
    //使用非阻塞io
    // int flags, flags2;
    if((flags = fcntl(STDIN_FILENO, F_GETFL, 0)) < 0)   // 获取(F_GETFL)标准IO输入(STDIN_FILENO)目前的状态，赋给flags
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
    clockin_machine_start();
    return 0;
}

