#include "totalorderinfo.h"
#include <string.h>

TotalOrderInfo::TotalOrderInfo():menu_price(0),amount(0),tot_menu_price(0)
{
    //order_date=nullptr;
   // menu_name=nullptr;
}

//char* TotalOrderInfo::get_order_date() const
//{
//    return order_date;
//}

//int TotalOrderInfo::get_order_num() const
//{
//    return order_num;
//}

char* TotalOrderInfo::get_menu_name()
{
    return menu_name;
}

int TotalOrderInfo::get_menu_price() const
{
    return menu_price;
}

int TotalOrderInfo::get_amount() const
{
    return amount;
}

int TotalOrderInfo::get_tot_menu_price() const
{
    return tot_menu_price;
}

//int TotalOrderInfo::get_payment() const
//{
//    return payment;
//}

//int TotalOrderInfo::get_tot_order_price() const
//{
//    return tot_order_price;
//}

//int TotalOrderInfo::get_print_cnt() const
//{
//    return print_cnt;
//}

//void TotalOrderInfo::set_order_date(char* order_date)
//{
//    this->order_date = order_date;
//}

//void TotalOrderInfo::set_order_num(int order_num)
//{
//    this->order_num=order_num;
//}

void TotalOrderInfo::set_menu_name(char* menu_name)
{
    strcpy(this->menu_name,menu_name);
}

void TotalOrderInfo::set_menu_price(int price)
{
    menu_price = price;
}

void TotalOrderInfo::set_amount(int amount)
{
    this->amount = amount;
}

void TotalOrderInfo::set_tot_menu_price(int tot_price)
{
    tot_menu_price = tot_price;
}

//void TotalOrderInfo::set_payment(int payment)
//{
//    this->payment = payment;
//}

//void TotalOrderInfo::set_tot_order_price(int tot_order_price)
//{
//    this->tot_order_price = tot_order_price;
//}

//void TotalOrderInfo::set_print_cnt(int cnt)
//{
//    print_cnt = cnt;
//}
