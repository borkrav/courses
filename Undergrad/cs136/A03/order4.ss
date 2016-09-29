#lang scheme

;f(x)=x, g(x)=sqrt(x)
;
;statement is false
;
;f(n) > c*g(n)
;n > c*(sqrt(n))      [n > 0]
;n/(sqrt(n)) > c
;sqrt(n) > c
;n > c^2
;
;pick any n > c^2
;
;n > c * (sqrt(n)) [provided n > c^2]
;
;n >= n0, so take n = max (c^2, n0)
;
; Since (findx c x0) produces x for all c,x0
;  we conclude that f(x) is not O(g(x))

;                                                    [] 
;

(provide c x0 findx)

(define c 'none)
  (define x0 'none)
  
(define (findx c x0)
     (max (expt c 2) x0))



