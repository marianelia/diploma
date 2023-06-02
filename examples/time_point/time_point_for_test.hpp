#pragma once

#include <string>
#include <iostream>

using namespace std;

bool comparator(long long a, long long b);

class TimePoint {
public:
        void SetSeconds(const int new_s);

        TimePoint();
        TimePoint(const int new_hours, const int new_minutes, const int new_seconds);

        ~TimePoint() {}

        int GetInSeconds() const;
        string Get() const;

private:
        void Translate(int h, int m, int s);
        string Translate() const;

        int seconds;
};
