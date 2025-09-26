#include<iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstdio>
using namespace std;

//账号
string accounts[30]={"_","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","admin"};
//座位预约姓名
string seat_account[8][6][5][5];
//座位预约状态
bool seat_state[8][6][5][5];
//用户状态
string user_state="visitor";
//指令
string command;

//指令切分
string disintegrated_command[100];

const char* filename1 = "seat_state.txt";
const char* filename2 = "seat_account.txt";

//输出
void output(string str){
    cout<<"export:"<<str<<endl;
}

//读取座位信息
void read_seat(){
    ifstream file1;
    ifstream file2;
    file1.open("seat_state.txt");
    file2.open("seat_account.txt");
    if(!file1 || !file2){
        for(int date=1;date<=7;date++){
            for(int x=1;x<=5;x++){
                for(int y=1;y<=4;y++){
                    for(int z=1;z<=4;z++){
                        seat_state[date][x][y][z]=0;
                        seat_account[date][x][y][z]='-';
                    }
                }
            }
        }
    }

    else{
        string line;
        int floor=1;
        int hang=1;
        int date=1;
        while(getline(file1,line)){
            for(int i=0;i<4;i++){
                seat_state[date][floor][hang][i+1]=line[i]-'0';
            }
            if(hang==4){
                hang=0;
                floor++;
            }
            if(floor==6){
                floor=1;
                date++;
            }
            hang++;
        }

        floor=1;
        hang=1;
        date=1;
        while(getline(file2,line)){
            for(int i=0;i<4;i++){
                seat_account[date][floor][hang][i+1]=line[i];
            }
            if(hang==4){
                hang=0;
                floor++;
            }
            if(floor==6){
                floor=1;
                date++;
            }
            hang++;
        }
        file1.close();
        file2.close();
    }    
}

//写入座位信息
void write_seat(){
    ofstream file1;
    ofstream file2;
    file1.open("seat_state.txt");
    file2.open("seat_account.txt");
    for(int date=1;date<=7;date++){
            for(int x=1;x<=5;x++){
                for(int y=1;y<=4;y++){
                    for(int z=1;z<=4;z++){
                        file1<<to_string(seat_state[date][x][y][z]);
                        file2<<seat_account[date][x][y][z];
                    }
                    file1<<"\n";
                    file2<<"\n";
                }
            }
        }
    file1.close();
    file2.close();
}

//游客状态
class visitor{
    public:
        void login(){
            user_state="login_visitor";
            output("please input your account");
        }
        void exit(){
            user_state="visitor";
        }
        int quit(){
            return 0;
        }

        //非游客权限，但为学生和管理员共同权限

        //查询预约
        void reservation(string name){
            bool gh=false;
            for(int date=1;date<=7;date++){
                for(int x=1;x<=5;x++){
                    for(int y=1;y<=4;y++){
                        for(int z=1;z<=4;z++){
                            if(seat_account[date][x][y][z]==name){
                                cout<<"export:";
                                switch(date){
                                    case 1: cout<<"Monday ";break;
                                    case 2: cout<<"Tuesday ";break;
                                    case 3: cout<<"Wednesday ";break;
                                    case 4: cout<<"Thursday ";break;
                                    case 5: cout<<"Friday ";break;
                                    case 6: cout<<"Saturday ";break;
                                    case 7: cout<<"Sunday ";break;
                                }
                                switch(x){
                                    case 1: cout<<"Floor 1 ";break;
                                    case 2: cout<<"Floor 2 ";break;
                                    case 3: cout<<"Floor 3 ";break;
                                    case 4: cout<<"Floor 4 ";break;
                                    case 5: cout<<"Floor 5 ";break;
                                }
                                switch(y){
                                    case 1: cout<<"Seat 1 ";break;
                                    case 2: cout<<"Seat 2 ";break;
                                    case 3: cout<<"Seat 3 ";break;
                                    case 4: cout<<"Seat 4 ";break;
                                }
                                switch(z){
                                    case 1: cout<<z;break;
                                    case 2: cout<<z;break;
                                    case 3: cout<<z;break;
                                    case 4: cout<<z;break;
                                }
                                gh=true;
                                cout<<endl;
                            }
                        }
                    }
                }
            }
            if(!gh) output("No reserve");
        }

        //判断指令是否有误，并执行正确预约指令
        bool reserve(string command1,string command2,string command3,string command4,string command5,string command6,string name){
            int date;
            int x;
            int y;
            int z;
            if(command1=="Monday") date=1;
            else if(command1=="Tuesday") date=2;
            else if(command1=="Wednesday") date=3;
            else if(command1=="Thursday") date=4;
            else if(command1=="Friday") date=5;
            else if(command1=="Saturday") date=6;
            else if(command1=="Sunday") date=7;
            else return false;

            if (command3=="1") x=1;
            else if(command3=="2") x=2;
            else if(command3=="3") x=3;
            else if(command3=="4") x=4;
            else if(command3=="5") x=5;
            else return false; 

            if (command5=="1") y=1;
            else if(command5=="2") y=2;
            else if(command5=="3") y=3;
            else if(command5=="4") y=4;
            else return false;

            if (command6=="1") z=1;
            else if(command6=="2") z=2;
            else if(command6=="3") z=3;
            else if(command6=="4") z=4;
            else return false;
            
            if(seat_state[date][x][y][z]==1){
                output("this seat has been reserved");
                return true;
            }
            else{
                output("reserve successfully");
                seat_state[date][x][y][z]=1;
                seat_account[date][x][y][z]=name;
                return true;
            }

        }

