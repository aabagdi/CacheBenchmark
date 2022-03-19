#include "MemoryAssignment.hh"

vector<uint16_t>* genBuffer() {
    vector<uint16_t>* buffer = new vector<uint16_t>(256);                       // initialise vector pointer with size 256
    random_device rd;                                                           // initialise random device
    mt19937 gen(rd());                                                          // make a generator using that random device
    uniform_int_distribution<> distr(0, 255);                                   // make distribution between 0 and 255 (indices of vector)
    for (uint16_t i = 0; i < 256; i++) {
        (*buffer)[i] = distr(gen);                                              // pick random number from distribution and store into array
    }
    shuffle(buffer->begin(), buffer->end(), gen);                               // shuffle array to mess with the pre-fetcher
    return buffer;
}

double timeAccess(vector<uint16_t>* buff, uint64_t buffSize) {
    struct timespec start, stop;                                                // initialise clocks
    random_device rd;                                                           // initialise random device
    mt19937 gen(rd());                                                          // make a generator using that random device
    uniform_int_distribution<> distr(0, 255);                                   // make distribution between 0 and 255 (indices of vector)
    auto index = distr(gen);                                                    // pick random number from distribution and use that as vector index
    auto nextIndex = (*buff)[index];                                            // fetch element from array using that index
    clock_gettime(CLOCK_MONOTONIC, &start);                                     // begin timing
    for (uint64_t i = 0; i <= buffSize; i++) {                                  // iterate loop for buffer size
        cout << nextIndex << endl;                                              // output fetched element
        nextIndex = (*buff)[nextIndex];                                         // use that fetched element as next index
    }    
    clock_gettime(CLOCK_MONOTONIC, &stop);                                      // end timing
    double time_taken = ((double)stop.tv_sec + 1.0e-9*stop.tv_nsec)
     - ((double)start.tv_sec + 1.0e-9*start.tv_nsec);                           // calculate time in seconds
    double avgTime = ((time_taken/(buffSize)) * 1e9) / 2;                       // convert to ns, divided by 2 as there are two reads in the loop
    return avgTime;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Please enter only one numerical argument." << endl;
        return -1;
    }
    uint64_t buffSize = atoi(argv[1]);                                          // take in buffer size as command-line argument
    auto randBuff = genBuffer();                                                // generate random array
    auto timeTaken = timeAccess(randBuff, buffSize);                            // read array and time
    cout << "Average time per buffer read = " << timeTaken << " ns" << endl;    // print average time per read
    return 0;
}