#include "P_orderInfo.h"
#include <cstring>

OrderInfo::OrderInfo():menu_name(""),order_date(""),menu_price(0),amount(0),tot_menu_price(0), status(0)
{
}

char* OrderInfo::get_order_date() 
{
    return order_date;
}

int OrderInfo::get_order_num() const
{
    return order_num;
}

char* OrderInfo::get_menu_name() 
{
    return menu_name;
}

int OrderInfo::get_menu_price() const
{
    return menu_price;
}

int OrderInfo::get_amount() const
{
    return amount;
}

int OrderInfo::get_tot_menu_price() const
{
    return tot_menu_price;
}

int OrderInfo::get_payment() const
{
    return payment;
}

int OrderInfo::get_tot_order_price() const
{
    return tot_order_price;
}

int OrderInfo::get_status() const
{
    return status;
}

void OrderInfo::set_order_date(char* order_date)
{
    strcpy(this->order_date,order_date);
}

void OrderInfo::set_order_num(int order_num)
{
    this->order_num=order_num;
}

void OrderInfo::set_menu_name(char* menu_name)
{
    strcpy(this->menu_name,menu_name);
}

void OrderInfo::set_menu_price(int price)
{
    menu_price = price;
}

void OrderInfo::set_amount(int amount)
{
    this->amount = amount;
}

void OrderInfo::set_tot_menu_price(int tot_price)
{
    tot_menu_price = tot_price;
}

void OrderInfo::set_payment(int payment)
{
    this->payment = payment;
}

void OrderInfo::set_status(int status)
{
    this->status = status;
}

void OrderInfo::set_tot_order_price(int tot_order_price)
{
    this->tot_order_price = tot_order_price;
}
