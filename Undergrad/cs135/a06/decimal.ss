;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname decimal) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
;Decimal definition: A natural number is one of:
;* 0 
;* 10k, where k is a non-zero natural number 
;* 10k + n, where k is a non-zero natural number, n is a natural number, n[1,9] 

;A digit is one of 0,1,2,3,4,5,6,7,8,9

;A natural number is one of:
;* d , where d is a digit
;* 10k, where k is a non-zero natural number 
;* 10k + d, where k is a non-zero natural number, d is a digit

;;my-natural-function: nat -> any 
;(define (my-natural-function number)
;  (cond [(zero? number)...]
;        [...(zero? (modulo number 10))...]
;        [else ...(my-natural-function (number - (modulo number 10)))...]


;num-digits: nat -> nat
;a function that takes in a natural number and returns the number of digits it has
;examples
(check-expect (num-digits 123) 3)
(check-expect (num-digits 1) 1)

(define (num-digits number)
  (cond [(= 1 number) 1]
        [(= 0 (modulo number 10)) (+ 1 (num-digits (/ number 10)))]
        [else (num-digits (- number 1))]))

;tests
(check-expect (num-digits 1233451534543523) 16)
(check-expect (num-digits 1) 1)
(check-expect (num-digits 123123123123123123123123123123123123) 36)

;sum-digits: nat -> nat
;a function that takes in a natural number and returns the sum of it's digits
;examples
(check-expect (sum-digits 123) 6)
(check-expect (sum-digits 12) 3)

(define (sum-digits number)
  (cond [(= 1 number) 1]
        [(= 0 (modulo number 10)) (+ 0 (sum-digits (/ number 10)))]
        [else (+ (modulo number 10) (sum-digits (/ (- number (modulo number 10)) 10)))]))

;tests
(check-expect (sum-digits 102) 3)
(check-expect (sum-digits 10) 1)
(check-expect (sum-digits 12304560789) 45)

;rev-digits: nat -> nat
;a function that takes in a natural number and reveres it's digits
;examples
(check-expect (rev-digits 123) 321)
(check-expect (rev-digits 456000) 654)

(define (rev-digits number)
  (cond 
    [(= 0 number) 0]
    [(= 0 (modulo number 10)) (+ 0 (rev-digits (/ number 10)))]
    [else (+ (* (modulo number 10) (expt 10 (- (num-digits number) 1 ))) (rev-digits (/ (- number (modulo number 10)) 10)))]))

;tests
(check-expect (rev-digits 123412341234) 432143214321)
(check-expect (rev-digits 1) 1)
(check-expect (rev-digits 0) 0)
(check-expect (rev-digits 101010100000000000) 1010101)
