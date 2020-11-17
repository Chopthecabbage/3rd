#ifndef ITEM_H
#define ITEM_H

#include "common.h"

class Item
{
private:
    int code;       // 아이템 코드
    char name[50];  // 아이템 이름
    int price;      // 아이템 가격
    int category;   // 아이템 분류
    char photo[50]; // 사진 경로
public:
    Item(){}
    Item(int code, char* name, int price,int category, char* photo)
    {
        this->code=code;
        strcpy(this->name,name);
        this->price=price;
        this->category=category;
        strcpy(this->photo,photo);
    }
    int GETcode() const {return code;} // 겟 함수
    char* GETname() {return name;}
    int GETprice() const {return price;}
    int GETcategory() const {return category;}
    char* GETphoto() {return photo;}

    void SETcode(int code) {this->code=code;} // 셋 함수
    void SETname(char* name) { strcpy(this->name,name); }
    void SETprice(int price) {this->price=price;}
    void SETcategory(int category) {this->category=category;}
    void SETphoto(char* photo) { strcpy(this->photo,photo); }

    Item& GETitem() {return *this;}

    bool operator==(const Item &item)
    {
        if(this->code==item.code && this->price==item.price && this->category==item.category)
        {
            if(!strcmp(this->name,item.name))
            {
                if(!strcmp(this->photo,item.photo))
                    return true;
            }
        }
        return false;
    }

    void initialize()
    {
        code=0;
        strcpy(this->name,"");
        price=0;
        category=0;
        strcpy(this->photo,"");
    }
    //
    void show()
    {
        qDebug() <<"코드: "<<code<<" 이름: "<<name<<" 가격: "<<price<<" 카테고리: "<<category<<" 경로: "<<photo;
    }

    void Set_Name_Price(char* name, int price)
    {
        strcpy(this->name,name);
        this->price=price;
    }

    void Set_Code_Category_Photo(int code, int category, char* photo)
    {
        this->code=code;
        this->category=category;
        strcpy(this->photo,photo);
    }
};

#endif // ITEM_H
