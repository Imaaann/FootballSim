#include <stdio.h>

int main() {
    int arr[]={1,2,3,4,5,6,7,8,9,10,11,12};
    int t , i=0,w;
    scanf("%d",&t);
    while(i<=11 && arr[i] != t){
        i++;
    }
    if (i > 11) {
        printf("Value not found\n");
    } 
    else { 
        printf("We found the index at %d\n",i);
    }
    printf("Press any key to continue");
    scanf("%d",&w);
return 0;    
    }