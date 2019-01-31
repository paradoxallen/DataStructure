#include <stdio.h>

int main(){
	int i, ans;
	char opr;
	
	scanf("%d", &ans);
	
	while((opr=getchar()) != '='){
		
		scanf("%d", &i);
		if(opr=='+'){
			ans += i;
		}
		else if(opr=='-'){
			ans -= i;
		}
		else if(opr=='*'){
			ans *= i;
		}
		else if(opr=='/'){
			if(i==0){
			printf("ERROR\n");
			return 0;
			}
			else{
				ans /= i;
			}			
		}
		else {
			printf("ERROR\n");
			return 0;
		}
	}
	
	printf("%d\n", ans);
	return 0;
} 

