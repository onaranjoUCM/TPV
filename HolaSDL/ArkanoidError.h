#ifndef ArkanoidErrorH
#define ArkanoidErrorH

#include <string>
#include <stdexcept>

class ArkanoidError : public std::logic_error {
protected:
	
public:
	using std::logic_error::logic_error;

	//logic_error(const std::string& what_arg);
	//char* what() const;
};

#endif