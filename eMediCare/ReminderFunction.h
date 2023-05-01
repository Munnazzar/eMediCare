#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
using namespace std;




bool reminder(string input_weekday, int input_hour, int input_minute)      //a function that returns a boolean, in case the current time and weekday matches with the given time and weekday
{
    // Get current time and weekday
    auto now = chrono::system_clock::now();                                // gets the current time from the system clock
    time_t current_time = chrono::system_clock::to_time_t(now);            /* This line converts the time stored in now to a time_t value, which is a C++ standard library type that represents
                                                                              a point in time uses the to_time_t function*/

    tm ltm;
    localtime_s(&ltm, &current_time);
    int current_hour = ltm.tm_hour;
    int current_minute = ltm.tm_min;
    string weekdays[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
    string current_weekday = weekdays[ltm.tm_wday];


    // Find index of input weekday in weekdays array
    int input_weekday_index = -1;
    for (int i = 0; i < 7; i++)
    {
        if (weekdays[i].compare(input_weekday) == 0)
        {

            input_weekday_index = i;
            break;
        }
    }

    // If input weekday is not valid exit
    if (input_weekday_index == -1)
    {
        return false;
    }

    // Calculate total minutes for current time and input time
    int current_total_minutes = current_hour * 60 + current_minute;
    int input_total_minutes = input_hour * 60 + input_minute;

    // Compare total minutes and weekday
    if (current_total_minutes == input_total_minutes && current_weekday == weekdays[input_weekday_index])
    {
        return true;        //returns true if the given time and weekday matches with the current time and weekday
    }
    else
    {
        return false;       //returns false if the given time and weekday does not matches with the current time and weekday
    }
}