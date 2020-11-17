#ifndef TOTALORDERINFO_H
#define TOTALORDERINFO_H


class TotalOrderInfo
{
private:
//    char *order_date; // 주문날짜
//    int order_num; // 전체주문개수
    char menu_name[50]; // 주문한메뉴명
    int menu_price; // 메뉴가격
    int amount; // 주문한 메뉴의 개수
    int tot_menu_price; // 1 메뉴당 주문한 총가격
//    int payment; // 결제수단
//    int tot_order_price; // 총주문가격
//    int print_cnt; // 주문개수
public:
    TotalOrderInfo();
//    char* get_order_date() const;
//    int get_order_num() const;
    char* get_menu_name();
    int get_menu_price() const;
    int get_amount() const;
    int get_tot_menu_price() const;
//    int get_payment() const;
//    int get_tot_order_price() const;
//    int get_print_cnt() const;

//    void set_order_date(char* order_date);
//    void set_order_num(int order_num);
    void set_menu_name(char* menu_name);
    void set_menu_price(int price);
    void set_amount(int amount);
    void set_tot_menu_price(int tot_price);
//    void set_payment(int payment);
//    void set_tot_order_price(int tot_order_price);
//    void set_print_cnt(int cnt);
};

#endif // TOTALORDERINFO_H
