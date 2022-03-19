#include <iostream>
#include <ctime>
#include <algorithm>
#include <time.h>
#include <chrono>
#include <random>
#include <vector>

using namespace std;

vector<uint16_t>* genBuffer();                                  // function to generate randomised vector of size 256

double timeAccess(vector<uint16_t>* buff, uint64_t buffSize);   // function to read array and time how long reads take given buffer size