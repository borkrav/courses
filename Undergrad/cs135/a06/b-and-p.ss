;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname b-and-p) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
;make-bp: any any any any -> listof any
;examples
(check-expect (make-bp 'a 'b 'c 'd) (cons (cons 'a (cons 'b empty)) (cons (cons 'c (cons 'd empty)) (cons empty empty))))

(define (make-bp a b c d)
  (cons (cons a (cons b empty)) 
        (cons (cons c (cons d empty)) 
              (cons empty empty))))

;tests
(check-expect (make-bp 1 2 3 4) (cons (cons 1 (cons 2 empty)) (cons (cons 3 (cons 4 empty)) (cons empty empty))))

;make-bp-alt: any any any any -> listof any
;examples
(check-expect (make-bp-alt 'a 'b 'c 'd) (list (list 'a 'b) (list 'c 'd) (list)))

(define (make-bp-alt a b c d)
  (list (list a b) (list c d) (list)))

;tests
(check-expect (make-bp-alt 1 2 3 4) (list (list 1 2) (list 3 4) (list)))

;bp-a: listof any -> any
;examples
(check-expect (bp-a (make-bp 'a 'b 'c 'd)) 'a)

(define (bp-a list)
  (first (first list)))

;test
(check-expect (bp-a (make-bp 1 2 3 4)) 1)

;bp-b: listof any -> any
;examples
(check-expect (bp-b (make-bp 'a 'b 'c 'd)) 'b)

(define (bp-b list)
  (first (rest (first list))))

;test
(check-expect (bp-b (make-bp 1 2 3 4)) 2)

;bp-c: listof any -> any
;examples
(check-expect (bp-c (make-bp 'a 'b 'c 'd)) 'c)

(define (bp-c list)
  (first (first (rest list))))

;test
(check-expect (bp-c (make-bp 1 2 3 4)) 3)

;bp-d: listof any -> any
;examples
(check-expect (bp-d (make-bp 'a 'b 'c 'd)) 'd)

(define (bp-d list)
  (first (rest (first (rest list)))))

;test
(check-expect (bp-d (make-bp 1 2 3 4)) 4)

;shape-of-bp?: any -> boolean
; a function that takes in any value and returns true if and only if that value can be created with the produced with the make-bp function

;examples
(check-expect (shape-of-bp? (make-bp 'a 'b 'c 'd)) true)

(define (shape-of-bp? value)
  (cond [(and (cons? value)
              (cons? (first value))
              (cons? (first (rest value)))  ;checks if the first three values are lists
              (cons? (rest (rest value)))
              (empty? (rest (rest (first value))))
              (empty? (rest (rest (first (rest value))))) ;checks if the list end at the appropriate places
              (empty? (first (rest (rest value))))
              (empty? (rest (rest (rest value)))))
         true]
        [else false]))

;tests
(check-expect (shape-of-bp? 10) false)
(check-expect (shape-of-bp? (list 1 2 3 4)) false)
(check-expect (shape-of-bp? (make-bp 52345 65361 512341 51234637)) true)
(check-expect (shape-of-bp? (list empty) ) false)
(check-expect (shape-of-bp? (list (list 123 123) (list 123 123))) false)
(check-expect (shape-of-bp? (list 10 10 32 14 51 13 231 "asda" 141)) false)

;remove-empties: listof listof any -> listof listof any
;a function that takes in a listof listof any, and outputs the same list, cutting out all the empty lists.
;examples
(check-expect (remove-empties (make-bp 'a 'b 'c 'd)) (list (list 'a 'b) (list 'c 'd)))
(check-expect (remove-empties (list (list 1 2) (list) (list 'c 'd))) (list (list 1 2) (list 'c 'd)))

(define (remove-empties input-list)
  (cond [(empty? input-list) empty]
        [(not (empty? (first input-list))) (cons (first input-list) (remove-empties (rest input-list)))]
        [(empty? (first input-list)) (remove-empties (rest input-list))]
        ))

(check-expect (remove-empties (cons empty (cons 2 empty))) (cons 2 empty))
(check-expect (remove-empties (cons empty (cons empty empty))) (list))
(check-expect (remove-empties (list (list empty))) (list (list empty)))
(check-expect (remove-empties (list empty)) (list))
(check-expect (remove-empties (list (list) (list 'a 'b 'c) (list (list)) (list 1 2 3 4) (list))) (list (list 'a 'b 'c) (list (list)) (list 1 2 3 4)))
