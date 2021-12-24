// Glass.h has all required includes for Glass.
#include "../includes/Glass.h"

// Wait for the given time.
void Sleep(const float& SleepTime)
{
    sleep(SleepTime);
}

// Get the Current Time (including milliseconds).
string TimeNow()
{
    time_t Now = time(0);
    return ctime(&Now);
}

// Only get current Hour, Minute and Seconds.
string OnlyTime()
{
    time_t Now = time(0);
    tm* TimePtr = localtime(&Now);

    const string Hour = to_string(TimePtr->tm_hour);
    const string Minutes = to_string(TimePtr->tm_min);
    const string Seconds = to_string(TimePtr->tm_sec);

    return Hour + ":" + Minutes + ":" + Seconds;
}

// Only get current Hour.
string Hour()
{
    time_t Now = time(0);
    tm* TimePtr = localtime(&Now);

    return to_string(TimePtr->tm_hour);
}

// Only get current Minute.
string Min()
{
    time_t Now = time(0);
    tm* TimePtr = localtime(&Now);

    return to_string(TimePtr->tm_min);
}

// Only get current Seconds.
string Sec()
{
    time_t Now = time(0);
    tm* TimePtr = localtime(&Now);

    return to_string(TimePtr->tm_sec);
}

// Get Current Date.
string Date()
{
    time_t Now = time(0);
    tm* TimePtr = localtime(&Now);
    auto MonthIndex = TimePtr->tm_mon;
    auto TodayDayIndex = TimePtr->tm_wday;

    const string Days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    const string Months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    const string TodayDay = Days[TodayDayIndex];
    const string CurrentMonth = Months[MonthIndex];
    const string CurrentDayInMonth = to_string(TimePtr->tm_mday);
    const string CurrentYear = to_string(1900 + TimePtr->tm_year);

    return TodayDay + ", " + CurrentDayInMonth + " " + CurrentMonth + " " + CurrentYear;
}

// Only get current Year.
string Year()
{
    time_t Now = time(0);
    tm* TimePtr = localtime(&Now);

    return to_string(1900 + TimePtr->tm_year);
}

// Only get current Month.
string Month()
{
    string Months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    time_t Now = time(0);
    tm* TimePtr = localtime(&Now);
    auto MonthIndex = TimePtr->tm_mon;

    return Months[MonthIndex];
}

// Only get current Day of the Week.
string DayOfWeek()
{
    string Days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    time_t Now = time(0);
    tm* TimePtr = localtime(&Now);
    auto TodayDayIndex = TimePtr->tm_wday;

    return Days[TodayDayIndex];
}

// Only get current Day of the Month.
string DayInMonth()
{
    time_t Now = time(0);
    tm* TimePtr = localtime(&Now);

    return to_string(TimePtr->tm_mday);
}
