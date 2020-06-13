//main.c的函数
void welcome();
int user_type();
void exit_system();
int regs();
int land(int user_type);
int getch();
//student_file.c的函数
int stu_search(long stu_num);
int stu_land();
int stu_menu();
void student();
void stu_modify();
void student();
//courier_file.c的函数
int cou_search(long cou_num);
int cou_land();
int cou_menu();
void courier();
void cou_modify();
void courier();
//administrator_file.c的函数
int package_search(long package_num);
int admin_land();
int admin_menu();
void administrator();
void manage_student();
void add_student();
void regs_student();
void regs_courier();
void display_all_student();
void dele_student();
void manage_package();
void add_package();
void display_all_package();
void pac_modify(); 
void administrator();
void Load_courier_information(char *file_name);
void Load_student_information(char *file_name);
void Load_package_information(char *file_name); 
void save_student_information(char *file_name);
void save_package_information(char *file_name);
void save_courier_information(char *file_name);
