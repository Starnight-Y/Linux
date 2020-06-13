#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "termios.h"
#include "unistd.h"
#include "macro_file.h"                        //宏定义文件 
#include "struct_file.h"                       //结构体文件 
#include "function_declare_file.h"             //函数声明文件 
#include "student_file.c"                      //学生代码文件 
#include "courier_file.c"                      //快递员代码文件 
#include "administrator_file.c"                //管理员代码文件
//全局变量
int stu_Count;                                 //学生数量 
int package_Count;                             //快递数量 
int user_num;                                  //账号 
int cou_Count;                                 //快递员数量 
//主函数
int main(){
    int temp,choice,t=-1;
    system("./judgeS.sh");                     //如果当前没有student.txt文件，则创建一个 
    system("./judgeC.sh");                     //如果当前没有courier.txt文件，则创建一个
    system("./judgeP.sh");                     //如果当前没有package.txt文件，则创建一个
    system("./clear.sh");                      //清屏 
    welcome();                                 //欢迎界面
    choice=user_type();                        //用户选择界面
    if(choice!=0){
        Load_package_information((char*)"package.txt");
        Load_student_information((char*)"student.txt");
        Load_courier_information((char*)"courier.txt");
        getchar();
        if(getchar()) system("./clear.sh");     //清屏 
            if(choice==1){
                t=regs();                       //登录注册界面 
                if(t==1){
                    regs_student();             //学生注册
                    temp=land(choice); 
                }
                else if(t==0){
                    exit_system();              //退出系统 
                }
                else if(t==2){
                    temp=land(choice);          //学生登录 
                }
            }
            else if(choice==2){
                temp=land(choice);              //管理员登录 
            }
            else if(choice==3){
                t=regs();
                if(t==1){
                    regs_courier();             //快递员注册
                    temp=land(choice); 
                }
                else if(t==0){
                    exit_system();              //退出系统 
                }
                else if(t==2){
                    temp=land(choice);          //快递员登录 
                }
            }
            if(temp==YES){
                system("./clear.sh");
                switch(choice){
                case 1:
                    student();                  //学生界面 
                    break;
                case 2:
                    administrator();            //管理员界面 
                    break;
                case 3:
                    courier();                  //快递员界面 
                    break;
                }
            }
            else
                printf("\n对不起，您的登录机会已用完！\n欢迎下次登录！\n");
    }
    else
        printf("\n系统已退出，欢迎下次登录！\n"); 
    return 0;
}
//欢迎界面
void welcome(){
    printf("\n\n");
    printf("\t\t ----------------------------------------------------\n");
    printf("\t\t|                                                    |\n");
    printf("\t\t|                                                    |\n");
    printf("\t\t|                                                    |\n");
    printf("\t\t|                                                    |\n");
    printf("\t\t|             欢迎使用之江学院菜鸟驿站               |\n");
    printf("\t\t|                                                    |\n");
    printf("\t\t|                                                    |\n");
    printf("\t\t|                                                    |\n");
    printf("\t\t|                                                    |\n");
    printf("\t\t ----------------------------------------------------\n");
    printf("\n\n\n\n按Enter键返回……");
    if(getchar())
        system("./clear.sh");
}
//选择用户类型界面
int user_type(){
    int choice;
    choice=-1;
    system("./clear.sh");
    printf("\n\n");
    printf("\t\t ----------------------------------------------------\n");
    printf("\t\t|                     用户类型                       |\n");
    printf("\t\t|----------------------------------------------------|\n");
    printf("\t\t|                                                    |\n");
    printf("\t\t|           [1]----------------学生                  |\n");
    printf("\t\t|           [2]----------------管理员                |\n");
    printf("\t\t|           [3]----------------快递员                |\n");
    printf("\t\t|                                                    |\n");
    printf("\t\t|           [0]----------------退出系统              |\n");
    printf("\t\t|                                                    |\n");
    printf("\t\t ----------------------------------------------------\n");
    printf("\n\n\n请输入您的选择：");
    scanf("%d",&choice);
    return choice; 
} 
//系统退出函数
void exit_system(){
    system("./clear.sh");
    printf("\n\n");
    printf("\t\t ----------------------------------------------------\n");
    printf("\t\t|                                                    |\n");
    printf("\t\t|                                                    |\n");
    printf("\t\t|                                                    |\n");
    printf("\t\t|                                                    |\n");
    printf("\t\t|            感谢您的使用，欢迎下次登录！:)          |\n");
    printf("\t\t|                                                    |\n");
    printf("\t\t|                                                    |\n");
    printf("\t\t|                                                    |\n");
    printf("\t\t|                                                    |\n");
    printf("\t\t ----------------------------------------------------\n");
    exit(0);
}
//注册界面
int regs()
{
    int ch;
    ch = -1;
    system("./clear.sh");
	printf("\n\n");
    printf("\t\t ----------------------------------------------------\n");
    printf("\t\t|                                                    |\n");
    printf("\t\t|                                                    |\n");
    printf("\t\t|            [1]----------------新用户               |\n");
    printf("\t\t|            [2]----------------老用户               |\n");
    printf("\t\t|                                                    |\n");
    printf("\t\t|            [0]----------------退出系统             |\n");
    printf("\t\t|                                                    |\n");
    printf("\t\t|                                                    |\n");
    printf("\t\t|                                                    |\n");
    printf("\t\t ----------------------------------------------------\n");
    printf("\n\n\n请输入您的选择：");
    scanf("%d", &ch);
    if(getchar()) 
        system("./clear.sh"); 
    return ch;
} 
//控制登录函数
int land(int user_type){
    int temp;
    switch(user_type){
        case 1:
            temp=stu_land();                    //学生                              
            break;
        case 2:
            temp=admin_land();                  //管理员验证 
            break;
        case 3:
            temp=cou_land();                    //快递员验证 
            break;
        default:
            printf("\n对不起，您选择错误！\n");
            break;
    }
    return temp;
} 
//linux中读取单个字符（用不到） 
int getch(){
    struct termios oldt,newt;
    int ch;
    tcgetattr(STDIN_FILENO,&oldt);
    newt=oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO,TCSANOW,&newt);
    ch=getchar();
    tcsetattr(STDIN_FILENO,TCSANOW,&oldt);
    return ch;
}
