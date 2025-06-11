#ifndef VOLATILITY_FORECAST_H
#define VOLATILITY_FORECAST_H

#include <vector> // For std::vector

// Calculates historical volatility from a series of historical prices.
// Assumes prices are daily closing prices.
// prices: a vector of historical prices
// period: the number of trading days in a year (e.g., 252 for daily data)
double calculate_historical_volatility(const std::vector<double>& prices, int period = 252);

#endif // VOLATILITY_FORECAST_H
