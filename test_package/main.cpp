#include "date/tz.h"
#include "date/date.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <locale>
#include <ostream>
#include <stdexcept>
#include <string>

date::sys_seconds parse(const std::string& str)
{
    std::istringstream in(str);
    date::sys_seconds tp;
    in >> date::parse("%FT%TZ", tp);
    if (in.fail())
    {
        in.clear();
        in.str(str);
        in >> date::parse("%FT%T%z", tp);
    }
    return tp;
}

int main()
{
    auto lprintdate = [](auto const & d) {std::cout << d << std::endl; };

    // create sys_days objects (including literals):
    {
        using namespace date;
        using namespace std::chrono;
        sys_days d1 = 2016_y / oct / 29;
        sys_days d2 = 29_d / oct / 2016;
        sys_days d3 = oct / 29 / 2016;
        auto today = floor<days>(system_clock::now());

        lprintdate(d1);      // 2016-10-29
        lprintdate(d2);      // 2016-10-29
        lprintdate(d3);      // 2016-10-29
        lprintdate(today);
    }

    // create year_month_day objects (including literals):
    {
        using namespace date;
        using namespace std::chrono;
        year_month_day d1 = 2016_y / oct / 29;
        year_month_day d2 = 29_d / oct / 2016;
        year_month_day d3 = oct / 29 / 2016;
        year_month_day today = floor<days>(system_clock::now());

        lprintdate(d1);      // 2016-10-29
        lprintdate(d2);      // 2016-10-29
        lprintdate(d3);      // 2016-10-29
        lprintdate(today);
    }

    // creating year_month_weekday literals and converting to year_month_day
    {
        using namespace date;
        using namespace std::chrono;
        auto wd1 = 2016_y / oct / mon[1];
        auto wd2 = mon[1] / oct / 2016;
        auto wd3 = oct / mon[1] / 2016;

        lprintdate(wd1);     // 2016/Oct/Mon[1]
        lprintdate(wd2);     // 2016/Oct/Mon[1]
        lprintdate(wd3);     // 2016/Oct/Mon[1]

        auto d1 = year_month_day{ wd1 };
        auto d2 = year_month_day{ wd2 };
        auto d3 = year_month_day{ wd2 };

        lprintdate(d1);      // 2016-10-03
        lprintdate(d2);      // 2016-10-03
        lprintdate(d3);      // 2016-10-03
    }

    // create year_month_day values for today, yesterday and tomorrow
    {
        using namespace date;
        using namespace std::chrono;
        auto today = floor<days>(system_clock::now());
        auto tomorrow = today + days{ 1 };
        auto yesterday = today - days{ 1 };

        lprintdate(yesterday);
        lprintdate(today);
        lprintdate(tomorrow);
    }

    // create year_month_day values for first and last day of the month
    {
        using namespace date;
        using namespace std::chrono;
        auto today = year_month_day{ floor<days>(system_clock::now()) };
        auto first_day_this_month = year_month_day{ today.year(), today.month(), day{ 1 } };
        lprintdate(first_day_this_month);// 2016-10-01

        auto d1 = year_month_day_last(today.year(), month_day_last{ today.month() });
        auto last_day_this_month = year_month_day{ d1 };
        lprintdate(last_day_this_month); // 2016-10-31

        auto d2 = year_month_day_last(year{ 2016 }, month_day_last{ month{ 2 } });
        auto last_day_feb = year_month_day{ d2 };
        lprintdate(last_day_feb);        // 2016-02-29
    }

    //{
    //    using namespace date;
    //    using namespace std::chrono;
    //    auto isod1 = 2016_y / 42 / mon;
    //    auto isod2 = 42_w / mon / 2016_y;
    //    auto isod3 = mon / 42_w / 2016_y;

    //    lprintdate(isod1);  // 2016-W44-Mon
    //    lprintdate(isod2);  // 2016-W44-Mon
    //    lprintdate(isod3);  // 2016-W44-Mon
    //}

    //{
    //    using namespace date;
    //    using namespace std::chrono;
    //    auto today = floor<days>(system_clock::now());
    //    auto today_iso = year_weeknum_weekday{ today };

    //    lprintdate(today_iso);  // 2016-W44-Mon
    //    std::cout << "week " << (unsigned)today_iso.weeknum() << std::endl; //44
    //}

    //{
    //    using namespace date;
    //    using namespace std::chrono;
    //    //std::cout << make_zoned(current_zone(), system_clock::now()) << '\n';
    //}

    //{
    //    using namespace date;
    //    std::cout << parse("2015-08-27T11:31:40+0100").time_since_epoch() << '\n';
    //    std::cout << parse("2015-08-27T10:31:40Z").time_since_epoch() << '\n';
    //}
    return 0;
}