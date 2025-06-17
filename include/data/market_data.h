#ifndef MARKET_DATA_H
#define MARKET_DATA_H

#include <compare>

class MarketData {
public:
    double spot_price{0.0};      // Current price of the underlying asset
    double risk_free_rate{0.0};  // Annualized risk-free interest rate (e.g., 0.05 for 5%)
    double dividend_yield{0.0};  // Annualized dividend yield (e.g., 0.02 for 2%)

    constexpr MarketData() = default;
    constexpr MarketData(double spot, double rate, double yield)
        : spot_price{spot}, risk_free_rate{rate}, dividend_yield{yield} {}

    auto operator<=>(const MarketData&) const = default;
};

#endif // MARKET_DATA_H
