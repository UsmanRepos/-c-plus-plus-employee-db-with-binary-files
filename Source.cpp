#include<iostream>
#include<string>
#include<fstream>

#define SIZE 70
using namespace std;

ofstream outfile;
ifstream infile;

enum Employ_Type { TM, TS, TL };
Employ_Type type;

class Employee
{
	int emp_no;
	string emp_name;
	string emp_cnic;
	static int eCount;
public:
	/*Employee() :emp_no(0), emp_name(" "), emp_cnic(" ")
	{
		eCount++;
	}*/
	Employee(int eno = 0, string ename = " ", string ecnic = " ") :emp_no(eno), emp_name(ename), emp_cnic(ecnic)
	{
		eCount++;
	}
	static int empCount()
	{
		return eCount;
	}
	virtual ~Employee()
	{
		eCount--;
	}
	virtual Employ_Type get_type();
	virtual void mySetter();
	virtual void myGetter();
};
void Employee::mySetter()
{
	cout << " Enter Employee No: ";
	cin >> emp_no;

	cin.ignore(10, '\n');
	cout << " Enter Employee Name: ";
	getline(cin, emp_name);

	cout << " Enter Employee Cnic: ";
	getline(cin, emp_cnic);
}

void Employee::myGetter()
{
	cout << " Employee No: " << emp_no << endl;
	cout << " Employee Name: " << emp_name << endl;
	cout << " Employee Cnic: " << emp_cnic << endl;
}

class Manager :public Employee
{
	string emp_title;
	double emp_clubDues;
	static int mCount;
public:
	/*Manager() :emp_title(" "), emp_clubDues(0.0)
	{
		mCount++;
	}*/
	Manager(int eno = 0, string ename = " ", string ecnic = " ", string etitle = " ", double eclubdues = 0.0) :Employee(eno, ename, ecnic)
	{

		emp_title = etitle;
		emp_clubDues = eclubdues;
		mCount++;
	}
	static int manCount()
	{
		return mCount;
	}
	~Manager()
	{
		mCount--;
	}
	void mySetter();
	void myGetter();
};
void Manager::mySetter()
{
	Employee::mySetter();
	cout << " Enter Employee Title: ";
	getline(cin, emp_title);
	cout << " Enter Employee Club Dues: ";
	cin >> emp_clubDues;
}
void Manager::myGetter()
{
	Employee::myGetter();
	cout << " Employee Title: " << emp_title << endl;
	cout << " Employee ClubDues: " << emp_clubDues << endl << endl;
}

class Scientist :public Employee
{
	string emp_resField;
	int    emp_noOfBookPub;
	static int sCount;
public:

	Scientist() :emp_resField(" "), emp_noOfBookPub(0)
	{
		sCount++;
	}
	static int sciCount()
	{
		return sCount;
	}
	~Scientist()
	{
		sCount--;
	}
	void mySetter();
	void myGetter();
};

