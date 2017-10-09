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
    string stu_no;           //学生号
    vector<string>dept_no;   //学生填报的部门
    vector<string>tags;     //学生的兴趣标签
    vector<vector<pair<int, int> > >times;       //学生空闲时段
    int pos;               //当前分配过程正在考虑第pos个志愿
    bool bechosen;         //是否被选中
    map<string, double>stupoint;    //部门对学生的打分
    Student() :times(7) {}

}stu[stumaxn];

struct Dept {
    string dept_no;           //部门号
    vector<vector<pair<int, int> > >times;      //部门活动时段
    int limit;               //招收部员的上限
    int choose;              //选择的部员数
    vector<string>tags;      //部门的特点标签
    vector<string>stu_no;    //招收的学生
    Dept() :times(7) {}
}dept[deptmaxn];


/*************************************************
Description:    得到星期几为一个星期中的第几天，星期一为第0天
Input:          字符串表示的星期数：Mon、Tues
Return:         星期几在一个星期的第几天
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
Description:    从字符串形式获取得到小时或分钟部分的整数值
Input:          字符串表示的小时部分或分钟部分
Return:         时间小时部分或分钟部分的整数值
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
Description:    将时间转换成以分钟为单位的整数值
Input:          小时部分的整数表示，分钟部分的整数表示
Return:         以分钟为单位的时间的整数值
*************************************************/
int converTime2Int(int hour, int minute)
{
    return hour * 60 + minute;
}

/*************************************************
Description:    解析学生的空闲时间段，时间格式为：Wed.16:05~18:00
Input:          学生及时间段
*************************************************/
void stuParseTime(Student &stu, string str)
{
    unsigned int dot_loc = str.find('.');
    unsigned int front_colon_loc = str.find(':');

    unsigned int wave_loc = str.find('~');
    unsigned int behind_colon_loc = str.find(":", wave_loc);

    string dayWeek = str.substr(0, dot_loc);
    int index = getDayIndex(dayWeek);

    //时间格式为：Wed.16:05~18:00
    //解析前半部分的时间
    string front_hour_str = str.substr(dot_loc + 1, front_colon_loc - dot_loc - 1);
    int front_hour_val = getTimeValue(front_hour_str);
    string front_minute_str = str.substr(front_colon_loc + 1, wave_loc - front_colon_loc - 1);
    int front_minute_val = getTimeValue(front_minute_str);

    //解析后半部分的时间
    string behind_hour_str
        = str.substr(wave_loc + 1, behind_colon_loc - wave_loc - 1);
    int behind_hour_val = getTimeValue(behind_hour_str);
    string behind_minute_str
        = str.substr(behind_colon_loc + 1, str.size() - behind_colon_loc - 1);
    int behind_minute_val = getTimeValue(behind_minute_str);

    //将时间段存入指定的星期中，下标0表示星期一，依次类推
    stu.times[index].push_back(make_pair(converTime2Int(front_hour_val, front_minute_val),
        converTime2Int(behind_hour_val, behind_minute_val)));
}

/*************************************************
Description:    解析部门的空闲时间段，时间格式为：Wed.16:05~18:00
Input:          部门及时间段
*************************************************/
void deptParseTime(Dept &dept, string str)
{
    unsigned int dot_loc = str.find('.');
    unsigned int front_colon_loc = str.find(':');

    unsigned int wave_loc = str.find('~');
    unsigned int behind_colon_loc = str.find(":", wave_loc);

    string dayWeek = str.substr(0, dot_loc);
    int index = getDayIndex(dayWeek);

    //时间格式为：Wed.16:05~18:00  
    //解析前半部分的时间
    string front_hour_str
        = str.substr(dot_loc + 1, front_colon_loc - dot_loc - 1);
    int front_hour_val = getTimeValue(front_hour_str);
    string front_minute_str
        = str.substr(front_colon_loc + 1, wave_loc - front_colon_loc - 1);
    int front_minute_val = getTimeValue(front_minute_str);

    //解析后半部分的时间
    string behind_hour_str
        = str.substr(wave_loc + 1, behind_colon_loc - wave_loc - 1);
    int behind_hour_val = getTimeValue(behind_hour_str);
    string behind_minute_str
        = str.substr(behind_colon_loc + 1, str.size() - behind_colon_loc - 1);
    int behind_minute_val = getTimeValue(behind_minute_str);

    //将时间段存入指定的星期中，下标0表示星期一，依次类推
    dept.times[index].push_back(make_pair(converTime2Int(front_hour_val, front_minute_val),
        converTime2Int(behind_hour_val, behind_minute_val)));
}

