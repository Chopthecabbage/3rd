#pragma once
#include "Common.h"
#include "SQL.h"
#include "P_signalInfo.h"
#include "P_orderInfo.h"

class Pos_Handler
{
public:
    void Progress_Order_Es(int clnt_sock, int order_num); // 주문 상태 확인
    void Progress_One_Order_info(int clnt_sock, int order_num); // 주문 상세정보 확인 
    void Progress_Order_Process(int clnt_sock); // 주문 처리
    void Progress_Order_Cancel(int clnt_sock); // 주문 취소
    int Progress_Tot_Order_Info_Cnt(); // 전체주문 갯수 반환
    OrderInfo* Progress_Tot_Order_Info(int orders_cnt); // 전체주문 반환
    void request_today_salesInfo(int clnt_sock); // 당일 주문 조회
    int get_currentDate_order_cnt(string current_date); // 당일 주문수 반환
    string get_current_date(); // 현재시간 반환
};