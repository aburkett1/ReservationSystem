#ifndef TIMERANGE_H_
#define TIMERANGE_H_

#include <string>
using namespace std;

// =============================================================================
// MARK: TimeRange Struct
// =============================================================================

struct TimeRange {
    int startHour;
    int endHour;

    TimeRange(): startHour(0), endHour(0) {}

    TimeRange(int start, int end)
        : startHour(start), endHour(end) {}

    static string converter24to12(int time24hr)
    {
        if (time24hr == 0 || time24hr == 24)
        {
            return "12 AM";
        }
        else if (time24hr == 12)
        {
            return "12 PM";
        }
        else if (time24hr > 12)
        {
            return to_string(time24hr - 12) + " PM";
        }
        else 
        {
            return to_string(time24hr) + " AM";
        }
    }
};


// =============================================================================
// MARK: DateAndTimeRange Struct
// =============================================================================

struct DateAndTimeRange : public TimeRange {
    string date;

    DateAndTimeRange(): TimeRange(), date("") {}

    DateAndTimeRange(int start, int end, string d)
        : TimeRange(start, end), date(d) {}
};

#endif