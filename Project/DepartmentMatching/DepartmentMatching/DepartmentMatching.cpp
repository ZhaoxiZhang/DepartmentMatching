#include <iostream>
#include <fstream>
#include<cstdio>
#include<string>
#include<vector>
#include<queue>
#include<map>
#include "json.h"
using namespace std;
const int stumaxn = 305;
const int deptmaxn = 25;

vector<vector<pair<int, int> > >::iterator iter;
vector<pair<int, int> >::iterator it;
vector<pair<int, int> >::iterator it1;
vector<pair<int, int> >::iterator it2;
map<string, double>::iterator mapit;

struct Student {
    string stu_no;           //ѧ����
    vector<string>dept_no;   //ѧ����Ĳ���
    vector<string>tags;     //ѧ������Ȥ��ǩ
    vector<vector<pair<int, int> > >times;       //ѧ������ʱ��
    int pos;               //��ǰ����������ڿ��ǵ�pos��־Ը
    bool bechosen;         //�Ƿ�ѡ��
    map<string, double>stupoint;    //���Ŷ�ѧ���Ĵ��
    Student() :times(7) {}

}stu[stumaxn];

struct Dept {
    string dept_no;           //���ź�
    vector<vector<pair<int, int> > >times;      //���Żʱ��
    int limit;               //���ղ�Ա������
    int choose;              //ѡ��Ĳ�Ա��
    vector<string>tags;      //���ŵ��ص��ǩ
    vector<string>stu_no;    //���յ�ѧ��
    Dept() :times(7) {}
}dept[deptmaxn];


/*************************************************
Description:    �õ����ڼ�Ϊһ�������еĵڼ��죬����һΪ��0��
Input:          �ַ�����ʾ����������Mon��Tues
Return:         ���ڼ���һ�����ڵĵڼ���
*************************************************/
int getDayIndex(string str)
{
    int index;
    if (str == "Mon")
    {
        index = 0;
    }
    else if (str == "Tues")
    {
        index = 1;
    }
    else if (str == "Wed")
    {
        index = 2;
    }
    else if (str == "Thur")
    {
        index = 3;
    }
    else if (str == "Fri")
    {
        index = 4;
    }
    else if (str == "Sat")
    {
        index = 5;
    }
    else if (str == "Sun")
    {
        index = 6;
    }
    return index;
}

/*************************************************
Description:    ���ַ�����ʽ��ȡ�õ�Сʱ����Ӳ��ֵ�����ֵ
Input:          �ַ�����ʾ��Сʱ���ֻ���Ӳ���
Return:         ʱ��Сʱ���ֻ���Ӳ��ֵ�����ֵ
*************************************************/
int getTimeValue(string str)
{
    int len = str.size();
    int res = 0;
    for (int i = 0; i < len; i++)
    {
        res = res * 10 + (str[i] - '0');
    }
    return res;
}


/*************************************************
Description:    ��ʱ��ת�����Է���Ϊ��λ������ֵ
Input:          Сʱ���ֵ�������ʾ�����Ӳ��ֵ�������ʾ
Return:         �Է���Ϊ��λ��ʱ�������ֵ
*************************************************/
int converTime2Int(int hour, int minute)
{
    return hour * 60 + minute;
}

