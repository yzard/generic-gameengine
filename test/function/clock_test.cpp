#include <iostream>
#include <infra/Profile.h>

int main() {
	CLOCK_INIT(b);

	CLOCK_REAL_BEGIN(b);

	int i = 3;

	CLOCK_REAL_END(b);

	CLOCK_PRINT(b);
}
