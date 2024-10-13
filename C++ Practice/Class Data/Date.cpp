#include"Date.h"

// 全缺省的构造函数
Date::Date(int year, int month, int day)
{
    _year = year;
    _month = month;
    _day = day;
    //目前只支持公元前的日期，可以检查一下是否合法
    if(CheckInvalid())
    {
        cout << "Date is invalid." << endl;
    }
}
// 拷贝构造函数 d2(d1)
Date::Date(const Date& d)
{
    _year = d._year;
    _month = d._month;
    _day = d._day;
    //加const还能避免d被修改
    //d._year = _year;
}
// 赋值运算符重载  d2 = d3 -> d2.operator=(&d2, d3)
Date& Date::operator=(const Date& d)
{
    if(this != &d)  //检测是否自己给自己赋值,节约时间
    {
        _year = d._year;
        _month = d._month;
        _day = d._day;
    }
    return *this;
}
// 析构函数
Date::~Date()
{
    //Data类里全是内置类型，并且没有空间的申请，不写析构也没事
    cout << "~Date()" << endl;
}

// 日期+=天数
Date& Date::operator+=(int day)
{
    _day += day;
    while (_day > GetMonthDay(_year, _month))
    {
        _day -= GetMonthDay(_year, _month);
        _month++; //加了月就要判断月是否满了
        if(13 == _month)
        {
            _year++;
            _month = 1;
        }
    }
    return *this;
}
// 日期+天数 (不期望改变原日期)
Date Date::operator+(int day) const //这里返回值是临时对象，不能传引用返回.加const是为了避免*this被修改
{
    Date tmp(*this);
    //Date tmp = *this   也是拷贝构造
    tmp += day;
    return tmp;
}
// 日期-天数
Date Date::operator-(int day)
{
    Date tmp(*this);
    tmp -= day;
    return tmp;
}
// 日期-=天数
Date& Date::operator-=(int day)
{
    _day -= day;
    while(_day < 1)
    {
        _month--;
        if(0 == _month)
        {
            _year--;
            _month = 12;
        }
        _day += GetMonthDay(_year, _month);
    }
    return *this;
}

// 前置++
Date& Date::operator++()
{
    // ++_day;
    // if(_day > GetMonthDay(_year, _month))
    // {
    //     ++_month;
    //     if(13 == _month)
    //     {
    //         ++_year;
    //         _month = 1;
    //     }
    //     _day = 1;
    // }
    *this += 1;  //直接复用+=
    return *this;
}
// 后置++，返回加之前的数
//C++规定：后置++重载时多增加一个int类型的参数，但调用函数时该参数不用传递，编译器自动传递
Date Date::operator++(int)
{
    Date tmp(*this);
    *this += 1;
    return tmp;
}
// 后置--
Date Date::operator--(int)
{
    Date tmp(*this);
    *this -= 1;
    return tmp;
}
// 前置--
Date& Date::operator--()
{
    *this -= 1;
    return *this;
}

// >运算符重载
bool Date::operator>(const Date& d)
{
    if(_year > d._year)
        return true;
    else if(_year == d._year)
    {
        if(_month > d._month)
            return true;
        else if(_month == d._month)
            if(_day > d._day)
                return true;
    }
    return false;
}
// ==运算符重载
bool Date::operator==(const Date& d)
{
    return _year == d._year && _month == d._month && _day == d._day; //注意表达式的结果就是真假。
}
// >=运算符重载
bool Date::operator>=(const Date& d)
{
    return *this > d || *this == d;
}
// <运算符重载
bool Date::operator<(const Date& d)
{
    return !(*this >= d);
}
// <=运算符重载
bool Date::operator<=(const Date& d)
{
    return !(*this > d);
}
// !=运算符重载
bool Date::operator!=(const Date& d)
{
    return !(*this == d);
}
// 日期-日期 返回天数
int Date::operator-(const Date& d)
{
    int flag = 1, ret = 0;
    Date max(*this), min(d);

    if(*this < d)
    {
        flag = -1;
        max = d;
        min = *this;
    }
    while(min != max)
    {
        ++min; //最好用前置++，减少拷贝
        ++ret;
    }
    return ret * flag;
}
bool Date::CheckInvalid() const
{
    if(_year <= 0 || _month < 1 || _month > 12 || _day < 1 || _day > GetMonthDay(_year, _month))
        return true;
    return false;
}

//必须为全局，来决定参数的顺序，如果为成员函数，参数顺序不符合逻辑
ostream& operator<<(ostream& out, const Date& d)
{
    out << d._year << "/" << d._month << "/" << d._day << endl;
    return out;
}
istream& operator>>(istream& in, Date& d)
{
    while(1)
    {
        cout << "Please input in turn year month day." << endl;
        in >> d._year >> d._month >> d._day;
        if(d.CheckInvalid())
        {
            cout << "error date";
        }
        else
            break;
    }
    return in;
}