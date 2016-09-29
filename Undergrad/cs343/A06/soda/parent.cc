#include "parent.h"

Parent::Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay )
	: m_printer( &prt ), m_bank( &bank ), m_nStudents( numStudents ), m_delay( parentalDelay ) { }

void Parent::main() {
	m_printer->print( Printer::Parent, 'S' ); 

	while( true ) {

		_Accept( ~Parent ) { break; }
		_Else {
			//first yield	
			yield( m_delay );
			
			unsigned int student_id = number_generator( m_nStudents - 1 ), 
									 amount = number_generator( 1, 3 );
		
			m_bank->deposit( student_id, amount );
			
			m_printer->print( Printer::Parent, 'D', student_id, amount );
		}

	}

	m_printer->print( Printer::Parent, 'F' ); 
}