/*************************************************
Description:    ����ѧ���Ŀ���ʱ��Σ�ʱ���ʽΪ��Wed.16:05~18:00
Input:          ѧ����ʱ���
*************************************************/
void stuParseTime(Student &stu, string str)
{
    unsigned int dot_loc = str.find('.');
    unsigned int front_colon_loc = str.find(':');

    unsigned int wave_loc = str.find('~');
    unsigned int behind_colon_loc = str.find(":", wave_loc);

    string dayWeek = str.substr(0, dot_loc);
    int index = getDayIndex(dayWeek);

    //ʱ���ʽΪ��Wed.16:05~18:00
    //����ǰ�벿�ֵ�ʱ��
    string front_hour_str = str.substr(dot_loc + 1, front_colon_loc - dot_loc - 1);
    int front_hour_val = getTimeValue(front_hour_str);
    string front_minute_str = str.substr(front_colon_loc + 1, wave_loc - front_colon_loc - 1);
    int front_minute_val = getTimeValue(front_minute_str);

    //������벿�ֵ�ʱ��
    string behind_hour_str
        = str.substr(wave_loc + 1, behind_colon_loc - wave_loc - 1);
    int behind_hour_val = getTimeValue(behind_hour_str);
    string behind_minute_str
        = str.substr(behind_colon_loc + 1, str.size() - behind_colon_loc - 1);
    int behind_minute_val = getTimeValue(behind_minute_str);

    //��ʱ��δ���ָ���������У��±�0��ʾ����һ����������
    stu.times[index].push_back(make_pair(converTime2Int(front_hour_val, front_minute_val),
        converTime2Int(behind_hour_val, behind_minute_val)));
}

/*************************************************
Description:    �������ŵĿ���ʱ��Σ�ʱ���ʽΪ��Wed.16:05~18:00
Input:          ���ż�ʱ���
*************************************************/
void deptParseTime(Dept &dept, string str)
{
    unsigned int dot_loc = str.find('.');
    unsigned int front_colon_loc = str.find(':');

    unsigned int wave_loc = str.find('~');
    unsigned int behind_colon_loc = str.find(":", wave_loc);

    string dayWeek = str.substr(0, dot_loc);
    int index = getDayIndex(dayWeek);

    //ʱ���ʽΪ��Wed.16:05~18:00  
    //����ǰ�벿�ֵ�ʱ��
    string front_hour_str
        = str.substr(dot_loc + 1, front_colon_loc - dot_loc - 1);
    int front_hour_val = getTimeValue(front_hour_str);
    string front_minute_str
        = str.substr(front_colon_loc + 1, wave_loc - front_colon_loc - 1);
    int front_minute_val = getTimeValue(front_minute_str);

    //������벿�ֵ�ʱ��
    string behind_hour_str
        = str.substr(wave_loc + 1, behind_colon_loc - wave_loc - 1);
    int behind_hour_val = getTimeValue(behind_hour_str);
    string behind_minute_str
        = str.substr(behind_colon_loc + 1, str.size() - behind_colon_loc - 1);
    int behind_minute_val = getTimeValue(behind_minute_str);

    //��ʱ��δ���ָ���������У��±�0��ʾ����һ����������
    dept.times[index].push_back(make_pair(converTime2Int(front_hour_val, front_minute_val),
        converTime2Int(behind_hour_val, behind_minute_val)));
}

/*************************************************
Description:    �õ������ڲ��������е��±�
Input:          ���źż���������
return:         ���Ŷ�Ӧ�������±�
*************************************************/
int getDeptIndex(string str, int size)
{
    int index;
    for (int i = 0; i < size; i++)
    {
        if (str == dept[i].dept_no)
        {
            index = i;
            break;
        }
    }
    return index;
}

/*************************************************
Description:    �õ�ѧ����ѧ�������е��±�
Input:          ѧ���ż�ѧ������
return:         ѧ����Ӧ�������±�
*************************************************/
int getStuIndex(string str, int size)
{
    int index;
    for (int i = 0; i < size; i++)
    {
        if (str == stu[i].stu_no)
        {
            index = i;
            break;
        }
    }
    return index;
}

/*************************************************
Description:    ����ѧ����Ȥ��ǩ�벿���ص��ǩ��ͬ�ĸ���
Input:          ѧ��������
return:         ѧ����Ȥ��ǩ�벿���ص��ǩ��ͬ�ĸ���
*************************************************/
int getIdenticalTags(Student stu, Dept dept)
{
    int cnt = 0;
    int stu_tags_size = stu.tags.size();
    int dept_tags_size = dept.tags.size();
    for (int i = 0; i < stu_tags_size; i++)
    {
        for (int j = 0; j < dept_tags_size; j++)
        {
            if (stu.tags[i] == dept.tags[j])
            {
                cnt++;
                break;
            }
        }
    }
    return cnt;
}

