# Profiling


## Task

**Tasks for work:**
1) Analyze the program, measure its execution time, see where there is room for improvement.
2) Based on the mechanisms described in the theory of memory organization to make the necessary changes in the code structure.
3) Measure the new execution time, in the presence of obvious improvements, go to paragraph 4, if not - to paragraph 1
4) Record new indicators and explain why the acceleration was achieved.


Code

```

#include<stdio.h>

void new_func1(void);

int func1(int a, int b)
{
	int res = 0;
    for(int i = 0; i < 10; i++)
	{
		int res = func2(a, b);
		if(res > 0)
			return res;
	}

    return;
}

int func2(int a, int b)
{
	int res = 0
    for(int i = 0; i < 10; i++)
	{
		sleep(1);
		if(i>8)
			res = resultOfSum(a, b);
		if(res > 0)
			return res;
	}
    return res;
}
int resultOfSum(int a, int b)
{
	return a+b;
}

int main(void)
{
    func1(5, 10);

    return 0;
}
```

## Rewrite

Original code was writed on C.
So I rewrite this code to C++ and I have:
```
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

```

## Unoptimazet program

After few tries I see that time isn't constant but keep around this result:

![example 1](/images/1.png)

As you can see code and program is very small, loop too, so it took not many time.

## Optimization

I optimazed this code and as I say higher, code and actions in it too small, so changes not many:

- Optimize loop with using `register int i = 0` as it should suggest the compiler to store this value in the registers.
- Delete unused variable `int res = 0;` what help minimize memory costs and some time.

And I have next result:

![example 2](/images/2.png)

- last optimization I made it's swap `this_thread::sleep_for(chrono::seconds(1));` and `if (i > 8) res = resultOfSum(a, b); if (res > 0) return res;`.
## Optimized code

```
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
		for (register int i = 0; i < 10; i++)
		{
			if (i > 8)
				res = resultOfSum(a, b);
			if (res > 0)
				return res;
			this_thread::sleep_for(chrono::seconds(1));

		}
	return res;
}


int func1(int a, int b)
{
	for ( int i = 0; i < 10; i++)
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

```
### Output of optimazed program

![example 3](/images/3.png)

As you can see it minimazed time but a little bit, because program also small.