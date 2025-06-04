#ifndef OPTION_DATA_H
#define OPTION_DATA_H

// Represents an option contract
struct OptionData {
    double strike_price;        // Strike price of the option
    double time_to_expiration;  // Time to expiration in years (e.g., 0.25 for 3 months)
    char type;                  // 'C' for Call, 'P' for Put
    double market_price;        // Current market price of the option
};

#endif // OPTION_DATA_H
