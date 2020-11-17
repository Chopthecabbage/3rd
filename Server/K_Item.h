#pragma once
#include "Common.h"

class Item
{
private:
    int code;               // 아이템 코드
    char name[MAX_NAME];    // 아이템 이름
    int price;              // 아이템 가격
    int category;           // 아이템 분류
    char photo[MAX_PHOTO];  // 사진 경로
public:
    Item(){}
    Item(int _code, char* _name, int _price, int _category, char* _photo)
    {
        code = _code;
        strcpy(name, _name);
        price = _price;
        category = _category;
        strcpy(photo, _photo);        
    }
    int GETcode() const {return code;} // 겟 함수
    char* GETname()  {return name;}
    int GETprice() const {return price;}
    int GETcategory() const {return category;}
    char* GETphoto()  {return photo;}

    void SETcode(int code) {this->code=code;} // 셋 함수
    void SETname(char *_name) { strcpy(name, _name);}
    void SETprice(int price) {this->price=price;}
    void SETcategory(int category) {this->category=category;}
    void SETphoto(char* _photo) { strcpy(photo, _photo);}
    void Set_Item(int _code, char* _name, int _price, int _category, char* _photo)
    {
        code = _code;
        strcpy(name, _name);
        price = _price;
        category = _category;
        strcpy(photo, _photo);        
    }

    Item& GETitem() {return *this;}

    bool operator==(const Item &item)
    {
        if(code==item.code && !strcmp(name, item.name) && price==item.price && category==item.category && !strcmp(photo, item.photo))
            return true;
        return false;
    }

    void Prt()
    {
        cout << "code : " << code << "  name : " << name << " price : " << price << endl;
    }
};
