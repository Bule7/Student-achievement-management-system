#include <iostream>
#include <string.h>
#include <fstream>
#include <conio.h>
#include <Windows.h>
#include <string>
using namespace std;
string ID;  //定义全局的变量 
class Student {     //定义学生类 

protected:
	string Number;
	char Name[30];
	char Sex[10];
	string Age;
	Student *next;
	float Grade1;
	float Grade2;
	float Grade3;
public:

	Student(string ID, char *Name, char *Sex, string Age, float Grade1, float Grade2, float Grade3) 
	{    //构造函数 
		strcpy_s(this->Name, Name);
		strcpy_s(this->Sex, Sex);
		this->Grade1 = Grade1;
		this->Grade2 = Grade2;
		this->Grade3 = Grade3;
		this->Number = ID;
		this->Age = Age;
	}
	friend class Teacher;
};
class Teacher {    //定义友元类 
private:
	Student *student;
public:
	Teacher() {   //构造函数 
		student = 0;
		Load();
	}
	~Teacher() {   //析构函数 
		Student *s;
		s = student;
		while (s) {
			s = s->next;
			delete student;
			student = s;
		}
		student = 0;
	}
	void Find(char Name[20]);		//名字查找 
	void Find(string ID);        //ID查找 
	void Add();		//添加信息 
	void Delete();			//删除信息 
	void Modify(string ID); //修改信息
	void Query(); //查询信息 
	void Save(); //保存数据 
	void Load(); //读入数据
	void Look();//预览
	void TJ();  //统计
	void DesTory();
	void Output(Student *s)		//输出函数 
	{
		cout << "\t\t学号: " << s->Number << endl;
		cout << "\t\t姓名: " << s->Name << endl;
		cout << "\t\t性别: " << s->Sex << endl;
		cout << "\t\t年龄: " << s->Age << endl;
		cout << "\t\t实验成绩: " << s->Grade1 << endl;
		cout << "\t\t考勤成绩: " << s->Grade2 << endl;
		cout << "\t\t报告成绩: " << s->Grade3 << endl;
		cout << endl;
	}
};
void Teacher::Add()		//添加成绩的信息 
{
	system("cls");
	Student *s, *s2; //新结点指针 
	string Number, Age;
	float Grade1;
	float Grade2;
	float Grade3;
	char Name[20], Sex[10];
	char c;
	cout << "\n新增学生成绩\n";
	//输入学生信息 
	cout << "输入学号:\t";
	cin >> Number;
	cout << endl;
	{
		Student *s1;
		s1 = student;
		while (s1)
		{
			if (s1->Number == Number)   //判断学号是否已经存在 
			{
				break;
			}
			else
			{
				s1 = s1->next;
			}
		}
		if (s1 != NULL)
		{
			cout << "该学号已存在,是否修改该学生信息(Y/N) " << endl;
			cin >> c;
			if (toupper(c) == 'Y')
			{
				cout << "该学生信息为:" << endl;
				Find(Number);
				cout << endl;
				Modify(Number);
				return;
			}
			else
				return;
		}
	}
	cout << "输入姓名:\t";
	cin >> Name;
	cout << endl;
	cout << "输入性别:\t";
	cin >> Sex;
	cout << endl;
	cout << "输入年龄:\t";
	cin >> Age;
	cout << endl;
	cout << "输入实验成绩:\t";
	cout << endl;
	cin >> Grade1;
	cout << "输入考勤成绩:\t";
	cout << endl;
	cin >> Grade2;
	cout << "输入报告成绩:\t";
	cout << endl;
	cin >> Grade3;
	cout << endl;
	s = new Student(Number, Name, Sex, Age, Grade1, Grade2, Grade3);
	s->next = 0;
	//学生结点加入链表  
	if (student) //若已经存在结点 
	{
		s2 = student;
		while (s2->next) //查找尾结点 
		{
			s2 = s2->next;
		}
		s2->next = s; //连接 
	}
	else //若不存在结点(表空) 
	{
		student = s; //连接 
	}
	system("cls");
	cout << "\t\t\t   添加成功\n" << endl;
	cout << "是否继续添加(Y/N)  " << endl;
	cin >> c;
	if (toupper(c) == 'Y')
	{
		Add();
		return;
	}
	else
		return;
}
void Teacher::Delete() //删除人员 
{
	system("cls");
	char c;
	string Number;
	cout << "\n删除信息\n";
	cout << "输入要删除的学生ID:\t";
	cin >> Number;
	cout << endl;
	//查找要删除的结点 
	Student *s1, *s2;
	s1 = student;
	s2 = 0;
	while (s1)
	{
		if (s1->Number == Number)
			break;
		else
		{
			s2 = s1;
			s1 = s1->next;
		}
	}
	//删除结点 
	if (s1 != NULL)//若找到结点，则删除 
	{
		cout << "所要删除的学生的信息如下:\n" << endl;
		Output(s1);
		cout << "确定是否删除(Y/N): ";
		cin >> c;
		if (toupper(c) != 'Y')
			return;
		//	system("pause");
		if (s1 == student) //若要删除的结点是第一个结点 
		{
			student = s1->next;
			delete s1;
		}
		else //若要删除的结点是后续结点 
		{
			s2->next = s1->next;
			delete s1;
		}
		cout << "\t\t删除成功\n";
		cout << "是否继续删除(Y/N)  " << endl;
		cin >> c;
		if (toupper(c) == 'Y')
		{
			Delete();
			return;
		}
		else
			return;
	}
	else //未找到结点 
		cout << "未找到该学生!\n";
	_getch();
}
void Teacher::Modify(string ID)
{
	Student *s1;
	char c;
	s1 = student;
	while (s1)
	{
		if (s1->Number == ID)
			break;
		else
		{
			s1 = s1->next;
		}
	}
	if (s1 != NULL)//若找到结点 
	{
		system("cls");
		cout << "所要修改的学生的信息如下:\n" << endl;
		Output(s1);
		do
		{
			cout << "1. 修改姓名  2. 修改性别  3. 修改年龄  4. 修改实验成绩  5. 修改考勤成绩  6. 修改报告成绩  7. 退出修改 \n" << endl;
			cout << "请选择(1-5)要修改的信息\n" << endl;
			cin >> c;
			if (c != '5')
				cout << "请输入新的信息:  ";
			switch (c)
			{
			case '1': cin >> s1->Name; break;
			case '2': cin >> s1->Sex; break;
			case '3': cin >> s1->Age; break;
			case '4': cin >> s1->Grade1; break;
			case '5': cin >> s1->Grade2; break;
			case '6': cin >> s1->Grade3; break;
			default: break;
			}
		} while (c != '7');
		system("cls");
		cout << "\t修改成功\n" << endl;
		cout << "是否继续修改(Y/N):  " << endl;
		cin >> c;
		if (toupper(c) == 'Y')
		{
			cout << "请输入要修改人员的ID:  ";
			cin >> ID;
			cout << endl;
			Modify(ID);
			return;
		}
		else
			return;
	}
	else //未找到结点 
		cout << "未找到该学生!\n";
	_getch();
}
void Teacher::Save() //数据写入到文件 
{
	ofstream fStudent("Student.txt", ios::out | ios::binary);
	char c;
	cout << "\n保存数据,是否继续?[Y/N]:";
	cin >> c;
	if (toupper(c) != 'Y')
		return;
	Student *s = student;
	while (s)
	{
		fStudent << s->Number << " " << s->Name << " " << s->Sex << " " << s->Age << " " << s->Grade1 << " " << s->Grade2 << " " << s->Grade3 << " " << endl;
		s = s->next;
	}
	fStudent.close();
	cout << "\n保存成功！\n";
	system("pause");
}
void Teacher::Load() //数据读入
{
	ifstream fStudent;
	Student *s = student;
	string Number, Age;
	float Grade1;
	float Grade2;
	float Grade3;
	char Name[20], Sex[10];
	fStudent.open("Student.dat", ios::in | ios::binary);
	fStudent >> Number >> Name >> Sex >> Age >> Grade1 >> Grade2 >> Grade3;

	while (fStudent.good())
	{
		s = new Student(Number, Name, Sex, Age, Grade1, Grade2, Grade3);
		s->next = 0; //学生的结点加入链表 
		if (student) //若已经存在结点 
		{
			Student *s2;
			s2 = student;
			while (s2->next) //查找尾结点 
			{
				s2 = s2->next;
			}
			s2->next = s; //连接 
		}
		else //若不存在结点(表空) 
		{
			student = s; //连接 
		}
		fStudent >> Number >> Name >> Sex >> Age >> Grade1 >> Grade2 >> Grade3;
	}
	fStudent.close();
}
void Teacher::Find(string ID)		//按照ID进行查找 
{
	Student *s1;
	s1 = student;
	while (s1)
	{
		if (s1->Number == ID)
			break;
		else
		{
			s1 = s1->next;
		}
	}
	if (s1 != NULL)
	{
		Output(s1);
	}
	else
		cout << "未找到该学生" << endl;
}

