#include <stdio.h>

int car(int d, int m, int n, int* stops){
	int i = 0, left = 0, right, count = 0;
	
	while(left + m < d){
		right = left + m;
		while(i < n && stops[i] <= right) i++;
		i--;
		if(left == stops[i]) return -1;
		left = stops[i];
		count++;
	}
	return count;
}

int main(){
	int d, m, n, stops[300], i;
	
	scanf("%d", &d);
	scanf("%d", &m);
	scanf("%d", &n);
	
	for(i=0;i<n;i++){
		scanf("%d", &stops[i]);
	}
	printf("%d", car(d, m, n, stops)); 
	return 0;
}
