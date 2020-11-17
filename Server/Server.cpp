#include "Server.h"

Server::Server()
{
    int nSockOpt = 1;
    
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET; 
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(PORT);
	
    setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &nSockOpt, sizeof(nSockOpt));
	if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr))==-1)
		Error_Handling("bind error");

}

Server::~Server()
{
    close(serv_sock);
}

void Server::Error_Handling(string msg)
{
    cout << msg << endl;
	exit(1);
}

void Server::Server_On()
{
    int clnt_sock;
    struct sockaddr_in clnt_adr;
    int clnt_adr_sz;
    int clnt_type;

    if(listen(serv_sock, 5)==-1)
	    Error_Handling("listen error");
	
	while(1)
	{
        clnt_type = 0;
        clnt_adr_sz=sizeof(clnt_adr);
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr,(socklen_t *)&clnt_adr_sz);
		cout << "[ 클라이언트 Connect IP: " << inet_ntoa(clnt_adr.sin_addr) << " SOCKET: " << clnt_sock << " ]" << endl;
		read(clnt_sock, &clnt_type, sizeof(int));

        if(clnt_type == TYPE_KIOSK) 
        {
            kiosk_mtx.lock();
            kiosk_socks.push_back(clnt_sock);
            kiosk_mtx.unlock();          

            thread thd(&Server::Kiosk_Thread, this, clnt_sock);
            thd.detach();
        }
        else if(clnt_type == TYPE_POS)
        {
            pos_mtx.lock();
            pos_socks.push_back(clnt_sock);
            pos_mtx.unlock();

            thread thd(&Server::Pos_Thread, this, clnt_sock);
            thd.detach();
        }
        else if(clnt_type == TYPE_POS_ORDER)
        {
            pos_order_mtx.lock();
            pos_order_socks.push_back(clnt_sock);
            pos_order_mtx.unlock();
            Pos_Handler pos;
            OrderInfo *orders_info; 
            int orders_cnt = 0;
            orders_cnt = pos.Progress_Tot_Order_Info_Cnt(); // 전체주문 갯수 반환
            cout << "[ orders_cnt : " << orders_cnt << " ]" << endl;
            write(clnt_sock, (char*)(&orders_cnt), sizeof(int));
            
            orders_info = pos.Progress_Tot_Order_Info(orders_cnt); // 전체주문 반환
            write(clnt_sock, (char*)orders_info, orders_cnt*sizeof(OrderInfo)); 
            
            delete[] orders_info;
        }
	}
}

// 키오스크 쓰레드 
void Server::Kiosk_Thread(int sock)
{
    cout << "[ 키오스크 Connect, 소켓 : "<< sock << "]"<< endl;
    Kiosk_Handler kiosk;
    Pos_Handler pos;
    int menu_cnt = 0;
    int data_size, signal = 0;

    // 키오스크 연결시 전체 메뉴 전송 
    Item *cafe_menu = kiosk.Get_Menu_From_DB(&menu_cnt);     
    write(sock, cafe_menu, sizeof(Item) * menu_cnt); 

    while(1)
    {
        data_size = read(sock, &signal, sizeof(int));
        if(data_size == 0) // 클라이언트 종료 
        {
            break;
        }
        else if(data_size != -1) // 전송한 신호가 있는경우 
        {
            switch(signal)
            {
                case K_ORDER_PROCESS: // 주문 완료
                    Order od;
                    read(sock, &od, sizeof(Order));     
                    kiosk.Save_Order_To_DB(od); // DB에 저장 

                    if(pos_order_socks.size() > 0)
                    {
                        OrderInfo *orders_info; 
                        int orders_cnt = 0;

                        orders_cnt = pos.Progress_Tot_Order_Info_Cnt(); // 전체주문 갯수 반환
                        orders_info = pos.Progress_Tot_Order_Info(orders_cnt); // 전체주문 반환
                        
                        pos_order_mtx.lock();
                        // 클라이언트 쪽에서 동적할당할 수 있게 총 갯수를 전달
                        for(int i = 0; i < pos_order_socks.size(); i++)
                            write(pos_order_socks[i], (char*)&orders_cnt, sizeof(orders_cnt));                    

                        // 전체 주문 정보 클래스배열을 클라이언트에 전달
                        for(int i = 0; i < pos_order_socks.size(); i++)
                            write(pos_order_socks[i], (char*)orders_info, orders_cnt*sizeof(OrderInfo));                         
                        pos_order_mtx.unlock();              
                        
                        delete[] orders_info;
                    }
                    break;                
            }
        }
    }
    Clnt_Disconnect(sock, TYPE_KIOSK);       
}

