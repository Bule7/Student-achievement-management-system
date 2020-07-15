#include <iostream>
#include <string.h>
#include <fstream>
#include <conio.h>
#include <Windows.h>
#include <string>
using namespace std;
string ID;  //����ȫ�ֵı��� 
class Student {     //����ѧ���� 

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
	{    //���캯�� 
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
class Teacher {    //������Ԫ�� 
private:
	Student *student;
public:
	Teacher() {   //���캯�� 
		student = 0;
		Load();
	}
	~Teacher() {   //�������� 
		Student *s;
		s = student;
		while (s) {
			s = s->next;
			delete student;
			student = s;
		}
		student = 0;
	}
	void Find(char Name[20]);		//���ֲ��� 
	void Find(string ID);        //ID���� 
	void Add();		//�����Ϣ 
	void Delete();			//ɾ����Ϣ 
	void Modify(string ID); //�޸���Ϣ
	void Query(); //��ѯ��Ϣ 
	void Save(); //�������� 
	void Load(); //��������
	void Look();//Ԥ��
	void TJ();  //ͳ��
	void DesTory();
	void Output(Student *s)		//������� 
	{
		cout << "\t\tѧ��: " << s->Number << endl;
		cout << "\t\t����: " << s->Name << endl;
		cout << "\t\t�Ա�: " << s->Sex << endl;
		cout << "\t\t����: " << s->Age << endl;
		cout << "\t\tʵ��ɼ�: " << s->Grade1 << endl;
		cout << "\t\t���ڳɼ�: " << s->Grade2 << endl;
		cout << "\t\t����ɼ�: " << s->Grade3 << endl;
		cout << endl;
	}
};
void Teacher::Add()		//��ӳɼ�����Ϣ 
{
	system("cls");
	Student *s, *s2; //�½��ָ�� 
	string Number, Age;
	float Grade1;
	float Grade2;
	float Grade3;
	char Name[20], Sex[10];
	char c;
	cout << "\n����ѧ���ɼ�\n";
	//����ѧ����Ϣ 
	cout << "����ѧ��:\t";
	cin >> Number;
	cout << endl;
	{
		Student *s1;
		s1 = student;
		while (s1)
		{
			if (s1->Number == Number)   //�ж�ѧ���Ƿ��Ѿ����� 
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
			cout << "��ѧ���Ѵ���,�Ƿ��޸ĸ�ѧ����Ϣ(Y/N) " << endl;
			cin >> c;
			if (toupper(c) == 'Y')
			{
				cout << "��ѧ����ϢΪ:" << endl;
				Find(Number);
				cout << endl;
				Modify(Number);
				return;
			}
			else
				return;
		}
	}
	cout << "��������:\t";
	cin >> Name;
	cout << endl;
	cout << "�����Ա�:\t";
	cin >> Sex;
	cout << endl;
	cout << "��������:\t";
	cin >> Age;
	cout << endl;
	cout << "����ʵ��ɼ�:\t";
	cout << endl;
	cin >> Grade1;
	cout << "���뿼�ڳɼ�:\t";
	cout << endl;
	cin >> Grade2;
	cout << "���뱨��ɼ�:\t";
	cout << endl;
	cin >> Grade3;
	cout << endl;
	s = new Student(Number, Name, Sex, Age, Grade1, Grade2, Grade3);
	s->next = 0;
	//ѧ������������  
	if (student) //���Ѿ����ڽ�� 
	{
		s2 = student;
		while (s2->next) //����β��� 
		{
			s2 = s2->next;
		}
		s2->next = s; //���� 
	}
	else //�������ڽ��(���) 
	{
		student = s; //���� 
	}
	system("cls");
	cout << "\t\t\t   ��ӳɹ�\n" << endl;
	cout << "�Ƿ�������(Y/N)  " << endl;
	cin >> c;
	if (toupper(c) == 'Y')
	{
		Add();
		return;
	}
	else
		return;
}
void Teacher::Delete() //ɾ����Ա 
{
	system("cls");
	char c;
	string Number;
	cout << "\nɾ����Ϣ\n";
	cout << "����Ҫɾ����ѧ��ID:\t";
	cin >> Number;
	cout << endl;
	//����Ҫɾ���Ľ�� 
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
	//ɾ����� 
	if (s1 != NULL)//���ҵ���㣬��ɾ�� 
	{
		cout << "��Ҫɾ����ѧ������Ϣ����:\n" << endl;
		Output(s1);
		cout << "ȷ���Ƿ�ɾ��(Y/N): ";
		cin >> c;
		if (toupper(c) != 'Y')
			return;
		//	system("pause");
		if (s1 == student) //��Ҫɾ���Ľ���ǵ�һ����� 
		{
			student = s1->next;
			delete s1;
		}
		else //��Ҫɾ���Ľ���Ǻ������ 
		{
			s2->next = s1->next;
			delete s1;
		}
		cout << "\t\tɾ���ɹ�\n";
		cout << "�Ƿ����ɾ��(Y/N)  " << endl;
		cin >> c;
		if (toupper(c) == 'Y')
		{
			Delete();
			return;
		}
		else
			return;
	}
	else //δ�ҵ���� 
		cout << "δ�ҵ���ѧ��!\n";
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
	if (s1 != NULL)//���ҵ���� 
	{
		system("cls");
		cout << "��Ҫ�޸ĵ�ѧ������Ϣ����:\n" << endl;
		Output(s1);
		do
		{
			cout << "1. �޸�����  2. �޸��Ա�  3. �޸�����  4. �޸�ʵ��ɼ�  5. �޸Ŀ��ڳɼ�  6. �޸ı���ɼ�  7. �˳��޸� \n" << endl;
			cout << "��ѡ��(1-5)Ҫ�޸ĵ���Ϣ\n" << endl;
			cin >> c;
			if (c != '5')
				cout << "�������µ���Ϣ:  ";
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
		cout << "\t�޸ĳɹ�\n" << endl;
		cout << "�Ƿ�����޸�(Y/N):  " << endl;
		cin >> c;
		if (toupper(c) == 'Y')
		{
			cout << "������Ҫ�޸���Ա��ID:  ";
			cin >> ID;
			cout << endl;
			Modify(ID);
			return;
		}
		else
			return;
	}
	else //δ�ҵ���� 
		cout << "δ�ҵ���ѧ��!\n";
	_getch();
}
void Teacher::Save() //����д�뵽�ļ� 
{
	ofstream fStudent("Student.txt", ios::out | ios::binary);
	char c;
	cout << "\n��������,�Ƿ����?[Y/N]:";
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
	cout << "\n����ɹ���\n";
	system("pause");
}
void Teacher::Load() //���ݶ���
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
		s->next = 0; //ѧ���Ľ��������� 
		if (student) //���Ѿ����ڽ�� 
		{
			Student *s2;
			s2 = student;
			while (s2->next) //����β��� 
			{
				s2 = s2->next;
			}
			s2->next = s; //���� 
		}
		else //�������ڽ��(���) 
		{
			student = s; //���� 
		}
		fStudent >> Number >> Name >> Sex >> Age >> Grade1 >> Grade2 >> Grade3;
	}
	fStudent.close();
}
void Teacher::Find(string ID)		//����ID���в��� 
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
		cout << "δ�ҵ���ѧ��" << endl;
}

