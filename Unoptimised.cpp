#include <stdio.h>
#include <stdlib.h> 
#include <iostream>
#include <thread>



using namespace std;

void new_func1(void);

int resultOfSum(int a, int b)
{
	return a + b;
}

int func2(int a, int b)
{
	int res = 0;
		for (int i = 0; i < 10; i++)
		{
			this_thread::sleep_for(chrono::seconds(1));
			if (i > 8)
				res = resultOfSum(a, b);
			if (res > 0)
				return res;
		}
	return res;
}


int func1(int a, int b)
{
	int res = 0;
	for (int i = 0; i < 10; i++)
	{
		int res = func2(a, b);
		if (res > 0)
			return res;
	}

	return 0;
}
int main(void)
{
	auto start_time = std::chrono::high_resolution_clock::now();
	func1(5, 10);
	auto end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> duration = end - start_time;
	cout << "The program worked for: " << duration.count() << endl;
	return 0;
}
