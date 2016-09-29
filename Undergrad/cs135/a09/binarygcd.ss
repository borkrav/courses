;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-lambda-reader.ss" "lang")((modname binarygcd) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
;binary-gcd: (nat [not 0]) (nat [not 0]) -> (nat [not 0])
;a function that consumes two integers and computes their GCD using binary represitation
;examples
(check-expect (binary-gcd 123 543) 3)
(check-expect (binary-gcd 555 666) 111)

(define (binary-gcd u v)
  (cond [(zero? (remainder u v)) v]
        
        [(and (even? u) (odd? v))
         (binary-gcd (/ u 2) v)]
        
        [(and (odd? u) (even? v))
         (binary-gcd u (/ v 2))]
        
        [(and (even? u) (even? v))
         (* 2 (binary-gcd (/ u 2) (/ v 2)))]
        
        [(and (odd? u) (odd? v)) 
         (binary-gcd (/ (abs (- u v)) 2) (min u v))]))


(check-expect (binary-gcd 22 999) 1)
(check-expect (binary-gcd 15 46) 1)
(check-expect (binary-gcd 22 11) 11)
(check-expect (binary-gcd 11 22) 11)
(check-expect (binary-gcd 864 586) 2)
(check-expect (binary-gcd 567 123) 3)

;this function always terminates because in every case, for every iteration, the generated u and v values get smaller

