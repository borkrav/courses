;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname region) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
;hline-segment is a structure (make-hline-segment left-point length) where:
;* left-point is a posn
;* length is a num
;(define-struct hline-segment (left-point length)) creates:
;* constructor make-hline-segment
;* selectors hline-segment-left-pont and hline-segment-length
;* predicate hline-segment?
;Example: (make-hline-segment (make-posn 1 1) 1) 

(define-struct hline-segment (left-point length))

;; my-hline-segment-fn: hline-segment -> any
;(define (my-hline-segment-fn segment)
;  ...(hline-segment-left-point segment)...
;  ...(hline-segment-length segment)...)

;vline-segment is a structure (make-vline-segment low-point length) where:
;* low-point is a posn
;* length is a num
;(define-struct vline-segment (low-point length)) creates:
;* constructor make-vline-segment
;* selectors vline-segment-low-pont and vline-segment-length
;* predicate vline-segment?
;Example: (make-vline-segment (make-posn 1 1) 1)

(define-struct vline-segment (low-point length))

;; my-vline-segment-fn: vline-segment -> any
;(define (my-vline-segment-fn segment)
;  ...(vline-segment-low-point segment)...
;  ...(vline-segment-length segment)...)

;square-region is a structure (make-square-region corner length) where:
;* corner is a posn
;* length is a num
;(define-struct square-region (corner length)) creates:
;* constructor make-square-region
;* selectors square-region-corner and square-region-length
;* predicate square-region?
;Example: (make-square-region (make-posn 1 1) 1)

(define-struct square-region (corner length))

;; my-square-region-fn: square-region -> any
;(define (my-square-region-fn region)
;  ...(square-region-corner region)...
;  ...(square-retion-length region)...)

;rectangle-region is a structure (make-rectangle-region corner length width) where:
;* corner is a posn
;* length is a num
;* width is a num
;(define-struct rectangle-region (corner width height)) creates:
;* constructor make-retangle-region
;* selectors rectangle-region-corner, rectangle-region-width and rectangle-region-length
;* predicate rectangle-region?
;Example: (make-rectangle-region (make-posn 1 1) 1 2)

(define-struct rectangle-region (corner width height))

;; my-rectangle-region-fn: rectangle-region -> any
;(define (my-rectangle-region-fn region)
;  ...(rectangle-region-corner region)...
;  ...(rectangle-region-length region)...
;  ...(rectangle-region-width region)...)

