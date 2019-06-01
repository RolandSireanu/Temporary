#include <iostream>
#include <cstdlib>
#include <memory>
#include <vector>
#include <tuple>
using namespace std;

//Simple template sum function 
template<typename T1 , typename T2>
T1 add(T1 arg1 , T2 arg2)
{
    return arg1 + arg2;
}

//Specialization of function , deleted 
//Can't add integer with character
template<>
int add(int , char) = delete;

//Declare template alias 
template<typename T>
using MyVector = std::vector<T>;


template<>
int add(int a, int b)
{
    return a + b;
}


template<typename T , T arg1 , T arg2>
T sumation()
{
    
    return arg1 + arg2;
}

int sumAllOfThem()
{
    return 0;
}

template<typename T , typename... D>
T sumAllOfThem(T arg1 , D... args)
{
    T tempVar = 0x00;
    
    return arg1+(sumAllOfThem(args...));
}

enum class Color:unsigned char {white =0xAA , blue = 0xBB , red = 0xCC};




template<typename T>
struct MyStruct
{
    typedef std::vector<T> type;
};

enum Positions {integer , character , floatingPoint};

std::tuple<int,char,double> t {0xFF , 'W' , 0.00145};

int main()
{
    MyVector<int> v;
    
    MyStruct<int>::type v2;

    Color c = Color::white;
    
    std::cout<<"1st : "<<std::get<integer>(t)<<" 2nd : "<<std::get<character>(t)<<" 3th : "<<std::get<floatingPoint>(t)<<std::endl;
        
    std::cout<<"sum = "<<add<int,int>(2,3)<<std::endl;
    
    std::cout<<"sumation = "<<sumation<int , 20,35>()<<std::endl;
    std::cout<<"sum all the values = "<<sumAllOfThem<int , int , int , int , int>(10,20,30,40,50)<<std::endl;
    //add<int , char>(2,'a');       Error used of deleted function 
    
    return 0;
}
