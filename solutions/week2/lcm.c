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

long long int lcm(long long int a, long long int b){
	return (a * b)/gcd(a,b);
}

int main(){
	long long int a, b;
	scanf("%lld %lld", &a, &b);
	printf("%lld", lcm(a, b));
	return 0;
}
