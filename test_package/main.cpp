#include "date/date.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <locale>
#include <ostream>
#include <stdexcept>
#include <string>

using namespace date;
using namespace std::chrono;

auto lprintdate = [](auto const & d) {std::cout << d << std::endl; };

int main()
{
    sys_days d1 = 2016_y / oct / 29;
    sys_days d2 = 29_d / oct / 2016;
    sys_days d3 = oct / 29 / 2016;
    auto today = floor<days>(system_clock::now());
     
    lprintdate(d1);      // 2016-10-29
    lprintdate(d2);      // 2016-10-29
    lprintdate(d3);      // 2016-10-29
    lprintdate(today);   // 2016-10-31

    return 0;
}