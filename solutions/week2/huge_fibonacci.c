#include <stdio.h>
#include <stdlib.h>

long int find_pisano(long int m){
	long int a=0, b=1, c, result=0, i;
	for(i=0;i<(m*m);i++){
		c = (a + b) % m;
        a = b;
        b = c;
		if(a == 0 && b == 1) result = i + 1;
	}
	return result;
}

long int huge_fibonacci(long int n, long int m){
	long int pisano = find_pisano(m), a=0, b=1, c, i;
	n = n % pisano;
	if(n<=1) return n;
	for(i=0;i<n-1;i++){
		c = (a + b) % m;
        a = b;
        b = c;
	}
	return b%m;
}

int main(){
	long int n, m, i;

	scanf("%ld %ld", &n, &m);
	printf("%ld", huge_fibonacci(n,m));
	
	return 0;
}
