#include <stdio.h>
#include <math.h>
void max_num(long int n, long int arr[]){
	long int digits[100], i, j, k, temp, temp1, temp2, key1, key2, ctrl;
	
	for(i=0;i<n;i++){
		temp = arr[i];
		k=0;
		while(temp){
			temp /= 10;
			k++;
		}
		digits[i] = k;
	}
	for(i=1;i<n;i++){
		j=i-1;
		key1 = arr[i];
		key2 = digits[i];
		ctrl = 1;
		while(j >= 0 && ctrl){
			temp1 = key1;
			temp2 = arr[j];
			for(k=0;k<digits[j];k++) temp1 *= 10;
			temp1 += arr[j];
			for(k=0;k<key2;k++) temp2 *= 10;
			temp2 += key1;
			if(temp1 > temp2){
				arr[j+1] = arr[j];
				digits[j+1] = digits[j];
				j--;
			}
			else ctrl = 0;
		}
		arr[j+1] = key1;
		digits[j+1] = key2;
	}
	for(i=0;i<n;i++){
		printf("%ld", arr[i]);
	}
}

int main(){
	long int n, i, j, arr[100];
	
	scanf("%ld", &n);
	
	for(i=0;i<n;i++){
		scanf("%ld", &arr[i]);
	}
	max_num(n, arr);
	return 0;
}
