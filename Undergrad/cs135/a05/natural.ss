;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname natural) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
;lessthan?: nat nat -> boolean
;a function that takes in two natural numbers and outputs whether or not the first number is smaller then the second number
;examples
(check-expect (lessthan? 13 2) false)
(check-expect (lessthan? 10 13) true)

(define (lessthan? a b)
  (cond [(and (zero? a) (zero? b)) false]
        [(zero? a) true]
        [(zero? b) false]
        [else (lessthan? (sub1 a) (sub1 b))]))

;tests
(check-expect (lessthan? 15 15) false)
(check-expect (lessthan? 35 100) true)
(check-expect (lessthan? 0 0) false)
(check-expect (lessthan? 0 1) true)


;add: nat nat -> nat
;a funtion that takes in two natural numbers and outputs their sum
;examples
(check-expect (add 10 10) 20)
(check-expect (add 33 25) 58)


(define (add a b)
  (cond [(zero? b) a]
        [else (add (add1 a) (sub1 b))]))

;tests
(check-expect (add 0 0) 0)
(check-expect (add 0 1) 1)
(check-expect (add 1 0) 1)
(check-expect (add 40 15) 55)


        
        
        

        
        