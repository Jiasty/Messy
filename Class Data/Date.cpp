#include"Date.h"


// 全缺省的构造函数
Date::Date(int year, int month, int day)
    :_year(year)
    ,_month(month)
    ,_day(day)
{
    //目前只支持公元前的日期，可以检查一下是否合法
    if(CheckInvalid())
    {
        cout << "Date is invalid." << endl;
    }
}
// 拷贝构造函数
// d2(d1)
Date::Date(const Date& d)
{

}
// 赋值运算符重载
// d2 = d3 -> d2.operator=(&d2, d3)
Date& Date::operator=(const Date& d)
{

}
// 析构函数
Date::~Date()
{

}

// 日期+=天数
Date& Date::operator+=(int day)
{

}
// 日期+天数
Date Date::operator+(int day)
{

}
// 日期-天数
Date Date::operator-(int day)
{

}
// 日期-=天数

Date& Date::operator-=(int day)
{

}
// 前置++
Date& Date::operator++()
{

}
// 后置++
Date Date::operator++(int)
{

}
// 后置--
Date Date::operator--(int)
{

}
// 前置--
Date& Date::operator--()
{}


// >运算符重载
bool Date::operator>(const Date& d)
{}
// ==运算符重载
bool Date::operator==(const Date& d)
{}
// >=运算符重载
bool Date::operator >= (const Date& d)
{}
// <运算符重载
bool Date::operator < (const Date& d)
{}
// <=运算符重载
bool Date::operator <= (const Date& d)
{}
// !=运算符重载
bool Date::operator != (const Date& d)
{}
// 日期-日期 返回天数
int Date::operator-(const Date& d)
{}
bool Date::CheckInvalid()
{
    if(_year <= 0 || _month < 1 || _month > 12 || _day < 1 || _day > GetMonthDay(_year, _month))
        return true;
    return false;
}