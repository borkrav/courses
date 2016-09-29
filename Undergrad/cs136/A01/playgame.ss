#lang scheme

(require "game.ss")

;; Player for simple guessing game
;; Provides:  playgame

;; (playgame n) uses "game.ss" to play an entire
;;              game of size n, and produces m,
;;              the total number of guesses necessary
;;              to produce 'right

;playgame: int -> int

(provide playgame)

(define (playgame n)
  
  (define algorithm (random 2))
  
  (startgame n)
  
  (cond [(eq? 0 algorithm) (algorithm-two)]
        [(eq? 1 algorithm) (algorithm-three n)]
        [(eq? 2 algorithm) (algorithm-four n)])  
  )
  
  
  
  


;(define (algorithm-one n)
;  
;  (define (guess-mid mid num)
;    (cond [(symbol=? 'right (guess mid)) num]
;          [(even? n) (guess-other-mid (+ 1 mid) (add1 num))]
;          [else (guess-start 1 n (add1 num))]))
;  
;  (define (guess-other-mid mid num)
;    (cond [(symbol=? 'right (guess mid)) num]
;          [else (guess-start 1 n (add1 num))]))
;  
;  (define (guess-start min max num)
;    (cond [(symbol=? 'right (guess min)) num]
;          [else (guess-end (add1 min) max (add1 num))]))
;  
;  (define (guess-end min max num)
;    (cond [(symbol=? 'right (guess max)) num]
;          [else (guess-start min (sub1 max) (add1 num))]))
;  
;  
;  
;  (cond [(odd? n) (guess-mid (quotient (+ n 1) 2) 1)]
;        [else (guess-mid (quotient n 2) 1)])
;  )


(define (algorithm-two)
  
  (define (guesser num)
    (cond [(symbol=? 'right (guess num)) num]
          [else (guesser (add1 num))]))
  
  (guesser 1)
  
  )

(define (algorithm-three n)
  
  (define (guesser max num)
    (cond [(symbol=? 'right (guess max)) num]
          [else (guesser (sub1 max) (add1 num))]))

  (guesser n 1))

(define (algorithm-four n)
  
  
  (define (guess-start min max num)
    (cond [(symbol=? 'right (guess min)) num]
          [else (guess-end (add1 min) max (add1 num))]))
  
  (define (guess-end min max num)
    (cond [(symbol=? 'right (guess max)) num]
          [else (guess-start min (sub1 max) (add1 num))]))

  (guess-start 1 n 1)
  )
