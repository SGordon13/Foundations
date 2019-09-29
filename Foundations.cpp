#include <iostream>
#include <list>
#include <string>
#include <cmath>

class Char {
public:
	char c;
	Char() { this->c = 'n'; }
	Char(char x) {this->c = x;}
};

class String {
public:
	String() {}
	virtual bool isEmpty() { return true; }
	virtual Char fChar() { return (Char('n')); }
	virtual String* next() { return (&String()); }
	virtual void print() {};
};

class epsilon : public String {
public:
	epsilon() {}
	bool isEmpty() { return true; }
	Char fChar() { throw new _exception; }
	String* next() { throw new _exception; }
	void print() { std::cout << 'E'; }
};

class OneString : public String{
public:
	Char c;
	String* s;
	OneString() {
		this->c = Char('n');
		this->s = new epsilon();
	}
	OneString(Char c, OneString* s) {
		this->c = c;
		this->s = s;
	}
	OneString(Char c, String* s) {
		this->c = c;
		this->s = s;
	}
	bool isEmpty() {
		return false;
	}
	Char fChar() { return this->c; }
	String* next() { return this->s; }

	void print() {
		std::string a;
		std::cout << this->c.c;
		this->s->print();
	}
};

class Alphabet {
public:
	virtual int size() { return 0; }
	virtual Char index(int i) { return 0; }
	virtual String* nString(int i) { return 0; }
};

class EmptyAlphabet : public Alphabet {
public:
	EmptyAlphabet() {}
	int size() { return 0; }
	Char index(int i) { 
		if (i == 0) { return(Char('E')); }
		else std::cout << "Exception here!\n";
	}
	String* nString(int i) {
		if (i == 0) { return (new epsilon()); }
		else throw new _exception;
	}
};

class SingleAlphabet : public Alphabet {
	Char c;
	Alphabet* a;
public:
	SingleAlphabet(Char c, SingleAlphabet* a) {
		this->c = c;
		this->a = a;
	}
	SingleAlphabet(Char c, Alphabet* a) {
		this->c = c;
		this->a = a;
	}
	int size() {
		return 1 + (a->size());
	}
	Char index(int i) {
		if (i == 0) { return c; }
		else return(a->index(i - 1));
	}
	String* nString(int in) {
		// deal with the trivial cases
		if (in == 1) {
			return new epsilon();
		}
		else if (in == 2) {
			return new OneString(Char(this->index(0)), new epsilon());
		}

		double z = in; // index of the desired string
		double x = this->size(); // number of characters in the alphabet
	
		double p = 0;	// max power of x so that (x^p < z)
						// also the length of the desired string

		double a = 0; // index of the desired string in the list of Strings of the correct length

		// setting p to the correct power
		int tracker = 1;
		for (double i = 0; i < 10; i++) {
			if (tracker > z) {
				p = (i - 1);
				break;
			}
			tracker += std::pow(x, i);
		}

		// getting the correct index of the set of strings of correct length
		int temp = pow(x, p);
		int sum = 0;
		for (int i = p; i >= 0; i--) {
			sum += pow(x, i);
		}
		a = temp - (sum - z);


		// creating the returning string and a pointer to it
		// in order to change the values.
		OneString* ret1 = new OneString();
		OneString* ret = ret1;
		// values i'll need for convenience
		int append = 0;
		int tester = (pow(x, p));

		/* debug help
		std::cout << "\nx = " << x << "\n";
		std::cout << "p = " << p << "\n";
		std::cout << "a = " << a << "\n";
		std::cout << "z = " << z << "\n";
		std::cout << "tester = " << tester << "\n";
		*/

		// loop for determining and creating the correct string
		for (int i = 0; i <= p - 1; i++) {
			for (double j = 1; j <= x+1; j++) {
				if (a <= (j * (tester / x))) {
					append = (j - 1);
					a = a - (((j - 1) * tester) / x);
					tester = ((tester) / x);
					break;
				}
			}
			
			//a = (temp - (sum - z)) / x;
			//tester = (pow(x, p)) / x;


			ret->c = this->index(append);

			// moving the pointer forward in the string 
			// and 'saving' the information
			if (i != p - 1) {
				OneString* temp = new OneString();
				ret->s = temp;
				ret = temp;
			}
		}
		// return the constructed string
		return ret1;
	}
};

int main()
{
	// 3 char alphabet
	SingleAlphabet a = SingleAlphabet(Char('0'), new SingleAlphabet(Char('1'),  new SingleAlphabet(Char('2'), new EmptyAlphabet())));

	// binary ( 2 char )
	SingleAlphabet b = SingleAlphabet(Char('0'), new SingleAlphabet(Char('1'), new EmptyAlphabet()));

	/* test area start */
	int m = 14;
	String* tester = a.nString(m);

	int n = 15;
	String* tester2 = a.nString(n);

	std::cout << "\n(3 char) nstring test with m = " << m << ": ";
	tester->print();

	std::cout << "\n(3 char) nstring test with n = " << n << ": ";
	tester2->print();


	int o = 26;
	String* testerb = b.nString(o);

	int p = 22;
	String* testerb2 = b.nString(p);

	std::cout << "\n\n(2 char) nstring test with m = " << o << ": ";
	testerb->print();

	std::cout << "\n(2 char) nstring test with n = " << p << ": ";
	testerb2->print();
	/* test area end */
}
