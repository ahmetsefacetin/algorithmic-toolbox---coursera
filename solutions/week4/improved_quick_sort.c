#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long rand_pivot(long long first, long long last){
	return (rand() % (last - first + 1)) + first;
}

long long pivot(long long* arr, long long n, long long first, long long last){
	long long i, j, k, temp, pivot_ind;
	
	pivot_ind = rand_pivot(first, last);
	
	temp = arr[pivot_ind];
	arr[pivot_ind] = arr[first];
	arr[first] = temp;
	
	i = first + 1; // i, pivotdan küçüklerin olduðu kýsmýn bir saðýný tutar. j ise pivotdan büyüklerin olduðu kýsmýn son elemanýný.
	k = first + 1;
	
	for(j=first+1;j<=last;j++){
		if(arr[first] > arr[j]){
			if(j != k){
				temp = arr[k];
				arr[k] = arr[i];
				arr[i] = temp;	
			}
			temp = arr[j];
			arr[j] = arr[i];
			arr[i] = temp;
			k++;
			i++;
		}
		else if(arr[first] == arr[j]){
			temp = arr[j];
			arr[j] = arr[k];
			arr[k] = temp;
			k++;
		}
	}

	temp = arr[first];
	arr[first] = arr[i-1];
	arr[i-1] = temp;
	return i-1;
}

long long find_m2(long long* arr, long long m1, long long last){
	long long i = m1;
	while(arr[m1] == arr[i]) i++;
	return i;
}

void quick_sort(long long* arr, long long n, long long first, long long last){
	long long m1, m2;
	if(first < last){
		m1 = pivot(arr, n, first, last);
		m2 = find_m2(arr, m1, last);
		quick_sort(arr, n, first, m1-1);
		quick_sort(arr, n, m2, last);
	}
}

int main(){
	long long arr[100000], n, i;
	
	srand(time(0));
	
	scanf("%lld", &n);
	
	for(i=0;i<n;i++){
		scanf("%lld", &arr[i]);
	}
	
	quick_sort(arr, n, 0, n-1);

	for(i=0;i<n;i++) printf("%lld ", arr[i]);

	return 0;
}