void Teacher::Find(char Name[20])	//按照名字查找 
{
	Student *s1;
	int count = 0;
	s1 = student;
	while (s1)
	{
		if (strcmp(s1->Name, Name) == 0)
		{
			count++;
			Output(s1);
		}
		s1 = s1->next;
	}
	if (count)
	{
		cout << "\t查询成功!!!" << endl;
		cout << "\n共找到 " << count << " 个名字为 " << Name << " 的同学\n" << endl;
	}
	else
		cout << "\n\t\t未找到该学生!!!\n" << endl;
}
void Teacher::Query()	//查找的方式 
{
	char c;
	string ID, Grade1, Grade2, Grade3;
	char Name[20];
	do {
		cout << "1.按学号查找\n2.按名字查找\n3.退出查找" << endl;
		cin >> c;
		//	system("cls");
		cout << endl;
		switch (c)
		{
		case '1': 
		{
			cout << "输入学号:  ";
			cin >> ID;
			Find(ID);
		}; break;
		case '2': 
		{
			cout << "输入姓名:  ";
			cin >> Name;
			Find(Name);
		}; break;
		case '3':break;
		default:  cout << "输入有误 请重新输入!!!\n" << endl;
		}
	} while (c != '1'&&c != '2'&&c != '3'&&c != '4'&&c != '5'&&c != '6');
	cout << "\t\t\t查找成功\n" << endl;
	cout << "是否继续查找(Y/N)  " << endl;
	cin >> c;
	if (toupper(c) == 'Y')
	{
		Query();
		return;
	}
	else
		return;
	system("pause");
}
void Teacher::Look()		//预览信息 
{
	system("cls");
	Student *s1;
	int count = 0;
	char c;
	s1 = student;
	while (s1)
	{
		cout << "ID: " << s1->Number << "\t姓名: " << s1->Name << endl;
		count++;
		s1 = s1->next;
	}
	if (count != 0)
	{
		cout << "\n\t\t预览成功!!! \n" << endl;
		cout << "查询详细信息(Y/N): ";
		cin >> c;
		if (toupper(c) == 'Y')
		{
			Query();
			return;
		}
		else
			return;
	}
	else
	{
		cout << "尚未创建成绩表，是否创建(Y/N)" << endl;
		cin >> c;
		if (toupper(c) == 'Y')
		{
			Add();
			return;
		}
		else
			return;
	}
}
void Teacher::DesTory()		//清楚表的信息 
{	
	char c;
	system("cls");
	cout << "\n\t\t\t清除信息\n";
	cout << "警告:\n    清除成绩表信息会导致您保存的信息完全消失\n" << endl;
	cout << "是否决定清除成绩表信息(Y/N):  " << endl;
	cin >> c;
	if (toupper(c) != 'Y')
		return;
	cout << "请再次确认(Y/N)" << endl;
	cin >> c;
	if (toupper(c) != 'Y')
		return;
	else
	{
		Student *s;
		s = student;
		while (s)
		{
			s = s->next;
			delete student;
			student = s;
		}
		student = 0;
	}
	system("pause");
}
void Teacher::TJ()		//统计学生的成绩
{
	Student *s1;
	int count = 0, student1 = 0, student2 = 0, student3 = 0;
	s1 = student;
	while (s1)
	{
		count++;
		if (s1->Grade1<60)
			student1++;
		if (s1->Grade2 < 60)
			student2++;
		if (s1->Grade3 < 60)
			student3++;
		s1 = s1->next;
	}
	cout << "\n总共有 " << count << "份成绩表\n" << endl;
	cout << "实验成绩不及格：" << student1 << "人" << endl;
	cout << "考勤成绩不及格：" << student2 << "人" << endl;
	cout << "报告成绩不及格：" << student3 << "人" << endl;
	system("pause");
}

