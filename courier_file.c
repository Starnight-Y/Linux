extern int user_num;
extern int cou_Count;
//搜索快递员函数
int cou_search(int cou_num){
    int i;
    for(i=0;i<cou_Count;i++)
        if(c[i].num==cou_num)  return i;
    return NO_FOUND;
}
//密码验证
int cou_land(){
    int i=1,j,temp;
    char user_pwd[15];
    char pwd;
    do{
        printf("\n请输入您的用户名：");
        scanf("%d",&user_num);
        printf("\n请输入您的密码：");
        system("stty -echo");
        pwd=getchar();
        scanf("%s",&pwd);
        system("stty echo");
        if((temp=cou_search(user_num))==NO_FOUND){
            printf("\n用户名错误！");
        }
        else{
            if(c[temp].num==user_num&&(strcmp(c[temp].password,&pwd)==0))
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
//快递员功能主菜单 
int cou_menu(){
    int choice=-1;
    printf("\n\n");
    printf("\t\t ----------------------------------------------------\n");
    printf("\t\t|                 快递员信息管理系统                 |\n");
    printf("\t\t|----------------------------------------------------|\n");
    printf("\t\t|           [1]----------------查询个人信息          |\n");
    printf("\t\t|           [2]----------------修改个人信息          |\n");
    printf("\t\t|           [3]----------------查询快递信息          |\n");
    printf("\t\t|           [4]----------------创建快递信息          |\n");
    printf("\t\t|           [5]----------------快递交给管理员        |\n");
    printf("\t\t|                                                    |\n");
    printf("\t\t|           [0]----------------退出系统              |\n");
    printf("\t\t ----------------------------------------------------\n");
    printf("请输入您的选择：");
    scanf("%d",&choice);
    return choice;
} 
//快递员功能控制函数
void courier(){
    int choice,temp,o=0,p=0;
    int putpac;
    system("./clear.sh");
    do{
        choice=cou_menu();
        system("./clear.sh");
        switch(choice){
            case 1:
                temp=cou_search(user_num);
                printf("账号：");
                printf("%d\n",c[temp].num);
                printf("姓名：");
                printf("%s\n",c[temp].name);
                printf("手机号：");
                printf("%s\n",c[temp].phone);
                printf("登录密码：");
                printf("%s\n",c[temp].password);
                break;
            case 2:
                cou_modify();
                system("./clear.sh");
                continue;
            case 3:
                for(int i=0;i<package_Count;i++){
                    if(strcmp(pac[i].cou_phone,c[temp].phone)==0){
                        printf("快递单号：%d\t",pac[i].num);
                        printf("收件人：%s\t",pac[i].name);
                        printf("收件人手机：%s\t",pac[i].stu_phone);
                        printf("快递员手机：%s\t",pac[i].cou_phone);
                        printf("快递状态：%s\n",pac[i].state);
                        o=1;
                    }                  
                }
                if(o==0){
                    printf("无结果！");
                }
                break;
            case 4:
                add_package();
                break;
            case 5:
                printf("\n\n\n\n输入需要提交的快递单号：");
                scanf("%d",&putpac);
                for(int i=0;i<package_Count;i++){
                   if((pac[i].num==putpac)&&strcmp(pac[i].cou_phone,c[temp].phone)==0&&strcmp(pac[i].state,"delivery")==0){
                        strcpy(pac[i].state,"arrival");
                        printf("提交成功！");
                        p=1;
                    }
                }
                if(p==0){
                    printf("提交失败！"); 
                }
                break;
            case 0:
                save_courier_information((char*)"courier.txt");
                save_package_information((char*)"package.txt");
                exit_system();
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
//快递员修改个人信息 
void cou_modify(){
    int temp;
    int choice;
    temp=cou_search(user_num);
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
            case 1:
                printf("请输入新姓名：");
                scanf("%s",c[temp].name);
                break;
            case 2:
                printf("请输入新手机号码：");
                scanf("%s",c[temp].phone);
                break;
            case 3:
                printf("请输入新密码：");
                scanf("%s",c[temp].password);
                break;
            case 0:
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
