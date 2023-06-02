#include "time_point_for_test.hpp"

bool comparator(long long a, long long b){
    return a>b?true:false;
}

void TimePoint::SetSeconds(const int new_s)
{ 
    seconds = new_s;
}

TimePoint::TimePoint()
{ 
    seconds = 0;
}

TimePoint::TimePoint(const int new_hours, const int new_minutes, const int new_seconds)
{
        Translate(new_hours, new_minutes, new_seconds);
}

int TimePoint::GetInSeconds() const
{
    return seconds;
}

string TimePoint::Get() const
{
        return Translate();
}

void TimePoint::Translate(int h, int m, int s_)
{
        seconds = h * 3600 + m * 60 + s_;
}
string TimePoint::Translate() const
{
        int hour = seconds / 3600;
        int minute = (seconds % 3600) / 60;
        int second = seconds - hour * 3600 - minute * 60;
	string h = to_string(hour);
	string m = to_string(minute);
	string s = to_string(second);
	string time = "";
	if (hour < 10)
        time += '0';
	time += h;
	time += ':';
	if (minute < 10)
        time += '0';
	time += m;
	time += ':';
	if (second < 10)
        time += '0';
	time += s;
	return time;
	}
