#include "MemoryAssignment.hh"

vector<uint16_t>* genBuffer() {
    srand(time(NULL));
    vector<uint16_t>* buffer = new vector<uint16_t>(256);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, 255);
    for (uint16_t i = 0; i < 256; i++) {
        (*buffer)[i] = distr(gen);
    }
    shuffle(buffer->begin(), buffer->end(), gen);
    return buffer;
}

double timeAccess(vector<uint16_t>* buff, uint64_t buffSize) {
    struct timespec start, stop;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(0, 255);
    auto index = distr(gen);
    auto nextIndex = (*buff)[index];
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (uint64_t i = 0; i <= buffSize; i++) {
        cout << nextIndex << endl;
        nextIndex = (*buff)[nextIndex];
    }    
    clock_gettime(CLOCK_MONOTONIC, &stop);
    double time_taken = (1E9 * (stop.tv_sec - start.tv_sec)) + (double)(stop.tv_nsec - start.tv_nsec);
    double avgTime = time_taken/buffSize;
    return avgTime;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Please enter only one numerical argument." << endl;
        return -1;
    }
    uint64_t buffSize = atoi(argv[1]);
    auto randBuff = genBuffer();
    auto timeTaken = timeAccess(randBuff, buffSize);
    cout << "Average time per buffer read = " << timeTaken << " ns" << endl;
    return 0;
}