        //判断指令是否正确，并执行正确楼层座位查询指令
        bool reserve_floor(string command1,string command2,string name){
            int date;
            int x;
            if(command1=="Monday") date=1;
            else if(command1=="Tuesday") date=2;
            else if(command1=="Wednesday") date=3;
            else if(command1=="Thursday") date=4;
            else if(command1=="Friday") date=5;
            else if(command1=="Saturday") date=6;
            else if(command1=="Sunday") date=7;
            else return false;

            if (command2=="1") x=1;
            else if(command2=="2") x=2;
            else if(command2=="3") x=3;
            else if(command2=="4") x=4;
            else if(command2=="5") x=5;
            else return false; 

            cout<<"export:"<<endl;
            for(int y=1;y<=4;y++){
                for(int z=1;z<=4;z++){
                    if(seat_account[date][x][y][z]==name){
                        cout<<2;
                    }
                    else if(name=="admin"){
                        cout<<seat_account[date][x][y][z];
                    }
                    else{
                        cout<<seat_state[date][x][y][z];
                    }
                }
                cout<<endl;
            }
            return true;
        }
};

//登录状态
class login_visitor:public visitor{
    public:
        void hello(){
            output("hello dian team");
        }
};

//学生状态
class student:public visitor{
    private:
        string name;
    public:
        void set_name(string n){
            name=n;
        }

        string get_name(){
            return name;
        }
        
};

//管理员状态
class admin:public visitor{
    private:
        string name="admin";
    public:
        void set_name(string n){
            name=n;
        }

        string get_name(){
            return name;
        }

        void clear(){
            ifstream filename;
            filename.open("seat_state.txt");
            if(!filename){
                filename.close();
                read_seat();
            }
            else{
                filename.close();
                remove(filename1);
                remove(filename2);
                read_seat();
            }
        }

        void remove_sb(string name){
            for(int date=1;date<=7;date++){
                for(int x=1;x<=5;x++){
                    for(int y=1;y<=4;y++){
                        for(int z=1;z<=4;z++){
                            if(seat_account[date][x][y][z]==name){
                                seat_account[date][x][y][z]="-";
                                seat_state[date][x][y][z]=0;
                            }
                        }
                    }
                }
            }

            output("remove success");
        }

        bool remove_time(string time){
            int date;
            if(time=="Monday") date=1;
            else if(time=="Tuesday") date=2;
            else if(time=="Wednesday") date=3;
            else if(time=="Thursday") date=4;
            else if(time=="Friday") date=5;
            else if(time=="Saturday") date=6;
            else if(time=="Sunday") date=7;
            else return false;
            for(int x=1;x<=5;x++){
                    for(int y=1;y<=4;y++){
                        for(int z=1;z<=4;z++){
                            seat_account[date][x][y][z]="-";
                            seat_state[date][x][y][z]=0;  
                        }
                    }
                }
            output("remove success");
            return true;
        }

        bool remove_floor(string time,string floor){
            int date;
            if(time=="Monday") date=1;
            else if(time=="Tuesday") date=2;
            else if(time=="Wednesday") date=3;
            else if(time=="Thursday") date=4;
            else if(time=="Friday") date=5;
            else if(time=="Saturday") date=6;
            else if(time=="Sunday") date=7;
            else return false;

            int x;
            if (floor=="1") x=1;
            else if(floor=="2") x=2;
            else if(floor=="3") x=3;
            else if(floor=="4") x=4;
            else if(floor=="5") x=5;
            else return false; 

            for(int y=1;y<=4;y++){
                for(int z=1;z<=4;z++){
                    seat_account[date][x][y][z]="-";
                    seat_state[date][x][y][z]=0;  
                }
            }
            output("remove success");
            return true;
        }
             
};

//判断账号是否合法
bool check_account(string name){
    for(int i=1;i<=27;i++){
        if(name==accounts[i]){
            return true;
        }
    }
    return false;
}

//分析指令中空格数量
int analyse_blank(string command){
    int k=0;
    for(int i=0;i<command.length();i++){
        if(command[i]==' '){
            k++;
        }
    }
    return k;
}


//将指令切片
string analyse_command(string command,int n){
    int location[100];
    location[0]=-1;
    int k=0;
    for(int i=0;i<command.length();i++){
        if(command[i]==' '){
            k++;
            location[k]=i;
        }
    }
    return command.substr(location[n-1]+1,location[n]-location[n-1]-1);
}

