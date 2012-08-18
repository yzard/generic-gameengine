#ifndef INFRA_PROBABILITY_H
#define INFRA_PROBABILITY_H

// class probability, it's for calculation of probability

class Probability {
public:
	Probability() {}; 
	~Probability();

	// initialize 
	Probability(double) {};

	// operators overriding
	Probability& operator= (const Probability& rhs)
	Probability& operator+ (const Probability& lhs, const Probability& rhs);
	Probability& operator- (const Probability& lhs, const Probability& rhs);
	Probability& operator* (const Probability& lhs, const Probability& rhs);
	Probability& operator/ (const Probability& lhs, const Probability& rhs);

	// test function
	bool isLog();
	bool isReal();

	// convert methods
	void toLog();
	void toReal();

private:
	double value;
}

#endif // INFRA_PROBABILITY_H

