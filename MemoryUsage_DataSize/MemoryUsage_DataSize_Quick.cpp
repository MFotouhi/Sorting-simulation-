//////////////////////////////////////////////// Memory Usage - DataSize
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <windows.h>

#include "psapi.h"
#pragma comment(Linker, "Psapi.Lib")


unsigned int input_arr[1020000];

unsigned int input_arr_1000[1000];
unsigned int input_arr_10000[10000];
unsigned int input_arr_20000[20000];
unsigned int input_arr_30000[30000];


void swap(unsigned int xp[],unsigned int ypp[])
{
    unsigned int temp = *xp;
    *xp = *ypp;
    *ypp = temp;
}



int partition (unsigned int arr1[], unsigned int low1, unsigned int high1)
{
    unsigned int pivot1 = arr1[high1];    // pivot
    unsigned int i1 = (low1 - 1);  // Index of smaller element
    
    for (unsigned int j1 = low1; j1 <= high1- 1; j1++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr1[j1] <= pivot1)
        {
            i1++;    // increment index of smaller element
            swap(&arr1[i1], &arr1[j1]);
        }
    }
    swap(&arr1[i1 + 1], &arr1[high1]);
    return (i1 + 1);
}


void quickSort(unsigned int arr1[],unsigned int low1,unsigned int high1)
{
    if (low1 < high1)
    {
        
        unsigned int pi1 = partition(arr1, low1, high1);
        
        // Separately sort elements before
        // partition and after partition

			   
        quickSort(arr1, low1, pi1 - 1);
        quickSort(arr1, pi1 + 1, high1);
        

    }
    
}




int main(){
    
    unsigned int  counter = 0;
    FILE *fp;
    char str[1020000];
    
    char* filename = "C:\\Sorting Project\\Code\\\MemoryUsage_DataSize\\Dataset4_connect.txt";
    
    fp = fopen(filename, "r");
    unsigned int array_length =0;
    
    while (fscanf(fp, "%s", str)!=EOF){
        array_length = array_length+1;
    }
    printf("array_length = %d\r\n",array_length);
    
    fp = fopen(filename, "r");
    for(unsigned int i=0;i<array_length;i++){
        fscanf(fp, "%s", str);
        input_arr[counter] = atoi(str);
        counter=counter+1;
        
    }
    fclose(fp);
    
    
    unsigned int co = 0;
    unsigned int data_size ;
    unsigned int MemoryUsage_DataSize[4]={0};
    
    int Mont_Carlo_Num = 1;
    
    PROCESS_MEMORY_COUNTERS_EX pmc1;
    PROCESS_MEMORY_COUNTERS_EX pmc2;
    for(int Mcount =0;Mcount<Mont_Carlo_Num;Mcount++){
        // printf("MontCarlo Count = %d\r\n",Mcount);
        
        ///////////////////////////////////////////////////////////////////////////////////   quickSort
        ///////////////////////////////////////////  Data Size=1000
        data_size = 1000;
        for(co=0;co<data_size;co++){
            input_arr_1000[co] = input_arr[co];
        }
        
        GetProcessMemoryInfo(GetCurrentProcess(),(PROCESS_MEMORY_COUNTERS*) &pmc1,sizeof( pmc1 ));
        quickSort(input_arr_1000, 0,data_size-1);
        GetProcessMemoryInfo(GetCurrentProcess(),(PROCESS_MEMORY_COUNTERS*) &pmc2,sizeof( pmc2 ));
        //printf(" Delta PrivateUsage : %d\n", pmc2.PrivateUsage - pmc1.PrivateUsage);
        
        MemoryUsage_DataSize[0] =MemoryUsage_DataSize[0]+ (pmc2.PrivateUsage - pmc1.PrivateUsage);
        ///////////////////////////////////////////  Data Size=10000
        data_size = 10000;
        for(co=0;co<data_size;co++){
            input_arr_10000[co] = input_arr[co];
        }
        
        quickSort(input_arr_10000, 0,data_size-1);
        GetProcessMemoryInfo(GetCurrentProcess(),(PROCESS_MEMORY_COUNTERS*) &pmc2,sizeof( pmc2 ));
        //printf(" Delta PrivateUsage : %d\n", pmc2.PrivateUsage - pmc1.PrivateUsage);
        
        MemoryUsage_DataSize[1] =MemoryUsage_DataSize[1]+ (pmc2.PrivateUsage - pmc1.PrivateUsage);
        ///////////////////////////////////////////  Data Size=20000
        data_size = 20000;
        for(co=0;co<data_size;co++){
            input_arr_20000[co] = input_arr[co];
        }
        
        quickSort(input_arr_20000, 0,data_size-1);
        GetProcessMemoryInfo(GetCurrentProcess(),(PROCESS_MEMORY_COUNTERS*) &pmc2,sizeof( pmc2 ));
       // printf(" Delta PrivateUsage : %d\n", pmc2.PrivateUsage - pmc1.PrivateUsage);
       
       MemoryUsage_DataSize[2] =MemoryUsage_DataSize[2]+ (pmc2.PrivateUsage - pmc1.PrivateUsage);
       
        ///////////////////////////////////////////  Data Size=30000
        data_size = 30000;
        for(co=0;co<data_size;co++){
            input_arr_30000[co] = input_arr[co];
        }
        
        quickSort(input_arr_30000, 0,data_size-1);
        GetProcessMemoryInfo(GetCurrentProcess(),(PROCESS_MEMORY_COUNTERS*) &pmc2,sizeof( pmc2 ));
        //printf(" Delta PrivateUsage : %d\n", pmc2.PrivateUsage - pmc1.PrivateUsage);
        

       MemoryUsage_DataSize[3] =MemoryUsage_DataSize[3]+ (pmc2.PrivateUsage - pmc1.PrivateUsage);
        
        printf("...Quick Sorting Finished\r\n");
        
        }
        
        for(int j =0;j<4;j++){
            MemoryUsage_DataSize[j] = MemoryUsage_DataSize[j]/Mont_Carlo_Num+200000;
            printf("MemoryUsage_DataSize[%d]=%d\r\n",j, MemoryUsage_DataSize[j]);
        }
        
        
    
}
