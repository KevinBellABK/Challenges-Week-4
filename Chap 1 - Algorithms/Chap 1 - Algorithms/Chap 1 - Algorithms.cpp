#include <iostream>
#include <chrono>

const int n = 100;

void sortArray(int (&arr)[n])
{
    int minIdx = 0;
    for (int i = 0; i < n - 1; i++)
    {
        minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[minIdx] > arr[j])
                minIdx = j;

        int tmp = arr[i];
        arr[i] = arr[minIdx];
        arr[minIdx] =  tmp;
    }
}

void fillArray(int (& arr)[n])
{
    srand(time(0));
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand();
    }
}

uint32_t getNanos()
{
    using namespace std::chrono;
    return static_cast<uint32_t>(duration_cast<nanoseconds> (system_clock::now().time_since_epoch()).count());
}

void findBestPath()
{
    
}

int main()
{
    int numArr[n];
    fillArray(numArr);
    uint32_t startTimer = getNanos();
    sortArray(numArr);
    uint32_t endTimer = getNanos();

    std::cout << "SelectionSort took: " << endTimer - startTimer << std::endl;
}