// 포스 쓰레드 
void Server::Pos_Thread(int sock)
{
    cout << "[ 포스 Connect, 소켓 : "<< sock << "]" << endl;    
    Pos_Handler pos;
    SignalInfo info ; // 시그널번호,주문번호정보를 가지는 클래스
    int data_size, signal, order_num;

    while(1)
    {
        data_size = read(sock, (char*)&info, sizeof(SignalInfo));
        if(data_size == 0) // 클라이언트 종료 
        {
            break;                
        }
        else if(data_size != -1) // 전송한 신호가 있는경우 
        {
            signal = info.get_signal();
            order_num = info.get_order_num();
            cout <<"[ signal : " << signal << "  order_num : " << order_num <<" ]"<<endl;
            switch(signal)
            {
                case P_ORDER_ES: // 주문 상태 확인
                    pos.Progress_Order_Es(sock, order_num);
                    break;                
                case P_ORDER_INFO: // 주문 상세정보 확인
                    pos.Progress_One_Order_info(sock, order_num);   
                    break;
                case P_ORDER_PROCESS: // 주문 처리
                    pos.Progress_Order_Process(sock);
                    break;
                case P_ORDER_CANCEL: // 주문 취소
                    pos.Progress_Order_Cancel(sock);    
                    break;
                case P_ORDER_REFRESH: {// 전체 주문 갱신                     
                    OrderInfo *orders_info; 
                    int orders_cnt = 0;                    
                    int order_sock = Find_Pos_Order_Sock(sock); // 주문 소켓 찾기 
                    cout << "order_sock : " << order_sock << "  pos_sock : " << sock <<endl; 
                    orders_cnt = pos.Progress_Tot_Order_Info_Cnt(); // 전체주문 갯수 반환
                    write(order_sock, (char*)&orders_cnt, sizeof(orders_cnt));
                    orders_info = pos.Progress_Tot_Order_Info(orders_cnt); // 전체주문 반환
                    write(order_sock, (char*)orders_info, orders_cnt*sizeof(OrderInfo)); 
                    delete[] orders_info;
                    break;  
                }
                case P_TODAY_SALES: // 당일 주문 조회
                    pos.request_today_salesInfo(sock);
                    break;                                  
            }
        }
    }
    Clnt_Disconnect(sock, TYPE_POS);        
}

void Server::Clnt_Disconnect(int sock, int type)
{
    string msg;
    vector<int>::iterator it;    
    int order_sock;

    if(type == TYPE_KIOSK)
    {
        msg = "[ 키오스크 Disconnect, 소켓 : ";        
        kiosk_mtx.lock();
        it = kiosk_socks.begin();
        for(int i = 0; i < kiosk_socks.size(); i++)
        {
            if(kiosk_socks[i] == sock)
            {
                it += i;
                kiosk_socks.erase(it);
                break;
            }
        }
        kiosk_mtx.unlock();
    }

    if(type == TYPE_POS)
    {
        msg = "[ 포스 Disconnect, 소켓 : ";     
        pos_mtx.lock();
        pos_order_mtx.lock();     
        it = pos_socks.begin();
        for(int i = 0; i < pos_socks.size(); i++)
        {
            if(pos_socks[i] == sock)
            {
                it += i;
                //close(pos_socks[i]);
                pos_socks.erase(it); // pos vector에서 pos소켓 삭제          
                //close(pos_order_socks[i]); // 포스주문 소켓 
                order_sock = pos_order_socks[i];
                pos_order_socks.erase(it); // pos_order vector에서 pos_order 소켓 삭제 
                break;
            }
        }
        pos_order_mtx.unlock();
        pos_mtx.unlock();
    }   
    msg += to_string(sock);
    msg += " ]";
    cout << msg << endl;    
    close(sock);
    close(order_sock);
}

int Server::Find_Pos_Order_Sock(int sock)
{
    int order_sock;

    pos_mtx.lock();
    pos_order_mtx.lock();
    for(int i = 0; i < pos_socks.size(); i++)
    {
        if(pos_socks[i] == sock)
        {
            order_sock = pos_order_socks[i];        
            break;    
        }
    }
    pos_order_mtx.unlock();
    pos_mtx.unlock();

    return order_sock;
}