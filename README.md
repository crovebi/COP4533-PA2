# COP4533-PA2
Programming Assignment 2: Greedy Algorithms by Sebastian Crovetto (51487318) & Mosimiloluwa Ajani (79157785)

## Instructions for Completion
In the COP4533-PA2 folder, run the commands:
g++ src/cache.cpp -o cache and g++ tests/randomTestGen.cpp -o randomTestGen
which build the executables for cache and generating random request sequences for testing,respectively.

## Running the Programs
Run the cache simulator with: ./cache

The generator can be executed with: ./randomTestGen <cache_capacity> <number_of_requests> <min_request_value> <max_request_value>

It takes in a command line input for cache capacity, number of requests, and sequence of integer IDs and inputs them in: data/example.in

The results are then outputted to: data/example.out

## IO Information
All input and output files are stored in the data folder. example.in stores the input request sequence for the cache simulator.

The input format is:
k m
r1 r2 r3 ... rm
where:
k is the cache capacity
m is the number of requests
r1 ... rm are the request IDs

Running ./cache produces example.out, which contains the number of cache misses for each eviction policy. The output file is overwritten each time the program is executed.

# Question 1: Empirical Comparison
We tested the algorithms using three input files with at least 50 requests.

Input File | k | m | FIFO | LRU | OPTFF
-----------|---|---|------|-----|------
File1      | 3 |60 |  46  |  44 |  39
File2      | 4 |70 |  45  |  45 |  35
File3      | 5 |80 |  51  |  53 |  38

Comments:
- OPTFF consistently produced the fewest cache misses, as it uses full knowledge of the request sequence to evict the item whose next use is farthest in the future.
- LRU generally performs better than FIFO. FIFO usually performs worse because it evicts the oldest item regardless of whether it's going to be used again.

# Question 2: Bad Sequence for LRU or FIFO
For a cache capacity (k=3), the following request sequence demonstrates that OPTFF can incur strictly fewer misses than FIFO and LRU.

Sequence: 1 2 3 4 1 2 5 1 2 3 4 5
Policy | Misses
-------|-------
FIFO   | 9
LRU    | 10
OPTFF  | 8

Reasoning: FIFO evicts the item that has been in the cache the longest. As a result, it may remove items that will soon be requested again, leading to additional cache misses. LRU performs slightly better by keeping recently used items, but it can still evict items that will be needed again in the future. OPTFF still outperforms both by evicting the item whose next request is farthest in the future, minimzing the number of cache misses and having fewer misses than both FIFO and LRU.

# Question 3: Prove OPTFF is Optimal
First, we can consider the first request where A and OPTFF would evict different items. OPTFF evicts the item whose next use is farthest in the future, while A evicts some other item. If A evicted an item that is needed sooner than OPTFF's choice, then A will have a cache miss before OPTFF does. On the other hand, if A evicted an item that is needed later than OPTFF's choice, then exchanging the choice with OPTFF will not increase cache misses. Doing this multiple times can then create a new algorithm that can do as well as A, but behave exactly like OPTFF without increasing its total number of cache misses, making it optimal.