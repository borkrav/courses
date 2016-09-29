;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname cond) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
(define (q1a x)
  (cond [(p1? x) (f1 x)]
        [(p2? x) (f2 x)]
        [else (cond [(p3? x) (f3 x)]
                    [(p4? x) (f4 x)]
                    [else (f5 x)])]
        )
  )
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (q1a-equiv x)
  (cond [(p1? x) (f1 x)]
        [(p2? x) (f2 x)]
        [(p3? x) (f3 x)]
        [(p4? x) (f4 x)]
        [else (f5 x)]
        )
  )
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (q1b x)
  (cond [(p1? x) (cond [(p3? x) (f1 x)]
                       [(not (p3? x)) (f2 x)])]
        
        [(p2? x) (cond [(p4? x) (f3 x)]
                       [(not (p4? x)) (f4 x)])]
        
        [else (f5 x)]
        )
  )

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (q1b-equiv x)
  (cond [(and (p1? x) (p3? x)) (f1 x)]
        [(and (p1? x) (not (p3? x))) (f2 x)]
        [(and (p2? x) (p4? x)) (f3 x)]
        [(and (p2? x) (not (p4? x))) (f4 x)]
        [else (f5 x)]
        )
  )
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (q1c x)
  (cond [(cond [(p1? x) (p2? x)]
               [(p3? x) (p4? x)]
               [else false])
         (f1 x)]
        [(p5? x) (f2 x)]
        [else (f3 x)])
  )
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (q1c-equiv x)
  (cond [(or (and (p1? x) (p2? x)) (and (p3? x) (p4? x))) (f1 x)]
        [(p5? x) (f2 x)]
        [else (f3 x)]
        )
  )
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;