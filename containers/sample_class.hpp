#ifndef SAMPLE_CLASS_HPP
# define SAMPLE_CLASS_HPP

# include <stdlib.h>

class sampleClass {
private:
	int *sampleArray;
public:
	sampleClass() {};
	sampleClass(int n) {
		sampleArray = new int[100];
		for (int i = 0; i < 100; i++)
			sampleArray[i] = n;
	}
	~sampleClass() {
		delete[] sampleArray;
	}
	sampleClass(const sampleClass & other) {
		sampleArray = new int[100];
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
};

#endif
