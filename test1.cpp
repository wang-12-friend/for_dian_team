#include<iostream>
using namespace std;

int main(){
    string a;
    bool b=true;
    while (b)
    {
        cout<<"input:";
        cin>>a;
        if(a=="Dian"){
            cout<<"2002"<<endl;
        }
        else if(a=="Quit"){
            b=false;
        }
        else{
            cout<<"Error"<<endl;
        }
    }
    return 0;
}