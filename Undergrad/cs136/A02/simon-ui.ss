#lang scheme

;; Note:  this module must be run on the command line
;;   in a Unix, Linux or MacOS terminal, with the command

;;     mzscheme simon-ui.ss

;; This module is the "user interface" to Simple Simon
;; It displays the colors to the user, and reads keystrokes
;; to represent the user's button presses
;; 
;; It plays multiple games, prompting the user for the
;; size of each game

(require "keyboard.ss")
(require "simon.ss")

(define (display-colors c)
  (cond
    [(null? c) (void)]
    [true
     (clear-screen)
     (display (first c))
     (sleep 1)
     (clear-screen)
     (sleep .25)
     (display-colors (rest c))]))

(define (player i n)
  (define k (get-keystroke))
  (define r
    (cond
      [(equal? k #\b) (press 'blue)]
      [(equal? k #\r) (press 'red)]
      [(equal? k #\y) (press 'yellow)]
      [(equal? k #\g) (press 'green)]
      [true (press 'black)]))
  (printf "For move number ~a you pressed ~a: ~a\n" i k r)
  (cond
    [(equal? r 'ok) (player (add1 i) n)]
    [true (void)]))

(define (simon-ui)
  (display "Enter size of game (0 to quit), then hit enter: ")
  (let ([n (read)])
    (read-line) ;; discard keystroke up to and including return
    (cond
      [(= n 0) 'bye]
      [true
       (let ([colors (full-simon n)])
         (display-colors colors)
         (player 1 n)
         (simon-ui))]))
  )
(simon-ui)