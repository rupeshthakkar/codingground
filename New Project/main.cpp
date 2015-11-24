#include <iostream>

using namespace std;

class A
{
public: 
virtual ~A(){
        cout<<"\n~A";
    }
};

class B
{
public: 
 ~B(){
        cout<<"\n~B";
    }
};

class C:public A,public B
{
public: 
 ~C(){
        cout<<"\n~C";
    }
};

int main()
{
   C c;
   return 0;
}