;; my-region-in-plane-fn: (union posn hline-segment vline-segment square-region rectangle-region symbol) -> any
;(define (my-region-in-plane-fn region)
;  ...(cond [(hline-segment? region) (my-hline-segment-fn region)]
;           [(vline-segment? region) (my-vline-segment-fn region)]
;           [(square-region? region) (my-square-region-fn region)]
;           [(rectangle-region? region) (my-rectangle-region-fn region)]
;           [(posn? region) (my-posn-fn region)]
;           [(symbol=? 'Empty-Region region) (my-Empty-Region-fn region)]
;           [else (error 'my-region-in-plane-fn "Not a region-in-plane")])...)

;********************************************************************************************************************************************************************************
; hline-segment-simlifier: hline-segment -> (union hline-segment posn)
;a function that takes in an hline-segment, and outputs the simplest from: if length is negative, then the output is an hline-segment with a positive length. If the length is zero, then a posn is returned. Else the original hline-segment is returned.
;examples
(check-expect (hline-segment-simplifier (make-hline-segment (make-posn 10 10) 10)) (make-hline-segment (make-posn 10 10) 10))
(check-expect (hline-segment-simplifier (make-hline-segment (make-posn 10 10) 0)) (make-posn 10 10))

(define (hline-segment-simplifier segment)
  (cond [(= (hline-segment-length segment) 0) (hline-segment-left-point segment)] 
        [(< (hline-segment-length segment) 0) (make-hline-segment
                                               (make-posn (+ (posn-x (hline-segment-left-point segment)) (hline-segment-length segment)) 
                                                          (posn-y (hline-segment-left-point segment))) 
                                               (-(hline-segment-length segment)))] 
        [else segment]
        ))

;tests
(check-expect (hline-segment-simplifier (make-hline-segment (make-posn 5 5) 2)) (make-hline-segment (make-posn 5 5) 2))
(check-expect (hline-segment-simplifier (make-hline-segment (make-posn 12 15) 0)) (make-posn 12 15))
(check-expect (hline-segment-simplifier (make-hline-segment (make-posn 10 10) -15)) (make-hline-segment (make-posn -5 10) 15))

;********************************************************************************************************************************************************************************
;vline-segment-simplifier: vline-segment -> (union vline-segment posn)
;a function that takes in a vline-segment, and outputs the simplest form: if the length is negative, the output is a vline-segment with a positive length. If the length is zero, then a posn is returned. Else the original vline-segment is returned.
;examples
(check-expect (vline-segment-simplifier (make-vline-segment (make-posn 4 4) 10)) (make-vline-segment (make-posn 4 4) 10))
(check-expect (vline-segment-simplifier (make-vline-segment (make-posn 4 4) 0)) (make-posn 4 4))

(define (vline-segment-simplifier segment)
  (cond [(= (vline-segment-length segment) 0) (vline-segment-low-point segment)] 
        [(< (vline-segment-length segment) 0) (make-vline-segment
                                               (make-posn (posn-x (vline-segment-low-point segment))
                                                          (+ (posn-y (vline-segment-low-point segment)) (vline-segment-length segment))) 
                                               (-(vline-segment-length segment)))] 
        [else segment]
        ))

;tests
(check-expect (vline-segment-simplifier (make-vline-segment (make-posn 6 100) 200)) (make-vline-segment (make-posn 6 100) 200))
(check-expect (vline-segment-simplifier (make-vline-segment (make-posn 12 15) 0)) (make-posn 12 15))
(check-expect (vline-segment-simplifier (make-vline-segment (make-posn 60 30) -100)) (make-vline-segment (make-posn 60 -70) 100))

;********************************************************************************************************************************************************************************
;square-region-simplifier: square-region -> (union square-region posn)
;a function that takes in a square-region, and outputs the simplest form: if the length is zero, then a posn is returned. Else the original square-region is returned.
;examples
(check-expect (square-region-simplifier (make-square-region (make-posn 4 4) 10)) (make-square-region (make-posn 4 4) 10))
(check-expect (square-region-simplifier (make-square-region (make-posn 6 6) 0)) (make-posn 6 6))

(define (square-region-simplifier region)
  (cond [(= 0 (square-region-length region)) (square-region-corner region)]
        [else region]
        ))

;tests
(check-expect (square-region-simplifier (make-square-region (make-posn -64 -64) 30)) (make-square-region (make-posn -64 -64) 30))
(check-expect (square-region-simplifier (make-square-region (make-posn 6 6) 0)) (make-posn 6 6))

;********************************************************************************************************************************************************************************
;rectangle-region-simplifier: rectangle-region -> (union rectangle-region square-region posn)
;a function that takes in a rectangle-region, and outputs the simplest form: if the length is zero, then a posn is returned. If length and width are the same, then a square is returned. If either length or width is zero, then the rectangle is converted into a vline-segment or hline-segment. Else the original square-region is returned.
;examples
(check-expect (rectangle-region-simplifier (make-rectangle-region (make-posn 6 10) 10 30)) (make-rectangle-region (make-posn 6 10) 10 30))
(check-expect (rectangle-region-simplifier (make-rectangle-region (make-posn 6 6) 0 0)) (make-posn 6 6))

(define (rectangle-region-simplifier region)
  (cond [(and (= 0 (rectangle-region-width region)) (= 0 (rectangle-region-height region))) (rectangle-region-corner region)]
        [(= 0 (rectangle-region-width region)) (vline-segment-simplifier (make-vline-segment (rectangle-region-corner region) (rectangle-region-height region)))]
        [(= 0 (rectangle-region-height region)) (hline-segment-simplifier (make-hline-segment (rectangle-region-corner region) (rectangle-region-width region)))]
        [(= (rectangle-region-height region) (rectangle-region-width region)) (make-square-region (rectangle-region-corner region) (rectangle-region-width region))]
        [else region]
        ))

;tests
(check-expect (rectangle-region-simplifier (make-rectangle-region (make-posn 1 2) 3 4)) (make-rectangle-region (make-posn 1 2) 3 4))
(check-expect (rectangle-region-simplifier (make-rectangle-region (make-posn 1 1) 0 0)) (make-posn 1 1))
(check-expect (rectangle-region-simplifier (make-rectangle-region (make-posn 4 4) 10 0)) (make-hline-segment (make-posn 4 4) 10))
(check-expect (rectangle-region-simplifier (make-rectangle-region (make-posn 4 4) 0 10)) (make-vline-segment (make-posn 4 4) 10))
(check-expect (rectangle-region-simplifier (make-rectangle-region (make-posn 1 2) 3 3)) (make-square-region (make-posn 1 2) 3))

;********************************************************************************************************************************************************************************
; canonical-region: (union posn hline-segment vline-segment square-region rectangle-region symbol) -> (union symbol posn vline-segment hline-segment square-region rectangle-regoin)
; a fuction that takes in a region-in-plane data type, and then outputs it in the simplest format, as a line segment, a rectangle, a square, a posn or the symbol 'Empty-Region
;examples
(check-expect (canonical-region (make-rectangle-region (make-posn 10 15) 1 1)) (make-square-region (make-posn 10 15) 1))
(check-expect (canonical-region (make-posn 10 15)) (make-posn 10 15))

(define (canonical-region region)
  (cond [(hline-segment? region)(hline-segment-simplifier region)]
        [(vline-segment? region) (vline-segment-simplifier region)]
        [(square-region? region) (square-region-simplifier region)]
        [(rectangle-region? region) (rectangle-region-simplifier region)]
        [(posn? region) region]
        [(and (symbol? region) (symbol=? 'Empty-Region region)) 'Empty-Region]
        [else (error 'my-region-in-plane-fn "Not a region-in-plane")]))

;tests
(check-expect (canonical-region (make-hline-segment (make-posn 123 456) -789)) (make-hline-segment (make-posn -666 456) 789))
(check-expect (canonical-region (make-vline-segment (make-posn 10 10) -15)) (make-vline-segment (make-posn 10 -5) 15))
(check-expect (canonical-region (make-square-region (make-posn 30 40) 0)) (make-posn 30 40))
(check-expect (canonical-region (make-rectangle-region (make-posn 200 300) 0 -500)) (make-vline-segment (make-posn 200 -200) 500))
(check-expect (canonical-region (make-posn 25 45)) (make-posn 25 45))
(check-expect (canonical-region 'Empty-Region) 'Empty-Region)
(check-error (canonical-region "string") "my-region-in-plane-fn: Not a region-in-plane")

;********************************************************************************************************************************************************************************
; empty-region? : (union posn hline-segment vline-segment square-region rectangle-region symbol) -> boolean
; a function that takes in a region-in-plane data type and outputs wherether or not its an empty region
;examples
(check-expect (empty-region? (make-rectangle-region (make-posn 10 15) 1 1)) false)
(check-expect (empty-region? 'Empty-Region) true)

(define (empty-region? region)
  (cond [(and (symbol? (canonical-region region)) (symbol=? 'Empty-Region (canonical-region region))) true]
        [else false]))

;tests 
(check-expect (empty-region? (make-vline-segment (make-posn 10 12) 3)) false)
(check-expect (empty-region? 'Empty-Region) true)

