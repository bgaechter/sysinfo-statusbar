#include <sys/types.h>
#include <sys/sysinfo.h>
#include <iostream>

float get_memory_usage(long long total_mem, long long used_mem)
{
	if(used_mem == 0)
	{
		return 0;
	}
 	return  (100*used_mem)/total_mem;
}

float get_swap_usage(long long total_swap, long long used_swap)
{
	if(used_swap == 0)
	{
		return 0;
	}

	return (100*total_swap)/used_swap;
}

int main()
{
	struct sysinfo mem_info;

	sysinfo(&mem_info);
	long long total_mem = mem_info.totalram;
	long long total_swap = mem_info.totalswap;

	long long used_mem = mem_info.totalram - mem_info.freeram;
	long long used_swap = mem_info.totalswap - mem_info.freeswap;


	float memory_usage = get_memory_usage(total_mem, used_mem);
	float swap_usage = get_swap_usage(total_swap, used_swap);

	std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
	std::cout.precision(2);

	std::cout << "Mem: " << memory_usage << "%" << std::endl;
	std::cout << "Swap: " << swap_usage << "%" << std::endl;

}
