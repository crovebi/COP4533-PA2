#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <queue>


int find(std::vector<std::string> requestSet, std::string str){
    for(int i = 0; i < requestSet.size(); i++){
        if(requestSet[i] == str) return i;
    }
    return -1;
}
int fifo(int cache_capacity, int num_requests, std::vector<std::string> requestSet){
    std::vector<std::string> cache;
    int num_misses = 0;
    for(int i = 0; i < num_requests; i++){
        int pos = find(cache, requestSet[i]);
        if(cache.size() < cache_capacity){
            if(pos == -1){ // cache miss
                cache.push_back(requestSet[i]);
                num_misses++;
            }
        }
        else{
            if(pos == -1){ // cache miss
            cache.erase(cache.begin());
            cache.push_back(requestSet[i]);
            num_misses++;
            }
        }
    }
    return num_misses;
}
int lru(int cache_capacity, int num_requests, std::vector<std::string> requestSet){
    std::vector<std::string> cache;
    int num_misses = 0;
    for(int i = 0; i < num_requests; i++){
        int pos = find(cache, requestSet[i]);
        if(cache.size() < cache_capacity){
            if(pos == -1){ // cache miss
                cache.insert(cache.begin(), requestSet[i]);
                num_misses++;
            }
            else{
                cache.erase(cache.begin() + pos);
                cache.insert(cache.begin(), requestSet[i]);
            }
        }
        else{
            if(pos == -1){ // cache miss
            cache.pop_back();
            cache.insert(cache.begin(), requestSet[i]);
            num_misses++;
            }
            else{
                cache.erase(cache.begin() + pos);
                cache.insert(cache.begin(), requestSet[i]);
            }
        }
    }
    return num_misses;
}
int opt(int cache_capacity, int num_requests, std::vector<std::string> requestSet){
        std::vector<std::string> cache;
    int num_misses = 0;
    for(int i = 0; i < num_requests; i++){
        int pos = find(cache, requestSet[i]);
        if(cache.size() < cache_capacity){
            if(pos == -1){ // cache miss
                cache.push_back(requestSet[i]);
                num_misses++;
            }
        }
        else{
            if(pos == -1){ // cache miss
                std::vector<int> furthest_future;
                for(int j = 0; j < cache.size(); j++){
                    bool found = false;
                    for(int k = i+1; k < requestSet.size(); k++){
                        if(cache[j] == requestSet[k]){
                            furthest_future.push_back(k-i);
                            found = true;
                            break;
                        }
                    }
                    if(!found){
                        furthest_future.push_back(2147483647);
                    }
                }
                int to_erase = 0;
                for(int j = 1; j < furthest_future.size()-1; j++){
                    if(furthest_future[j] > furthest_future[to_erase])to_erase = j;
                }
            cache.erase(cache.begin() + to_erase);
            cache.push_back(requestSet[i]);
            num_misses++;
            }
        }
    }
    return num_misses;
}
std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}
int main(){
    std::string filePath = "data/example.in";
    std::ifstream infile(filePath);
    if(!infile) {
        std::cerr << "Error: Cannot open file: " << filePath << std::endl;
        return 1;
    }
    
    std::string line;
    std::getline(infile, line);
    std::vector<std::string> splitLine = split(line, ' ');
    int cache_size = std::stoi(splitLine[0]);
    int num_requests = std::stoi(splitLine[1]);
    std::getline(infile, line);
    std::vector<std::string> requestSet = split(line, ' ');
    infile.close();
    
    int fifo_miss = fifo(cache_size, num_requests, requestSet);
    int lru_miss = lru(cache_size, num_requests, requestSet);
    int opt_miss = opt(cache_size, num_requests, requestSet);
    std::ofstream outfile("data/example.out");
    if(outfile.is_open()) {
        outfile << "FIFO  : " << " " << fifo_miss << std::endl;
        outfile << "LRU   : " << " " << lru_miss << std::endl;
        outfile << "OPTFF : " << " " << opt_miss << std::endl;
    }
}