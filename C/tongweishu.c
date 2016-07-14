#include "stdio.h"

void print_arr(int *arr, int arr_length);

int main(void)
{
    const int MAX = 100;
    int arr[MAX];

    int i = 0, j = 0;
    for(i = 1; i < 1000 ; i++) {
	if (i < 10){
	    if ( i == ((i * i) % 10) )
		arr[j++] = i;
	}
	else if (i < 100){
	    if ( i == ((i * i) % 100))
		arr[j++] = i;
	}
	else if ( i < 1000) {
	    if ( i == ((i * i) % 1000))
		arr[j++] = i;
	}
    }

    
    print_arr(arr, j);

    return 0;
    
}

void print_arr(int *arr, int arr_length)
{
    int i = 0;
    for(i = 0; i < arr_length; i++)
    {
	printf("%d\t", arr[i]);
	if ( i%4 == 0)
	    putchar('\n');
    }
    putchar('\n');
}
