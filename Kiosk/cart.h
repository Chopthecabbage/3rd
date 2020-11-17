#ifndef BASKET_H
#define BASKET_H

#include "common.h"
#include "item.h"

class Cart
{
private:
    Item item[CART_MAX];
    int item_cnt[CART_MAX];
    int tot_cnt;
    int tot_price;
public:
    Cart();
    void Add_Item(Item item, int add_cnt); // 장바구니에 품목추가
    void Remove_Item(Item item, int remove_cnt); // 장바구니에 품목제거
    int Get_Tot_Cnt() const; // 품목개수 확인
    int Get_Tot_Price() const; // 장바구니 총액 확인
    Item* Get_Item_List(); // 장바구니에 담긴 아이템들 확인
    int* Get_Item_Cnt(); // 장바구니에 담긴 아이템들의 개수들을 확인
    Cart& Get_Cart(); // 장바구니객체 확인
    void Set_Item_Cnt(int amount);
    //
    QString Item_Name(int dotX);
    QString Item_Price(int dotX);
    QString Item_Amount(int dotX);
    int Get_Item_Cnt(int dotX);
    //
    void show(int dotX);
    //
    char* Compare_Item_Name(int dotX);
    char* Compare_Item_Photo(int dotX);
    int Compare_Item_Price(int dotX);

    void Set_Code_Category_Photo(int code,int category,char* photo,int dotX);
    int Item_Tot_Price(int dotX);
};

#endif // BASKET_H
