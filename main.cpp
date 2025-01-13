#include "MarketDataMerger.h"      
#include <iostream>                  
#include <stdexcept>                
#include <thread>                  
#include <filesystem>                
#include <string>                    

namespace fs = std::filesystem;      


int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Error: Missing input directory or output file arguments.\n";
        return 1;
    }

    std::string input_dir = argv[1];
    std::string output_file = argv[2];

    size_t num_threads = std::thread::hardware_concurrency();
   
    //  we can use the try catch exception for thread also //

    try {
        mergeAllFiles(input_dir, output_file, num_threads);
        std::cout << "Merged output file created successfully: " << output_file << std::endl;
    } 
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error during file merging: " << e.what() << std::endl;
        return 1;
    } 
    catch (const std::exception& e) {
        std::cerr << "Error during file merging: " << e.what() << std::endl;
        return 1;
    } 
    catch (...) {
        std::cerr << "An unknown error \n";
        return 1;
    }

    return 0;
}
