#include "measure.h"
#include <vector>
#include <iomanip>
#include <iostream>

static long long GetThreadCpuTimeNs()
{
    struct timespec t;

    if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t))
    {
        perror("clock_gettime");
        return 0;
    }

    return t.tv_sec * 1000000000LL + t.tv_nsec;
}

double MeasureCPUTime(const Matrix &m1, const Matrix &m2, MatMulFunc fn)
{
    long long beg = GetThreadCpuTimeNs();
    Matrix res = fn(m1, m2);
    long long end = GetThreadCpuTimeNs();

    return static_cast<double>(end - beg);
}

void PrintHead()
{
    std::cout << "╔════════╤═══════════════════════════════════════════════════════════════╗\n"
                 "║        │                         Время(нс)                             ║\n"
                 "║        ├───────────────┬───────────────────────────────┬───────────────╢\n"
                 "║ Размер │               │           Винограда           │               ║\n"
                 "║        │ Классический  ├───────────────┬───────────────┤   Штрассена   ║\n"
                 "║        │               │  Неоптимизир. │   Оптимизир.  │               ║\n"
                 "╟────────┼───────────────┼───────────────┼───────────────┼───────────────╢\n";
}
#include <fstream>
void TimeMeasure(int start, int maxLen, int iters, const std::string &csvFilename)
{
    srandom(time(NULL));

    const int step = 10;
    start = (start == 0) ? step : start;

    PrintHead();

    std::ofstream csvFile(csvFilename);
    if (!csvFile.is_open())
    {
        std::cerr << "Error opening CSV file: " << csvFilename << std::endl;
        return;
    }

    // CSV header
    csvFile << "Size,Classic,Winograd,WinogradOpt";
    if (start == 2)
    {
        csvFile << ",Strassen";
    }
    csvFile << std::endl;

    for (int i = start; i <= maxLen + start; )
    {
        std::vector<long long> times(4, 0);

        Matrix m1(i, i);
        Matrix m2(i, i);
        m1.fillRandom();
        m2.fillRandom();

        for (int j = 0; j < iters; ++j)
        {
            times[0] += MeasureCPUTime(m1, m2, Multiply::classicAlg);
            times[1] += MeasureCPUTime(m1, m2, Multiply::winograd);
            times[2] += MeasureCPUTime(m1, m2, Multiply::winogradOpt);

            if (start == 2)
                times[3] += MeasureCPUTime(m1, m2, Multiply::strassenAlg);
        }

        double times_0 = times[0] / static_cast<double>(iters);
        double times_1 = times[1] / static_cast<double>(iters);
        double times_2 = times[2] / static_cast<double>(iters);

        std::cout << "║ " << std::setw(6) << i << " │ "
                  << std::fixed << std::setprecision(2) << std::setw(13) << times_0 << " │ "
                  << std::fixed << std::setprecision(2) << std::setw(13) << times_1 << " │ "
                  << std::fixed << std::setprecision(2) << std::setw(13) << times_2 << " │ ";

        // CSV data
        csvFile << i << "," << times_0 << "," << times_1 << "," << times_2;
        if (start == 2)
        {
            double times_3 = times[3] / static_cast<double>(iters);
            std::cout << std::fixed << std::setprecision(2) << std::setw(13) << times_3 << " ║\n";
            csvFile << "," << times_3;
            i *= 2;
        }
        else
        {
            i += step;
            std::cout << std::setw(13) << '-' << " ║\n";
        }
        csvFile << std::endl;
    }

    std::cout << "CSV data has been saved to: " << csvFilename << std::endl;

    std::cout << "╚════════╧═══════════════╧═══════════════╧═══════════════╧═══════════════╝\n";
}
