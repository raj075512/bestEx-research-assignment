#pragma once

#include <string>


struct MarketDataRecord {
    std::string symbol;    
    std::string timestamp;  
    std::string data;       

  bool operator<(const MarketDataRecord& other) const {
    return std::tie(timestamp, symbol, data) < std::tie(other.timestamp, other.symbol, other.data);
  }


};


