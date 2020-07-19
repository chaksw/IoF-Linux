/*
 * @Author: Runsheng WU 
 * @Date: 2020-07-16 13:34:39 
 * @Last Modified by: Runsheng WU
 * @Last Modified time: 2020-07-17 22:26:25
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


// 1.数组倒序
void inverse_array(int *array, int size);

// 2.统计标准输入字符串中有多少个大写字母、小写字母、 数字
void statistic(char *str, int len);

// 3. 找出随机数组中的最大数或最小数、计算总和、平均值
void random_array();

// 4. 求5个评分平均分
void average(float *grade, int len);

int main(int argc, char **argv)
{
    int array[] = {1,2,3,4,5,6,7,8};
    inverse_array(array, (sizeof(array)/sizeof(int)));

    char *str = (char*)malloc(20*sizeof(char));     // 初始化成动态数组
    if(str == NULL)                                 //如果malloc的返回值是NULL，说明申请不到内存
    {	
		printf("malloc failed\n");
		return 0;
	}
    scanf("%s", str);
    statistic(str, strlen(str));

    random_array();
    
    float grade[5] = {90.0, 89.0, 99.0, 91.0, 75.0};
    average(grade, sizeof(grade)/sizeof(float));

    free(str);
    str = NULL;
    return 0;
}


void inverse_array(int *array, int size)
{
    int buf = 0, l = 0;
    for (int i = 0; i < (size / 2); i++)
    {
        buf = array[size - i - 1];
        array[size - i - 1] = array[i];
        array[i] = buf;
    }

    for (int i = 0; i < size; i++)
        printf("%d   ", array[i]);
    printf("\n");
    printf("==============================================================\n");
}

void statistic(char *str, int len)
{
    int num = 0, cap = 0, low = 0;
    for (int i = 0; i < len; i++)
    {
        printf("%c", str[i]);
        if ((str[i] >= '0') && (str[i] <= '9'))
            num++;
        else if((str[i] >= 'a') && (str[i] <= 'z'))
            low++;
        else if((str[i] >= 'A') && (str[i] <= 'Z'))
            cap++;
    }
    printf("\n");
    printf("there are %d number, %d capital, %d lowercase\n", num, cap, low);
    printf("==============================================================\n");
}


void random_array()
{
    int array[10], mini = 0, aver = 0, sum = 0;
    printf("10 random value is: ");
    for (size_t i = 0; i < 10; i++)
    {
        array[i] = rand();
        printf("%d\t", array[i]);
        mini = array[0];
        sum += array[i];
        if(array[i] < mini)
            mini = array[i];
    }
    aver = sum / 10;
    printf("\n");
    printf("minimum value = %d\n", mini);
    printf("Sum of ten random values is: %d\n", sum);
    printf("Average of ten random values is: %d\n", aver);
    printf("==============================================================\n");
}

void average(float *grade, int len)
{
    float max = grade[0], min = grade[0], aver = 0, sum = 0;
    for (size_t i = 0; i < len; i++)
    {
        printf("%.2f   ", grade[i]);
        if(grade[i] > max)
            max = grade[i];
        else if(grade[i < min])
            min = grade[i];
        sum += grade[i];
    }
    aver = (sum - (max + min)) / 5;
    printf("\n");
    printf("Average is %.2f\n", aver);
}


