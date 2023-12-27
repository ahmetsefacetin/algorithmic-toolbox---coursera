#include <stdio.h>

void merge(long left, long mid, long right, long arr[]){
	long n, m, i, j, k;
	n = mid - left + 1;
	m = right - mid;
	long L[n], R[m];
	
	for(i=0;i<n;i++){
		L[i] = arr[left + i];
	}
	
	for(i=0;i<m;i++){
		R[i] = arr[mid + 1 + i];
	}
	
	i=0, j=0, k=left;
	while(i < n && j < m && L[n-1] > R[j]){
		if(L[i] > R[j]){
			arr[k] = R[j];
			j++;
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
}

void merge_sort(long left, long right, long arr[]){
	long mid;
	if(left < right){
		mid = left + (right - left) / 2;
		
		merge_sort(left, mid, arr);
		merge_sort(mid + 1, right, arr);
		
		merge(left, mid, right, arr);
	}
}

int major(long* arr, long n){
	long count = 1, i=0, j;
	
	for(i=0;i<n;i++){
		if(arr[i] == arr[i+1]) count++;
		else count = 1;
		if(count > n/2) return 1;
	}
	return 0;
}

int main(){
	long arr[100000], i, n;
	
	scanf("%ld", &n);
	
	for(i=0;i<n;i++) scanf("%ld", &arr[i]);
	
	merge_sort(0, n-1, arr);
	
	printf("%d", major(arr, n));
	return 0;
}
