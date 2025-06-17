#ifndef OPTION_DATA_H
#define OPTION_DATA_H

#include <compare>
#include <concepts>
#include <string_view>

// Option type as enum class for type safety
enum class OptionType : char { Call = 'C', Put = 'P' };

// Represents an option contract
struct OptionData {
    double strike_price{};        // Strike price of the option
    double time_to_expiration{};  // Time to expiration in years (e.g., 0.25 for 3 months)
    OptionType type{};            // Option type: Call or Put
    double market_price{};        // Current market price of the option

    // Defaulted three-way comparison and equality
    auto operator<=>(const OptionData&) const = default;
};

// Utility function for string representation (optional)
constexpr std::string_view to_string(OptionType type) {
    switch (type) {
        case OptionType::Call: return "Call";
        case OptionType::Put:  return "Put";
        default:               return "Unknown";
    }
}

#endif // OPTION_DATA_H
