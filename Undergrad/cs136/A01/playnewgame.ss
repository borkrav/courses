#lang scheme

(require "newgame.ss")

;; Player for ordered guessing game
;; Provides:  playgame

;; (playgame n) uses "newgame.ss" to play an entire
;;              game of size n, and produces m,
;;              the total number of guesses necessary
;;              to produce 'right

;playgame: int -> int

(provide playgame)

(define (playgame n)

 (define (bisection ub lb num)
   
    (define checker (guess (quotient (+ ub lb) 2)))
    
    (cond  
      [(symbol=? 'right checker) num]
      [(symbol=? 'high checker) (bisection (quotient (+ ub lb) 2) lb (add1 num))]
      [(symbol=? 'low checker) (bisection ub (quotient (+ ub lb) 2) (add1 num))]))

  (startgame n)
  (bisection (+ n 1) 0 1)
  
  )



