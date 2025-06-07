#ifndef BLACK_SCHOLES_H
#define BLACK_SCHOLES_H

#include "data/market_data.h"
#include "data/option_data.h"

// Calculates the Black-Scholes option price
double black_scholes_price(double spot_price, double strike_price, double time_to_expiration,
                           double risk_free_rate, double dividend_yield, double volatility, char type);

// Calculates implied volatility using the bisection method
double implied_volatility_bisection(const OptionData& option, const MarketData& market,
                                    double tolerance = 1e-5, int max_iterations = 100);

#endif // BLACK_SCHOLES_H
