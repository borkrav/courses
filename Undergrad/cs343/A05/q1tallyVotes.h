#include <uC++.h>
#include <vector>
_Monitor Printer;

#if defined( IMPLTYPE_LOCK )		// mutex/condition solution
#include <uSemaphore.h>
class TallyVotes {
	private:
		uSemaphore *entry;
		uOwnerLock mutex;
		std::vector<uCondLock*> m_sleepers;
		unsigned int m_ballots;


#elif defined( IMPLTYPE_EXT )		// external scheduling monitor solution
_Monitor TallyVotes {
	private:
		void wait(unsigned int id);
		unsigned int m_ballots;
	

#elif defined( IMPLTYPE_INT )		// internal scheduling monitor solution
_Monitor TallyVotes {
	private:
		std::vector<uCondition*> m_sleepers;
		void wait(unsigned int id);
		unsigned int m_ballots;

#elif defined( IMPLTYPE_AUTO )		// automatic-signal monitor solution
#include "AutomaticSignal.h"
_Monitor TallyVotes {
	private:
		AUTOMATIC_SIGNAL;
		bool voteIsDone;
		void wait(unsigned int id);
		unsigned int m_ballots;


#elif defined( IMPLTYPE_TASK )		// internal/external scheduling task solution
_Task TallyVotes {
	private:
		uCondition m_sleepers;
		std::vector<int> m_arrivers;
		void main();

#else
#error unsupported voter type
#endif

	private:
		unsigned int m_group;
		Printer *m_prt; 
		std::vector<bool> m_results;
		bool m_result;
		unsigned int m_voters;

		//shared code, don't want to copy paste this across solutions so I put it here
		//gets the result from the vote
		bool getResult(){
			int tally = 0;
			for (int i = 0; i < m_group; i++){
				if (m_results[i] == true) tally++;
			}
			if (tally > (double) m_voters/2) return true;
			else return false;
		}

  public:
		TallyVotes( unsigned int group, Printer &prt );
		~TallyVotes();
		bool vote( unsigned int id, bool ballot );
};
