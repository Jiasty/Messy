#include<iostream>
#include<assert.h>
using namespace std;

class Date
{
public:
    // 全缺省的构造函数
    Date(int year = 2024, int month = 1, int day = 1);
    // 拷贝构造函数d2(d1)
    Date(const Date& d);
    // 赋值运算符重载 d2 = d3 -> d2.operator=(&d2, d3)
    Date& operator=(const Date& d);
    // 析构函数
    ~Date();

    // 日期+=天数
    Date& operator+=(int day);
    // 日期+天数
    Date operator+(int day) const;
    // 日期-天数
    Date operator-(int day);
    // 日期-=天数

    Date& operator-=(int day);
    // 前置++
    Date& operator++();
    // 后置++
    Date operator++(int);
    // 后置--
    Date operator--(int);
    // 前置--
    Date& operator--();

    
    // >运算符重载
    bool operator>(const Date& d);
    // ==运算符重载
    bool operator==(const Date& d);
    // >=运算符重载
    bool operator >= (const Date& d);
    // <运算符重载
    bool operator < (const Date& d);
    // <=运算符重载
    bool operator <= (const Date& d);
    // !=运算符重载
    bool operator != (const Date& d);
    // 日期-日期 返回天数
    int operator-(const Date& d);

    bool CheckInvalid() const;
    //获取某年某月的天数.会频繁调用，在类里面定义,不声明定义分离,相当于inline
    int GetMonthDay(int year, int month) const
    {
        assert(month > 0 && month < 13);    
        static int month_day[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        //判断闰年2月
        if(2 == month && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) //判断顺序，是2月才继续判断，节省时间
        {
            return 29;
        }
        else
        {
            return month_day[month];
        }
    }

    //因为是全局函数要访问私有成员，所以加友元声明
    friend ostream& operator<<(ostream& out, const Date& d);
    friend istream& operator>>(istream& in, Date& d);
private:
    int _year;
    int _month;
    int _day;
};