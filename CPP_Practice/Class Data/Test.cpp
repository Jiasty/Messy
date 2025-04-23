#include"Date.h"

void test1()
{
    Date d1(2024, 1, 4);
    Date d2(2024, 2, 29);

    //cout << (d1 > d2) <<endl;
    //cout << d1-- <<endl;
    cout << (d2 - d1) <<endl; 

}

int main()
{
    test1();
    
    
    return 0;
}