#ifndef DATE_UTILS_H
#define DATE_UTILS_H

#include <string> // For std::string (e.g., for parsing/formatting)
#include <stdexcept> // For std::invalid_argument

namespace date_utils {

// Simple Date struct
struct Date {
    int year;
    int month; // 1-12
    int day;   // 1-31

    // Default constructor
    Date() : year(1970), month(1), day(1) {}

    // Parameterized constructor
    Date(int y, int m, int d);

    // Converts the date to a string in YYYY-MM-DD format
    std::string to_string() const;
};

// Checks if a given year is a leap year.
bool is_leap_year(int year);

// Returns the number of days in a given month of a given year.
int days_in_month(int year, int month);

// Converts a Date object to the number of days since a fixed epoch (e.g., 0001-01-01).
// This is a common way to calculate day differences easily.
long long date_to_days(const Date& date);

// Calculates the number of actual days between two dates (end_date - start_date).
// Returns a positive value if end_date is after start_date, negative if before, 0 if same.
long long days_between(const Date& start_date, const Date& end_date);

// Converts a number of days into years, typically for time to expiration calculations.
// Uses 365.25 days per year to account for leap years on average.
double days_to_years(long long days);

} // namespace date_utils

#endif // DATE_UTILS_H
