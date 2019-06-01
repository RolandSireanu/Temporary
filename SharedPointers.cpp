#include <iostream>
#include <cstdlib>
#include <memory>
#include <vector>
#include <tuple>
using namespace std;


class MyType
{
  public:
  
  const unsigned int nr = 0xFF;
  
  MyType()
  {
      std::cout<<"MyType constructor "<<std::endl;
  }
  
  MyType(const MyType& arg)
  {
    std::cout<<"MyType copy constructor "<<std::endl;    
  }
  
  ~MyType()
  {
      std::cout<<"MyType destructor "<<std::endl;
  }
    
};

void printMe(const MyType* ptr)
{
    std::cout<<"nr = "<<ptr->nr<<std::endl;
}


int main()
{
    std::shared_ptr<MyType> sptr = std::make_shared<MyType>();
    std::shared_ptr<MyType> sptr2 = std::make_shared<MyType>();
    
    sptr2 = sptr;
    
    std::shared_ptr<MyType> sptr3(sptr2);
    
    std::cout<<"sptr3.use_count() = "<<sptr.use_count()<<std::endl;
    
    if(sptr2.unique())
    {
        std::cout<<"I am the only one who points to this resource !"<<std::endl;
    }
    else
    {
        std::cout<<"I am not the only one who points to this resource !"<<std::endl;
    }
    sptr2.reset(new MyType());
    
    printMe(sptr.get());
    
    std::cout<<"sptr1.use_count() = "<<sptr.use_count()<<std::endl;
    
    return 0;
}
