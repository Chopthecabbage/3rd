#include "Pos_Handler.h"

void Pos_Handler::Progress_Order_Es(int clnt_sock, int order_num)
{ 
    SQL sql;
	MYSQL_ROW sql_row;
	MYSQL_RES* res = nullptr;	
	
    sql.Connect();    
    res = sql.Check_order_info(1,order_num);
    sql_row = mysql_fetch_row(res);

    // 주문번호가 존재한다면
    if(strcmp(sql_row[0],"1")==0)
    {
        // 해당 주문번호의 주문처리상태를 확인한다. 
        res = sql.Check_order_info(2,order_num);
        sql_row = mysql_fetch_row(res);
        if(strcmp(sql_row[0],"1")==0) // 처리전
        {
            cout << "처리 대기중인 주문" << endl;
            write(clnt_sock,"1",strlen("1"));
        }
        else if(strcmp(sql_row[0],"0")==0) // 처리
        {
            cout << "이미 처리된 주문" << endl;
            write(clnt_sock,"0",strlen("0"));
        }
        else if(strcmp(sql_row[0],"2")==0) // 취소
        {
            cout << "취소된 주문" << endl;
            write(clnt_sock,"2",strlen("2"));
        }
    }
    else if(strcmp(sql_row[0],"0")==0) // 주문번호 미존재
    {
        cout << "없는 주문번호" << endl;
        write(clnt_sock,"-1",strlen("-1"));
    }
    sql.Disconnect();
}

void Pos_Handler::Progress_One_Order_info(int clnt_sock, int order_num)
{
    SQL sql;
	MYSQL_ROW sql_row;
	MYSQL_RES* res = nullptr;
	
	OrderInfo *orders_info;
	int orders_cnt=0;

    sql.Connect();
    // 주문정보를 개수를 요청하다.
    res = sql.Request_order_cnt(order_num);
    sql_row = mysql_fetch_row(res);
    orders_cnt = atoi(sql_row[0]);

    // 클라이언트에서도 동적할당하게하기위해 개수를 보낸다. 
    cout << "orders_cnt :" << orders_cnt << endl;
    
    write(clnt_sock,(char*)&orders_cnt,sizeof(orders_cnt));

    // // 개수만큼 클래스배열을 동적할당한다. 
    orders_info = new OrderInfo[orders_cnt];

    res = sql.Request_order_info(order_num);

    int i=0;

    // 테이블뷰에 출력할 요소를 클래스배열에 등록한다. 
    while(sql_row = mysql_fetch_row(res))
    {
        orders_info[i].set_menu_name(sql_row[0]);
        orders_info[i].set_menu_price(atoi(sql_row[1]));
        orders_info[i].set_amount(atoi(sql_row[2]));
        orders_info[i].set_tot_menu_price(atoi(sql_row[3]));
    
        i++;
    }
    // // 클래스배열을 클라이언트에 전달하다.
    write(clnt_sock,(char*)orders_info,orders_cnt*sizeof(OrderInfo));
    delete [] orders_info;
    sql.Disconnect();
}

void Pos_Handler::Progress_Order_Process(int clnt_sock)
{    
    SQL sql;
	MYSQL_ROW sql_row;
	MYSQL_RES* res = nullptr;
	int query_stat;
    int order_num;

    cout << "주문처리하기" << endl;
    read(clnt_sock,(char*)(&order_num),sizeof(int));
    
    sql.Connect();
    // 주문처리상태를 확인한다. 
    res = sql.Check_order_info(2,order_num);
    sql_row = mysql_fetch_row(res);
    
    if(strcmp(sql_row[0],"1")==0)
    {
        cout << "처리할 주문번호 :" << order_num << endl;
        query_stat =sql.Change_order_status(order_num,0);
    }
    else // 이미 처리 또는 취소된 주문
    {
        query_stat = 1;
    }
    write(clnt_sock,(char*)(&query_stat),sizeof(int));
   
    sql.Disconnect();
}

void Pos_Handler::Progress_Order_Cancel(int clnt_sock)
{
    SQL sql;
	MYSQL_ROW sql_row;
	MYSQL_RES* res = nullptr;
	int query_stat;
    int order_num;

    cout << "주문취소하기" << endl;
    read(clnt_sock,(char*)(&order_num),sizeof(int));

    sql.Connect();
    // 주문처리상태를 확인한다. 
    res = sql.Check_order_info(2,order_num);
    sql_row = mysql_fetch_row(res);
    
    if(strcmp(sql_row[0],"1")==0)
    {
        cout << "취소할 주문번호 :" << order_num << endl;
        query_stat = sql.Change_order_status(order_num,2);
    }
    else // 이미 처리 또는 취소된 주문
    {
        query_stat = 1;
    }
    write(clnt_sock,(char*)(&query_stat),sizeof(int));
    
    sql.Disconnect();
}

