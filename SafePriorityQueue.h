#pragma once

#include "MarketDataRecord.h"
#include <queue>
#include <mutex>


class SafePriorityQueue {
public:
    void push(const MarketDataRecord& record);
    bool pop(MarketDataRecord& record);
    bool empty();

private:
    std::priority_queue<MarketDataRecord> pq;  
    std::mutex mtx;                            
};


