;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname fibonacci) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
;;**************************************************************************************************************
;; Boris Kravchenko
;; 20332359
;; A00 - Fibonacci calculator
;;**************************************************************************************************************

(define theta ; the golden ratio, defined under constant theta
  (/ (+ 1 (sqrt 5)) 2))

(define (fib n)  ; function that calculates the nth fibonacci number
  (/ (- (expt theta n) (expt (- 1 theta) n)) (sqrt 5)))