/*************************************************
Description:    ����ѧ������ʱ���벿�ų���ʱ���غϵĸ���
�԰�СʱΪ��λ�����Сʱ�غϸ���Ϊ1���Դ�����
Input:          ѧ��������
return:         ѧ������ʱ���벿�ų���ʱ���غϵĸ���
*************************************************/
int getOverlayTime(Student stu, Dept dept)
{
    int overlay_time_cnt = 0;
    for (int i = 0; i < 7; i++)
    {
        for (it1 = stu.times[i].begin(); it1 != stu.times[i].end(); it1++)
        {
            for (it2 = dept.times[i].begin(); it2 != dept.times[i].end(); it2++)
            {
                int stu_begin_time = (*it1).first;
                int stu_end_time = (*it1).second;
                int dept_begin_time = (*it2).first;
                int dept_end_time = (*it2).second;
                int overlay_time = min(dept_end_time, stu_end_time) - max(dept_begin_time, stu_begin_time);

                //û���ص�ʱ��
                if (overlay_time <= 0)
                {
                    continue;
                }
                else
                {
                    overlay_time_cnt = (overlay_time) / 30;
                }
            }
        }
    }
    return overlay_time_cnt;
}

/*************************************************
Description:    ��������ѧ����������ŵ����ȶȣ�ʱ���ص��ȣ�
��Ȥ��ǩ���϶ȶ����ѧ������һ������ȣ�������ܷ�100��
Input:          ѧ���������Լ����������ѧ���ĵڼ�����Ը
return:         ���Ŷ�ѧ���������
*************************************************/
double getPoints(Student stu, Dept dept, int pos)
{
    double points = 0;

    //�������ȶ�ռ��40%���������ȼ���һ��ȫ�ã��������ο����
    points += 100 * 0.4 - (5 * pos);

    //��Ȥ��ǩ���϶�ռ��30%�������嵵��һ����ǩ�����6��,
    int identical_tags_cnt = getIdenticalTags(stu, dept);

    points += 6 * (identical_tags_cnt > 5 ? 5 : identical_tags_cnt);

    //ʱ���ص���ռ��30%�������嵵���԰�СʱΪ��λ��һ����λ���ص���6��
    int overlay_time_cnt = getOverlayTime(stu, dept);
    points += 6 * (overlay_time_cnt > 5 ? 5 : overlay_time_cnt);

    return points;
}

/*************************************************
Description:    ����ѧ������ʱ��
Input:          json���ڵ㣬ѧ���������е��±�
*************************************************/
void parseStuFreeTime(Json::Value& root,int index)
{
    Json::Value stu_times = root["students"][index]["free_time"];
    int stu_times_size = stu_times.size();
    for (int j = 0; j < stu_times_size; j++)
    {
        string str = stu_times[j].asString();
        stuParseTime(stu[index], str);
    }
}

/*************************************************
Description:    ����ѧ��ѧ��
Input:          json���ڵ㣬ѧ���������е��±�
*************************************************/
void parseStuNo(Json::Value& root, int index)
{
    string stu_no = root["students"][index]["student_no"].asString();
    stu[index].stu_no = stu_no;
}

/*************************************************
Description:    ����ѧ��������Ĳ���
Input:          json���ڵ㣬ѧ���������е��±�
*************************************************/
void parseStuApplyDept(Json::Value& root, int index)
{
    Json::Value app_dept = root["students"][index]["applications_department"];
    int app_dept_size = app_dept.size();
    for (int j = 0; j < app_dept_size; j++)
    {
        string str = app_dept[j].asString();
        stu[index].dept_no.push_back(str);
    }
}

/*************************************************
Description:    ����ѧ����Ȥ��ǩ
Input:          json���ڵ㣬ѧ���������е��±�
*************************************************/
void parseStuTags(Json::Value& root, int index)
{
    Json::Value stu_tags = root["students"][index]["tags"];
    int stu_tags_size = stu_tags.size();
    for (int j = 0; j < stu_tags_size; j++)
    {
        string str = stu_tags[j].asString();
        stu[index].tags.push_back(str);
    }
}

