#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <fstream>

using namespace std;

ofstream fout("./input_data.txt");
/*************************************************
Description:    // ö��ѧ����Ȥ��ǩ
Input:          //
Return:         //
*************************************************/
enum Tagset 
{
	chess, dance, football, reading, film, basketball, music, English, study, programming
};
/*************************************************
Description:    // ö�ٲ��ű��
Input:          //
Return:         //
*************************************************/
enum Deptment
{
	D001,D002,D003,D004,D005,D006,D007,D008,D009,D010,D011,D012,D013,D014,D015,D016,D017,D018,D019,D020
};
/*************************************************
Description:    // ö��ѧ������ʱ��
Input:          //
Return:         //
*************************************************/
enum LeisureTime
{
	t1, t2, t3, t4, t5, t6, t7
};
/*************************************************
Description:    // ö��ѧ������ʱ��
Input:          // 
Return:         // 
*************************************************/
enum DeptSheldue 
{
	t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20
};

class Student
{
    public:
        string student_no;
        string tag[11];
        string application_dept[6];
        string Mon[7];
        string Tues[7];
        string Wed[7];
        string Thur[7];
        string Fri[7];
        string Sat[7];
        string Sun[7];
}Stu[301];

class Department {
public:
    int num;
    int sum;
    string dept_no;
    string tag[11];
    string Mon[2];
    string Tues[2];
    string Wed[2];
    string Thur[2];
    string Fri[2];
    string Sat[2];
    string Sun[2];
}Dept[21];
/*************************************************
Description:    // ��ȡ��Ȥ��ǩ
Input:          // ����һ��intֵ��ö��ֵ���Ӧ
Return:         // ������Ȥ��ǩ
*************************************************/
string setTag(int x) 
{
	switch (x) 
    {
	case chess: return "chess";
	case dance: return "dance";
	case football: return "football";
	case reading: return "reading";
	case film: return "film";
	case basketball: return "basketball";
	case music: return "music";
	case English: return "English";
	case study: return "study";
	case programming: return "programming";
	default: return "";
	}
}
/*************************************************
Description:    // ��ȡ���ű��
Input:          // ����һ��intֵ��ö��ֵ���Ӧ
Return:         // ���ز��ű��
*************************************************/
string setDept(int x)
{
	switch (x)
    {
    case D001: return "D001";
    case D002: return "D002";
    case D003: return "D003";
    case D004: return "D004";
    case D005: return "D005";
    case D006: return "D006";
    case D007: return "D007";
    case D008: return "D008";
    case D009: return "D009";
    case D010: return "D010";
    case D011: return "D011";
    case D012: return "D012";
    case D013: return "D013";
    case D014: return "D014";
    case D015: return "D015";
    case D016: return "D016";
    case D017: return "D017";
    case D018: return "D018";
    case D019: return "D019";
    case D020: return "D020";
	default: return "";
	}
}
/*************************************************
Description:    // ��ȡѧ������ʱ���
Input:          // ����һ��intֵ��ö��ֵ���Ӧ
Return:         // ����ѧ������ʱ���
*************************************************/
string setTime(int x) 
{                                                      
	switch (x) 
    {
	case t1: return "8:00~10:00";
	case t2: return "10:00~12:00";
	case t3: return "12:00~14:00";
	case t4: return "14:00~16:00";
	case t5: return "16:00~18:00";
	case t6: return "18:00~20:00";
	case t7: return "20:00~22:00";
	default: return "";
	}
}
/*************************************************
Description:    // ��ȡ���Żʱ��
Input:          // ����һ��intֵ��ö��ֵ���Ӧ
Return:         // ���ػʱ��
*************************************************/
string setSheldue(int x)
{
	switch (x)
	{
	case t9: return "8:00~9:00";
	case t10: return "9:00~10:00";
	case t11: return "10:00~11:00";
	case t12: return "11:00~12:00";
	case t13: return "12:00~13:00";
	case t14: return "13:00~14:00";
	case t15: return "14:00~15:00";
	case t16: return "15:00~16:00";
	case t17: return "16:00~17:00";
	case t18: return "17:00~18:00";
	case t19: return "18:00~19:00";
	case t20: return "19:00~19:30";
	default: return "";
	}
}
/*************************************************
Description:    // ��������е�ö��ֵ��Ϊ�˱�������ظ���ö��ֵ
Input:          // ����ö��ֵ�ķ�Χ
Return:         // ����һ���Ѿ��ڲ�Ԫ�ش��ҵ�����
*************************************************/
vector<int> randVector(int num) 
{
	vector<int> result;
	result.reserve(num);
	for (int i = 0; i < num; i++)
	{
		result.push_back(i);
	}
	int p1;
	int p2;
	int temp;
	int count = num;

	while (--num)
	{
		p1 = num;
		p2 = rand() % num;
		temp = result[p1];
		result[p1] = result[p2];
		result[p2] = temp;
	}
	return result;
}
vector<int> ve = randVector(1);
/*************************************************
Description:    // �趨���ŵĻʱ��
Input:          // ����һ��intֵ����ʱ��ĸ�����һ���ַ����������ڴ洢�ʱ��
Return:         // ��
*************************************************/
void setShelduer(int count, string x[]) {
	ve = randVector(12);
	for (int i = 1; i <= count; i++) {
		x[i - 1] = setSheldue(ve[i - 1]);
	}
	ve.clear();
}
/*************************************************
Description:    // �趨ѧ������ʱ��
Input:          // ����һ��intֵ�������ʱ��ĸ�����һ���ַ����������ڴ洢����ʱ��
Return:         // ��
*************************************************/
void setLt(int count, string x[]) 
{
	ve = randVector(7);
	for (int i = 1; i <= count; i++)
    {
		x[i - 1] = setTime(ve[i-1]);
	}
	ve.clear();
}
/*************************************************
Description:    // ���ѧ������ʱ��
Input:          // day��ʾ���ڼ����ж������������Ŀ���ʱ�䣬�ַ��������д洢���ǵ���Ŀ���ʱ���
Return:         // ��
*************************************************/
void outputTime(string day, string x[]) 
{
	for (int j = 0; j < 7; j++)
		if (x[j].length() == 0) break;
		else
		{
			if (x[j].length() != 0&&x[j + 1].length() != 0) 
                fout << "\t\t\t\t\"" << day << "." << x[j] << "\"," << endl;
			if (x[j].length() != 0&&x[j + 1].length() == 0&&day == "Sun") 
                fout << "\t\t\t\t\"" << day << "." << x[j] << "\"" <<endl;
		}
}
/*************************************************
Description:    // ������Żʱ��
Input:          // day��ʾ���ڼ����ж������������Ļʱ�䣬�ַ��������д洢���ǵ���Ļʱ���
Return:         // ��
*************************************************/
void outputTimed(int i, string day, string x[]) {

    for (int j = 0; j < 2; j++)
        if (x[j].length() == 0 || Dept[i].sum == 0) break;
        else
        {
            if (Dept[i].sum == 1) {
                Dept[i].sum = 0;
                fout << "\t\t\t\t\"" << day << "." << x[j] << "\"" << endl;
                break;
            }
            else {
                Dept[i].sum--;
                fout << "\t\t\t\t\"" << day << "." << x[j] << "\"," << endl;
            }
        }
}

