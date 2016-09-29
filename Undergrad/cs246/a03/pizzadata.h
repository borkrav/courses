// Data for Tony's Pizza Place  V0.0
// This isolates the English text used for talking with customer
// See pizzadata.cpp for values of below constants

// Messages
#ifndef PIZZA_DATA
#define PIZZA_DATA

extern const char * helloPhrase;
extern const char * goodbyePhrase;
extern const char * goodbyePhrase;
extern const char * abortPhrase;

extern const char * sizePrompt;
extern const char * toppingPrompt;

extern const char * sizeNotice;
extern const char * toppingNotice;
extern const char * requestPayment;

// Define characters used to make size choices
#define BASIC_SIZE 'a'   // What size?
#define SIZE_RANGE 3

extern const char * sizeName[SIZE_RANGE];
extern const double pizzaPrice[SIZE_RANGE];

// Define characters used to make topping choices
#define FIRST_TOPPING '1'   // What toppings?
#define TOPPING_RANGE 5

extern const char * toppingName[TOPPING_RANGE];
extern const double toppingPrice[TOPPING_RANGE];

#endif
