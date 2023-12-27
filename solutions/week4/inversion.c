#include <stdio.h>

long long merge_sort(long long left, long long right, long long arr[], long long* p);

long long merge(long long left, long long mid, long long right, long long arr[], long long* p);

int main(){
	long long n, arr[30000], i, count=0;
	
	scanf("%lld", &n);
	
	for(i=0;i<n;i++){
		scanf("%lld", &arr[i]);
	}
	
	count = merge_sort(0, n -1, arr, &count);
	printf("\n%lld", count);
	return 0;
}

long long merge_sort(long long left, long long right, long long arr[], long long* p){
	long long mid, count = 0;
	if(left < right){
		mid = left + (right - left) / 2;
		
		count += merge_sort(left, mid, arr, p);
		count += merge_sort(mid + 1, right, arr, p);
		
		count += merge(left, mid, right, arr, p);
	}
	return count;
}

long long merge(long long left, long long mid, long long right, long long arr[], long long* p){
	long long n, m, i, j, k, count=0;
	n = mid - left + 1;
	m = right - mid;
	long long L[n], R[m];
	
	for(i=0;i<n;i++){
		L[i] = arr[left + i];
	}
	
	for(i=0;i<m;i++){
		R[i] = arr[mid + 1 + i];
	}
	
	i=0, j=0, k=left;
	while(i < n && j < m){
		if(L[i] > R[j]){
			arr[k] = R[j];
			j++;
			count += n-i;
			//(*p) += (n-i); //eðer bulunduðumuz i indexindeki L elemaný R[j] den büyükse diziler sýralý olduðundan i nin saðýndaki tüm elemanlar da R[j] den büyüktür.		
		}
		else{
			arr[k] = L[i];
			i++;
		}
		k++;
	}
	
	while(i < n){
		arr[k] = L[i];
		i++;
		k++;
	}
	
	while(j < m){
		arr[k] = R[j];
		j++;
		k++;
	}
	return count;
}
