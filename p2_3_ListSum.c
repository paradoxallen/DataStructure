#include <stdio.h>
#include <math.h>

#define MAX_N 100000

int main(void){
    int A, N, i, S, r=0;
    int arr[MAX_N+1];
    scanf("%d%d", &A, &N);
    if(N==0){
        printf("0");
        return 0;
    }
    for(i=0; i<N; i++){ /*���м�����Ȩֵ��ͬ��λ��ͣ���λ���λ��λ*/
        S = A*(N-i)+r;
        arr[i] = S%10;
        r = S/10;
    }//�����λ����
    if(r)
        arr[i] = r;
    else
        i--;
    for(;i>=0; i--){
        printf("%d", arr[i]);
    }
    
    return 0;
}
