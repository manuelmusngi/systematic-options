#include "models/black_scholes.h"
#include "utils/math_utils.h" // For normal_cdf

#include <cmath>    // For std::log, std::sqrt, std::exp
#include <algorithm>// For std::max
#include <iostream> // For debugging (can be removed in production)

double black_scholes_price(double spot_price, double strike_price, double time_to_expiration,
                           double risk_free_rate, double dividend_yield, double volatility, char type) {
    if (time_to_expiration <= 0.0) { // Handle options at or past expiration
        if (type == 'C') {
            return std::max(0.0, spot_price - strike_price);
        } else { // Put
            return std::max(0.0, strike_price - spot_price);
        }
    }
    if (volatility <= 0.0) { // Handle zero or negative volatility
        // This is a degenerate case, options have no extrinsic value
        if (type == 'C') {
            return std::max(0.0, spot_price * std::exp(-dividend_yield * time_to_expiration) - strike_price * std::exp(-risk_free_rate * time_to_expiration));
        } else { // Put
            return std::max(0.0, strike_price * std::exp(-risk_free_rate * time_to_expiration) - spot_price * std::exp(-dividend_yield * time_to_expiration));
        }
    }

    double d1 = (std::log(spot_price / strike_price) + (risk_free_rate - dividend_yield + 0.5 * volatility * volatility) * time_to_expiration) /
                (volatility * std::sqrt(time_to_expiration));
    double d2 = d1 - volatility * std::sqrt(time_to_expiration);

    if (type == 'C') {
        return spot_price * std::exp(-dividend_yield * time_to_expiration) * normal_cdf(d1) -
               strike_price * std::exp(-risk_free_rate * time_to_expiration) * normal_cdf(d2);
    } else { // Put
        return strike_price * std::exp(-risk_free_rate * time_to_expiration) * normal_cdf(-d2) -
               spot_price * std::exp(-dividend_yield * time_to_expiration) * normal_cdf(-d1);
    }
}

double implied_volatility_bisection(const OptionData& option, const MarketData& market,
                                    double tolerance, int max_iterations) {
    double low_vol = 0.001; // Minimum possible volatility (e.g., 0.1%)
    double high_vol = 5.0;  // Maximum possible volatility (e.g., 500%)
    double mid_vol;
    double price_diff;

    // Check for invalid market price
    if (option.market_price <= 0) {
        // Option price cannot be zero or negative for IV calculation
        // In a real system, you might throw an exception or log an error.
        return 0.0; // Return a default or error value
    }

    for (int i = 0; i < max_iterations; ++i) {
        mid_vol = (low_vol + high_vol) / 2.0;
        // Ensure mid_vol is positive to avoid issues with black_scholes_price
        if (mid_vol <= 0) mid_vol = 0.0001; // Small positive value

        double calculated_price = black_scholes_price(market.spot_price, option.strike_price,
                                                      option.time_to_expiration, market.risk_free_rate,
                                                      market.dividend_yield, mid_vol, option.type);
        price_diff = calculated_price - option.market_price;

        if (std::abs(price_diff) < tolerance) {
            return mid_vol; // Found implied volatility within tolerance
        }

        if (price_diff > 0) {
            high_vol = mid_vol; // Calculated price is too high, so volatility is too high
        } else {
            low_vol = mid_vol;  // Calculated price is too low, so volatility is too low
        }
    }
    return mid_vol; // Return the best estimate after max_iterations
}