void Teacher::Find(char Name[20])	//�������ֲ��� 
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
		cout << "\t��ѯ�ɹ�!!!" << endl;
		cout << "\n���ҵ� " << count << " ������Ϊ " << Name << " ��ͬѧ\n" << endl;
	}
	else
		cout << "\n\t\tδ�ҵ���ѧ��!!!\n" << endl;
}
void Teacher::Query()	//���ҵķ�ʽ 
{
	char c;
	string ID, Grade1, Grade2, Grade3;
	char Name[20];
	do {
		cout << "1.��ѧ�Ų���\n2.�����ֲ���\n3.�˳�����" << endl;
		cin >> c;
		//	system("cls");
		cout << endl;
		switch (c)
		{
		case '1': 
		{
			cout << "����ѧ��:  ";
			cin >> ID;
			Find(ID);
		}; break;
		case '2': 
		{
			cout << "��������:  ";
			cin >> Name;
			Find(Name);
		}; break;
		case '3':break;
		default:  cout << "�������� ����������!!!\n" << endl;
		}
	} while (c != '1'&&c != '2'&&c != '3'&&c != '4'&&c != '5'&&c != '6');
	cout << "\t\t\t���ҳɹ�\n" << endl;
	cout << "�Ƿ��������(Y/N)  " << endl;
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
void Teacher::Look()		//Ԥ����Ϣ 
{
	system("cls");
	Student *s1;
	int count = 0;
	char c;
	s1 = student;
	while (s1)
	{
		cout << "ID: " << s1->Number << "\t����: " << s1->Name << endl;
		count++;
		s1 = s1->next;
	}
	if (count != 0)
	{
		cout << "\n\t\tԤ���ɹ�!!! \n" << endl;
		cout << "��ѯ��ϸ��Ϣ(Y/N): ";
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
		cout << "��δ�����ɼ����Ƿ񴴽�(Y/N)" << endl;
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
void Teacher::DesTory()		//��������Ϣ 
{	
	char c;
	system("cls");
	cout << "\n\t\t\t�����Ϣ\n";
	cout << "����:\n    ����ɼ�����Ϣ�ᵼ�����������Ϣ��ȫ��ʧ\n" << endl;
	cout << "�Ƿ��������ɼ�����Ϣ(Y/N):  " << endl;
	cin >> c;
	if (toupper(c) != 'Y')
		return;
	cout << "���ٴ�ȷ��(Y/N)" << endl;
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
void Teacher::TJ()		//ͳ��ѧ���ĳɼ�
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
	cout << "\n�ܹ��� " << count << "�ݳɼ���\n" << endl;
	cout << "ʵ��ɼ�������" << student1 << "��" << endl;
	cout << "���ڳɼ�������" << student2 << "��" << endl;
	cout << "����ɼ�������" << student3 << "��" << endl;
	system("pause");
}

int main()			//������ 
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
		cout << "��ӭ�����û�" << endl;
	}
	else if (strcmp(password, "111") == 0)
	{
		cout << "��ӭ���ڲ��û�" << endl;
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
		cout << "                             ��ӭʹ��ѧ���ɼ�����ϵͳ" << endl;
		cout << "                    ==========================================" << endl;
		cout << "                    ||  \t    1.����ѧ���ɼ�    \t   ||" << endl;
		cout << "                    ||  \t    2.ɾ��ѧ���ɼ�    \t   ||" << endl;
		cout << "                    ||  \t    3.�޸�ѧ���ɼ�    \t   ||" << endl;
		cout << "                    ||  \t    4.��ѯ��ϸ��Ϣ  \t   ||" << endl;
		cout << "                    ||  \t    5.��������      \t   ||" << endl;
		cout << "                    ||  \t    6.Ԥ����Ϣ      \t   ||" << endl;
		cout << "                    ||  \t    7.���ѧ���ɼ�    \t   ||" << endl;
		cout << "                    ||  \t    8.ͳ������    \t   ||" << endl;
		cout << "                    ==========================================" << endl;
		cout << "\t\t\t\t\t\t\tcreated by Wang" << endl;
		cout << "   0���˳�\t��ѡ��(1-7):";
		cin >> c;
		switch (c)
		{
		case 1: m.Add(); break;
		case 2: m.Delete(); break;
		case 3: {
			system("cls");
			cout << "������Ҫ�޸���Ա��ID:  ";
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
	cout << "\n�Ƿ�Ҫ�����������в���(Y/N):  " << endl;
	cin >> s;
	if (toupper(s) == 'Y')
		m.Save();
	return 0;
}

