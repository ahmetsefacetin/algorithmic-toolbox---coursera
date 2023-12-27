#include <stdio.h>
#include <stdlib.h>

int fibonacci_last_digit(long long int n){
	long long int a=0, b=1, c, i;
	if(n <= 1) return n;
	for(i=0;i<n-1;i++){
		c=a+b;
		a = b % 10;
		b = c % 10;
	}
	return c % 10;
}

int main(){
	long long int n;
	scanf("%lld", &n);
	printf("%lld", fibonacci_last_digit(n));
	return 0;
}
