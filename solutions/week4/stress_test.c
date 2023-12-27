#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long binary_search_counter(long long* dizi, long long n, long long low, long long high, long long x, long long *p){
	long long mid = (high - low) / 2 + low;
	
	if(low > high) return low;
	
	if(dizi[mid] == x){
		if(*p){
			while(mid+1 < n && dizi[mid] == dizi[mid+1]) mid++;
			return mid+1;
		}
		else{
			while(mid-1 >= 0 && dizi[mid] == dizi[mid-1]) mid--;
			return mid;
		}
	}
	
	else if(dizi[mid] > x) return binary_search_counter(dizi, n, low, mid-1, x, p);
	else return binary_search_counter(dizi, n, mid+1, high, x, p);
}

long long rand_pivot(long long first, long long last){
	return (rand() % (last - first + 1)) + first;
}

long long pivot(long long* arr, long long first, long long last){
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

void quick_sort(long long* arr, long long first, long long last){
	long long m1, m2;
	if(first < last){
		m1 = pivot(arr, first, last);
		m2 = find_m2(arr, m1, last);
		quick_sort(arr, first, m1-1);
		quick_sort(arr, m2, last);
	}
}

void naive(long long left[], long long right[], long long points[], long long n, long long m, long long results2[]){
	long long count, i, j;
	
	for(i=0;i<m;i++){
		count=0;
		for(j=0;j<n;j++){
			if(points[i] >= left[j] && points[i] <= right[j]) count++;
		}
		results2[i] = count;
	}
}

int main(){
	srand(time(0));
	while(1){
	long long n, m, left[500], right[500], points[500], i, results[500], results2[500], ctrl = 1, flag = 1, temp;
	
	//scanf("%lld %lld", &n, &m);
	
	//for(i=0;i<n;i++) scanf("%lld %lld", &left[i], &right[i]);
	
	n = rand() % 10 + 4;	
	m = rand() % 10 + 4;
	
	for(i=0;i<n;i++){
		left[i] = rand() % 30;
		right[i] = rand() % 30;
		if(left[i] > right[i]){
			temp = left[i];
			left[i] = right[i];
			right[i] = temp;
		}
	}
	//for(i=0;i<m;i++) scanf("%lld", &points[i]);
	for(i=0;i<m;i++){
		points[i] = rand() % 30;
		results[i] = 0;
		results2[i] = 0; 
	}
	
	printf("\n\n\n\n\nn: %lld m: %lld\n", n, m);
	printf("\nsegments:\n");
	for(i=0;i<n;i++) printf("(%lld, %lld) ", left[i], right[i]);
	printf("\npoints:\n");
	for(i=0;i<m;i++) printf("%lld ", points[i]);
	
	naive(left, right, points, n, m, results2);
	
	quick_sort(left, 0, n-1);
	quick_sort(right, 0, n-1);
	
	for(i=0;i<m;i++){
		ctrl = 1;
		results[i] = binary_search_counter(left, n, 0, n-1, points[i], &ctrl);
		ctrl = 0;
		results[i] -= binary_search_counter(right, n, 0, n-1, points[i], &ctrl); 
	}
	
	for(i=0;i<m;i++){
		if(results[i] != results2[i]){
			printf("\nadvance:\n");
			for(i=0;i<m;i++) printf("%lld ", results[i]);
			printf("\nnaive:\n");
			for(i=0;i<m;i++) printf("%lld ", results2[i]);
			flag = 0;
			break;
		}
	}
	if(flag == 0) break;
	}
	return 0;
}
