;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-lambda-reader.ss" "lang")((modname matrix) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
;dot-prod: intvec intvec -> int
;a function that takes in a vector (list of natural numbers) and ouputs their dot product
;examples
(check-expect (dot-prod '(1 1 1) '(2 2 2)) 6)
(check-expect (dot-prod '(4 5 6) '(3 2 1)) 28)

(define (dot-prod vector-1 vector-2)
  (foldr (lambda (x y) (+ x y)) 0 (map * vector-1 vector-2)))

(check-expect (dot-prod '() '()) 0)
(check-expect (dot-prod '(1) '(2)) 2)
(check-expect (dot-prod '(1 2 3 4 5 6) '(6 5 4 3 2 1)) 56)

;mat-vec-prod: intmat intvec -> intvec
;a function that takes in a matrix and a vector and calculates the matrix-vector procuct
;exaples
(check-expect (mat-vec-prod '((1 2)(3 4)) '(5 6)) '(17 39))
(check-expect (mat-vec-prod '((1 1 1)(1 1 1)) '(9 8 7)) '(24 24))

(define (mat-vec-prod matrix vector)
  (map (lambda (mat-insides) (dot-prod vector mat-insides)) matrix))

(check-expect (mat-vec-prod '() '()) '())
(check-expect (mat-vec-prod '((1 2 3 4)(5 6 7 8)) '(9 9 9 9)) '(90 234))


;vec-mat-prod: intvec intmat -> intvec
;a function that takes in a vector and a matrix and calculates the vector-matrix procuct
;exaples
(check-expect (vec-mat-prod '(5 6) '((1 2)(3 4))) '(23 34))
(check-expect (vec-mat-prod '(9 8 7) '((1 1 1)
                                       (1 1 1)
                                       (1 1 1))) '(24 24 24))

(define (vec-mat-prod vector matrix)
  (cond [(empty? (first matrix)) empty]
        [else (cons 
               (dot-prod vector (foldr (lambda (mat-inside rest) 
                                         (cons (first mat-inside) rest))
                                       empty matrix))
               (vec-mat-prod vector (map (lambda (mat-inside) (rest mat-inside)) matrix)))]))

(check-expect (vec-mat-prod '() '(())) '())
(check-expect (vec-mat-prod '(9 9 9 9) '((1 2) (3 4)(5 6)(7 8))) '(144 180))

;mat-mat-prod: intmat intmat -> intmat
;a function that takes in two matricies and multiplies the first matrix by the second matrix 
;examples
(check-expect (mat-mat-prod '((1 2)(3 4)) '((5 6)(7 8))) '((19 22)(43 50)))

(define (mat-mat-prod matrix-1 matrix-2)
  (cond [(empty? matrix-1) empty]
        [else (cons
               (vec-mat-prod (first matrix-1) matrix-2)
               (mat-mat-prod (rest matrix-1) matrix-2))]))

(check-expect (mat-mat-prod '(()) '(())) '(()))
(check-expect (mat-mat-prod '((1 1)) '((2)(2))) '((4)))
(check-expect (mat-mat-prod '((1 1 2 2) (6 7 8 9)) '((123 321)(456 654)(987 789)(101 101))) '((2755 2755)(12735 13725)))
(check-expect (mat-mat-prod '((11)) '((11))) '((121)))
(check-expect (mat-mat-prod '((0 32)) '((0)(34))) '((1088)))