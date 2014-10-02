#include <stdio.h>
#include <stdlib.h>

int *array;

int cmp(const void *a, const void *b){
    int ia = *(int *)a;
    int ib = *(int *)b;
    return array[ia] < array[ib] ? -1 : array[ia] > array[ib];
}

int main(void){
    int data[] ={ 5,4,1,2,3,3 };
    int size = sizeof(data)/sizeof(*data);
    int index[size];//use malloc to large size array
    int i;

    for(i=0;i<size;i++){
        index[i] = i;
    }
    array = data;
    qsort(index, size, sizeof(*index), cmp);
    printf("\n\ndata\tindex\n");
    for(i=0;i<size;i++){
        printf("%d\t%d\n", data[index[i]], index[i]);
    }
    return 0;
}
