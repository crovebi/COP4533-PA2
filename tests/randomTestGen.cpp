#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <random>
#include <chrono>

int main(int argc, char *argv[]){
     if(argc < 5) {
        std::cout << "Usage: " << argv[0] << " <cache capacity>" << " <number of requests>"
        << " <min request value>" << " <max request value>" << std::endl;
        return 1;
    }
    
    int cache_capacity = atoi(argv[1]);
    int num_requests = atoi(argv[2]);
    std::ofstream outfile("data/example.in");
    if(outfile.is_open()) {
        outfile << cache_capacity << " " << num_requests << std::endl;

         unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 gen(seed);
        int min_val = atoi(argv[3]);
        int max_val = atoi(argv[4]);
        std::uniform_int_distribution<> rand(min_val, max_val);
        for(int i = 0; i < num_requests; i++) {
                outfile << rand(gen) << ((i < num_requests - 1) ? " " : "");
        }
    }
}