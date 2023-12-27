#include <stdio.h>

//doðrusu bu, ilki hatalý
void sign(long int n, long int arr[][2]){
	long int i, j, tempL, tempR, left, right, count = 0, point[100];
	//right deðerlerine göre sýralamak için, max tan min e doðru
	for(i=1;i<n;i++){
		j = i-1;
		tempL = arr[i][0];
		tempR = arr[i][1];
		while(j >= 0 && arr[j][1] < tempR){
			arr[j+1][0] = arr[j][0];
			arr[j+1][1] = arr[j][1];
			j--;
		}
		arr[j+1][0] = tempL;
		arr[j+1][1] = tempR;
	}
	i=0;
	while(i < n){
		left = arr[i][0];
		right = arr[i][1];
		j=i+1;
		while(j < n && arr[j][1] >= left){
				right = arr[j][1];
				if(arr[j][0] > left) left = arr[j][0];
				j++;
		}
		i=j;
		point[count++] = right;
	}
	printf("%ld\n", count);
	for(i=count-1;i>=0;i--) printf("%ld ", point[i]);
}

int main(){
	long int n, arr[100][2], i;
	
	scanf("%ld", &n);
	for(i=0;i<n;i++){
		scanf("%ld %ld", &arr[i][0], &arr[i][1]);
	}
	sign(n, arr);
	return 0;
}
