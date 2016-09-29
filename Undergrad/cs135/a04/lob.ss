;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname lob) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
; a listof booleans is either:
; * empty
; * (cons n empty) where n is a boolean
; * (cons n lob) where los is a listof booleans


;list-checker: listof any -> boolean
;a function that checks if a list is a listof boolean
;examples
(check-expect (list-checker (cons true empty)) true)
(check-expect (list-checker (cons 1 empty)) false)

(define (list-checker list)
  (cond [(empty? list) true]
        [else (cond [(boolean? (first list))(list-checker (rest list))]
                    [else false])]))

;tests  
(check-expect (list-checker (cons empty empty)) false)
(check-expect (list-checker (cons true (cons false (cons true (cons true empty))))) true)
(check-expect (list-checker (cons 1 (cons 'aaa empty))) false)


;true-counter: listof booleans -> num
;a function that adds up all the instances of "true" in a given listof booleans
;examples
(check-expect (true-counter (cons true empty))1)
(check-expect (true-counter (cons true(cons true empty))) 2)

(define (true-counter lob)
  (cond [(empty? lob) 0] ;base case, returns zero
        [else (+  (cond[(first lob) 1]
                       [else 0])
                  (true-counter (rest lob)))]))
;tests
(check-expect (true-counter (cons true (cons true (cons true (cons true (cons true (cons true (cons false (cons true (cons false (cons true (cons true empty)))))))))))) 9)
(check-expect (true-counter (cons false empty)) 0)
(check-expect (true-counter (cons true empty)) 1)

;parity?: listof booleans -> boolean
;a function that determines if the result num returned from true-counter is even or odd
;examples
(check-expect (parity? (cons true empty)) true)
(check-expect (parity? (cons true(cons true empty))) false)

(define (parity? lob)
  (cond [(not (cons? lob)) (error 'parity? "Input not a list")]
        [(not (list-checker lob)) (error 'parity? "Input not a list of booleans")]
        [(odd? (true-counter lob)) true]
        [else false]))

;tests
(check-expect (parity? (cons true (cons true (cons true (cons true (cons true (cons true (cons false (cons true (cons false (cons true (cons true empty)))))))))))) true)
(check-expect (parity? (cons false empty)) false)
(check-expect (parity? (cons true empty)) true)
(check-expect (parity? (cons true (cons true (cons true (cons true (cons true (cons true empty))))))) false)
(check-error (parity? (cons empty empty)) "parity?: Input not a list of booleans")
(check-error (parity? (cons true (cons 5 empty))) "parity?: Input not a list of booleans")
(check-error (parity? 7) "parity?: Input not a list")



;alterlating?: listof booleans -> boolean
;a function that determines if the values in a listof booleans is alternating.
;examples
(check-expect (alternating? (cons true (cons false (cons true (cons false empty))))) true)
(check-expect (alternating? (cons true (cons true (cons false (cons false empty))))) false)

(define (alternating? lob)
  (cond [(empty? lob) true] 
        [(not (cons? lob)) (error 'alternating? "Input not a list")]
        [(not (list-checker lob)) (error 'alternating? "Input not a list of booleans")]
        [(empty?(rest lob)) true] ;base case
        [(not (boolean=? (first lob) (first (rest lob)))) (alternating? (rest lob))]
        [else false]))

;tests
(check-expect (alternating? (cons false (cons true (cons false (cons true (cons false (cons true empty)))))))true)
(check-expect (alternating? (cons false empty)) true)
(check-expect (alternating? (cons true empty)) true)
(check-expect (alternating? (cons false (cons false empty))) false)
(check-expect (alternating? empty) true)
(check-error (alternating? (cons empty empty)) "alternating?: Input not a list of booleans")
(check-error (alternating? (cons true (cons 5 empty))) "alternating?: Input not a list of booleans")
(check-error (alternating? 7) "alternating?: Input not a list")