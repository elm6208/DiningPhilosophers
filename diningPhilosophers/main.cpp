#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

//each philosopher is a thread
thread philosophers[5];

//bools for whether or not the chopstick is available
bool chopsticks[] = { true, true, true, true, true };

mutex m;


void philosopher(int id, int left) {

	while (true)
	{
		//lock mutex
		unique_lock<mutex> lock(m);

		//if the current chopstick and the one to the left is open
		if (chopsticks[id] == true && chopsticks[left] == true)
		{
			cout << id << " is eating" << endl;

			//make chopsticks unavailable to other people
			chopsticks[id] = false;
			chopsticks[left] = false;

			//unlock
			lock.unlock();

			// wait while they're eating
			this_thread::sleep_for(1000ms);

			// lock mutex
			unique_lock<mutex> lock(m);

			cout << id << " is done eating" << endl;

			// make chopsticks available again
			chopsticks[id] = true;
			chopsticks[left] = true;

			//unlock mutex
			lock.unlock();

			// sleep while waiting
			this_thread::sleep_for(1000ms);
		}
	}


}



int main() {
	
	thread t0(philosopher, 0, 4);
	thread t1(philosopher, 1, 0);
	thread t2(philosopher, 2, 1);
	thread t3(philosopher, 3, 2);
	thread t4(philosopher, 4, 3);

	t0.join();
	t1.join();
	t2.join();
	t3.join();
	t4.join();

	return 0;
}