#pragma once
#include "Common.h"
#include "K_Item.h"

class Cart
{
private:
    Item item[MAX_CART];
    int item_cnt[MAX_CART];
    int tot_cnt;
    int tot_price;
public:
    Cart() : tot_cnt(0),tot_price(0)
    {
        memset(item_cnt, 0, sizeof(int) * MAX_CART);
    }
    int Get_Tot_Cnt() const
    {
        return tot_cnt;
    }    
    Item& Get_Item(int idx) 
    {
        return item[idx];
    }
    int Get_Item_Cnt(int idx)
    {
        return item_cnt[idx];
    }
    void Prt(int idx)
    {
        item[idx].Prt();
    }
};

