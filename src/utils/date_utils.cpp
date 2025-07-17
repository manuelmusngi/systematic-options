#include "utils/date_utils.h"
#include <iomanip> // For std::setfill, std::setw
#include <sstream> // For std::stringstream
#include <vector>  // For days_in_month_lookup

namespace date_utils {

// Lookup table for days in each month (non-leap year)
static const std::vector<int> days_in_month_lookup = {
    0, // Dummy for 0-index
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

// Helper function to validate date components
static void validate_date_components(int y, int m, int d) {
    if (m < 1 || m > 12) {
        throw std::invalid_argument("Invalid month: " + std::to_string(m) + ". Month must be between 1 and 12.");
    }
    int dim = days_in_month(y, m);
    if (d < 1 || d > dim) {
        throw std::invalid_argument("Invalid day: " + std::to_string(d) + " for month " + std::to_string(m) + ", year " + std::to_string(y) + ". Day must be between 1 and " + std::to_string(dim) + ".");
    }
}

// Parameterized constructor implementation
Date::Date(int y, int m, int d) : year(y), month(m), day(d) {
    validate_date_components(y, m, d);
}

// Converts the date to a string in YYYY-MM-DD format
std::string Date::to_string() const {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(4) << year << "-"
       << std::setfill('0') << std::setw(2) << month << "-"
       << std::setfill('0') << std::setw(2) << day;
    return ss.str();
}

// Checks if a given year is a leap year.
bool is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Returns the number of days in a given month of a given year.
int days_in_month(int year, int month) {
    if (month < 1 || month > 12) {
        // This should ideally be caught by validate_date_components or handled by caller
        return 0; // Invalid month
    }
    if (month == 2 && is_leap_year(year)) {
        return 29;
    }
    return days_in_month_lookup[month];
}

// Converts a Date object to the number of days since a fixed epoch (e.g., 0001-01-01).
// This is a common way to calculate day differences easily.
// Algorithm based on Fliegel and Van Flandern (1968) or similar Julian Day calculations.
long long date_to_days(const Date& date) {
    // This algorithm works for positive years (AD).
    // Adjust month and year for calculation if month is Jan or Feb
    long long y = date.year;
    long long m = date.month;
    long long d = date.day;

    if (m <= 2) {
        y--;
        m += 12;
    }

    // Calculate Julian Day Number (simplified for Gregorian calendar)
    // K = day of month, J = month, I = year
    // JDN = K + floor((153*J + 2)/5) + 365*I + floor(I/4) - floor(I/100) + floor(I/400) - 32045
    // Using a common variation that maps 1-Jan-0001 to day 1.
    return d + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400;
}

// Calculates the number of actual days between two dates (end_date - start_date).
// Returns a positive value if end_date is after start_date, negative if before, 0 if same.
long long days_between(const Date& start_date, const Date& end_date) {
    return date_to_days(end_date) - date_to_days(start_date);
}

// Converts a number of days into years, typically for time to expiration calculations.
// Uses 365.25 days per year to account for leap years on average.
double days_to_years(long long days) {
    return static_cast<double>(days) / 365.25;
}

} // namespace date_utils
