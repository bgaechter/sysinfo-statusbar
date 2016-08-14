#include <sys/types.h>
#include <sys/sysinfo.h>
#include <iostream>
#include <string>

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

std::string get_bar_chart(float usage)
{
	std::string chart{"["};
	int bars = usage*20/100;
	for(int i=0; i<22;i++)
	{
		if(i<bars)
		{
			chart += "|";
		}
		else
		{
			chart += " ";
		}

	}
	chart += "]";
	return chart;
}


int main()
{
	struct sysinfo info;

	sysinfo(&info);
	long long total_mem = info.totalram;
	long long total_swap = info.totalswap;

	long long used_mem = info.totalram - info.freeram;
	long long used_swap = info.totalswap - info.freeswap;


	float memory_usage = get_memory_usage(total_mem, used_mem);
	float swap_usage = get_swap_usage(total_swap, used_swap);

	std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
	std::cout.precision(2);

	std::cout << "Mem: " << memory_usage << "% ";
	std::cout << "Swap: " << swap_usage << "% ";
	// the divison by 65536.0 is kind of a cheat
	// beacause loads returns the averaged active tasks
	// see getloadavg.c, uptime.c for details
	std::cout << info.loads[0]/65536.0 << " ";
	std::cout << info.loads[1]/65536.0 << " ";
	std::cout << info.loads[2]/65536.0 << " " << std::endl;
	

}
