#include <stdio.h>

long long without_r(long long n, long long* w, long long W){
	long long i, j; 
	long long arr[n+1][W+1]; 
	
	for(i=0;i<=W;i++) arr[0][i] = 0; 
	//for(i=0;i<=n;i++) arr[i][0] = 0;
	
	for(i=1;i<=n;i++){
		for(j=0;j<=W;j++){
			arr[i][j] = arr[i-1][j];
			if(j >= w[i-1] && arr[i-1][j - w[i-1]] + w[i-1] > arr[i][j]){
				arr[i][j] = arr[i-1][j - w[i-1]] + w[i-1];
			}
		}
	}
	for(i=0;i<=n;i++){
		for(j=0;j<=W;j++){
			printf("%lld ", arr[i][j]);
		}
		printf("\n");
	}
	return arr[n][W];
}

long long without_r1(long long n, long long* w, long long W){
	long long i, j; 
	long long arr[W+1]; 
	
	for(i=0;i<=W;i++) arr[i] = 0;
	
	for(i=0;i<n;i++){
		for(j=W;j>=0;j--){
			if(j >= w[i] && arr[j - w[i]] + w[i] > arr[j]){
				arr[j] = arr[j - w[i]] + w[i];
			}
		}
	}
	
	return arr[W];
}

int main(){
	long long n, W, w[400], i;
	
	scanf("%lld %lld", &W, &n);
	
	for(i=0;i<n;i++) scanf("%lld", &w[i]);
	
	printf("%lld\n\n", without_r1(n, w, W));
	without_r(n,w,W);
	return 0;
}
