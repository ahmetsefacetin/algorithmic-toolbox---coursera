#include <stdio.h>

long long min(long long x, long long y, long long z){
	long long min = x;
	if(min > y) min = y;
	if(min > z) min = z;
	return min;
}

long long edit_dist(long long n, char* str1, long long m, char* str2){
	long long i, j, dist[n+1][m+1];
	
	for(i=0;i<=n;i++) dist[i][0] = i;
	for(i=0;i<=m;i++) dist[0][i] = i;
	
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			if(str1[i-1] == str2[j-1]){
				dist[i][j] = min(dist[i][j-1] + 1, dist[i-1][j] + 1, dist[i-1][j-1]);
			}
			else{
				dist[i][j] = min(dist[i][j-1] + 1, dist[i-1][j] + 1, dist[i-1][j-1] + 1);
			}
		}
	}
	
	return dist[n][m];
}

int main(){
	long long n, m;
	char str1[100], str2[100];
	
	scanf("%s", str1);
	scanf("%s", str2);
	
	while(str1[n++]);
	while(str2[m++]);
	
	printf("%lld", edit_dist(n-1, str1, m-1, str2));
	
	return 0;
}