//获取指令
string get_command(){
    string command;
    cout<<"input:";
    getline(cin,command);
    return command;
}


//初始化四种状态
visitor state_visitor;
student state_student;
admin state_admin;
login_visitor state_login_visitor;

int main(){
    read_seat();    

    while(true){
        command=get_command();

        //游客状态
        if(user_state=="visitor"){
            if(command=="Login"){
                state_visitor.login();
                
            }
            else if(command=="Exit"){
                state_visitor.exit();
            }
            else if(command=="Quit"){
                write_seat();
                return state_visitor.quit();
            }
            else{
                output("Error");
            }
        }

        //登录状态
        else if(user_state=="login_visitor"){
            if(command=="Exit"){            
                state_login_visitor.exit();
            }
            else if(command=="Quit"){
                write_seat();
                return state_login_visitor.quit();
            }
            else
                if(check_account(command)){
                    if(command=="admin"){
                        user_state="admin";
                        state_admin.set_name(command);
                        output("login success!");
                    }
                    else{
                        user_state="student";
                        state_student.set_name(command);
                        output("login success!");
                    }
                }
                else{
                    output("Error");
                }
            
        }

        //学生状态
        else if(user_state=="student"){
            if(command=="Exit"){
                state_student.exit();
            }
            else if(command=="Quit"){
                write_seat();
                return state_student.quit();
            }
            else if(command=="Reservation"){
                state_student.reservation(state_student.get_name());
            }
            else{
                if(analyse_blank(command)==0){
                    output("Error");
                }
                else{
                    //将指令进行切片
                    for(int i=1;i<=analyse_blank(command)+1;i++){
                        disintegrated_command[i]=analyse_command(command,i);
                    }
                    //进行预约
                    if(analyse_blank(command)==6){
                        if(disintegrated_command[1]=="Reserve" && disintegrated_command[3]=="Floor" && disintegrated_command[5]=="Seat"){
                            if(!(state_student.reserve(disintegrated_command[2],disintegrated_command[3],disintegrated_command[4],disintegrated_command[5],disintegrated_command[6],disintegrated_command[7],state_student.get_name()))){
                                output("Error");
                            }
                        }
                        else{
                            output("Error");
                        }
                    }

                    //进行楼层座位的查询
                    else if(analyse_blank(command)==2){
                        if(disintegrated_command[2]=="Floor"){
                            if(!(state_student.reserve_floor(disintegrated_command[1],disintegrated_command[3],state_student.get_name()))){
                                output("Error");
                            }
                        }
                        else{
                            output("Error");
                        }
                    }
                    else{
                        output("Error");
                    }
                }
            }
            
        }

        //管理员状态
        else{
            if(command=="Exit"){
                state_student.exit();
            }
            else if(command=="Quit"){
                write_seat();
                return state_student.quit();
            }

            else if(command=="Clear"){
                state_admin.clear();
                output("clear success");
            }

            else{
                    //将指令进行切片
                    for(int i=1;i<=analyse_blank(command)+1;i++){
                        disintegrated_command[i]=analyse_command(command,i);
                    }
                    //帮助预约
                    if(analyse_blank(command)==7){
                        if(disintegrated_command[2]=="Reserve" && disintegrated_command[4]=="Floor" && disintegrated_command[6]=="Seat" && check_account(disintegrated_command[1]) && !(disintegrated_command[1]=="admin")){
                            if(!(state_admin.reserve(disintegrated_command[3],disintegrated_command[4],disintegrated_command[5],disintegrated_command[6],disintegrated_command[7],disintegrated_command[8],disintegrated_command[1]))){
                                output("Error");
                            }
                        }
                        else{
                            output("Error");
                        }
                    }

                    //进行楼层座位的查询
                    else if(analyse_blank(command)==2){
                        if(disintegrated_command[2]=="Floor"){
                            if(!(state_student.reserve_floor(disintegrated_command[1],disintegrated_command[3],state_admin.get_name()))){
                                output("Error");
                            }
                        }
                        else{
                            output("Error");
                        }
                    }

                    //删除预约
                    else if(analyse_blank(command)==1){
                        //删除某人预约
                        if(disintegrated_command[1]=="Remove" && check_account(disintegrated_command[2]) && !(disintegrated_command[2]=="admin")){
                            state_admin.remove_sb(disintegrated_command[2]);
                        }
                        //删除某天预约
                        else if(disintegrated_command[1]=="Remove"){
                            if(!(state_admin.remove_time(disintegrated_command[2]))){
                                output("Error");
                            }
                        }
                        else{
                            output("Error");
                        }
                    }

                    //删除楼层
                    else if(analyse_blank(command)==3){
                        if(disintegrated_command[1]=="Remove" && disintegrated_command[3]=="Floor"){
                            if(!(state_admin.remove_floor(disintegrated_command[2],disintegrated_command[4]))){
                                output("Error");
                            }
                        }
                    }

                    else{
                        output("Error");
                    }
                }
        }

    }
    return 0;

}