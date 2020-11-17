#pragma once
#include <iostream>
#include <unistd.h>
#include <string>
#include <vector>
#include <cstring>
#include "/usr/include/mariadb/mysql.h"

#define MAX_NAME 50 // Item 클래스 아이템 이름 
#define MAX_PHOTO 50 // Item 클래스 아이템 사진경로 
#define MAX_CART 5 // K_Cart 클래스 장바구니 크기 

// DB연동 관련
#define DB_HOST "10.10.20.240"
#define DB_USER "root"
#define DB_PASS "123"
#define DB_NAME "min"
#define DB_PORT 3306
// TCP/IP 포트
#define PORT 7878

using namespace std;

enum { TYPE_KIOSK = 1, TYPE_POS = 2, TYPE_POS_ORDER = 3 }; // 소켓 타입 
enum { K_ORDER_PROCESS = 1 }; // 키오스크 쓰레드 시그널 
enum { P_ORDER_ES = 1, P_ORDER_INFO = 2, P_ORDER_PROCESS = 3, P_ORDER_CANCEL = 4, P_ORDER_REFRESH = 5 , P_TODAY_SALES = 6 }; // 포스 쓰레드 시그널 