/*************************************************
Description:    得到部门在部门数组中的下标
Input:          部门号及部门总数
return:         部门对应的数组下标
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
Description:    得到学生在学生数组中的下标
Input:          学生号及学生总数
return:         学生对应的数组下标
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
Description:    计算学生兴趣标签与部门特点标签相同的个数
Input:          学生及部门
return:         学生兴趣标签与部门特点标签相同的个数
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
Description:    计算学生空闲时间与部门常规活动时间重合的个数
以半小时为单位，半个小时重合个数为1，以此类推
Input:          学生及部门
return:         学生空闲时间与部门常规活动时间重合的个数
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

                //没有重叠时间
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
Description:    社团依据学生对于填报社团的优先度，时间重叠度，
兴趣标签符合度对填报的学生给出一个满意度，满意度总分100分
Input:          学生，部门以及这个部门是学生的第几个意愿
return:         社团对学生的满意度
*************************************************/
double getPoints(Student stu, Dept dept, int pos)
{
    double points = 0;

    //社团优先度占比40%，社团优先级第一则全得，其他依次扣五分
    points += 100 * 0.4 - (5 * pos);

    //兴趣标签符合度占比30%，共分五档，一个标签相符得6分,
    int identical_tags_cnt = getIdenticalTags(stu, dept);

    points += 6 * (identical_tags_cnt > 5 ? 5 : identical_tags_cnt);

    //时间重叠度占比30%，共分五档，以半小时为单位，一个单位相重叠得6分
    int overlay_time_cnt = getOverlayTime(stu, dept);
    points += 6 * (overlay_time_cnt > 5 ? 5 : overlay_time_cnt);

    return points;
}

/*************************************************
Description:    解析学生空闲时段
Input:          json根节点，学生在数组中的下标
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
Description:    解析学生学号
Input:          json根节点，学生在数组中的下标
*************************************************/
void parseStuNo(Json::Value& root, int index)
{
    string stu_no = root["students"][index]["student_no"].asString();
    stu[index].stu_no = stu_no;
}

/*************************************************
Description:    解析学生所倾向的部门
Input:          json根节点，学生在数组中的下标
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
Description:    解析学生兴趣标签
Input:          json根节点，学生在数组中的下标
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
Description:    解析部门常规活动时间
Input:          json根节点，部门在数组中的下标
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
Description:    解析部门招收部员人数上限
Input:          json根节点，部门在数组中的下标
*************************************************/
void parseDeptLimit(Json::Value& root, int index)
{
    int dept_limit = root["departments"][index]["member_limit"].asInt();
    dept[index].limit = dept_limit;
}

