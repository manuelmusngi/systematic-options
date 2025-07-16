#include "models/risk_management.h"
#include <iostream> // For logging/debugging
#include <cmath>    // For std::sqrt, std::abs
#include <algorithm>// For std::max

// Constructor definition
RiskManagement::RiskManagement(double total_capital, double risk_per_trade_percent)
    : total_capital_(total_capital), risk_per_trade_percent_(risk_per_trade_percent) {
    if (total_capital_ <= 0) {
        std::cerr << "Warning: Total capital must be positive. Setting to 100000.0." << std::endl;
        total_capital_ = 100000.0; // Default to a reasonable value
    }
    if (risk_per_trade_percent_ <= 0 || risk_per_trade_percent_ >= 1) {
        std::cerr << "Warning: Risk per trade percent must be between 0 and 1. Setting to 0.01." << std::endl;
        risk_per_trade_percent_ = 0.01; // Default to 1%
    }
}

int RiskManagement::calculate_position_size(double forecasted_volatility, double trade_value_per_unit) const {
    if (forecasted_volatility <= 0 || trade_value_per_unit <= 0) {
        std::cerr << "Warning: Invalid input for position sizing. Volatility and trade value must be positive." << std::endl;
        return 0;
    }

    // Calculate the maximum dollar amount to risk per trade
    double max_dollar_risk = total_capital_ * risk_per_trade_percent_;

    // A very simplified approach:
    // Estimate potential daily move based on forecasted volatility (e.g., 1-day 1-sigma move)
    // This is highly simplified and needs to be refined for options.
    // For stocks: daily_move_estimate = spot_price * forecasted_volatility / sqrt(252)
    // For options: This is more complex, involving option delta and gamma.
    // For this example, let's assume `trade_value_per_unit` represents the premium
    // and we're risking a portion of that premium.

    // Let's assume for simplicity, the "risk" per unit is a fixed fraction of the `trade_value_per_unit`
    // or a more sophisticated calculation involving option Greeks.
    // For now, let's use a very basic approach:
    // Assume a "typical" loss per contract if the trade goes wrong, e.g., 50% of premium.
    // This needs to be replaced with a proper risk model (e.g., using option delta for underlying exposure).

    // A more robust but still simple approach for options:
    // If we buy an option, the maximum loss is the premium paid.
    // If we sell an option, the loss can be theoretically unlimited, so this is very naive.
    // For a long volatility strategy (buying straddles/strangles), max loss is premium paid.
    // For short volatility strategy (selling straddles/strangles), risk is much higher.

    // Let's assume we are buying options (long volatility strategy).
    // The maximum loss per contract is the premium paid (trade_value_per_unit).
    double risk_per_contract = trade_value_per_unit; // Max loss if option expires worthless

    if (risk_per_contract <= 0) {
        std::cerr << "Warning: Risk per contract is zero or negative. Cannot calculate position size." << std::endl;
        return 0;
    }

    int position_size = static_cast<int>(max_dollar_risk / risk_per_contract);

    // Ensure position size is at least 1 if risk allows, otherwise 0.
    return std::max(0, position_size);
}

double RiskManagement::calculate_stop_loss_price(double entry_price, double stop_loss_percent, bool is_long_position) const {
    if (entry_price <= 0 || stop_loss_percent <= 0) {
        std::cerr << "Warning: Invalid input for stop-loss calculation. Entry price and percentage must be positive." << std::endl;
        return 0.0;
    }

    if (is_long_position) {
        // For long positions, stop loss is below entry
        return entry_price * (1.0 - stop_loss_percent);
    } else {
        // For short positions, stop loss is above entry
        return entry_price * (1.0 + stop_loss_percent);
    }
}

double RiskManagement::calculate_take_profit_price(double entry_price, double take_profit_percent, bool is_long_position) const {
    if (entry_price <= 0 || take_profit_percent <= 0) {
        std::cerr << "Warning: Invalid input for take-profit calculation. Entry price and percentage must be positive." << std::endl;
        return 0.0;
    }

    if (is_long_position) {
        // For long positions, take profit is above entry
        return entry_price * (1.0 + take_profit_percent);
    } else {
        // For short positions, take profit is below entry
        return entry_price * (1.0 - take_profit_percent);
    }
}
