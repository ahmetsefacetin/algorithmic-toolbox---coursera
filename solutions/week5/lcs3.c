#include <stdio.h>


long long max(long long x, long long y, long long z){
	long long max = x;
	if(max < y) max = y;
	if(max < z) max = z;
	return max;
}

long long lcs3(long long n, long long* arr1, long long m, long long* arr2, long long l, long long* arr3){
	long long i, j, k, dist[n+1][m+1][l+1], result;
	
	for(i=0;i<=n;i++){
		for(j=0;j<=m;j++){
			for(k=0;k<=l;k++){
				if(i == 0 || j == 0 || k == 0) dist[i][j][k] = 0;
				else if(arr1[i-1] == arr2[j-1] && arr1[i-1] == arr3[k-1]){
					result = max(dist[i-1][j][k], dist[i][j-1][k], dist[i][j][k-1]);
					if(result > dist[i-1][j-1][k-1] + 1) dist[i][j][k] = result;
					else dist[i][j][k] = dist[i-1][j-1][k-1] + 1;
				}
				else{
					dist[i][j][k] = max(dist[i-1][j][k], dist[i][j-1][k], dist[i][j][k-1]);
				}
			}
		}
	}

	return dist[n][m][l];
}

int main(){
	long long n, m, l, p, arr1[100], arr2[100], arr3[100], i;
	
	scanf("%lld", &n);
	
	for(i=0;i<n;i++) scanf("%lld", &arr1[i]);
	
	scanf("%lld", &m);
	
	for(i=0;i<m;i++) scanf("%lld", &arr2[i]);
	
	scanf("%lld", &l);
	
	for(i=0;i<l;i++) scanf("%lld", &arr3[i]);
	
	printf("\n%lld", lcs3(n, arr1, m, arr2, l, arr3));
	
	return 0;
}
