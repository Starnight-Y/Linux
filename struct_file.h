
struct package{
    int num;                        //快递单号 
    char name[20];                   //收件人姓名 
    char code[20];                   //取件码 
    char location[20];               //所在快递柜位置 
    char stu_phone[20];              //收件人手机 
    char cou_phone[20];              //快递员手机 
    char state[20];                  //快递状态 
}pac[200];

struct student{
    int num;                        //学生账号 
    char name[20];                   //学生姓名 
    char phone[20];                  //学生手机 
    char password[50];               //学生密码 
}s[STUDENT_MAX];

struct courier{
    int num;                        //快递员账号 
    char name[20];                   //快递员姓名 
    char phone[20];                  //快递员手机 
    char password[50];               //快递员密码 
}c[COURIER_MAX];
