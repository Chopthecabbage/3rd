#include "Kiosk_Handler.h"

Item* Kiosk_Handler::Get_Menu_From_DB(int *menu_cnt)
{
    SQL sql;
    MYSQL_RES *result;
    MYSQL_ROW row;
    Item *cafe_menu;           

    sql.Connect();
    result = sql.Select_All_Menu();  
    *menu_cnt = mysql_num_rows(result);    
    cafe_menu = new Item[*menu_cnt];

    cout << "menu_cnt : " << *menu_cnt << endl;  
    for(int i = 0; i < *menu_cnt ; i++)
    {
        row = mysql_fetch_row(result);    
        cafe_menu[i].Set_Item(atoi(row[0]), row[1], atoi(row[2]), atoi(row[3]), row[4]);
        //cout << row[0] << "-" << row[1] << "-" << row[2] << "-" << row[3] << "-" << row[4] << endl;        
    }     
    sql.Disconnect();

    return cafe_menu;      
}  

void Kiosk_Handler::Save_Order_To_DB(Order order)
{
    SQL sql;
    
    sql.Connect();
    sql.Insert_Order(order);
    sql.Disconnect();    

}