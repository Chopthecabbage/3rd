#pragma once
#include "Common.h"
#include "K_Order.h"

class SQL
{
private:
    MYSQL *connection;
    MYSQL conn; 
    MYSQL_RES *sql_result;
    MYSQL_ROW sql_row;
    
public:
    SQL();
    ~SQL();
    bool Connect();
    void Disconnect();
    // 키오스크 관련
    MYSQL_RES* Select_All_Menu(); // 전체 메뉴 조회, 결과 리턴 
    void Insert_Order(Order order); // 주문 DB에 저장
    // 포스 관련
    int Query_and_check(string query);
	MYSQL_RES* Check_order_info(int sig,int order_num);
	MYSQL_RES* Request_order_info(int order_num);
	MYSQL_RES* Request_order_cnt(int order_num);
	int Change_order_status(int order_num,int status);
    MYSQL_RES* Get_tot_order_info();
    MYSQL_RES* Request_allorder_cnt();
    
	MYSQL_RES* Get_todayOrder_info(string current_date);
	int Request_todayOrder_cnt(string current_date);
    MYSQL_RES* Get_current_date();
};


