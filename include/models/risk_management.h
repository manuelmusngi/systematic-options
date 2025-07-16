#ifndef RISK_MANAGEMENT_H
#define RISK_MANAGEMENT_H

#include "data/market_data.h"
#include "data/option_data.h"

// Forward declaration to avoid circular includes if needed,
// but for now, we'll just pass primitive types or simple structs.
// If you need to calculate option Greeks for risk, you'd include black_scholes.h here.

class RiskManagement {
public:
    // Constructor (can take initial risk parameters)
    explicit RiskManagement(double total_capital, double risk_per_trade_percent);

    // Calculates the number of contracts/shares to trade based on risk parameters.
    // forecasted_volatility: The annualized volatility used to estimate potential move.
    // trade_value_per_unit: The value of one unit (e.g., option premium or stock price).
    // Returns the calculated position size (e.g., number of option contracts).
    int calculate_position_size(double forecasted_volatility, double trade_value_per_unit) const;

    // Calculates a simple stop-loss price based on a percentage of the entry price.
    // entry_price: The price at which the position was entered.
    // stop_loss_percent: The percentage (e.g., 0.02 for 2%) below/above entry for stop.
    // is_long_position: True if it's a long position (stop loss below entry), false for short.
    // Returns the calculated stop-loss price.
    double calculate_stop_loss_price(double entry_price, double stop_loss_percent, bool is_long_position) const;

    // Calculates a simple take-profit price based on a percentage of the entry price.
    // entry_price: The price at which the position was entered.
    // take_profit_percent: The percentage (e.g., 0.05 for 5%) above/below entry for profit.
    // is_long_position: True if it's a long position (take profit above entry), false for short.
    // Returns the calculated take-profit price.
    double calculate_take_profit_price(double entry_price, double take_profit_percent, bool is_long_position) const;

private:
    double total_capital_;
    double risk_per_trade_percent_; // e.g., 0.01 for 1% of capital per trade
};

#endif // RISK_MANAGEMENT_H