/*************************************************
Description:    �������ų���ʱ��
Input:          json���ڵ㣬�����������е��±�
*************************************************/
void parseDeptTime(Json::Value& root, int index)
{
    Json::Value event_schedules = root["departments"][index]["event_schedules"];
    int event_schedules_size = event_schedules.size();
    for (int j = 0; j < event_schedules_size; j++) {
        string str = event_schedules[j].asString();
        deptParseTime(dept[index], str);
    }
}

/*************************************************
Description:    �����������ղ�Ա��������
Input:          json���ڵ㣬�����������е��±�
*************************************************/
void parseDeptLimit(Json::Value& root, int index)
{
    int dept_limit = root["departments"][index]["member_limit"].asInt();
    dept[index].limit = dept_limit;
}

/*************************************************
Description:    �������ź�
Input:          json���ڵ㣬�����������е��±�
*************************************************/
void parseDeptNo(Json::Value& root, int index)
{
    string dept_no = root["departments"][index]["department_no"].asString();
    dept[index].dept_no = dept_no;
}

void parseDeptTags(Json::Value& root, int index)
{
    Json::Value dept_tags = root["departments"][index]["tags"];
    int dept_tags_size = dept_tags.size();
    for (int j = 0; j < dept_tags_size; j++) {
        string str = dept_tags[j].asString();
        dept[index].tags.push_back(str);
    }
}

/*************************************************
Description:    ��������ѧ����������ŵ����ȶȣ�ʱ���ص��ȣ�
                ��Ȥ��ǩ���϶ȶ����ѧ������һ�������
Input:          ѧ���������������ܸ���
*************************************************/
void deptScoreStu(int stu_size,int dept_size)
{
    for (int i = 0; i < stu_size; i++)
    {
        int dept_no_size = stu[i].dept_no.size();
        for (int j = 0; j < dept_no_size; j++)
        {
            stu[i].stupoint[stu[i].dept_no[j]]
                = getPoints(stu[i], dept[getDeptIndex(stu[i].dept_no[j], dept_size)], j);
        }
    }
}

/*************************************************
Description:    ��ѧ���벿�ŵ�ƥ������json��ʽд���ļ�
Input:          ѧ���������������ܸ����������
*************************************************/
void writeResultMessage2File(int stu_size, int dept_size, ofstream& fout)
{
    //rootΪ���ڵ�
    Json::Value root;

    //�ӽڵ�
    Json::Value admitted;

    //δ�����յ�ѧ��
    for (int i = 0; i < stu_size; i++)
    {
        if (!stu[i].bechosen)
        {
            root["unlucky_student"].append(stu[i].stu_no);
        }
    }

    //�����������
    for (int i = 0; i < dept_size; i++)
    {
        admitted.clear();
        admitted["department_no"] = Json::Value(dept[i].dept_no);

        //����jsoncpp����Ϊ�ջ����null����˽��������С��0����������ָ����"[]"��ʽ������"[null]"
        if (dept[i].choose == 0)
        {
            admitted["member"].resize(0);
        }
        else
        {
            for (int j = 0; j < dept[i].choose; j++)
            {
                admitted["member"].append(dept[i].stu_no[j]);
            }
        }

        //�ӽڵ�ҵ����ڵ�
        root["admitted"].append(admitted);
    }

    //δ�е��˵Ĳ���
    bool set_size_zero = true;
    for (int i = 0; i < dept_size; i++)
    {
        if (dept[i].choose == 0)
        {
            set_size_zero = false;;
            root["unlucky_department"].append(dept[i].dept_no);
        }
    }

    //����jsoncpp����Ϊ�ջ����null����˽��������С��0����������ָ����"[]"��ʽ������"[null]"
    if (set_size_zero)
    {
        root["unlucky_department"].resize(0);
    }

    //����������json��ʽд���ļ�
    Json::StyledWriter sw;
    fout << sw.write(root);
}

