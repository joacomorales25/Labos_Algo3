#include <iostream>

using namespace std;


class Twenty{

};

class Fourty : public Twenty{


    public:
        void print(){
            cout << "Fourty" << endl;
        }
};

int main(){

    Fourty p = Fourty();
    p.print();


    return 0;
}