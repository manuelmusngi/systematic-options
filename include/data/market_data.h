#ifndef MARKET_DATA_H
#define MARKET_DATA_H

// Represents market data for an underlying asset
struct MarketData {
    double spot_price;      // Current price of the underlying asset
    double risk_free_rate;  // Annualized risk-free interest rate (e.g., 0.05 for 5%)
    double dividend_yield;  // Annualized dividend yield (e.g., 0.02 for 2%)
};

#endif // MARKET_DATA_H
