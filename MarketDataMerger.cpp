#include "MarketDataMerger.h"
#include "MarketDataRecord.h"
#include "SafePriorityQueue.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <thread>



bool parseLine(const std::string& line, const std::string& symbol, MarketDataRecord& record) {
    
    size_t start = 0;
    size_t end = line.find(',');

   
    if (end == std::string::npos) return false;
    record.timestamp = line.substr(start, end - start);
    
    start = end + 1;
    end = line.find(',', start);
    if (end == std::string::npos) return false;
    std::string price = line.substr(start, end - start);

   
    start = end + 1;
    end = line.find(',', start);
    if (end == std::string::npos) return false;
    std::string size = line.substr(start, end - start);

    
    start = end + 1;
    end = line.find(',', start);
    if (end == std::string::npos) return false;
    std::string exchange = line.substr(start, end - start);

   
    start = end + 1;
    if (start >= line.size()) return false;
    std::string type = line.substr(start);

    
    record.symbol = symbol;
    record.data = price + "," + size + "," + exchange + "," + type;

    return true;
}


void mergeFilesChunk(const std::vector<std::string>& files, const std::string& output_file) {
    SafePriorityQueue pq;
    std::vector<std::ifstream> file_streams(files.size());

    for (size_t i = 0; i < files.size(); ++i) {
        file_streams[i].open(files[i]);
        if (file_streams[i]) {
            std::string line;
            if (std::getline(file_streams[i], line) && std::getline(file_streams[i], line)) {
                MarketDataRecord record;
                const std::string symbol = std::filesystem::path(files[i]).stem().string();
                if (parseLine(line, symbol, record)) {
                    pq.push(record);
                }
            }
        }
    }




    std::ofstream out(output_file);

    if (!out.is_open()) {
        throw std::runtime_error("Failed to open output file" + output_file);
    }

    out << "Symbol,Timestamp,Price,Size,Exchange,Type\n";
    while (!pq.empty()) {
        MarketDataRecord top;
        pq.pop(top);
        out << top.symbol << "," << top.timestamp << "," << top.data << "\n";

        for (size_t i = 0; i < files.size(); ++i) {
            if (!file_streams[i]) continue;

            std::string line;
            if (std::getline(file_streams[i], line)) {
                MarketDataRecord record;
                const std::string symbol = std::filesystem::path(files[i]).stem().string();
                if (parseLine(line, symbol, record)) {
                    pq.push(record);
                }
            }
        }
    }
}


void mergeAllFiles(const std::string& input_dir, const std::string& output_file, size_t num_threads) {
    
    std::vector<std::string> all_files;
    for (const auto& entry : std::filesystem::directory_iterator(input_dir)) {
        if (entry.is_regular_file()) {
            all_files.push_back(entry.path().string());
        }
    }

    std::vector<std::thread> threads;
    std::vector<std::string> intermediate_files;
    size_t chunk_size = (all_files.size() + num_threads - 1) / num_threads;

    for (size_t i = 0; i < num_threads; ++i) {
        size_t start = i * chunk_size;
        size_t end = std::min(start + chunk_size, all_files.size());

        std::vector<std::string> chunk(all_files.begin() + start, all_files.begin() + end);
        std::string intermediate_file = "intermediate_" + std::to_string(i) + ".txt";
        intermediate_files.push_back(intermediate_file);

        threads.emplace_back(mergeFilesChunk, chunk, intermediate_file);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    mergeFilesChunk(intermediate_files, output_file);
}
