#include <stdio.h>
#include <stdlib.h>

long binary_search(long* dizi, int n, long low, long high, long x){
	long mid = (high - low) / 2 + low;
	
	if(low > high) return (low < n && dizi[low] == x) ? low : -1;
	else if(dizi[mid] >= x) return binary_search(dizi, n, low, mid-1, x);
	else return binary_search(dizi, n, mid+1, high, x);
}

int main(){
	long *arr, i, n, m, x;
	
	scanf("%ld", &n);
	arr = (long*) malloc(n * sizeof(long));
	for(i = 0; i < n; i++) scanf("%ld", &arr[i]);
	
	scanf("%ld", &m);
	
	for(i = 0; i < m; i++){
		scanf("%ld", &x);
		printf("%ld ", binary_search(arr, n, 0, n-1, x));
	}
	
	return 0;
}

