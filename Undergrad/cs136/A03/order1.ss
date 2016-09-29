#lang scheme

;f(x)=x, g(x)=2*x
;
;n <= 2cn
;0 <= 2cn - n
;0 <= n(2c - 1) 
;
;0 <= 2c - 1       [n > 0]
;1/2 <= c          
;
;take c = 1
;n => 0
;take n0 = 0
;
;0 <= n
;0 <= (2 - 1)n
;0 <= 2n - n
;n <= 2n               [] 
;

;Thus the statement is true for c = 1, x0 = 0, and (findx 1 0) must produce 'impossible

(provide c x0 findx)

(define c 1)
(define x0 0)

(define (findx c x0)
  (cond [(> x0 (* c 2 x0)) x0]
        [else 'impossible]))



