#include <stdio.h>
#include <stdlib.h>


int main(){
 int V1[100];
 int V2 [200];
 int M , N;

 do{
    printf("input the size of the arry V1 : ");
    scanf("%d",&N);
 }while(N>100 && N<1);
 do{
    printf("input the size of the arry V2 : ");
    scanf("%d",&M);
 }while(M>100 && M<1);

 for(int i = 0 ; i<N ; i++){
    printf("input the %dth value of the array V1: ", i+1);
    scanf("%d",&V1[i]);
 }
 for(int i = 0 ; i<M ; i++){
    printf("input the %dth value of the array V2: ", i+1);
    scanf("%d",&V2[i]);
 }


if(M+N>200){
    printf("error");
}else{
    for(int i = 0 ; i<N ; i++){
        int j = M-1 ;
        while(V1[i]<V2[j] && j>=0){
            V2[j+1]=V2[j];
            j-- ;
        }
        V2[j+1]=V1[i] ;
        M++;
    }

    for (int i = 0; i < M; i++)
    {
     printf("%d ,",V2[i]);
    }
    


}








    return 0 ;
}