/*************************************************
Description:    �����ȶ������㷨�ı���ʵ�ֲ���Ҫ����ѧ����Ը��ƥ��
Input:          ѧ���������������ܸ���
return:         ��
*************************************************/
void distribute(int stu_size, int dept_size)
{
    //�ȶ������㷨��Ӧ��
    //��ʼѧ��ȫ�������
    queue<Student>que;
    for (int i = 0; i < stu_size; i++)
    {
        que.push(stu[i]);
    }

    //�ȶ������㷨Ӧ�ñ���
    while (!que.empty())
    {
        Student& student = stu[getStuIndex(que.front().stu_no, stu_size)];
        que.pop();

        //����ѧ��student�ĵ�pos��־Ը
        Dept& department = dept[getDeptIndex(student.dept_no[student.pos++], dept_size)];

        //������Ż�����Ա�����ѧ��ֱ����ѡ
        if (department.limit > department.choose)
        {
            department.stu_no.push_back(student.stu_no);
            department.choose++;
            student.bechosen = true;
        }
        else
        {
            //���û������Ļ����ҳ�������ѡѧ���е�������ֵ��ˣ���֮�Ƚ�
            string min_stu_no = "";
            int pos = -1;
            double min_points = 100.0;
            for (int i = 0; i < department.choose; i++)
            {
                Student tmp = stu[getStuIndex(department.stu_no[i], stu_size)];
                if (tmp.stupoint[department.dept_no] < min_points)
                {
                    min_points = tmp.stupoint[department.dept_no];
                    min_stu_no = tmp.stu_no;
                    pos = i;
                }
            }

            //���Ŷ���ѧ�������ֱ������������ѡ��ѧ����������ֻ��ͣ��ȴ���һ��
            if (student.stupoint[department.dept_no] < min_points)
            {
                //ѧ���Ĳ�����Ը��û�п�����ϣ�������һ��
                if (student.pos < (int)student.dept_no.size())
                {
                    que.push(student);
                }
            }
            else
            {
                //���Ŷ���ѧ�������ָ��������������ѡ��ѧ����������֣��滻�����������ֵ�ѧ��
                Student& min_stu = stu[getStuIndex(min_stu_no, stu_size)];
                min_stu.bechosen = false;
                if (min_stu.pos < (int)min_stu.dept_no.size())
                {
                    que.push(min_stu);
                }
                department.stu_no[pos] = student.stu_no;
                student.bechosen = true;
            }
        }
    }
}

int main()
{
    int stu_size;
    int dept_size;

    Json::Reader reader;
    Json::Value root;

    ifstream in("input_data.txt", ios::binary);
    ofstream fout;
    fout.open("output_data.txt");

    if (!in.is_open())
    {
        fout << "Open Error��can't open file" << endl;
    }

    if (reader.parse(in, root))
    {
        //����Students����
        stu_size = root["students"].size();

        for (int i = 0; i < stu_size; i++)
        {
            //����ѧ������ʱ��
            parseStuFreeTime(root,i);

            //����ѧ��ѧ��
            parseStuNo(root, i);

            //����ѧ��������Ĳ���
            parseStuApplyDept(root, i);

            //����ѧ����Ȥ��ǩ
            parseStuTags(root, i);
        }

        //����Department����
        dept_size = root["departments"].size();
        for (int i = 0; i < dept_size; i++)
        {
            //�������ų���ʱ��
            parseDeptTime(root, i);

            //����������������
            parseDeptLimit(root, i);

            //�������ź�
            parseDeptNo(root, i);

            //�������ű�ǩ
            parseDeptTags(root, i);
        }

    }

    //��������ѧ����������ŵ����ȶȣ�ʱ���ص��ȣ���Ȥ��ǩ���϶ȶ����ѧ������һ�������
    deptScoreStu(stu_size, dept_size);

    //�����ȶ������㷨ʵ��ѧ���벿��֮���ƥ��
    distribute(stu_size,dept_size);

    //�������json��ʽ������ļ�
    writeResultMessage2File(stu_size, dept_size, fout);

    //�ر��ļ�
    in.close();

    //system("pause");

    return 0;
}