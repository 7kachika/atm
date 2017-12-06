// Copyright 2017 7kachika
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "atm.h"

int fileOpen() {
	int i;
	char name[20], id[20], password[20], balance[20];
	fp_r = fopen("account.txt", "r");
	fp_w = fopen("temp.txt", "w");

	if (fp_r == NULL) {
		return -1;
	}
	if (fp_w == NULL) {
		return -1;
	}

	while(!feof(fp_r)) {
		fscanf(fp_r, "%s %s %s %s\n", &id, &name, &password, &balance);
		strcpy(db[i].id, id);
		strcpy(db[i].name, name);
		strcpy(db[i].password, password);
		db[i++].balance = atoi(balance);
	}
	return i;
}

void fileClose(int i) {
	int index;
	for (index = 0; index < i; index++) {
		fprintf(fp_w, "%s\t%s\t%s\t%d\n", db[index].id, db[index].name, db[index].password, db[index].balance);
	}
	fclose(fp_r);
	fclose(fp_w);
	remove("account.txt");
	rename("temp.txt","account.txt");
}

int menu(int index, int i) {
	switch (index) {
		case -3:
			// 密碼錯誤
			return -3;
			break;
		case -2:
			// 查無此帳號
			return -2;
			break;
		case -1:
			// 未登入
			return -1;
			break;
		case 0:
			// 提款機後台
		default:
		printf("\n%s 您好，歡迎使用本系統。\n", db[index].name);
		puts("------------------------");
		puts("提款機選單\n");
		puts("1.查詢餘額");
		puts("2.提款");
		puts("3.存款");
		puts("4.更改密碼");
		if (index == 0) {
			puts("5.建立新帳戶");
		}
		puts("0.離開");
		printf("\n請輸入選項: ");
		int flag, amount;
		char password[20];
		scanf("%1d", &flag);
		while((c = getchar()) != '\n' && c != EOF);
		switch (flag) {
	    	case 0:
	    		// 離開
	  			puts("------------------------");
				puts("您已登出本系統。");
				return -1;
	    		break;
			case 1:
				if (index == 0) {
					management(i);
					return index;
				}
				checkBalances(index);
				return index;
	    		break;
	    	case 2:
	    		// 提款
				puts("\n請輸入欲提款金額: ");
	    		amount = tryAmount(-1, index);
				if (amount == 0) {
		    		return index;
					break;
				}
				printf("\n完成: 提款 $%d 元。 \n", amount);
				reload = 1;
				return index;
	    		break;
	    	case 3:
	    		// 存款
				puts("\n請輸入欲存款金額: ");
	    		amount = tryAmount(1, index);
				if (amount == 0) {
					return index;
					break;
				}
				printf("\n完成: 存款 $%d 元。 \n", amount);
				reload = 1;
				return index;
	    		break;
	    	case 4:
	    		// 更改密碼
				printf("\n請輸入新密碼: ");
				scanf("%s", &password);
				while((c = getchar()) != '\n' && c != EOF);
				strcpy(db[index].password, password);
				puts("\n已修改密碼。");
				reload = 1;
				return -1;
	    		break;
	    	case 5:
	    		if (index == 0) {
	    			char var[20];
					printf("\nid: %d\n", atoi(db[i - 1].id) + 1);
					sprintf(db[i].id, "%d", atoi(db[i - 1].id) + 1);

					printf("\nname: ");
					scanf("%s", &var);
					while((c = getchar()) != '\n' && c != EOF);
					strcpy(db[i].name, var);

					printf("\npassword: ");
					scanf("%s", &var);
					while((c = getchar()) != '\n' && c != EOF);
					strcpy(db[i].password, var);

					printf("\nbalance: ");
					scanf("%s", &var);
					while((c = getchar()) != '\n' && c != EOF);
					db[i].balance = atoi(var);
	    			reload = 2;
	    			return index;
				}
			default:
				printf("\n錯誤: 無此選項。 \n");
				return index;
				break;
		}
		break;
	}
}

void management(int i) {
	int index;
	puts("\n提款機後台");
	printf("提款機的餘額為: %d\n", db[0].balance);
  	puts("------------------------");
	for (index = 1; index < i; index++) {
		printf("帳戶: %s, 戶主: %s, 餘額: %d\n", db[index].id, db[index].name, db[index].balance);
	}
  	puts("------------------------");
}

int checkAccount(int i) {
	int index;
	char temp[100];
	printf("請輸入帳號: ");
	gets(temp);
	for (index = 0; index < i; index++) {
		if (strcmp(temp, db[index].id) == 0) {
			return index;
		}
	}
	puts("查無此帳號。");
	return -2;
}

int checkPassword(int index) {
	if (index == -2) {
		return -2;
	}
	char temp[100];
	printf("請輸入密碼: ");
	gets(temp);
	if (strcmp(temp, db[index].password) == 0) {
		system("cls");
		return index;
	}
	puts("密碼錯誤。");
	return -3;

}

void checkBalances(int index) {
	// 查詢餘額
	puts("------------------------");
	printf("您的帳戶餘額為: %d\n", db[index].balance);
}

int tryAmount(int sign, int index) {
	int amount;
	scanf("%d", &amount);
	while((c = getchar()) != '\n' && c != EOF);
	if (sign < 0) {
		if (checkBalance(amount) == 0) {
			return 0;
		}
		if (checkAccountBalance(amount, index) == 0) {
			return 0;
		}
	}
	db[index].balance += amount * sign;
	if (index != 0) {
		db[0].balance += amount * sign;
	}
	return amount;
}

int checkBalance(int amount) {
	if (amount > db[0].balance) {
		puts("提款機餘額不足。");
		return 0;
	}
	return 1;
}

int checkAccountBalance(int amount, int index) {
	if (amount > db[index].balance) {
		puts("帳戶餘額不足。");
		return 0;
	}
	return 1;
}
