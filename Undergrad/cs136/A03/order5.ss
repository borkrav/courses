#lang scheme

;f(x)=2^x, g(x)=2^(x-1)
;
;statement is false
;
;f(n) > c*g(n)
;2^n > c*2^(n-1)      
;n(log 2) > c(n-1)(log 2)
;n > c(n-1)                   [n > 0]
;n/(n-1) > c
;[(n-1)+2]/(n-1) > c
;1+(2/(n-1)) > c              [n > 0]
;(2/n-1) > c-1
;(n-1)/2 > c-1
;n-1 > 2c-2
;n > 2c-1


;pick any n > 2c-1
;
;2^n > c*(2^(n-1)) [provided n > 2c-1]
;
;n >= n0, so take n = max (2c, n0)
;
; Since (findx c x0) produces x for all c,x0
;  we conclude that f(x) is not O(g(x))
;                                                    [] 
;

(provide c x0 findx)

(define c 'none)
  (define x0 'none)
  
(define (findx c x0)
     (max (* 2 c) x0))



