#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <infra/Queue.h>

Queue<int> queue;

void *feeder(void *id) {
	const int all = 2000;
	const int step = 5;

	int array[all];
	for (int i=0; i< all; i++)
		array[i] = i;

	int pushed 	= 0;
	int counter 	= 0;

	while (counter < all) {
		if (counter + step >= all)
			pushed = queue.put(&array[counter], all - counter);
		else
			pushed = queue.put(&array[counter], step);
		counter += pushed;
	}

	pthread_exit(NULL);
}

void *consumer(void *id) {
	const int step = 5;
	int array[step];
	int received;
	while (true) {
		received = queue.get(array, step);
		if (received > 0) {
			std::cout << "Received:";
			for (int i = 0; i < received; i++)
				std::cout << array[i] << " ";
			std::cout << std::endl;

		}
	}
}

int main() {
	pthread_t threads[2];

	pthread_create(&threads[0], NULL, feeder, (void*)0);
	pthread_create(&threads[1], NULL, consumer, (void*)1);

	pthread_exit(NULL);
}