int main() 
{
	srand((unsigned)time(NULL));
	vector<int>::iterator it;
	int sum = 0, ram;
	//���ѧ��������������
    for (int k = 1; k <= 300; k++) 
    {   	
		setLt(rand() % 4, Stu[k].Mon);                                                    //���ѧ����������ʱ��
		setLt(rand() % 4, Stu[k].Tues);
		setLt(rand() % 4, Stu[k].Wed);
		setLt(rand() % 4, Stu[k].Thur);
		setLt(rand() % 4, Stu[k].Fri);
		setLt(rand() % 3 + 2, Stu[k].Sat);
		setLt(rand() % 4 + 1, Stu[k].Sun);

		if (k <= 9)Stu[k].student_no = "03150200" + to_string(k);                      //�������ѧ�����
		else if (k <= 99)Stu[k].student_no = "0315020" + to_string(k);
		else Stu[k].student_no = "031502" + to_string(k);

		ve = randVector(20);
		for (int p = rand() % 5 + 1; p > 0; p--) 
        {                                        //���ѧ��־Ը��ǩ
			Stu[k].application_dept[p-1] = setDept(ve[p-1]);
		}
		ve.clear();

		ve = randVector(10);                          //�����Ȥ��ǩ
		for (int p = rand() % 9 + 2; p > 0; p--) 
        {                                       
			Stu[k].tag[p-1] = setTag(ve[p-1]);
		}
		ve.clear();
	}
     //����������Ÿ�������
	for (int k = 1; k <= 20; k++) 
    {
		ram = rand() % 3;
		setShelduer(ram, Dept[k].Mon);                                         //������Ų�������ʱ��
		sum += ram;
		ram = rand() % 3;
		setShelduer(ram, Dept[k].Tues);
		sum += ram;
		ram = rand() % 3;
		setShelduer(ram, Dept[k].Wed);
		sum += ram;
		ram = rand() % 3;
		setShelduer(ram, Dept[k].Thur);
		sum += ram;
		ram = rand() % 3;
		setShelduer(ram, Dept[k].Fri);
		sum += ram;
		ram = rand() % 2+1;
		setShelduer(ram, Dept[k].Sat);
		sum += ram;
		ram = rand() % 2+1;
		setShelduer(ram, Dept[k].Sun);
		sum += ram;
		if (sum < 3) Dept[k].sum = 2;
		else Dept[k].sum = sum % 3 + 2; 
		sum = 0;

		Dept[k].num = rand() % 6 + 10;                                               //���������������

		if (k <= 9)Dept[k].dept_no = "D00" + to_string(k);                           //����������ű��
		else if (k <= 20) Dept[k].dept_no = "D0" + to_string(k);

		ve = randVector(10);
		for (int p = rand() % 9 + 2; p > 0; p--) 
        {                                      //���������Ȥ��ǩ
			Dept[k].tag[p-1] = setTag(ve[p-1]);
		}
		ve.clear();
	}
	fout << "{" << endl << "\t\"students\": [" << endl;
	//ѧ����Ϣͳһ���
	for (int i = 1; i < 301; i++)                                                        
	{
		fout << "\t\t{" << endl;

		fout << "\t\t\t\"free_time\": [" << endl;                                       // �������ʱ��
		outputTime("Mon", Stu[i].Mon);
		outputTime("Tues", Stu[i].Tues);
		outputTime("Wed", Stu[i].Wed);
		outputTime("Thur", Stu[i].Thur);
		outputTime("Fri", Stu[i].Fri);
		outputTime("Sat", Stu[i].Sat);
		outputTime("Sun", Stu[i].Sun);
		fout << "\t\t\t]," << endl;
		
		fout << "\t\t\t\"student_no\": " << "\"" << Stu[i].student_no << "\"," << endl; // ���ѧ�����
		
		fout << "\t\t\t\"applications_department\": [" << endl;                         // �����Ȥ���ű��
		for (int j = 0; j < 5; j++) {
			if (Stu[i].application_dept[j].length() != 0&&Stu[i].application_dept[j + 1].length() != 0) 
                fout << "\t\t\t\t\"" << Stu[i].application_dept[j] << "\"," << endl;
			else if (Stu[i].application_dept[j].length() != 0&&Stu[i].application_dept[j + 1].length() == 0) 
                fout << "\t\t\t\t\"" << Stu[i].application_dept[j] << "\"" << endl << "\t\t\t]," << endl;
		}
		
		fout << "\t\t\t\"tags\": [" << endl;                                            // �����Ȥ��ǩ
		for (int j = 0; j < 10; j++)
			if (Stu[i].tag[j].length()!=0&&Stu[i].tag[j+1].length() != 0) 
                fout << "\t\t\t\t\"" << Stu[i].tag[j] << "\"," << endl;
			else if (Stu[i].tag[j].length() != 0&&Stu[i].tag[j + 1].length() == 0) 
                fout << "\t\t\t\t\"" << Stu[i].tag[j] << "\"" << endl << "\t\t\t]" << endl;
		
		if (i == 300) fout << "\t\t}" << endl;
		else fout << "\t\t}," << endl;
	}
	fout << "\t]," << endl;

	fout<< "\t\"departments\": [" << endl;
	//���������Ϣ	
	for (int i = 1; i <= 20; i++) 
    {
		fout << "\t\t{" << endl;

		fout << "\t\t\t\"event_shedules\": [" << endl;                                       // �������ʱ��
		outputTimed(i, "Mon", Dept[i].Mon); 
		outputTimed(i, "Tues", Dept[i].Tues); 
		outputTimed(i, "Wed", Dept[i].Wed);
		outputTimed(i, "Thur", Dept[i].Thur);
		outputTimed(i, "Fri", Dept[i].Fri); 
		outputTimed(i, "Sat", Dept[i].Sat); 
		outputTimed(i, "Sun", Dept[i].Sun); 
		fout << "\t\t\t]," << endl;

		fout << "\t\t\t\"member_limit\": " << Dept[i].num << "," << endl;                     //���������������

		fout << "\t\t\t\"department_no\": \"" << Dept[i].dept_no << "\"," << endl;                

		fout << "\t\t\t\"tags\": [" << endl;                                          //������ű��
		for (int j = 0; j < 10; j++)                                                  //���������Ȥ��ǩ
			if (Dept[i].tag[j].length() != 0&&Dept[i].tag[j + 1].length() != 0) 
                fout << "\t\t\t\t\"" <<Dept[i].tag[j] << "\"," << endl;
			else if (Dept[i].tag[j].length() != 0&&Dept[i].tag[j + 1].length() == 0) 
                fout << "\t\t\t\t\"" << Dept[i].tag[j] << "\"" << endl << "\t\t\t]" << endl;
	
		if (i == 20) fout << "\t\t}" << endl;
		else fout << "\t\t}," << endl;
	}
	fout << "\t]" << endl;
	fout << "}" << endl;
	system("pause");
	return 0;
	}
