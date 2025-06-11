#include "models/volatility_forecast.h"

#include <cmath>    // For std::log, std::sqrt
#include <numeric>  // For std::accumulate
#include <vector>   // For std::vector

double calculate_historical_volatility(const std::vector<double>& prices, int period) {
    if (prices.size() < 2) {
        return 0.0; // Not enough data to calculate volatility
    }

    std::vector<double> daily_returns;
    for (size_t i = 1; i < prices.size(); ++i) {
        if (prices[i-1] > 0) { // Avoid division by zero
            daily_returns.push_back(std::log(prices[i] / prices[i-1]));
        } else {
            // In a real application, you might log an error or handle this more robustly.
            // For simplicity, we skip this data point.
        }
    }

    if (daily_returns.empty()) {
        return 0.0;
    }

    // Calculate mean of daily returns
    double sum_returns = std::accumulate(daily_returns.begin(), daily_returns.end(), 0.0);
    double mean_return = sum_returns / daily_returns.size();

    // Calculate sum of squared differences from the mean
    double sum_sq_diff = 0.0;
    for (double r : daily_returns) {
        sum_sq_diff += (r - mean_return) * (r - mean_return);
    }

    // Calculate variance and standard deviation
    // Use (daily_returns.size() - 1) for sample variance if daily_returns.size() > 1
    double variance = (daily_returns.size() > 1) ? (sum_sq_diff / (daily_returns.size() - 1)) : 0.0;
    double daily_std_dev = std::sqrt(variance);

    // Annualize the volatility
    return daily_std_dev * std::sqrt(static_cast<double>(period));
}