int main()			//主函数 
{
	system("color E3");
	char* password;
	int length = 3;
	password = new char[length + 1];
	char* p = NULL;
	int count = 0;
	cout << "welcome users"<<endl;
	cout << "Please input password:";
	p = password;
	count = 0;
	while (((*p = _getch()) != 13) && count < length) 
	{
		_putch('*');
		fflush(stdin);
		p++;
		count++;
	}
	password[count] = '\0';
	cout << endl;
	if (strcmp(password, "123") == 0)
	{
		cout << "欢迎，新用户" << endl;
	}
	else if (strcmp(password, "111") == 0)
	{
		cout << "欢迎，内部用户" << endl;
	}
	else
		return 0;
	getchar();
	Teacher m;
	int c;
	do
	{
		
		system("color E3");
		system("cls");
		cout << "                             欢迎使用学生成绩管理系统" << endl;
		cout << "                    ==========================================" << endl;
		cout << "                    ||  \t    1.新增学生成绩    \t   ||" << endl;
		cout << "                    ||  \t    2.删除学生成绩    \t   ||" << endl;
		cout << "                    ||  \t    3.修改学生成绩    \t   ||" << endl;
		cout << "                    ||  \t    4.查询详细信息  \t   ||" << endl;
		cout << "                    ||  \t    5.保存数据      \t   ||" << endl;
		cout << "                    ||  \t    6.预览信息      \t   ||" << endl;
		cout << "                    ||  \t    7.清除学生成绩    \t   ||" << endl;
		cout << "                    ||  \t    8.统计名单    \t   ||" << endl;
		cout << "                    ==========================================" << endl;
		cout << "\t\t\t\t\t\t\tcreated by Wang" << endl;
		cout << "   0－退出\t请选择(1-7):";
		cin >> c;
		switch (c)
		{
		case 1: m.Add(); break;
		case 2: m.Delete(); break;
		case 3: {
			system("cls");
			cout << "请输入要修改人员的ID:  ";
			cin >> ID;
			cout << endl;
			m.Modify(ID);
		}; break;
		case 4: {
			system("cls");
			m.Query();
		}; break;
		case 5: m.Save(); break;
		case 6: m.Look(); break;
		case 7: m.DesTory(); break;
		case 8: m.TJ(); break;
		default: break;
		}
	} while (c != 0);
	char s;
	cout << "\n是否要保存您的所有操作(Y/N):  " << endl;
	cin >> s;
	if (toupper(s) == 'Y')
		m.Save();
	return 0;
}

