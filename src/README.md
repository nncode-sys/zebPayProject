# README

## Prerequisite
 -**libcurl** *can be instlaled using* `sudo apt-get install libcurl4-openssl-dev`

## steps
 - Run `run.sh` or type `g++ main.cpp -o main -lcurl` to compile the code
 - `./main` runs the program for 10 Qty by default. To change qty you can use `--qty` 

 ## Note
  - This exe exits execution after returning the asked value. i.e it runs only once so the following things are written based on this.
    - Aggregated orderbook only needs to read and sort the number of levels from each exchange such that both sides have atleast targetQty. Processing any more levels is unnecessary. But in case of recurring calls we'll have to have the complete orderbook.
    - RateLimiter never stops the request because we are not going to request more than once. In an actual scenario where httpGet can be called more than once the RateLimiter comes into action.
  - A pre compiled exe is included in the zip. This exe should work most unix systems running x86 arch