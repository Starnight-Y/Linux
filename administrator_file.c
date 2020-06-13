extern int package_Count;
extern int user_num;
//搜索快递函数
int package_search(int package_num){
    int i;
    for(i=0;i<package_Count;i++){
        if(pac[i].num==package_num) return i;
    }
    return NO_FOUND;
}
//管理员登录密码验证 
int admin_land(){
    int i=1,j;
    char user_name[15];
    char admin_pwd[15];
    char pwd;
    do{
        printf("\n请输入管理员用户名：");
        scanf("%s",user_name);
        printf("\n请输入管理员密码:");
        system("stty -echo");
        pwd=getchar();
        scanf("%s",&pwd);
        system("stty echo");
        if((strcmp(user_name,ADMIN_PASSWARD)==0 && strcmp(&pwd,ADMIN_PASSWARD)==0)){
            return YES;
        }
        else
            printf("\n密码错误！");
        printf("请重新输入！\n");
        i++;
        printf("---------------------------------------------------\n");
    }while(i<=3);
    return NO;
} 
//管理员功能主菜单
int admin_menu(){
    int choice=-1;
	printf("\n\n");
    printf("\t\t ----------------------------------------------------\n");
    printf("\t\t|                   管理员管理系统                   |\n");
    printf("\t\t|----------------------------------------------------|\n");
    printf("\t\t|                                                    |\n");
    printf("\t\t|           [1]----------------维护学生信息          |\n");
    printf("\t\t|           [2]----------------维护快递信息          |\n");
    printf("\t\t|                                                    |\n");
    printf("\t\t|                                                    |\n");
    printf("\t\t|           [0]----------------退出系统              |\n");
    printf("\t\t|                                                    |\n");
    printf("\t\t ----------------------------------------------------\n");
    printf("请输入您的选择：");
    scanf("%d",&choice);
    return choice;
}
//管理员功能控制函数
void administrator(){
    int choice;
    system("./clear.sh");
    do{
        choice=admin_menu();
        system("./clear.sh");
        switch(choice){
            case 1:
                manage_student();
                break;
            case 2:
                manage_package();
                break;
            case 0:
                save_package_information((char*)"package.txt");
                save_student_information((char*)"student.txt");
                exit_system();
                break;
            default:
                printf("\n对不起，您选择错误！\n");
                break;
        }
        system("./clear.sh");
    }while(1);
} 
//维护学生信息的菜单和控制
void manage_student(){
    int choice;
    int num;
    do{
    	printf("\n\n");
        printf("\t\t ----------------------------------------------------\n");
        printf("\t\t|                  学生维护管理系统                  |\n");
        printf("\t\t|----------------------------------------------------|\n");
        printf("\t\t|                                                    |\n");
        printf("\t\t|           [1]----------------录入学生信息          |\n");
        printf("\t\t|           [2]----------------浏览学生信息          |\n");
        printf("\t\t|           [3]----------------删除学生信息          |\n");
        printf("\t\t|           [4]----------------修改学生信息          |\n");
        printf("\t\t|           [0]----------------取消                  |\n");
        printf("\t\t|                                                    |\n");
        printf("\t\t ----------------------------------------------------\n"); 
        printf("请选择：");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                add_student();
                break;
            case 2:
                display_all_student();
                break;
            case 3:
                dele_student();
                break;
            case 4:
                printf("输入您要修改的学生账号：");
                scanf("%d",&num); 
                for(int i=0;i<stu_Count;i++){
                    if(s[i].num==num){
                        user_num=num;
                        stu_modify();                        
                    }
                    else{
                        printf("未找到学生账号！");
                    }
                }
            case 0:
                return;
            default:
                printf("\n对不起，您选择错误！\n");
                break;
        }
        printf("\n\n\n\n按Enter键返回……");
        getchar();
        if(getchar()) system("./clear.sh");      
    }while(1);
}
//管理员录入新学生
void add_student(){
    int i;
    char judge;
    printf("\n\n");
    printf("输入账号：");
    scanf("%d",&s[stu_Count].num);
    printf("输入姓名：");
    scanf("%s",s[stu_Count].name);
    printf("输入手机号：");
    scanf("%s",s[stu_Count].phone);
    printf("输入密码：");
    scanf("%s",s[stu_Count].password);
    getchar();
    printf("\n\n\n您的录入操作已完成！您是否要保存录入的信息？\n");
    printf("\n\"是\" 请按 Y");
    printf("\n\"否\" 请按 N\n");
    judge=getchar();
    if(judge=='Y' || judge=='y'){
        stu_Count++;
    }
    else
        printf("\n\n信息未保存！\n");
}
//注册新学生
void regs_student(){
    int i;
    char judge;
    printf("\n\n");
    printf("输入账号：");
    scanf("%d",&s[stu_Count].num);
    printf("\n"); 
    printf("输入姓名：");
    scanf("%s",s[stu_Count].name);
    printf("\n"); 
    printf("输入手机号：");
    scanf("%s",s[stu_Count].phone);
    printf("\n"); 
    printf("输入密码：");
    scanf("%s",s[stu_Count].password);
    printf("\n"); 
    getchar();
    printf("\n\n\n您的录入操作已完成！您是否要保存录入的信息？\n");
    printf("\n\"是\" 请按 Y");
    printf("\n\"否\" 请按 N\n");
    judge=getchar();
    if(judge=='Y' || judge=='y'){
        stu_Count++;
    }
    else
        printf("\n\n注册失败！\n");
    if(getchar()) system("./clear.sh");
}
//注册新快递员
void regs_courier(){
    int i;
    char judge;
    printf("\n\n");
    printf("输入账号：");
    scanf("%d",&c[cou_Count].num);
    printf("\n"); 
    printf("输入姓名：");
    scanf("%s",c[cou_Count].name);
    printf("\n"); 
    printf("输入手机号：");
    scanf("%s",c[cou_Count].phone);
    printf("\n"); 
    printf("输入密码：");
    scanf("%s",c[cou_Count].password);
    printf("\n"); 
    getchar();
    printf("\n\n\n您的录入操作已完成！您是否要保存录入的信息？\n");
    printf("\n\"是\" 请按 Y");
    printf("\n\"否\" 请按 N\n");
    judge=getchar();
    if(judge=='Y' || judge=='y'){
        cou_Count++;
    }
    else
        printf("\n\n注册失败！\n");
    if(getchar()) system("./clear.sh");
} 
//管理员浏览学生的基本信息
void display_all_student(){
    int i;
    for(i=0;i<stu_Count;i++)
        printf("账号：%d\t姓名：%s\t手机号码：%s\t密码：%s\n",s[i].num,s[i].name,s[i].phone,s[i].password);
}
//管理员删除学生
void dele_student(){
    int j=0,temp;
    int stu_num;
    char judge;
    printf("\n请输入要删除学生的账号：");
    scanf("%d",&stu_num);
    getchar();
    if((temp=stu_search(stu_num))==NO_FOUND)
        printf("\n对不起，该用户信息不存在！\n");
    else{
        printf("\n\n\n您确定要删除学号为%d的学生？\n",stu_num);
        printf("\n\"是\" 请按 Y");
        printf("\n\"否\" 请按 N\n");
        judge=getchar();
        if(judge=='Y'||judge=='y'){
            for(j=temp;j<=stu_Count-1;j++){
                s[j]=s[j+1];
            }
            stu_Count--;
            printf("\n删除信息完成！");
        }
        else
            printf("\n\n您暂未删除学号为%d的学生！\n",stu_num);
    }
}
//维护快递信息的菜单和控制
void manage_package(){
    int choice;
    int num;
    int p=0;
    do{
    	printf("\n\n");
        printf("\t\t ----------------------------------------------------\n");
        printf("\t\t|                  快递维护管理系统                  |\n");
        printf("\t\t|----------------------------------------------------|\n");
        printf("\t\t|                                                    |\n");
        printf("\t\t|           [1]----------------浏览快递信息          |\n");
        printf("\t\t|           [2]----------------修改快递信息          |\n");
        printf("\t\t|           [3]----------------将快递存入快递柜      |\n");
        printf("\t\t|                                                    |\n");
        printf("\t\t|           [0]----------------取消                  |\n");
        printf("\t\t|                                                    |\n");
        printf("\t\t ----------------------------------------------------\n"); 
        printf("请选择：");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                display_all_package();
                break;
            case 2:
                pac_modify();
                break;
            case 3:
                printf("输入存入快递柜的快递单号：");
                scanf("%d",&num); 
                for(int i=0;i<package_Count;i++){
                    if(strcmp(pac[i].state,"arrival")==0&&pac[i].num==num){
                        printf("请输入快递柜位置：");
                        scanf("%s",pac[i].location);
                        printf("请输入取件码：");
                        scanf("%s",pac[i].code); 
                        printf("存放成功！");
                        strcpy(pac[i].state,"pick");
                        p=1;
                    }                  
                } 
                if(p==0){
                    printf("default!");
                }
                break;               
            case 0:
                return;
            default:
                printf("\n对不起，您选择错误！\n");
                break;
        }
        printf("\n\n\n\n按Enter键返回……");
        getchar();
        if(getchar()) system("./clear.sh");       
    }while(1);
}
//添加快递函数 
void add_package(){
    int i;
    char judge;
    printf("\n\n");
    printf("输入快递单号：");
    scanf("%d",&pac[package_Count].num);
    printf("输入收件人：");
    scanf("%s",pac[package_Count].name);
    printf("输入学生手机号：");
    scanf("%s",pac[package_Count].stu_phone);
    printf("输入快递员手机号：");
    scanf("%s",pac[package_Count].cou_phone);
    strcpy(pac[package_Count].state,"delivery");
    strcpy(pac[package_Count].code,"0");
    strcpy(pac[package_Count].location,"0");    
    getchar();
    printf("\n\n\n您的录入操作已完成！您是否要保存录入的信息？\n");
    printf("\n\"是\" 请按 Y");
    printf("\n\"否\" 请按 N\n");
    judge=getchar();
    if(judge=='Y' || judge=='y'){
        package_Count++;
    }
    else{
        printf("\n\n信息未保存！\n");
    }
}
//浏览快递信息
void display_all_package(){
    int i;
    for(i=0;i<package_Count;i++){
        printf("快递单号：%d\t",pac[i].num);
        printf("收件人：%s\t",pac[i].name);
        printf("收件人手机：%s\t",pac[i].stu_phone);
        printf("快递员手机：%s\t",pac[i].cou_phone);
        printf("所在快递柜位置：%s\t",pac[i].location);
        printf("快递状态：%s\t",pac[i].state);
        printf("取件码：%s\n",pac[i].code);
    }
}
//修改快递函数
void pac_modify(){
    int temp;
    int choice;
    int id,p=0,o;
    printf("请输入快递单号:");
    scanf("%d",&id);
    for(int i=0;i<package_Count;i++){
        if(id==pac[i].num){
            o=1;
            p=i;   
        }
    }
    if(o==1){
    system("./clear.sh");
    do{
        printf("\n\n");
        printf("\t\t ----------------------------------------------------\n");
        printf("\t\t|                请选择您要修改的信息                |\n");
        printf("\t\t|----------------------------------------------------|\n");
        printf("\t\t|                                                    |\n");
        printf("\t\t|           快递状态                 请按 1          |\n");
        printf("\t\t|           取件码                   请按 2          |\n");
        printf("\t\t|           快递柜位置               请按 3          |\n");
        printf("\t\t|                                                    |\n");
        printf("\t\t|           取消                     请按 0          |\n");
        printf("\t\t|                                                    |\n");
        printf("\t\t ----------------------------------------------------\n");
        printf("请选择：");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                printf("请输入快递状态：");
                scanf("%s",pac[p].state);
                break;
            case 2:
                printf("请输入取件码：");
                scanf("%s",pac[p].code);
                break;
            case 3:
                printf("请输入快递柜位置：");
                scanf("%s",pac[p].location);
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
    else{
        printf("no result!");
    }
}
//载入快递信息
void Load_package_information(char * file_name){
    FILE *fp;
    struct package *p;
    if((fp=fopen(file_name,"r"))==NULL){
        printf("未找到货物文件！\n");
        return;
    }
    while(!feof(fp)){
        p=(struct package *)malloc(sizeof(struct package));
        if(fscanf(fp,"%d%s%s%s%s%s%s\r",&p->num,p->name,p->code,p->location,p->stu_phone,p->cou_phone,p->state)==0){
            printf("货物文件载入失败!\n");
            return;
        }
        pac[package_Count]=*p;
        package_Count++;
    }
    printf("package_Count=%d",package_Count);
    free(p);
    fclose(fp);
    printf("\n货物文件已载入!\n\n");
}
//载入学生信息 
void Load_student_information(char * file_name){
    FILE *fp;
    struct student *p;
    if((fp=fopen(file_name,"r"))==NULL){
        printf("未找到用户文件！\n");
        return;
    }
    while(!feof(fp)){
        p=(struct student *)malloc(sizeof(struct student));
        if(fscanf(fp,"%d%s%s%s\r",&p->num,p->name,p->phone,p->password)==0){
            printf("用户文件载入失败!\n");
            return;
        }
        s[stu_Count]=*p;
        stu_Count++;
    }
    printf("stu_Count=%d",stu_Count);
    free(p);
    fclose(fp);
    printf("\n学生文件已载入!\n\n");
}
//载入快递员信息 
void Load_courier_information(char * file_name){
    FILE *fp;
    struct courier *p;
    if((fp=fopen(file_name,"r"))==NULL){
        printf("未找到用户文件！\n");
        return;
    }
    while(!feof(fp)){
        p=(struct courier *)malloc(sizeof(struct courier));
        if(fscanf(fp,"%d%s%s%s\r",&p->num,p->name,p->phone,p->password)==0){
            printf("用户文件载入失败!\n");
            return;
        }
        c[cou_Count]=*p;
        cou_Count++;
    }
    printf("cou_Count=%d",cou_Count);
    free(p);
    fclose(fp);
    printf("\n快递员文件已载入!\n\n");
}
//保存快递信息 
void save_package_information(char *file_name){
    FILE *fp;
    struct package *p;
    int i;
    if((fp=fopen(file_name,"w"))==NULL)
        printf("未找到货物文件,不能保存!\n");
    for(i=0;i<package_Count;i++){
        p=(struct package *)malloc(sizeof(struct package));
        *p=pac[i];
        if(fprintf(fp,"%d %s %s %s %s %s %s\n",p->num,p->name,p->code,p->location,p->stu_phone,p->cou_phone,p->state)==0){
            printf("货物文件保存失败!\n");
            return;
        }
    }
    free(p);
    fclose(fp); 
    printf("货物文件已保存!\n");
}
//保存学生信息
void save_student_information(char *file_name){
    FILE *fp;
    struct student *p;
    int i;
    if((fp=fopen(file_name,"w"))==NULL)
        printf("未找到学生文件,不能保存!\n");
    for(i=0;i<stu_Count;i++){
        p=(struct student *)malloc(sizeof(struct student));
        *p=s[i];
        if(fprintf(fp,"%d %s %s %s\n",p->num,p->name,p->phone,p->password)==0){
            printf("学生文件保存失败!\n");
            return;
        }
    }
    free(p);
    fclose(fp); 
    printf("学生文件已保存!\n");
}
//保存快递员信息 
void save_courier_information(char *file_name){
    FILE *fp;
    struct courier *p;
    int i;
    if((fp=fopen(file_name,"w"))==NULL)
        printf("未找到快递员文件,不能保存!\n");
    for(i=0;i<cou_Count;i++){
        p=(struct courier *)malloc(sizeof(struct courier));
        *p=c[i];
        if(fprintf(fp,"%d %s %s %s\n",p->num,p->name,p->phone,p->password)==0){
            printf("快递员文件保存失败!\n");
            return;
        }
    }
    free(p);
    fclose(fp); 
    printf("快递员文件已保存!\n");
} 

