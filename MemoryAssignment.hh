#include <iostream>
#include <ctime>
#include <algorithm>
#include <time.h>
#include <chrono>
#include <random>
#include <vector>

using namespace std;


vector<uint16_t>* genBuffer();

double timeAccess(vector<uint16_t>* buff, uint64_t buffSize);