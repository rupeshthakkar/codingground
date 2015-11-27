#include <iostream>

using namespace std;

class A{
    int fun(){};
};
class V{
    virtual int fun(){};
};
class VD{
    int fun(){};
};
int main()
{
   A a;    
   V v; 
   VD vd;
   
   cout <<"A="<<sizeof(a)<<"V="<< sizeof(v)<<"VD="<< sizeof(vd) << endl;
   cout << "Hello World" << endl; 
   
   return 0;
}


