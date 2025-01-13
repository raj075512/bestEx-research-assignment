#include "SafePriorityQueue.h"

void SafePriorityQueue::push(const MarketDataRecord& record) {
    std::lock_guard<std::mutex> lock(mtx);
    pq.push(record);
}

bool SafePriorityQueue::pop(MarketDataRecord& record) {
    std::lock_guard<std::mutex> lock(mtx);
    if (pq.empty()) return false;
    record = pq.top();
    pq.pop();
    return true;
}

bool SafePriorityQueue::empty() {
    std::lock_guard<std::mutex> lock(mtx);
    return pq.empty();
}
