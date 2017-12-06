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

int main(int argc, const char * argv[]) {
	int i, login = -1;
	i = fileOpen();
	while (1) {
		switch (reload) {
			case 2:
				i++;
			case 1:
//				puts("\nreloaded.");
//				puts("------------------------");
				reload = 0;
				fileClose(i);
				i = fileOpen();
			default:
				switch (login) {
					case -3:
						// 密碼錯誤
					case -2:
						// 查無此帳號
					case -1:
						// 未登入
						puts("\nATM自動提款機");
						puts("------------------------");
						login = menu(checkPassword(checkAccount(i)), i);
						break;
					default:
						login = menu(login, i);
						break;
				}
				break;
		}
		puts("------------------------");
		system("PAUSE");
		system("cls");
	}
	fileClose(i);
	return system("PAUSE");
}
