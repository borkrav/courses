#lang scheme

;; Implementation of simple guessing game
;; Provides:  startgame, guess

;; (startgame n) starts a new game in which the
;;    game [this module] chooses a secret integer
;;    between 1 and n, and you [the client module]
;;    tries to guess it

;; (guess x) consumes an integer x and produces
;;     either 'right or 'wrong, depending on whether
;;     or not (respectively) x is the secret integer

(provide startgame guess secret)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; A simple implementation                                 ;;
;;   uses builtin (random n) which picks between 0 and n-1 ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define secret 0) ;; This is our the game's secret number

(define (startgame n) (set! secret (+ 1 (random n)))
  )

(define (guess x)
  (display "aaa")
  (newline)
  (cond
    [(= x secret) 'right]
    [(< x secret) 'low]
    [(> x secret) 'high]))