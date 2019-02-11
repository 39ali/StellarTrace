#pragma once
#include <thread>
#include <iostream>
namespace StellarTrace
{

#define TIME_IT(x) \
    auto begin = std::chrono::steady_clock::now();\
x; \
	auto end = std::chrono::steady_clock::now(); \
	std::cout << "Time difference in ms = "<< std::chrono::duration_cast<std::chrono::milliseconds>(end -begin).count()<< std::endl; \
	std::cout<< "Time difference in seconds = "<< std::chrono::duration_cast<std::chrono::seconds>(end - begin).count()<< std::endl;
	

}
