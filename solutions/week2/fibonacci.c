#include <stdio.h>
#include <stdlib.h>

long long int fibonacci(long long int n){
	long long int a=0, b=1, c, i;
	if(n <= 1) return n;
	for(i=0;i<n-1;i++){
		c=a+b;
		a=b;
		b=c;
	}
	return c;
}

int main(){
	long long int n;
	scanf("%lld", &n);
	printf("%lld", fibonacci(n));
	return 0;
}
