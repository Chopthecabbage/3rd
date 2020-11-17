#include "common.h"
#include "item.h"
#include "cart.h"

// 생성자
Cart::Cart() : tot_cnt(0),tot_price(0)
{
    memset(item_cnt,0,sizeof(int[CART_MAX]));
}
// 장바구니에 아이템 추가 함수
void Cart::Add_Item(Item item, int add_cnt)
{
    int idx=0;
    bool check = true;

    // 기존에 같은 품목 있나 검사
    for(int i = 0; i < tot_cnt; i++)
    {
        if(this->item[i] == item) // 중복품목 있을시
        {
            idx = i; // 인덱스 저장
            check = false;
            break;
        }
    }
    if(check) // 새로운 품목
    {
        this->item[tot_cnt] = item;
        item_cnt[tot_cnt] += add_cnt;
        tot_price+=item.GETprice();
        tot_cnt++;
    }
    else // 기존 품목
    {
        item_cnt[idx] += add_cnt; // 수량만 증가
        tot_price+=item.GETprice();
    }
}
// 장바구니 아이템 삭제 함수
void Cart::Remove_Item(Item item, int remove_cnt)
{
    Item temp;
    int idx=0, temp_cnt;

    // 지울 아이템 인덱스 찾기
    for(int i = 0; i < tot_cnt; i++)
    {
        if(this->item[i] == item)
        {
            idx = i;
            break;
        }
    }
    // 해당 아이템 수량 감소
    item_cnt[idx] -= remove_cnt;
    tot_price -= item.GETprice()*remove_cnt;
    // 만약 수량이 0이면
    if(item_cnt[idx] < 1)
    {
        this->item[idx].initialize(); // 아이템 삭제

        // 장바구니 배열 앞으로 한칸씩
        for(int i = idx; i < tot_cnt-1; i++)
        {
            temp = this->item[i];
            this->item[i] = this->item[i+1];
            this->item[i+1] = temp;

            temp_cnt = item_cnt[i];
            item_cnt[i] = item_cnt[i+1];
            item_cnt[i+1] = temp_cnt;
        }
        tot_cnt--;
    }
}

Cart& Cart::Get_Cart()
{
    return *this;
}

int Cart::Get_Tot_Cnt() const
{
    return tot_cnt;
}

Item* Cart::Get_Item_List()
{
    return item;
}

int* Cart::Get_Item_Cnt()
{
    return item_cnt;
}

int Cart::Get_Tot_Price() const
{
    return tot_price;
}

void Cart::Set_Item_Cnt(int amount)
{
    item_cnt[tot_cnt]=amount;
}

QString Cart::Item_Name(int dotX)
{
    QString temp;
    temp=QString(item[dotX].GETname());
    return temp;
}

QString Cart::Item_Price(int dotX)
{
    QString temp;
    temp=QString::number(item[dotX].GETprice());
    return temp;
}

QString Cart::Item_Amount(int dotX)
{
    QString temp;
    temp=QString::number(Get_Item_Cnt(dotX));
    return temp;
}

int Cart::Get_Item_Cnt(int dotX)
{
    return item_cnt[dotX];
}

void Cart::show(int dotX)
{
    item[dotX].show();
    qDebug() << "수량: " <<item_cnt[dotX];
}
//
char* Cart::Compare_Item_Name(int dotX)
{
    return item[dotX].GETname();
}

char* Cart::Compare_Item_Photo(int dotX)
{
    return item[dotX].GETphoto();
}

int Cart::Compare_Item_Price(int dotX)
{
    return item[dotX].GETprice();
}

void Cart::Set_Code_Category_Photo(int code,int category,char* photo,int dotX)
{
    item[dotX].Set_Code_Category_Photo(code,category,photo);
}

int Cart::Item_Tot_Price(int dotX)
{
    return item[dotX].GETprice()*item_cnt[dotX];
}








