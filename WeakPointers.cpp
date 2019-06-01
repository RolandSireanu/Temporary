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



int main()
{
    
    std::weak_ptr<MyType> wptr;
    
    {
        std::shared_ptr<MyType> sptr = std::make_shared<MyType>();
        wptr = sptr;
    
        std::cout<<"sptr.use_count() = "<<sptr.use_count()<<std::endl;
        std::cout<<"wptr.use_count() = "<<wptr.use_count()<<std::endl;
        std::shared_ptr<MyType> sptr2 = wptr.lock();
        std::cout<<"sptr.use_count() = "<<sptr.use_count()<<std::endl;
    }
    
    if(wptr.expired())
    {
        std::cout<<"the managed resource has been destroyed ! "<<std::endl;
    }
    
    
    
    return 0;
}