int Pos_Handler::Progress_Tot_Order_Info_Cnt()
{
    SQL sql;
	MYSQL_ROW sql_row;
	MYSQL_RES* res = nullptr;

    int orders_cnt=0;
    
    cout << "전체주문건 확인" << endl;
    sql.Connect();
    // 전체 주문건수를 요청하다.
    res = sql.Request_allorder_cnt();
    sql_row = mysql_fetch_row(res);
    orders_cnt = atoi(sql_row[0]);

    // 클라이언트에서도 동적할당하게하기위해 개수를 보낸다. 
    cout << "orders_cnt :" << orders_cnt << endl;
    sql.Disconnect();

    return orders_cnt;
}

OrderInfo* Pos_Handler::Progress_Tot_Order_Info(int orders_cnt)
{
    SQL sql;
	MYSQL_ROW sql_row;
	MYSQL_RES* res = nullptr;
    OrderInfo *orders_info; 

    cout << "전체주문정보 확인" << endl;
    sql.Connect();
    // 개수만큼 클래스배열을 동적할당한다. 
    orders_info = new OrderInfo[orders_cnt];
    // 전체주문정보를 요청하다.
    res = sql.Get_tot_order_info();
    int i=0;
    // 테이블뷰에 출력할 요소를 클래스배열에 등록한다. 
    while((sql_row = mysql_fetch_row(res))!=NULL)
    {
    orders_info[i].set_order_date(sql_row[0]);
    orders_info[i].set_order_num(atoi(sql_row[1]));
    orders_info[i].set_menu_name(sql_row[2]);
    orders_info[i].set_amount(atoi(sql_row[3]));
    orders_info[i].set_tot_order_price(atoi(sql_row[4]));
    orders_info[i].set_payment(atoi(sql_row[5]));

    cout << orders_info[i].get_order_date() << "  " << orders_info[i].get_order_num()<< "  " << orders_info[i].get_menu_name() << endl;
    
    i++;
    }    
    sql.Disconnect();

    return orders_info;
}


string Pos_Handler::get_current_date()
{
	SQL sql;
	MYSQL_ROW sql_row;
	MYSQL_RES* res = nullptr;
	
	sql.Connect();

	res = sql.Get_current_date();
	sql_row = mysql_fetch_row(res);

	sql.Disconnect();

	cout << "date :" << sql_row[0] << endl;

	char* temp = strtok(sql_row[0]," ");  
    string current_date(temp);

	return current_date;
}

int Pos_Handler::get_currentDate_order_cnt(string current_date)
{
	SQL sql;
	int order_cnt;

    sql.Connect();    
	order_cnt = sql.Request_todayOrder_cnt(current_date);
	sql.Disconnect();
	return order_cnt;
}

void Pos_Handler::request_today_salesInfo(int clnt_sock)
{
	SQL sql;
	MYSQL_ROW sql_row;
	MYSQL_RES* res=nullptr;
	string current_date;
	int orders_cnt;
	OrderInfo *orders_info;

	// 오늘 날짜를 가져오다 
	current_date = get_current_date();
	// 오늘 날짜의 총 주문정보개수를 가져오다
	orders_cnt = get_currentDate_order_cnt(current_date);
	// 오늘 날짜 주문정보개수를 클라이언트에 전달한다. 
	write(clnt_sock,(char*)(&orders_cnt),sizeof(int));
	// 오늘 날짜의 총 주문정보들을 가져오다.
	sql.Connect();
	res = sql.Get_todayOrder_info(current_date);
	sql.Disconnect();
	// 오늘자 주문수만큼 클래스배열을 동적할당한다. 
	orders_info = new OrderInfo[orders_cnt];
	// 주문정보들을 클래스배열에 담는다. 
	int i=0;

	// 테이블뷰에 출력할 요소를 클래스배열에 등록한다. 
	while(sql_row = mysql_fetch_row(res))
	{
		orders_info[i].set_order_num(atoi(sql_row[0])); // 주문번호
		orders_info[i].set_menu_name(sql_row[1]); // 대표메뉴
		orders_info[i].set_amount(atoi(sql_row[2])); //품목수
		orders_info[i].set_tot_order_price(atoi(sql_row[3])); // 총액
		orders_info[i].set_payment(atoi(sql_row[4])); // 결제수단
		orders_info[i].set_status(atoi(sql_row[5])); // 주문결과

		cout << orders_info[i].get_order_num() << " " << orders_info[i].get_menu_name() << " " << orders_info[i].get_amount() << " " << orders_info[i].get_tot_order_price() << " " << orders_info[i].get_payment() << " " << orders_info[i].get_status() << endl;

		i++;
	}
	// 클래스배열을 클라이언트에 전달하다.
	write(clnt_sock,(char*)orders_info,orders_cnt*sizeof(OrderInfo));

}