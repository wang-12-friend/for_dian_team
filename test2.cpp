#include<iostream>
#include<fstream>
using namespace std;

int main(){
    string str;
    fstream text;
    string key[5000];
    string value[5000];
    int n=0;//正确行数数量
    text.open("data.txt");
    while(getline(text, str)){
        if(str.length()==0) continue;//空行
        bool k=false;//错行
        int j;//冒号位置
        for (int i=0;i<str.length();i++){
            if(str[i]==':'){
                k=true;
                j=i;
                break;
            }
        }
        if(!k) continue;
        //正确情况
        n++;
        key[n]=str.substr(0,j);
        value[n]=str.substr(j+1);
    };
    text.close();

    while(true){
        string search_key;
        cin>>search_key;
        if (search_key=="Quit") break;
        bool found=false;
        for(int i=1;i<=n;i++){
            if(key[i]==search_key){
                cout<<value[i]<<endl;
                found=true;
                break;
            }
        }
        if(!found) cout<<"Error"<<endl;
    }
}