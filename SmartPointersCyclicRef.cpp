#include <iostream>
#include <memory>
using namespace std;

class Child;

class Parent
{
    public:
    
        unsigned int parentId;
        
        Parent(unsigned int arg_id):parentId(arg_id)
        {
            std::cout<<"Parent constructor "<<std::endl;
        }
        
        void SetChild(std::shared_ptr<Child>arg_child)
        {
            child = arg_child;
        }
        
        ~Parent()
        {
            std::cout<<"Parent destructor "<<std::endl;
        }
    
    private:
    
        std::shared_ptr<Child> child;
    
};


class Child
{
    public:
        Child(unsigned int arg_id , std::shared_ptr<Parent> arg_mom , std::shared_ptr<Parent> arg_dad)
        {
            mom = arg_mom;
            dad = arg_dad;
            childID = arg_id;
            
            std::cout<<"Child constructor "<<std::endl;
        }
        
        ~Child()
        {
            std::cout<<"Child destructor "<<std::endl;
        }
    
    private:    
        unsigned int childID;  
        std::shared_ptr<Parent> mom;
        std::shared_ptr<Parent> dad;
};

int main()
{
    std::shared_ptr<Parent>p = std::make_shared<Parent>(0xAA);
    std::shared_ptr<Parent>p2 = std::make_shared<Parent>(0xBB);
    std::shared_ptr<Child>c1 = std::make_shared<Child>(0x00 , p , p);
    
    p->SetChild(c1);
    p2->SetChild(c1);
    
    

    return 0;
}
