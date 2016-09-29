;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-lambda-reader.ss" "lang")((modname filter) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
;filter-even: ((string -> nat) -> boolean) (listof string) -> (listof string)
;a function that takes in a funcion that returns a natural and a list, and filters all the even values out of the list
;example
(check-expect (filter-even string-length (list "this" "is" "a" "test")) (list "this" "is" "test"))

(define (filter-even f list)
  (filter (lambda (item) (even? (f item))) list)
  )

;test
(check-expect (filter-even string-length (list "thisa" "isa" "a" "test")) (list "test"))

;pair-filter: (num num -> boolean) (listof num) -> (listof num)
;a function that filters a list according to the function given
;example
(check-expect (pair-filter < '((3 1)(4 1)(5 9)(2 6))) '((5 9)(2 6)))

(define (pair-filter f list)
  (filter (lambda (item) (f (first item) (second item))) list))

;tests
(check-expect (pair-filter > '((3 1)(4 1)(5 9)(2 6))) '((3 1)(4 1)))
(check-expect (pair-filter = '((3 1)(4 1)(5 9)(2 6))) '())

;bifilter: (num nu -> boolean) (listof num) (listof num) -> (listof (listof num))
;a fucntion that filters two lists according to function given
;example
(check-expect (bifilter < '(3 1 4 1 5) '(2 7 8 1 8)) '((1 7)(4 8)(5 8)))

(define (bifilter f list-1 list-2)
  (cond [(empty? list-1) empty]
        [((lambda (item-1 item-2) (f item-1 item-2)) (first list-1) (first list-2))
         (cons (list (first list-1) (first list-2)) 
               (bifilter f (rest list-1) (rest list-2)))]
        [else (bifilter f (rest list-1) (rest list-2))]
        ))

;tests
(check-expect (bifilter > '(3 1 4 1 5) '(2 7 8 1 8)) '((3 2)))
(check-expect (bifilter = '(3 1 4 1 5) '(2 7 8 1 8)) '((1 1)))



  