#include "SQL.h"

/*
    [ mysql 함수 설명 ] 
    http://www.mysqlkorea.com/sub.html?mcode=manual&scode=01&m_no=21855&cat1=22&cat2=596&cat3=606&lang=k
*/

SQL::SQL()
{
    connection = NULL;
    mysql_init(&conn); 
}

SQL::~SQL()
{
    if (&conn != NULL)
        mysql_close(&conn);
}

bool SQL::Connect()
{
    connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT, (char *)NULL, 0);
    
    if (connection == NULL)
    {
        fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
        return false;
    }
    //한글 사용을위해 추가 
    mysql_query(connection, "set session character_set_connection=utf8;");
    mysql_query(connection, "set session character_set_results=utf8;");
    mysql_query(connection, "set session character_set_client=utf8;");

    return true;
}
void SQL::Disconnect()
{
    mysql_free_result(sql_result);
    connection = NULL;
}

//////////////////////////////////////////////////
////////////  [ 키오스크 관련 ] ///////////////////
//////////////////////////////////////////////////
MYSQL_RES* SQL::Select_All_Menu()
{
    int query_stat;
    string query = "SELECT * FROM menu";
    query_stat = mysql_query(connection, query.c_str());
    if(query_stat != 0)
    {
        cout << "메뉴 조회 실패" << endl;
        fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));        
    }
    sql_result = mysql_store_result(connection);    

    return sql_result;    
}
void SQL::Insert_Order(Order order)
{
    int query_stat;
    string query = "INSERT INTO orders(date, payment, status) VALUES(NOW(), ";
    query += to_string(order.Get_Payment());
    query += ", 1 )";

    query_stat = mysql_query(connection, query.c_str());
    if(query_stat != 0)
    {
        cout << "주문 저장 실패" << endl;
        fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));        
    }
    //cout << "주문 저장 성공" << endl;
    query = "SELECT LAST_INSERT_ID()";
    query_stat = mysql_query(connection, query.c_str());
    if(query_stat != 0)
    {
        cout << "PK 가져오기 실패" << endl;
        fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));        
    }
    sql_result = mysql_store_result(connection);
    sql_row = mysql_fetch_row(sql_result);    
    int orders_pk = atoi(sql_row[0]);    
    //cout << "PK 가져오기 성공 : " << orders_pk << endl;
    
    int cart_cnt = order.Get_Cart().Get_Tot_Cnt();    
    
    for(int i = 0; i < cart_cnt; i++)
    {
        int code = order.Get_Cart().Get_Item(i).GETcode();
        int amount = order.Get_Cart().Get_Item_Cnt(i); 

        query = "INSERT INTO orders_detail VALUES(";   
        query += to_string(orders_pk);
        query += ", ";            
        query += to_string(code);
        query += ", ";
        query += to_string(amount);
        query += ")";
        query_stat = mysql_query(connection, query.c_str());
        if(query_stat != 0)
        {
            cout << "상세 주문 저장 실패" << endl;
            fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));        
        }
    }
    // cout << "상세 주문 저장 성공" << endl;
}

//////////////////////////////////////////////////
//////////////  [ 포스 관련 ] /////////////////////
//////////////////////////////////////////////////
int SQL::Query_and_check(string query)
{
	int query_stat;
	query_stat = mysql_query(connection, query.c_str());
	if (query_stat != 0)
	{
		cout << query_stat << endl;
		cout << "초기화 쿼리전달 실패" << endl;
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
	}
	return query_stat;
}

MYSQL_RES* SQL::Check_order_info(int sig,int order_num)
{
	string query;
	int query_stat;

	// 주문번호 조회
	if(sig==1)
	{
		query += "SELECT EXISTS (SELECT * FROM orders WHERE id=";
		query += to_string(order_num);
		query += ");";
	}
	// 주문처리상태 조회
	else if(sig==2)
	{
		query += "SELECT status FROM orders WHERE id=";
		query += to_string(order_num);
		query += ";";
	}

	//cout << "query :" << query << endl;

	query_stat = mysql_query(connection,query.c_str());
	
	if(query_stat != 0)
	{
		fprintf(stderr,"Mysql query error : %s",mysql_error(&conn));
	}
	sql_result = mysql_store_result(connection);

	return sql_result;
}

// 한건의 주문정보를 요청하다.
MYSQL_RES* SQL::Request_order_info(int order_num)
{
	string query;
	int query_stat;
	MYSQL_ROW sql_row;

	query += "SELECT m.name AS 메뉴명,m.price AS 가격,od.amount AS 개수,m.price*od.amount AS 주문금액 ";
	query += "FROM orders_detail ";
	query += "AS od JOIN menu AS m ";
	query += "ON od.code = m.code WHERE id=";
	query +=  to_string(order_num);
	query += ";";

	//cout << "query :" << query << endl;

	query_stat = mysql_query(connection,query.c_str());
	
	if(query_stat != 0)
	{
		fprintf(stderr,"Mysql query error : %s",mysql_error(&conn));
	}
	sql_result = mysql_store_result(connection);
	return sql_result;
}

