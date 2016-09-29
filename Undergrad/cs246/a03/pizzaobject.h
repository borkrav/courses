#ifndef PIZZA_OBJECT
#define PIZZA_OBJECT

#include <vector>
using namespace std;

class pizzaobject{
	
private:
	char *orderSize;
	vector<char*> orderToppings;
	double total;
	int numberOfToppings;
	void calculateOrder(double price);
	
public:
	
	pizzaobject();
	void recordSize(int index);
	void recordTopping(int index);
	double printOrder();
	int countToppings(int index);
	char* printSize();
};


#endif