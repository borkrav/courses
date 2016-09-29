#lang scheme

;; simon.ss plays a single round of the "Simon" game
;; provides:
;;   (simple-simon n)  consumes a positive integer n
;;                     produces (list seq press-fn)
;;                     where seq is a length-n sequence of colors
;;                       from {red, blue, green, yellow}
;;                     and press-fn is a `press' function
;; ----------------------
;;   A `press' function  consumes a color c
;;                       produces (list 'win score) if c is correct and game done
;;                       another `press' function if correct and game not done
;;                       (list 'lose score) if c is incorrect


(provide simple-simon press)

;; helper function (random-color) produces a color
;;           from {red, blue, green, yellow}
(define (random-color)
  (define r (random 4))
  (cond
    [(= r 0) 'blue]
    [(= r 1) 'red]
    [(= r 2) 'yellow]
    [true 'green]))



(define (simple-simon n)
  (define (build-list x)
    (cond
      [(= x 0) empty]
      [true (cons (random-color) (build-list (sub1 x)))]))
  (list (build-list n) (lambda (x) (press x))))


(define (press c)
  (cond
    [(equal? c shouldbe)
     (cond
       [(empty? c) (list 'win 10)]
       [true (lambda (x) (press x))])]
    (list 'lose 10)))
