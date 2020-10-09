#include <iostream>
using namespace std;

class Date
{
    public:
        Date(int m, int d, int y):month(m),day(d),year(y)
        {
            if (checkIfLeapYear(year))
                isLeapYear = true;
            else
                isLeapYear = false;
            setDayNum();
        }
        ~Date(){};

        int month;
        int day;
        int year;
        bool isLeapYear;
        int dayNum;

        bool checkIfLeapYear(int yr)
        {
            if (yr % 4 == 0)
            {
                if (yr % 100 == 0)
                {
                    if (yr % 400 == 0)
                        return true;
                    return false;
                }
                return true;
            }
            return false;
        }

        void printDate()
        {
            cout << month << "/" << day << "/" << year << endl;
        }

        void setDayNum()
        {
            int count = 0;
            for (int i = 1; i<month; i++)
            {
                if (i==9||i==4||i==6||i==11)
                    count+=30;
                else if (i==2 && isLeapYear)
                    count+=29;
                else if (i==2)
                    count+=28;
                else
                    count+=31;
            }
            count += day;
            dayNum = count;
        }

        /*
            Given a number of days, adds to current date and prints out new date
        */
        void printFutureDate(int days)
        {
            int newDayNum = dayNum+days;
            int currentMonth = month;
            int currentDay = day;
            int currentYear = year;

            int daysLeft = newDayNum;
            

            while (true) {
                if (checkIfLeapYear(currentYear) && daysLeft>366)
                {
                    daysLeft -= 366;
                    currentYear+=1;
                    currentMonth=0;
                }
                else if (!checkIfLeapYear(currentYear) && daysLeft>365)
                {
                    daysLeft -= 365;
                    currentYear+=1;
                    currentMonth=0;
                }
                else
                {
                    break;
                }

            }
            // last day of every month as represented in nth day of year form
            // 59 should be 60 on leap year and everything after +1
            int nonLeapYearmonths[13] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
            int leapYearMonths[13]= {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366};;
            int (*months)[13] = (checkIfLeapYear(currentYear)) ? &leapYearMonths : &nonLeapYearmonths;

            while ((*months)[currentMonth] < daysLeft) {
                // Figure out the correct month.
                currentMonth++;
            }

            // Get the day thanks to the months array
            currentDay = daysLeft - (*months)[currentMonth - 1];

            cout << currentMonth << "/" << currentDay << "/" << currentYear << endl;
        }
};

int main () 
{ 
    Date date(4,5,2020);
    date.printFutureDate(200); // prints 10/22/2020
    date.printFutureDate(271); // prints 1/1/2021
    cout << std::boolalpha << date.isLeapYear << endl;
    cout << date.dayNum << endl;
    return 0;
}
