#include <stdio.h>
#include <stdlib.h>

long binary_search(long* dizi, long low, long high, long x){
	long mid = (high - low) / 2 + low;
	
	if(low > high) return -1;
	
	if(dizi[mid] == x) return mid;
	
	else if(dizi[mid] > x) return binary_search(dizi, low, mid-1, x);
	else return binary_search(dizi, mid+1, high, x);
}

int main(){
	long *arr, i, j, n, m, x;
	
	scanf("%ld", &n);
	arr = (long*) malloc(n * sizeof(long));
	for(i=0;i<n;i++) scanf("%ld", &arr[i]);
	
	scanf("%ld", &m);
	
	for(i=0;i<m;i++){
		scanf("%ld", &x);
		printf("%ld ", binary_search(arr, 0, n-1, x));
	}
	
	return 0;
}
