#include "WATCard.h"    

WATCard::WATCard() : m_balance( 0 ) { }

//Each student has their own card, and they never
// do more than one operation at a time.
void WATCard::deposit( unsigned int amount ) {
	m_balance += amount;
}
void WATCard::withdraw( unsigned int amount ) {
	m_balance -= amount;
}
unsigned int WATCard::getBalance() {
	return m_balance;
}
