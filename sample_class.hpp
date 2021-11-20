#ifndef SAMPLE_CLASS_HPP
# define SAMPLE_CLASS_HPP

# include <stdlib.h>

class sampleClass {
private:
	int sampleArray[100];
public:
	sampleClass() {};
	sampleClass(int n) {
		for (int i = 0; i < 100; i++)
			sampleArray[i] = n;
	}
	~sampleClass() {}
	sampleClass(const sampleClass & other) {
		*this = other;
	}
	int & value() {
		return (sampleArray[0]);
	}
	sampleClass & operator=(const sampleClass & other) {
		if (this != &other)
			for (int i = 0; i < 100; i++)
				sampleArray[i] = other.sampleArray[i];
		return (*this);
	}
	bool operator==(const sampleClass & other) const {
		if (sampleArray[0] != other.sampleArray[0])
			return false;
		return true;
	}
	bool operator!=(const sampleClass & other) const {
		return (!(operator==(other)));
	}
	bool operator<(const sampleClass & other) const {
		if (sampleArray[0] < other.sampleArray[0])
			return true;
		return false;
	}
};

#endif
