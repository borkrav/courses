   // Implementation of ordered guessing game
   // Provides:  startgame, guess

   int startgame(int n);
   // starts a new game in which the
   //    game [this module] chooses a secret integer
   //    between 1 and n, and you [the client module]
   //    tries to guess it

   char guess(int x); 
   //     consumes an integer x and produces
   //     one of 'r' or 'h' or 'l', depending on 
   //     whether x is equal to, greater than, or less than
   //     the secret integer

