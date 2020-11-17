#pragma once
#include <thread>
#include <mutex>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "Common.h"
#include "SQL.h"
#include "Kiosk_Handler.h"
#include "Pos_Handler.h"

class Server
{
private:
    int serv_sock; // 서버 소켓
    struct sockaddr_in serv_adr; // 주소 구조체
    
    vector <int> kiosk_socks; // 키오스크 클라이언트 소켓들
    vector <int> pos_socks; // 포스 클라이언트 소켓들
    vector <int> pos_order_socks; // 키오스크에서 주문시 포스에 주문 갱신하기위한 소켓들 
    
    mutex kiosk_mtx;
    mutex pos_mtx;
    mutex pos_order_mtx; 

public:
    Server(); // 서버 소켓 설정
    ~Server(); // 서버 소켓 close
    void Error_Handling(string msg); // 에러시 출력 후 프로그램 종료
    void Server_On(); // listen 상태 시작 및 클라이언트 연결 처리   
    void Kiosk_Thread(int sock); // 키오스크 쓰레드
    void Pos_Thread(int sock); // 포스 쓰레드
    void Clnt_Disconnect(int sock, int type); // 클라이언트 Discoonect처리
    int Find_Pos_Order_Sock(int sock); // 포스의 메인소켓으로 주문 소켓 찾기 
};
