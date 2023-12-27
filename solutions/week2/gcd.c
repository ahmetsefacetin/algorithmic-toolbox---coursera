#include <stdio.h>
#include <stdlib.h>

long long int gcd(long long int a, long long int b){
	
	while(a != 0 && b != 0){
		if(a > b) a = a % b;
		else b = b % a;
	}
	if(a) return a;
	else return b;
}

int main(){
	long long int a, b;
	scanf("%lld %lld", &a, &b);
	printf("%lld", gcd(a, b));
	return 0;
}
