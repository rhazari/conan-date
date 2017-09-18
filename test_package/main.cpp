#include "date/date.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <locale>
#include <ostream>
#include <stdexcept>
#include <string>

date::year
current_year()
{
    using namespace std::chrono;
    using namespace date;
    year_month_day ymd = floor<days>(system_clock::now());
    return ymd.year();
}

// The number of weeks in a calendar month layout plus 2 more for the calendar titles
unsigned
number_of_lines_calendar(date::year_month const ym, date::weekday const firstdow)
{
    using namespace date;
    return static_cast<unsigned>(
        ceil<weeks>((weekday{ym/1} - firstdow) + ((ym/last).day() - day{0})).count()) + 2;
}

// Print one line of a calendar month
void
print_line_of_calendar_month(std::ostream& os, date::year_month const ym,
                             unsigned const line, date::weekday const firstdow)
{
    using namespace std;
    using namespace date;
    switch (line)
    {
    case 0:
        // Output month and year title
        os << left << setw(21) << format(os.getloc(), " %B %Y", sys_days{ym/1}) << right;
        break;
    case 1:
        {
        // Output weekday names title
        auto sd = sys_days{ym/firstdow[1]};
        for (auto const esd = sd + weeks{1}; sd < esd; sd += days{1})
        {
            auto d = format(os.getloc(), "%a", sd);
            d.resize(2);
            os << ' ' << d;
        }
        break;
        }
    case 2:
        {
        // Output first week prefixed with spaces if necessary
        auto wd = weekday{ym/1};
        os << string(static_cast<unsigned>((wd-firstdow).count())*3, ' ');
        auto d = 1_d;
        do
        {
            os << setw(3) << unsigned(d);
            ++d;
        } while (++wd != firstdow);
        break;
        }
    default:
        {
        // Output a non-first week:
        // First find first day of week
        unsigned index = line - 2;
        auto sd = sys_days{ym/1};
        if (weekday{sd} == firstdow)
            ++index;
        auto ymdw = ym/firstdow[index];
        if (ymdw.ok()) // If this is a valid week, print it out
        {
            auto d = year_month_day{ymdw}.day();
            auto const e = (ym/last).day();
            auto wd = firstdow;
            do
            {
                os << setw(3) << unsigned(d);
            } while (++wd != firstdow && ++d <= e);
            // Append row with spaces if the week did not complete
            os << string(static_cast<unsigned>((firstdow-wd).count())*3, ' ');
        }
        else  // Otherwise not a valid week, output a blank row
            os << string(21, ' ');
        break;
        }
    }
}

void
print_calendar_year(std::ostream& os, unsigned const cols = 3,
                    date::year const y = current_year(),
                    date::weekday const firstdow = date::sun)
{
    using namespace date;
    if (cols == 0 || 12 % cols != 0)
        throw std::runtime_error("The number of columns " + std::to_string(cols)
                                 + " must be one of [1, 2, 3, 4, 6, 12]");
    // Compute number of lines needed for each calendar month
    unsigned ml[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    for (auto& m : ml)
        m = number_of_lines_calendar(y/month{m}, firstdow);
    for (auto r = 0u; r < 12/cols; ++r) // for each row
    {
        const auto lines = *std::max_element(std::begin(ml) + (r*cols),
                                             std::begin(ml) + ((r+1)*cols));
        for (auto l = 0u; l < lines; ++l) // for each line
        {
            for (auto c = 0u; c < cols; ++c) // for each column
            {
                if (c != 0)
                    os << "   ";
                print_line_of_calendar_month(os, y/month{r*cols + c+1}, l, firstdow);
            }
            os << '\n';
        }
        os << '\n';
    }
}

int
main()
{
    print_calendar_year(std::cout, 3);
}