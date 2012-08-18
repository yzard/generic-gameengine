#include <infra/Probability.h>
#include <math.h>

Probability::Probability()
	: value(0)
{
}

Probability::~Probability()
{
}

Probability::Probability(double value)
	: value(value)
{
	if (value < )
}

void Probability::toLog()
{
	if (value > 0)
}

void Probability::toReal()
{
	// if value is positive, then it's real
	if (value > 0)
		return;

	// if value is negtive, then it's log value
	if (value < 0) {
		value = exp(value);
		return;
	}

	if (value == 0)

}

