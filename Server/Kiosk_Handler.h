#pragma once
#include "Common.h"
#include "SQL.h"
#include "K_Item.h"
#include "K_Cart.h"
#include "K_Order.h"

class Kiosk_Handler
{
public:
    Item* Get_Menu_From_DB(int *menu_cnt); // 전체 메뉴 DB에서 가져옴 
    void Save_Order_To_DB(Order order); // 완료된 주문 DB에 저장
};