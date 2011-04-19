#include <infra/Mutex.h>

Mutex::Mutex () {
	description = std::string("Mutex");
	pthread_mutex_init(&mtx, NULL);
}

Mutex::Mutex (const char* str) {
	description = std::string(str);
	pthread_mutex_init(&mtx, NULL);
}

Mutex::Mutex (std::string str) {
	description = str;
	pthread_mutex_init(&mtx, NULL);
}

Mutex::~Mutex () {
	ReturnValue ret = pthread_mutex_destroy(&mtx);
	if (ret != RET_GOOD) {
		std::cerr << AT << ": Destroy mutex failed\n";
	}
}

void Mutex::lock() {
	pthread_mutex_lock(&mtx);
}

void Mutex::unlock() {
	pthread_mutex_lock(&mtx);
}

void Mutex::setDescription(std::string str) {
	description = str;
}

std::ostream& operator<<(std::ostream& os, Mutex& m) {
	os << m.description;
	return os;
}

