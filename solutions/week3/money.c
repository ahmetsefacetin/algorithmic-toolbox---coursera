#include <stdio.h>

int main(){
	int money, count = 0;
	scanf("%d", &money);
	count += money / 10;
	money = money % 10;
	count += money / 5;
	money = money % 5;
	count += money;
	printf("%d", count);
	return 0;
}
