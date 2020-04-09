#include <iostream>
#include<string>
#include <iomanip>  //不要忘了头文件

#include<vector>
using namespace std;
//IsLeap函数判断一个年份是否为闰年，方法如下:
bool IsLeap(int year)
{
	//return (year % 4 == 0 || year % 400 == 0) && (year % 100 != 0);
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

//上面的StringToDate函数用于取出日期中的年月日并判断日期是否合法
//从字符中最得年月日 规定日期的格式是yyyy-mm-dd
bool StringToDate(string date, int& year, int& month, int& day)
{
	year = atoi((date.substr(0, 4)).c_str());
	month = atoi((date.substr(5, 2)).c_str());
	day = atoi((date.substr(8, 2)).c_str());
	int DAY[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (IsLeap(year)) {
		DAY[1] = 29;
	}
	return year >= 0 && month <= 12 && month > 0 && day <= DAY[month] && day > 0;
}

//DayInYear能根据给定的日期，求出它在该年的第几天，代码如下
int DayInYear(int year, int month, int day)
{
	//int _day = 0;
	int DAY[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (IsLeap(year))
		DAY[1] = 29;
	for (int i = 0; i < month - 1; ++i)
	{
		day += DAY[i];
	}
	return day;
}

int DaysBetween2Date(string date1, string date2)
{
	//取出日期中的年月日
	int year1, month1, day1;
	int year2, month2, day2;
	if (!StringToDate(date1, year1, month1, day1) || !StringToDate(date2, year2, month2, day2))
	{
		cout << "输入的日期格式不正确";
		return -1;
	}
	if (year1 == year2 && month1 == month2)
	{
		return day1 > day2 ? day1 - day2 : day2 - day1;

		//如果年相同
	}
	else if (year1 == year2)
	{
		int d1, d2;
		d1 = DayInYear(year1, month1, day1);
		d2 = DayInYear(year2, month2, day2);
		return d1 > d2 ? d1 - d2 : d2 - d1;

		//年月都不相同
	}
	else {
		//确保year1年份比year2早
		if (year1 > year2)
		{
			//swap进行两个值的交换
			swap(year1, year2);
			swap(month1, month2);
			swap(day1, day2);
		}
		int d1, d2, d3;
		if (IsLeap(year1))
			d1 = 366 - DayInYear(year1, month1, day1); //取得这个日期在该年还于下多少天
		else
			d1 = 365 - DayInYear(year1, month1, day1);
		d2 = DayInYear(year2, month2, day2); //取得在当年中的第几天

		d3 = 0;
		for (int year = year1 + 1; year < year2; year++)
		{
			if (IsLeap(year))
				d3 += 366;
			else
				d3 += 365;
		}
		return d1 + d2 + d3;
	}
}

void stringToTime(string time, int& hour, int& min, int& sec)
{
	hour = atoi((time.substr(0, 2)).c_str());
	min = atoi((time.substr(3, 2)).c_str());
	sec = atoi((time.substr(6, 2)).c_str());
}

int zeorTime(string time1, string time2)
{
	int hour1, hour2, min1, min2, sec1, sec2;
	stringToTime(time1, hour1, min1, sec1);
	stringToTime(time2, hour2, min2, sec2);
	int sumTime1,sumTime2;
	sumTime1 = -sec1 - min1 * 60 + (24 - hour1) * 3600;
	sumTime2 = hour2 * 3600 + min2 * 60 + sec2;
	
	return sumTime1 + sumTime2;

}
int nzeorTime(string time1, string time2)
{
	int hour1, hour2, min1, min2, sec1, sec2;
	stringToTime(time1, hour1, min1, sec1);
	stringToTime(time2, hour2, min2, sec2);
	int sumTime;
	sumTime = (hour2 - hour1) * 3600 + (min2 - min1) * 60 + sec2 - sec1;
	
	return sumTime;

}

int main()
{
	string date1, time1, date2, time2;
	vector<string> s;
	for (int i = 0; i < 2; i++)
	{
		string ss;
		getline(cin, ss);
		s.push_back(ss);
	}
	date1 = s[0].substr(0, 10);
	date2 = s[1].substr(0, 10);
	time1 = s[0].substr(11, 8);
	time2 = s[1].substr(11, 8);
	long long a = DaysBetween2Date(date1, date2);
	if (a == 0)
	{
		long long b = nzeorTime(time1, time2);
		long long sumTime;
		sumTime = b * 1000LL;
		cout << sumTime;
	}
	else
	{
		long long b = zeorTime(time1, time2);
		long long  sumTime;
		sumTime = ((a-1LL) * 24LL * 60LL * 60LL  + b)*1000LL;	
		cout <<  sumTime;
	}
}