#ifndef ORDER_H
#define ORDER_H

#include "cart.h"

class Orders
{
protected:
    int payment; // 결제 수단 0: 초기화 1: 현금 2: 카드
    Cart cart; // 장바구니
public:
    Orders() : payment(0) { }
    Orders(int payment, Cart cart)
        : payment(payment)
    {
        this->cart = cart;
    }
    void Set_Order(int _p, Cart _c)
    {
        payment = _p;
        cart = _c;
    }
    Cart& Get_Cart()
    {
        return cart.Get_Cart();
    }
    int Get_Payment_Info() const
    {
        return payment;
    }
    void Set_Payment_Info(int payment)
    {
        this->payment=payment;
    }
    //
    void Add_Item(char* name, int price, int amount)
    {
        Item temp;
        temp.Set_Name_Price(name,price);
        cart.Add_Item(temp,amount);
    }
    void Remove_Item(char* name, int price, int amount)
    {
        Item temp;
        temp.Set_Name_Price(name,price);
        cart.Remove_Item(temp,amount);
    }
    int Cart_Tot_Cnt()
    {
        return cart.Get_Tot_Cnt();
    }
    QString Cart_Item_Name(int dotX)
    {
        QString temp=cart.Item_Name(dotX);
        return temp;
    }
    QString Cart_Item_Price(int dotX)
    {
        QString temp=cart.Item_Price(dotX);
        return temp;
    }
    QString Cart_Item_Amount(int dotX)
    {
        QString temp=cart.Item_Amount(dotX);
        return temp;
    }
    int Cart_Item_Cnt(int dotX)
    {
        return cart.Get_Item_Cnt(dotX);
    }
    void show(int dotX)
    {
        cart.show(dotX);
    }
    //
    char* Compare_Item_Name(int dotX)
    {
        return cart.Compare_Item_Name(dotX);
    }
    char* Compare_Item_Photo(int dotX)
    {
        return cart.Compare_Item_Photo(dotX);
    }
    int Compare_Item_Price(int dotX)
    {
        return cart.Compare_Item_Price(dotX);
    }
    int Compare_Item_Amount(int dotX)
    {
        return cart.Get_Item_Cnt(dotX);
    }
    //
    void Set_Code_Category_Photo(int code, int category, char* photo, int dotX)
    {
        cart.Set_Code_Category_Photo(code,category,photo,dotX);
    }
    int Cart_Tot_Price(int dotX)
    {
       return cart.Item_Tot_Price(dotX);
    }
};

#endif // ORDER_H
