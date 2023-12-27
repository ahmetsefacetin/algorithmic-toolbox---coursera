#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void game(int n, int m){
	int player1_condition[n+1][m+1], i, j, answer, ctrl, flag = 0;
	
	for(i=0;i<=n;i++){
		for(j=0;j<=m;j++){
			player1_condition[i][j] = 1;
			if(i % 2 == 0 && j % 2 == 0){
				player1_condition[i][j] = 0;
			}
		}
	}
	
	while(n + m > 0){
		if(n > 0 && m > 0 && player1_condition[n-1][m-1] == 0) n--, m--;
		else if(n > 0 && player1_condition[n-1][m] == 0){
			n--;
		}
		else if(m > 0 && player1_condition[n][m-1] == 0){
			m--;
		}
		else if(n > 0) n--;
		else m--;
		
		if(n + m > 0){
			do{
				ctrl = 0;
				printf("first pile: %d\nsecond pile: %d\n", n, m);
				printf("enter 1 to take from first pile\nenter 2 to take from second pile\nenter 3 to take from both piles...\n");
				scanf("%d", &answer);
				
				if(answer == 1 && n > 0) n--, ctrl = 1;
				if(answer == 2 && m > 0) m--, ctrl = 1;
				if(answer == 3 && n > 0 && m > 0) n--, m--, ctrl = 1;
			} while(ctrl == 0);
		}
		else{
			printf("computer won...");
			flag = 1;
		}
	}
	if(flag == 0) printf("you won...");
}

int main(){
	int n, m;

	scanf("%d %d", &n, &m);
	
	game(n, m);
	
	return 0;
}
