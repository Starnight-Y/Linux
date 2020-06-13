extern int user_num;
extern int stu_Count;
extern int package_Count;
//搜索学生函数
int stu_search(int stu_num){
    int i;
    for(i=0;i<stu_Count;i++)
        if(s[i].num==stu_num) return i;
    return NO_FOUND;
}
//密码验证
int stu_land(){
    int i=1,j,temp;
    char user_pwd[15];
    char pwd;
    do{
        printf("\n请输入您的用户名：");
        scanf("%d",&user_num);
        printf("\n请输入您的密码：");
        system("stty -echo");                                                          //密码加密，看不到输入的密码 
        pwd=getchar();
        scanf("%s",&pwd);
        system("stty echo");                                                           //密码加密，看不到输入的密码
        if((temp=stu_search(user_num))==NO_FOUND){
            printf("\n用户名错误！");
        }
        else{
            if(s[temp].num==user_num&&(strcmp(s[temp].password,&pwd)==0))
                return YES;
            else
                printf("\n密码错误！");
        }
        printf("请重新输入！\n");
        i++;
        printf("---------------------------------------------\n");
        }while(i<3);
        return NO;
}
//学生功能主菜单
int stu_menu(){
    int choice=-1;
    printf("\n\n");
    printf("\t\t ----------------------------------------------------\n");
    printf("\t\t|                 学生信息管理系统                   |\n");
    printf("\t\t|----------------------------------------------------|\n");
    printf("\t\t|           [1]----------------查询个人信息          |\n");
    printf("\t\t|           [2]----------------修改个人信息          |\n");
    printf("\t\t|           [3]----------------查询快递信息          |\n");
    printf("\t\t|           [4]----------------取件                  |\n");
    printf("\t\t|                                                    |\n");
    printf("\t\t|           [0]----------------退出系统              |\n");
    printf("\t\t|                                                    |\n");
    printf("\t\t ----------------------------------------------------\n");
    printf("请输入您的选择：");
    scanf("%d",&choice);
    return choice;
}
//学生功能控制函数 
void student(){
    int choice,temp;
    int pacnum,o=0,p=0;
    char location[20],code[20];
    system("./clear.sh");
    do{
        choice=stu_menu();
        system("./clear.sh");
        switch(choice){
            case 1:                                                                  //查询学生个人信息 
                temp=stu_search(user_num);
                printf("账号：");
                printf("%d\n",s[temp].num);
                printf("姓名：");
                printf("%s\n",s[temp].name);
                printf("手机号：");
                printf("%s\n",s[temp].phone);
                printf("登录密码：");
                printf("%s\n",s[temp].password);
                break;
            case 2:                                                                  //修改学生个人信息 
                stu_modify();
                system("./clear.sh");
                continue;
            case 3:                                                                  //查询与学生关联的快递信息 
                for(int i=0;i<package_Count;i++){
                    if(strcmp(pac[i].stu_phone,s[temp].phone)==0){
                        printf("快递单号：%d\t",pac[i].num);
                        printf("收件人：%s\t",pac[i].name);
                        printf("收件人手机：%s\t",pac[i].stu_phone);
                        printf("快递员手机：%s\t",pac[i].cou_phone);
                        printf("所在快递柜位置：%s\t",pac[i].location);
                        printf("快递状态：%s\t",pac[i].state);
                        printf("取件码：%s\n",pac[i].code);
                        o=1;
                    }
                 }
                 if(o==0){
                     printf("no result!");
                 }
                break;
            case 4:                                                                   //取件 
                printf("输入您想要取件的快递单号：");
                scanf("%d",&pacnum);
                for(int i=0;i<package_Count;i++){
                        if((pac[i].num==pacnum)&&(strcmp(pac[i].state,"pick")==0)&&strcmp(s[temp].phone,pac[i].stu_phone)==0){
                        printf("输入快递柜位置：");
                        scanf("%s",&location[1]);
                        printf("输入取件码：");
                        scanf("%s",&code[1]);
                        if((strcmp(pac[i].location,&location[1])==0)&&(strcmp(pac[i].code,&code[1])==0)){
                            printf("取件成功！");
                            p=1;
                            strcpy(pac[i].state,"finish");                             //快递状态改为"finish"已取件状态 
                        }
                    }
                }
                    if(p==0){
                        printf("failure!");
                    }
                break;
            case 0:                                                                    //保存数据并退出系统 
                save_student_information((char*)"student.txt");                        //保存学生数据到student.txt 
                save_package_information((char*)"package.txt");                        //保存快递数据到package.txt 
                exit_system();                                                         //退出系统 
                break;
            default:
                printf("\n对不起，您选择错误！\n");
                break;
        }
        printf("\n\n\n\n按Enter键返回……");
        getchar();
        if(getchar())
            system("./clear.sh");
    }while(1);
}
//学生修改个人信息
void stu_modify(){
    int temp;
    int choice;
    temp=stu_search(user_num);
    system("./clear.sh");
    do{
        printf("\n\n");
        printf("\t\t ----------------------------------------------------\n");
        printf("\t\t|                请选择您要修改的信息                |\n");
        printf("\t\t|----------------------------------------------------|\n");
        printf("\t\t|                                                    |\n");
        printf("\t\t|           姓名                     请按 1          |\n");
        printf("\t\t|           手机号码                 请按 2          |\n");
        printf("\t\t|           登录密码                 请按 3          |\n");
        printf("\t\t|                                                    |\n");
        printf("\t\t|           取消                     请按 0          |\n");
        printf("\t\t|                                                    |\n");
        printf("\t\t ----------------------------------------------------\n");
        printf("请选择：");
        scanf("%d",&choice);
        switch(choice){
            case 1:                                                                   //修改姓名 
                printf("请输入新姓名：");
                scanf("%s",s[temp].name);
                break;
            case 2:                                                                   //修改手机
                printf("请输入新手机号码：");
                scanf("%s",s[temp].phone);
                break;
            case 3:                                                                   //修改密码 
                printf("请输入新密码：");
                scanf("%s",s[temp].password);
                break;
            case 0:                                                                   //返回学生界面  
                return;
            default:
                printf("\n无效选项！");
                continue; 
            }
            printf("\n\n\n\n按Enter键返回……");
            getchar();
            if(getchar()) system("./clear.sh");      
    }while(choice!=0);
} 
