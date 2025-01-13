#pragma once

#include <string>
#include <vector>
#include "MarketDataRecord.h"


bool parseLine(const std::string& line, const std::string& symbol, MarketDataRecord& record);

void mergeFilesChunk(const std::vector<std::string>& files, const std::string& output_file);

void mergeAllFiles(const std::string& input_dir, const std::string& output_file, size_t num_threads);


