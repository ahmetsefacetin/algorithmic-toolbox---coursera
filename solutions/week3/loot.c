#include <stdio.h>

int main(){
	long long int w[1000], v[1000], n, i, W, index, count;
	double result = 0.0, max_per_unit=0.0, curr_unit; 
	
	scanf("%lld %lld", &n, &W);
	for(i=0;i<n;i++){
		scanf("%lld %lld", &v[i], &w[i]);
	}
	count = n;
	while(W > 0 && count > 0){
		//max_per_unit i bulmak icin
		for(i=0;i<n;i++){
			curr_unit = (double) v[i] / w[i];
			if(curr_unit > max_per_unit){
				max_per_unit = curr_unit;
				index = i;
			}
		}
		if(w[index] < W){
			result += max_per_unit * w[index];
			W -= w[index];
		}
		else{
			result += max_per_unit * W;
			W = 0;
		}
		max_per_unit = 0.0;
		w[index] = -1;
		count--;
	}
	
	printf("%.4lf", result);
	return 0;
}
