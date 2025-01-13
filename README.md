
# Market Data Merger

### Overview
The **Market Data Merger** program merges multiple CSV files containing market data into a single consolidated file. It processes the files in parallel using multithreading and ensures the data is sorted based on timestamp and symbol.

---

### Features
- **Parallel Processing**: Efficiently merges files using multiple threads.
- **Cross-Platform Compatibility**: Works on both Linux and Windows.
- **Safe Priority Queue**: Thread-safe queue ensures correct order during merging.
- **Error Handling**: Handles filesystem and runtime errors gracefully.

---

### Functionality

1. **File Parsing**:
   - Reads individual market data files.
   - Extracts and parses records into a structured format.

2. **Thread-Safe Priority Queue**:
   - Utilizes a custom `SafePriorityQueue` to manage sorting across threads.

3. **Data Consolidation**:
   - Combines sorted data chunks into intermediate files.
   - Merges intermediate files into the final output file.

4. **Sorting**:
   - Ensures data is sorted by timestamp, symbol, and other fields.

5. **Scalable Multithreading**:
   - Dynamically adjusts the number of threads based on system hardware.

6. **Robust Error Handling**:
   - Catches filesystem errors (e.g., missing directories).
   - Handles malformed CSV data gracefully.

---

### Optimizations

1. **Multithreading**:
   - Divides input files into chunks and processes them in parallel.
   - Automatically determines the number of threads based on hardware capabilities.

2. **Batch File Processing**:
   - Processes smaller batches of files to reduce memory overhead.

3. **Minimized Disk I/O**:
   - Uses intermediate in-memory structures to minimize writes to disk.

4. **Efficient Parsing**:
   - Optimized CSV parsing using lightweight string operations.

5. **Priority Queue**:
   - Custom thread-safe priority queue ensures proper sorting with minimal locking overhead.

6. **Dynamic Resource Allocation**:
   - Balances workload distribution across threads for optimal CPU utilization.

---

### Flow of Execution

1. **Input Validation**:
   - The program verifies that the input directory exists and contains files.
   - Ensures the output file can be created.

2. **File Chunking**:
   - The input directory is scanned for all valid CSV files.
   - Files are divided into smaller chunks, each assigned to a thread.

3. **Parallel Processing**:
   - Each thread processes its chunk:
     - Reads CSV files line by line.
     - Parses and validates each record.
     - Pushes parsed records into the thread-safe priority queue.

4. **Intermediate File Creation**:
   - Each thread writes its sorted chunk to an intermediate file.

5. **Intermediate File Merging**:
   - All intermediate files are read and merged using the priority queue.
   - The final merged data is written to the output file.

6. **Final Output**:
   - The program creates a consolidated CSV file sorted by timestamp and symbol.

---

### Project Structure

```
.
├── main.cpp                # Entry point for the program
├── marketdatamerger.cpp    # Handles file merging logic
├── safepriorityqueue.cpp   # Thread-safe priority queue implementation
├── marketdatamerger.h      # Header file for MarketDataMerger
├── marketdatarecord.h      # Data structure for market records
├── safepriorityqueue.h     # Header file for SafePriorityQueue
├── Makefile                # Makefile for building the project
├── README.md               # Documentation
└── bin/                    # Directory for the compiled executable
```

---

### Build Instructions

#### Linux
1. **Clone the Repository**:
   ```bash
   git clone https://github.com/<your-username>/market-data-merger.git
   cd market-data-merger
   ```

2. **Build the Project**:
   ```bash
   make
   ```

3. **Run the Program**:
   ```bash
   ./bin/market_data_merger <input_directory> <output_file>
   ```
   - Replace `<input_directory>` with the path to the directory containing input files.
   - Replace `<output_file>` with the desired output file path.

4. **Clean Up**:
   ```bash
   make clean
   ```

---

#### Windows (Using MinGW)
1. **Clone the Repository**:
   ```cmd
   git clone https://github.com/<your-username>/market-data-merger.git
   cd market-data-merger
   ```

2. **Build the Project**:
   ```cmd
   make
   ```

3. **Run the Program**:
   ```cmd
   bin\market_data_merger.exe <input_directory> <output_file>
   ```
   - Replace `<input_directory>` with the path to the directory containing input files.
   - Replace `<output_file>` with the desired output file path.

4. **Clean Up**:
   ```cmd
   make clean
   ```

---

### Example Usage

#### Input Directory
```
input_data/
├── AAPL.txt
├── MSFT.txt
└── TSLA.txt
```

Each txt file has the following structure:
```
Timestamp,Price,Size,Exchange,Type
2025-01-01T10:00:00,150.00,100,NASDAQ,BID
2025-01-01T10:01:00,151.00,200,NASDAQ,ASK
```

#### Command
```bash
./bin/market_data_merger input_data output.txt
```

#### Output File (`output.txt`)
```
Symbol,Timestamp,Price,Size,Exchange,Type
AAPL,2025-01-01T10:00:00,150.00,100,NASDAQ,BID
MSFT,2025-01-01T10:01:00,151.00,200,NASDAQ,ASK
```

---

### Troubleshooting

#### Common Errors
1. **Command not found (`make` or `g++`)**:
   - Install the required tools:
     - Linux: `sudo apt install build-essential`
     - Windows: Install MinGW and add it to the `PATH`.

2. **Filesystem errors**:
   - Ensure the input directory exists and contains valid CSV files.

3. **Runtime errors**:
   - Check if you have write permissions for the output file path.

---

### Contributing
Feel free to open issues or submit pull requests to improve this project.

---

### License
This project is licensed under the [MIT License](LICENSE).
