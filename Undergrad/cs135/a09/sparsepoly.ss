;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-lambda-reader.ss" "lang")((modname sparsepoly) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
;poly-eval: sparse-poly int -> int
;a funcion that takes in a sparse-poly and an integer, evaluates the polynomial, and outputs the solution
;examples
(check-expect (poly-eval '((1 2)(1 1)(1 0)) 1) 3)
(check-expect (poly-eval '((1 2)(1 1)(1 0)) 2) 7)

(define (poly-eval polynomial input)
  (foldr (lambda (x y) (+ (* (first x) 
                             (expt input (second x)))
                          y)) 0 polynomial))


(check-expect (poly-eval '() 1) 0)
(check-expect (poly-eval '((-10 5)(6 1)(8 0)) 3) -2404)
(check-expect (poly-eval '((4 4)(-1 1)(-1 0)) 4) 1019)
(check-expect (poly-eval '((1 2)(1 1)(1 0)) 0) 1)

;derivative: sparse-poly -> sparse-poly
;a function that takes in a sparse-poly and returns it's derivative
;examples
(check-expect (derivative '((1 2)(1 1)(1 0))) '((2 1)(1 0)()))
(check-expect (derivative '((1 5)(1 4)(1 3))) '((5 4)(4 3)(3 2)))

(define (derivative polynomial)
  (cond [(empty? polynomial) empty]
        [(= 0 (second(first polynomial))) empty]
        [else (foldr (lambda (x y) (cons 
                                    (cond [(= (second x) 0) empty] 
                                          [else(list (* (first x) (second x)) 
                                                     (sub1 (second x)))])
                                    y)) 
                     empty polynomial)]))

(check-expect (derivative '()) '())
(check-expect (derivative '((8 0))) '())
(check-expect (derivative '((-10 5)(6 1)(8 0))) '((-50 4)(6 0)()))
(check-expect (derivative '((4 4)(-1 1)(-1 0))) '((16 3)(-1 0)()))
(check-expect (derivative '((1 2)(1 1)(1 0))) '((2 1)(1 0)()))