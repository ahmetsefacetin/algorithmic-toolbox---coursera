#include <stdio.h>

/*
you are given an array called coins which have the number of different coins in an increasing order. And also you are given the sum that you 
need to make with those coins. The goal is to find the minimum number of coins you can use to achive the sum. Assume that you have infinite
supply of each coin...
*/

/*
greedy approach: sum'ý aþmadýðý sürece elimizdeki en büyük coin i kullan. Aþtýktan sonra bir küçük coin e geç. Gördüðün gibi bir seçim yaptýk.
Ama bu yaklaþým öyle görünse de her zaman doðru sonucu vermiyor. Mesela coins = {1,5,6}, sum = 10 olsun. önce 6 yý deniycez, 6 dan yalnýzca bir
tane var sonra 5'e geçicez ancak sum þu anda 4 olduðu için 1 e geçicez ve 1 den 4 tane alýp bitiricez. Toplamda 5 coin kullandýk ancak 2 tane 5
ile halledebilirdik.
*/

int greedy(int coins[], int n, int sum){
	int i = n-1, count = 0;
	
	while(sum > 0 && i >= 0){
		count += sum / coins[i];
		sum = sum % coins[i];
		i--;
	}
	
	return count;
}

//recursive approach: Olabilecek tüm seçenekleri deniyor. Mesela sum = 11, coins = {1,5,6} olsun. hem 6,5'i hem 5,6 yý hesaplar. O yüzden kesin
//doðru sonuç verir ama gereksiz yere tekrardan ayný hesaplamalarý yapar. naive approach gibi biþey yani. karmaþýklýk üstel olur.

int recursive(int coins[], int n, int sum){
	int i, min_num_coins = sum / coins[0] + 1, num_coins;
	
	if(sum == 0) return 0;
	
	for(i=n-1;i>=0;i--){
		if(sum >= coins[i]){
			num_coins = recursive(coins, n, sum - coins[i]);
			if(num_coins + 1 < min_num_coins) min_num_coins = num_coins + 1;
		}
	}
	
	return min_num_coins;
}

/*
dynamic programming approach: Hesapladýðýmýz sonuçlarý kaydederek tekradan ayný hesaplamalarý yapmamamýzý saðlýyor. Ýstenen sum kadarlýk bir
dizi oluþturuyoz. Mesela sum 9'sa index'i 9'a kadar 10 elemanlý bir dizi. Her bir index sum'ýn o deðeri için minimum coin sayýsýný tutuyor. 
Mesela coins = {1,5,6} için min_num_coins[10] dizisi {0,1,2,3,4,1,1,2,3,4} elemanlarýndan oluþacak. Çünkü sum = 0 için 0, 1 için 1, 2 için 2 ...
5 için ise önce min_num_coins[5-1] + 1' e bakacak çünkü sum = 4'e çýkardýðýmýz 1'i eklersek sum = 5'i elde ederiz. Buradan num_coins = 5 gelir. 
Sonra min_num_coins[5-5] + 1'e bakar çünkü sum = 0'a çýkardýðýmýz 5'i eklersek sum = 5'i elde ederiz. Burdan num_coins = 1 gelir. Gördüðün gibi 
recursive'de min_num_coins[5-1]'i bulmak için 4 çaðrý daha yapmamýz gerekmiþken burada tek adýmda iþi hallediyoruz.
Karmaþýklýk sum*n olur. Ýnanýlmaz bir iyileþtirme...
*/

int dynamic(int coins[], int n, int sum){
	int i, min_num_coins[sum+1], m, num_coins;
	
	min_num_coins[0] = 0;
	for(m=1;m<=sum;m++){
		min_num_coins[m] = min_num_coins[m-1] + coins[n-1]; //sonsuz bir sayý olmasýný saðlýyoruz.
		for(i=0;i<n;i++){
			if(m >= coins[i]){
				num_coins = min_num_coins[m-coins[i]] + 1;
				if(num_coins < min_num_coins[m]){
					min_num_coins[m] = num_coins;
				}
			}
		}
	}
	return min_num_coins[sum];
}

int main(){
	int n = 3, coins[10] = {2,4,8};
	
	printf("%d", greedy(coins, n, 15));
	printf("\n%d", recursive(coins, n, 15));
	printf("\n%d", dynamic(coins, n, 997));
	
	return 0;
}
