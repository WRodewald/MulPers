#include <stdint.h>
#include <string>
#include <memory>
#include <iostream>

#include <thread>
#include <vector>
#include <algorithm>
#include <atomic>

// small class used to measure time etc

class TicToc
{
public:
	TicToc()
	{
		using namespace std::chrono;
		start = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	}

	void tic()
	{
		using namespace std::chrono;
		start = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	}

	uint64_t tocMS()
	{
		using namespace std::chrono;
		auto stop = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
		dt = stop - start;
		return dt.count();
	}

	std::chrono::milliseconds dt{ 0 };
	std::chrono::milliseconds start{ 0 };
};