MYSQL_RES* SQL::Request_order_cnt(int order_num)
{
	string query;
	int query_stat;

	query += "SELECT COUNT(*) ";
	query += "FROM orders_detail ";
	query += "AS od JOIN menu AS m ";
	query += "ON od.code = m.code WHERE id=";
	query += to_string(order_num);
	query += ";";

	//cout << "query :" << query << endl;

	query_stat = mysql_query(connection,query.c_str());
	
	if(query_stat != 0)
	{
		fprintf(stderr,"Mysql query error : %s",mysql_error(&conn));
	}
	sql_result = mysql_store_result(connection);

	return sql_result;
}

int SQL::Change_order_status(int order_num,int status)
{
	string query;
	int query_stat;
	// UPDATE orders SET status = 2 WHERE id=1;  
	query += "UPDATE orders SET status = ";
	query += to_string(status);
	query += " WHERE id=";
	query += to_string(order_num);
	query += ";";

	//cout << "query :" << query << endl;

	query_stat = mysql_query(connection,query.c_str());
	
	if(query_stat != 0)
	{
		fprintf(stderr,"Mysql query error : %s",mysql_error(&conn));
	}
	return query_stat;
}


MYSQL_RES* SQL::Request_allorder_cnt()
{
   string query;
   int query_stat;

   query += "SELECT COUNT(*) FROM orders WHERE status = 1;";
   //cout << "query :" << query << endl;
   query_stat = mysql_query(connection,query.c_str());
   
   if(query_stat != 0)
   {
      fprintf(stderr,"Mysql query error : %s",mysql_error(&conn));
   }
   sql_result = mysql_store_result(connection);

   return sql_result;
}

MYSQL_RES* SQL::Get_tot_order_info()
{
   string query;
   int query_stat;

   query += "SELECT date AS 날짜, o.id AS 주문번호 ,";
   query += "( SELECT name FROM menu WHERE code IN(SELECT MIN(code) FROM orders_detail WHERE id = o.id)) AS 대표메뉴,";
   query += "( SELECT COUNT(*) FROM orders_detail WHERE id = o.id ) AS 품목수,";
   query += "( SELECT SUM(m.price * od.amount) FROM orders_detail AS od, menu AS m WHERE od.code = m.code AND od.id = o.id) AS 총액, payment AS 결제수단 ";
   query += "FROM orders AS o WHERE status = 1;";

   //cout << "query :" << query << endl;

   query_stat = mysql_query(connection,query.c_str());
   if(query_stat != 0)
   {
      fprintf(stderr,"Mysql query error : %s",mysql_error(&conn));
   }
   sql_result = mysql_store_result(connection);

   return sql_result;
}


MYSQL_RES* SQL::Get_todayOrder_info(string current_date)
{
	string query;
	int query_stat;

	// SELECT id AS 주문번호,
	// ( SELECT name FROM menu WHERE code IN(SELECT MIN(code) FROM orders_detail WHERE id = o.id)) AS 대표메뉴,
	// ( SELECT COUNT(*) FROM orders_detail WHERE id = o.id ) AS 품목수,
	// ( SELECT SUM(m.price * od.amount) FROM orders_detail AS od, menu AS m WHERE od.code = m.code AND id = od.id ) AS 총액,
	// payment AS 결제수단,
	// status AS 주문결과
	// FROM orders AS o
	// WHERE date="2020-01-01";

	query += "SELECT o.id AS 주문번호,";
	query += "( SELECT name FROM menu WHERE code IN(SELECT MIN(code) FROM orders_detail WHERE id = o.id)) AS 대표메뉴,";
	query += "( SELECT COUNT(*) FROM orders_detail WHERE id = o.id ) AS 품목수,";
	query += "( SELECT SUM(m.price * od.amount) FROM orders_detail AS od, menu AS m WHERE od.code = m.code AND od.id = o.id ) AS 총액,";
	query += "payment AS 결제수단,status AS 주문결과 ";
	query += "FROM orders AS o WHERE DATE(date)='";
	query += current_date;
	query += "';";

	cout << "query :" << query << endl;

	query_stat = mysql_query(connection,query.c_str());
	if(query_stat != 0)
	{
		fprintf(stderr,"Mysql query error : %s",mysql_error(&conn));
	}
	sql_result = mysql_store_result(connection);

	return sql_result;	
}

int SQL::Request_todayOrder_cnt(string current_date)
{
	string query;
	int query_stat;	
	int order_cnt;

	query += "SELECT COUNT(*) FROM orders WHERE DATE(date)='";
	
	query += current_date;
	
	query += "';";

	cout << "query :" << query << endl;

	query_stat = mysql_query(connection,query.c_str());
	if(query_stat != 0)
	{
		fprintf(stderr,"Mysql query error : %s",mysql_error(&conn));
	}

	sql_result = mysql_store_result(connection);
	sql_row = mysql_fetch_row(sql_result);

	order_cnt = atoi(sql_row[0]);

	return order_cnt;
}

MYSQL_RES* SQL::Get_current_date()
{
	string query;
	int query_stat;

	query += "SELECT NOW();";
	
	cout << "query :" << query << endl;
	query_stat = mysql_query(connection,query.c_str());
	
	if(query_stat != 0)
	{
		fprintf(stderr,"Mysql query error : %s",mysql_error(&conn));
	}
	sql_result = mysql_store_result(connection);

	return sql_result;
}