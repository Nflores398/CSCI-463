//***************************************************************************
//
//  Noah Flores
//  z1861588
//  CSCI-463-1
//
//  I certify that this is my own work and where appropriate an extension
//  of the starter code provided for the assignment.
//
//***************************************************************************
#include <thread>
#include <vector>
#include <mutex>
#include "unistd.h"
#include <string>
#include <iostream>
#include <sstream>

constexpr int rows = 1000; /// < the number of rows in the work matrix
constexpr int cols = 100;  /// < the number of cols in the work matrix

std ::mutex stdout_lock; /// < for serializing access to stdout

std ::mutex counter_lock;	 /// < for dynamic balancing only
volatile int counter = rows; /// < for dynamic balancing only

std ::vector<int> tcount;	/// < count of rows summed for each thread
std ::vector<uint64_t> sum; /// < the calculated sum from each thread

int work[rows][cols]; /// < the matrix to be summed

/**
 * @brief Calculate the sum of matrix using static threading
 *
 * Loop through the matrix and get the sum
 *
 * @param tid id of the thread
 *
 * @param num_threads amount of threads that are suppose to be running
 *
 ********************************************************************************/
void sum_static(int tid, int num_threads)
{
	// lock and print which thread is starting
	stdout_lock.lock();
	std::cout << "Thread " << tid << " starting" << std::endl;
	stdout_lock.unlock();

	// loop through on each thread to cal sum
	for (int i = tid; i < rows; i += num_threads)
	{
		// increase tcount
		tcount[tid]++;
		for (int k = 0; k < cols; k++)
		{
			// add to sum of thread
			sum[tid] += work[i][k];
		}
	}

	// print out the amount work and sum that was calc per thread
	stdout_lock.lock();
	std::cout << "Thread " << tid << " ending tcount=" << tcount[tid] << " sum=" << sum[tid] << std::endl;
	stdout_lock.unlock();
}
/**
 * @brief Calculate the sum of matrix using dynamic threading
 *
 * Loop through the matrix and get the sum using dynamic threading
 *
 * @param tid id of the thread
 *
 *
 ********************************************************************************/
void sum_dynamic(int tid)
{
	int count_copy;	   // get a copy of counter
	bool done = false; // done flag
	// lock to print which thread is starting
	stdout_lock.lock();
	std::cout << "Thread " << tid << " starting" << std::endl;
	stdout_lock.unlock();

	// loop until count = 0
	while (!done)
	{
		// lock and decrease count
		counter_lock.lock();
		{
			if (counter > 0)
				counter--;
			else
				done = true;
			// copy count to copy
			count_copy = counter;
		}
		counter_lock.unlock();
		if (!done)
		{
			// loop through cols and and get sum of row and add to sum
			for (int k = 0; k < cols; k++)
			{
				sum[tid] += work[count_copy][k];
			}
			// increase tcount
			tcount[tid]++;
		}
	}
	// print out tcount and sum of each thread
	stdout_lock.lock();
	std::cout << "Thread " << tid << " ending tcount=" << tcount[tid] << " sum=" << sum[tid] << std::endl;
	stdout_lock.unlock();
}
/**
 * @brief Check op code calculated total sum of matrix based.
 *
 * The program will get the user to select static or dynamic and
 *  how many treads to us. Then print out sum and amout of work down
 *  by the threads
 *
 * @param argc	used to get option types
 *
 * @param argv  used to get option types
 *
 * @return 0
 ********************************************************************************/
int main(int argc, char **argv)
{
	bool d = false;	   // dynamic flag
	int totalwork = 0; // total work sum
	int opt;
	int core_amount = 2;  // defualt core amount is duo
	int64_t totalsum = 0; // total sum
	srand(0x1234);		  // set random seed to fill matrix
	// loop and fill matrix work
	for (auto &row : work)
	{
		for (auto &i : row)
		{
			i = rand();
		}
	}
	// get the actual core amount of pc
	int actual_core = std::thread::hardware_concurrency();
	// create vector of thread pointers
	std::vector<std::thread *> threads;
	// print out amount of threads supported
	std::cout << actual_core << " concurrent threads supported.\n";
	// get op code
	while ((opt = getopt(argc, argv, "t:d")) != -1)
	{
		switch (opt)
		{
		case 'd': // if dynamic
		{
			d = true;
		}
		break;
		case 't': // set max threads
		{
			std::istringstream iss(optarg);
			iss >> core_amount;
		}
		break;

		default: /* ’?’ */
			break;
		}
	}
	tcount.resize(core_amount, 0); // resize tcount
	sum.resize(core_amount, 0);	   // resize sum
	if (d == true)
	{
		// check if input amount of core is greater than system
		if (core_amount > actual_core)
		{
			// set max thread amount to core amount
			core_amount = actual_core;
		}
		// loop and fill vector and run dynamic
		for (int i = 0; i < core_amount; i++)
			threads.push_back(new std::thread(sum_dynamic, i));
	}
	else
	{
		// loop and fill vector and run static
		for (int i = 0; i < core_amount; i++)
			threads.push_back(new std::thread(sum_static, i, core_amount));
	}
	// cleaning up threads and calc total work and sum from all threads
	for (int i = 0; i < core_amount; i++)
	{
		threads.at(i)->join();
		delete threads.at(i);
		totalwork += tcount.at(i);
		totalsum += sum.at(i);
	}
	// print put gross sum of matrix
	std::cout << "main() exiting, total_work=" << totalwork << " gross_sum=" << totalsum << std::endl;
	// end
	return 0;
}
