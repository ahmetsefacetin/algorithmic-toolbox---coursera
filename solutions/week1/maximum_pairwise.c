#include<stdio.h>
#include<stdlib.h>

int main(){
	long long int i, n = 10, x, max1= -1, max2 = -1;
	
	scanf("%lld", &n);
	
	for(i=0;i<n;i++){
		scanf("%lld", &x);
		if(x > max2 && x > max1){
			max2 = max1;	
			max1 = x;
		}
		else if(x > max2) max2 = x;
	}
	printf("%lld", max1 * max2);
	return 0;
}