void Scientist::mySetter()
{
	Employee::mySetter();
	cout << " Enter Employee Research Field: ";
	cin >> emp_resField;
	cout << " Enter Employee No Of Book Published: ";
	cin >> emp_noOfBookPub;
}
void Scientist::myGetter()
{
	Employee::myGetter();
	cout << " Employee Research Field: " << emp_resField << endl;
	cout << " Employee Book Publidhed: " << emp_noOfBookPub << endl << endl;
}
class Labour :public Employee
{
	int emp_WrkHrs;
	int emp_HrsRate;
	static int lCount;
public:
	Labour() :emp_WrkHrs(0), emp_HrsRate(0)
	{
		lCount++;
	}
	static int labCount()
	{
		return lCount;
	}
	~Labour()
	{
		lCount--;
	}
	void mySetter();
	void myGetter();
};
void Labour::mySetter()
{
	Employee::mySetter();
	cout << " Enter Employee Working Hours: ";
	cin >> emp_WrkHrs;
	cout << " Enter Employee Hours Rate: ";
	cin >> emp_HrsRate;

}
void Labour::myGetter()
{
	Employee::myGetter();
	cout << " Employee Working Hours: " << emp_WrkHrs << endl;
	cout << " Employee Hours Rate: " << emp_HrsRate << endl << endl;
}
Employ_Type Employee::get_type()
{
	if (typeid(*this) == typeid(Manager))
		return TM;
	if (typeid(*this) == typeid(Scientist))
		return TS;
	if (typeid(*this) == typeid(Labour))
		return TL;
}
void writeToFile(Employee* array[], int nn)
{
	int size;
	cout << "Writing " << nn << " Employees.\n";

	ofstream outfile;
	outfile.open("Employ.dat", ios::trunc | ios::binary);
	if (!outfile.good())
	{
		cout << "Eror.......!" << endl;
		exit(-1);

	}
	for (int i = 0; i < nn; i++)
	{
		type = array[i]->get_type();
		outfile.write((char*)&type, sizeof(type));

		switch (type)
		{
		case TM:
			size = sizeof(Manager);
			break;
		case TS:
			size = sizeof(Scientist);
			break;
		case TL:
			size = sizeof(Labour);
			break;
		}

		outfile.write((char*)array[i], size);
		if (!outfile.good())
			cout << "Can't Written to Files.\n";
	}
	outfile.close();
}

void readFromFile(Employee* array[], int& nn)
{
	int size;
	ifstream infile;
	infile.open("Employ.dat", ios::in | ios::binary);
	if (!infile.good())
	{
		cout << "Eror.......!" << endl;
		exit(-1);
	}
	nn = 0;
	while (!infile.eof())
	{

		infile.read((char*)&type, sizeof(type));

		if (infile.eof())
			break;

		cout << "Type: " << type << endl;
		switch (type)
		{
		case TM:
			array[nn] = new Manager;
			size = sizeof(Manager);
			break;
		case TS:
			array[nn] = new Scientist;
			size = sizeof(Scientist);
			break;
		case TL:
			array[nn] = new Labour;
			size = sizeof(Labour);
			break;
		}
		infile.read((char*)array[nn], size);
		nn++;
	}
	cout << "Read " << nn << " Employees\n";
	infile.close();
}
int Employee::eCount = 0;
int Manager::mCount = 0;
int Scientist::sCount = 0;
int Labour::lCount = 0;

int main()
{
	Employee* employee[SIZE];
	int e = 0;

	char ch;
	while (true)
	{

		cout << "\n ----------(MAIN MENU)----------\n";
		cout << " 1) MANAGER \n";
		cout << " 2) SCIENTIST \n";
		cout << " 3) LABOUR \n";
		cout << " 4) GETTER \n";
		cout << " 5) WRITE TO FILE \n";
		cout << " 6) READ FROM FILE \n";
		cout << " 7) EXIT \n\n";

		cout << " Enter Your Choice: ";
		cin >> ch;

		switch (ch)
		{
		case '1':
			employee[e] = new Manager();
			employee[e++]->mySetter();
			break;
		case '2':
			employee[e] = new Scientist();
			employee[e++]->mySetter();
			break;
		case '3':
			employee[e] = new Labour();
			employee[e++]->mySetter();
			break;
		case'4':
			if (e == 0)
				cout << "\n Database Is Empty...\n First Create Or Read Data Then Perform Any Operation.\n";
			else
			{
				cout << "\n Employees Data...\n\n" << endl;
				for (int i = 0; i < e; i++)
				{
					employee[i]->myGetter();
					cout << endl;
				}
				cout << "\n Total Employees: " << Employee::empCount() << endl;
				cout << " Number of Managers: " << Manager::manCount() << endl;
				cout << " Number of Scientist: " << Scientist::sciCount() << endl;
				cout << " Number of Labours: " << Labour::labCount() << endl;
			}
			break;
		case '5':
			writeToFile(employee, e);
			break;
		case '6':
			readFromFile(employee, e);
			break;
		case '7':
			exit(-1);
		default:
			cout << "\n Invalid Input ... !!! \n";
		}
	}

}

















