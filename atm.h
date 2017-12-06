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

#ifndef SHARED_LIB_H
#define SHARED_LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

#ifdef __cplusplus
  extern "C" {
#endif

#ifdef BUILD_MY_DLL
    #define SHARED_LIB __declspec(dllexport)
#else
    #define SHARED_LIB __declspec(dllimport)
#endif

struct account{
    char id[20];		// 帳號
    char name[20];		// 姓名
    char password[20];	// 密碼
    int balance;		// 餘額
};

int SHARED_LIB fileOpen();
void SHARED_LIB fileClose(int i);
int SHARED_LIB menu(int index, int i);
void SHARED_LIB management(int i);
int SHARED_LIB checkAccount(int i);
int SHARED_LIB checkPassword(int index);
void SHARED_LIB checkBalances(int index);
int SHARED_LIB tryAmount(int sign, int index);
int SHARED_LIB checkBalance(int amount);
int SHARED_LIB checkAccountBalance(int amount, int index);

int	c, reload = 0;
struct account db[100];
FILE *fp_r;
FILE *fp_w;

#ifdef __cplusplus
  }
#endif

#endif  // end of DLL
