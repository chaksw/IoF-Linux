/*
 * @Author: Runsheng WU 
 * @Date: 2020-07-19 15:11:26 
 * @Last Modified by: Runsheng WU
 * @Last Modified time: 2020-07-19 15:11:55
 */

#include <stdio.h>

void bubbleSort(int *array, int len);

int main(int argc, char **argv)
{
    // 定义数组
    int array[] = {1, 2, 3, 7, 3, 4, 5, 3, 9, 8, 2, 7, 5, 9, 8, 7};
    bubbleSort(array, sizeof(array)/ sizeof(int));
    printf("array after bubble sort: \n");
    for (int i = 0; i < sizeof(array)/sizeof(int); i++)
        printf("%d   ",array[i]);
    printf("\n");
}

// 冒泡排序，升序
void bubbleSort(int *array, int len)
{
    int temp = 0;
    for (int i = 1; i < len; i++)
    {
        for (int k = 0; k < (len - i); k++)
        {
            // Compare
            if(array[k] > array[k+1])
            {
                // Swap
                temp = array[k];
                array[k] = array[k+1];
                array[k+1] = temp;
            }
        }
    }
}