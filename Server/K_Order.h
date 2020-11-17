#pragma once
#include "Common.h"
#include "K_Cart.h"

class Order
{
protected:
    int payment; // 결제 수단 0: 초기화 1: 현금 2: 카드
    Cart cart; // 장바구니
public:
    Order() : payment(0) { }
    Cart& Get_Cart() 
    {
        return cart;
    }
    int Get_Payment() const
    {
        return payment;
    }
};