/*************************************************
Description:    解析部门号
Input:          json根节点，部门在数组中的下标
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
Description:    社团依据学生对于填报社团的优先度，时间重叠度，
                兴趣标签符合度对填报的学生给出一个满意度
Input:          学生总人数，部门总个数
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
Description:    将学生与部门的匹配结果用json格式写入文件
Input:          学生总人数，部门总个数，输出流
*************************************************/
void writeResultMessage2File(int stu_size, int dept_size, ofstream& fout)
{
    //root为根节点
    Json::Value root;

    //子节点
    Json::Value admitted;

    //未被招收的学生
    for (int i = 0; i < stu_size; i++)
    {
        if (!stu[i].bechosen)
        {
            root["unlucky_student"].append(stu[i].stu_no);
        }
    }

    //部门招收情况
    for (int i = 0; i < dept_size; i++)
    {
        admitted.clear();
        admitted["department_no"] = Json::Value(dept[i].dept_no);

        //由于jsoncpp数组为空会输出null，因此将其数组大小置0，则可以输出指定的"[]"格式，而非"[null]"
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

        //子节点挂到根节点
        root["admitted"].append(admitted);
    }

    //未招到人的部门
    bool set_size_zero = true;
    for (int i = 0; i < dept_size; i++)
    {
        if (dept[i].choose == 0)
        {
            set_size_zero = false;;
            root["unlucky_department"].append(dept[i].dept_no);
        }
    }

    //由于jsoncpp数组为空会输出null，因此将其数组大小置0，则可以输出指定的"[]"格式，而非"[null]"
    if (set_size_zero)
    {
        root["unlucky_department"].resize(0);
    }

    //以有缩进的json格式写入文件
    Json::StyledWriter sw;
    fout << sw.write(root);
}

/*************************************************
Description:    利用稳定婚姻算法的变形实现部门要求与学生意愿的匹配
Input:          学生总人数，部门总个数
return:         无
*************************************************/
void distribute(int stu_size, int dept_size)
{
    //稳定婚姻算法的应用
    //初始学生全部入队列
    queue<Student>que;
    for (int i = 0; i < stu_size; i++)
    {
        que.push(stu[i]);
    }

    //稳定婚姻算法应用变形
    while (!que.empty())
    {
        Student& student = stu[getStuIndex(que.front().stu_no, stu_size)];
        que.pop();

        //考虑学生student的第pos个志愿
        Dept& department = dept[getDeptIndex(student.dept_no[student.pos++], dept_size)];

        //如果部门还有人员名额，则学生直接中选
        if (department.limit > department.choose)
        {
            department.stu_no.push_back(student.stu_no);
            department.choose++;
            student.bechosen = true;
        }
        else
        {
            //如果没有名额的话，找出部门挑选学生中的最低评分的人，与之比较
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

            //部门对于学生的评分比这个部门中中选的学生的最低评分还低，等待下一轮
            if (student.stupoint[department.dept_no] < min_points)
            {
                //学生的部门意愿还没有考虑完毕，放入下一轮
                if (student.pos < (int)student.dept_no.size())
                {
                    que.push(student);
                }
            }
            else
            {
                //部门对于学生的评分高于这个部门中中选的学生的最低评分，替换到这个最低评分的学生
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
        fout << "Open Error：can't open file" << endl;
    }

    if (reader.parse(in, root))
    {
        //解析Students部分
        stu_size = root["students"].size();

        for (int i = 0; i < stu_size; i++)
        {
            //解析学生空闲时段
            parseStuFreeTime(root,i);

            //解析学生学号
            parseStuNo(root, i);

            //解析学生所倾向的部门
            parseStuApplyDept(root, i);

            //解析学生兴趣标签
            parseStuTags(root, i);
        }

        //解析Department部分
        dept_size = root["departments"].size();
        for (int i = 0; i < dept_size; i++)
        {
            //解析部门常规活动时间
            parseDeptTime(root, i);

            //解析部门人数上限
            parseDeptLimit(root, i);

            //解析部门号
            parseDeptNo(root, i);

            //解析部门标签
            parseDeptTags(root, i);
        }

    }

    //社团依据学生对于填报社团的优先度，时间重叠度，兴趣标签符合度对填报的学生给出一个满意度
    deptScoreStu(stu_size, dept_size);

    //利用稳定婚姻算法实现学生与部门之间的匹配
    distribute(stu_size,dept_size);

    //将结果以json格式输出到文件
    writeResultMessage2File(stu_size, dept_size, fout);

    //关闭文件
    in.close();

    //system("pause");

    return 0;
}