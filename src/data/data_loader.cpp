#include "data/data_loader.h"
#include <fstream>      // For file input/output
#include <sstream>      // For string stream operations
#include <iostream>     // For error messages
#include <limits>       // For numeric_limits (used in error handling)

namespace data_loader {

    std::optional<MarketData> load_market_data_from_csv(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open market data file: " << filepath << std::endl;
            return std::nullopt;
        }

        std::string line;
        // Read header line
        std::getline(file, line);
        if (file.eof() && line.empty()) { // Check for empty file after header read attempt
            std::cerr << "Warning: Market data file is empty: " << filepath << std::endl;
            return std::nullopt;
        }

        // Read data line
        if (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string segment;
            MarketData data;

            try {
                // spot_price
                if (std::getline(ss, segment, ',')) {
                    data.spot_price = std::stod(segment);
                } else return std::nullopt;

                // risk_free_rate
                if (std::getline(ss, segment, ',')) {
                    data.risk_free_rate = std::stod(segment);
                } else return std::nullopt;

                // dividend_yield
                if (std::getline(ss, segment, ',')) {
                    data.dividend_yield = std::stod(segment);
                } else return std::nullopt;

                return data;
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error parsing market data (invalid argument): " << e.what() << " on line: " << line << std::endl;
            } catch (const std::out_of_range& e) {
                std::cerr << "Error parsing market data (out of range): " << e.what() << " on line: " << line << std::endl;
            }
        } else {
            std::cerr << "Error: No data found in market data file after header: " << filepath << std::endl;
        }

        return std::nullopt;
    }

    std::vector<double> load_historical_prices_from_csv(const std::string& filepath) {
        std::vector<double> prices;
        std::ifstream file(filepath);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open historical prices file: " << filepath << std::endl;
            return prices; // Return empty vector
        }

        std::string line;
        // Read header line (e.g., "price")
        std::getline(file, line);
        if (file.eof() && line.empty()) {
            std::cerr << "Warning: Historical prices file is empty after header: " << filepath << std::endl;
            return prices;
        }

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string segment;
            if (std::getline(ss, segment)) { // Only one column expected
                try {
                    prices.push_back(std::stod(segment));
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Warning: Skipping invalid price value '" << segment << "' in " << filepath << ": " << e.what() << std::endl;
                } catch (const std::out_of_range& e) {
                    std::cerr << "Warning: Skipping out-of-range price value '" << segment << "' in " << filepath << ": " << e.what() << std::endl;
                }
            }
        }
        return prices;
    }

    std::vector<OptionData> load_option_data_from_csv(const std::string& filepath) {
        std::vector<OptionData> options;
        std::ifstream file(filepath);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open option data file: " << filepath << std::endl;
            return options; // Return empty vector
        }

        std::string line;
        // Read header line
        std::getline(file, line);
        if (file.eof() && line.empty()) {
            std::cerr << "Warning: Option data file is empty after header: " << filepath << std::endl;
            return options;
        }

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string segment;
            OptionData data;
            bool valid_line = true;

            try {
                // strike_price
                if (std::getline(ss, segment, ',')) {
                    data.strike_price = std::stod(segment);
                } else { valid_line = false; }

                // time_to_expiration
                if (valid_line && std::getline(ss, segment, ',')) {
                    data.time_to_expiration = std::stod(segment);
                } else { valid_line = false; }

                // type
                if (valid_line && std::getline(ss, segment, ',')) {
                    if (segment.length() == 1 && (segment[0] == 'C' || segment[0] == 'P')) {
                        data.type = segment[0];
                    } else {
                        valid_line = false;
                        std::cerr << "Warning: Invalid option type '" << segment << "' in " << filepath << std::endl;
                    }
                } else { valid_line = false; }

                // market_price
                if (valid_line && std::getline(ss, segment)) { // Read till end of line for last segment
                    data.market_price = std::stod(segment);
                } else { valid_line = false; }

                if (valid_line) {
                    options.push_back(data);
                } else {
                    std::cerr << "Warning: Skipping malformed option data line: " << line << std::endl;
                }
            } catch (const std::invalid_argument& e) {
                std::cerr << "Warning: Skipping option data line (invalid argument): '" << line << "': " << e.what() << std::endl;
            } catch (const std::out_of_range& e) {
                std::cerr << "Warning: Skipping option data line (out of range): '" << line << "': " << e.what() << std::endl;
            }
        }
        return options;
    }

} // namespace data_loader
