;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-lambda-reader.ss" "lang")((modname crossfilter) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
;crossfilter: (X X -> boolean) (listof X) (listof X) -> (listof (listof X X))
;a function that takes a predicate and two lists, and outputs a every possible combibation between the two lists for which the predicate is true
;examples 
(check-expect (crossfilter < '(3 1 6) '(2 5 8)) '((3 5)(3 8)(1 2)(1 5)(1 8)(6 8)))
(check-expect (crossfilter > '(5 5 1 0) '(2 6 1)) '((5 2)(5 1)(5 2)(5 1)))

(define (crossfilter pred list-1 list-2)
  (foldr (lambda (x y) 
           (append (map (lambda (first) (list x first)) 
                        (filter (lambda (item) (pred x item)) list-2))
                   y))    
         empty list-1)
  )

(check-expect (crossfilter = '(1 2 3) '(1 2 3)) (list (list 1 1) (list 2 2) (list 3 3)))
(check-expect (crossfilter symbol=? '() '()) '())
(check-expect (crossfilter = empty empty) empty)
(check-expect (crossfilter symbol=? '() '(a a a)) '())
(check-expect (crossfilter symbol=? '(a a a) '()) '())
(check-expect (crossfilter symbol=? '(a a a) '(a a a)) '((a a)(a a)(a a)(a a)(a a)(a a)(a a)(a a)(a a)))
(check-expect (crossfilter string=? (list "The" "cake" "is" "a" "lie") (list "Dr" "Gordon" "Freeman")) '())



