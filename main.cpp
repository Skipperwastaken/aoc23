#include <chrono>
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

/*#include "solution1_1.h"
#include "solution1_2.h"
#include "solution2_1.h"
#include "solution2_2.h"
#include "solution3_1.h"
#include "solution3_2.h"
#include "solution4_1.h"
#include "solution4_2.h"
#include "solution5_1.h"
#include "solution5_2.h"
#include "solution6_1.h"
#include "solution6_2.h"
#include "solution7_1.h"
#include "solution7_2.h"
#include "solution8_1.h"*/
#include "solution8_2.h"

int main() {
    auto t1 = high_resolution_clock::now();
    solution();
    auto t2 = high_resolution_clock::now();

    duration<double, std::milli> ms_double = t2 - t1;
    std::cout << "Execution time: " << ms_double.count() << "ms\n";
    return 0;
}