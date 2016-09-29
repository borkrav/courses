;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-lambda-reader.ss" "lang")((modname dominosa) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Skeleton code for A10Q2.  Replace this with your own header, and
;; fill in the relevant fragments of code and functions below.  You
;; should delete the portions of the comments that are tips and
;; solution strategies, and add in all missing elements of the design
;; recipes for all functions (including additional examples and tests
;; of your own).
;;

(define-struct config (board pairs free))

;; A board is a (listof (listof nat)).
;; A pair is of the form (list (list x1 y1) (list x2 y2)), where
;;   x1, y1, x2 and y2 are natural numbers.
;; A domino is of the form (list a b), where a and b are
;;   natural numbers.
;; A configuration is a structure (make-config b ps fl), where
;;   b is a board, ps is a (listof pair) and fl is a (listof
;;   domino).

;; Define a few sample boards and, for some, associated solutions.
;; More can easily be constructed from the website mentioned
;; in the assignment.

(define B0 '((0 0 1)
             (0 1 1)))
(define B0-soln '(((0 1) (1 1)) ((2 0) (2 1)) ((0 0) (1 0))))

(define B1 '((2 1 2 1 1 4)
             (3 4 2 2 2 0)
             (1 4 0 0 4 1)
             (0 3 4 2 0 4)
             (3 3 1 3 3 0)))
(define B1-soln 
  '(((4 4) (5 4)) ((2 4) (3 4)) ((0 4) (1 4)) ((3 3) (4 3))
                  ((1 3) (2 3)) ((5 2) (5 3)) ((2 2) (3 2)) ((0 2) (0 3))
                  ((4 1) (4 2)) ((2 1) (3 1)) ((1 1) (1 2)) ((5 0) (5 1))
                  ((3 0) (4 0)) ((1 0) (2 0)) ((0 0) (0 1))))

(define B2 '((4 1 1 2 1 0)
             (0 0 1 2 3 4)
             (0 0 3 1 4 4)
             (3 3 3 2 4 4)
             (2 1 3 2 2 0)))
(define B2-soln 
  '(((4 4) (5 4)) ((2 4) (3 4)) ((0 4) (1 4)) ((3 3) (4 3))
                  ((1 3) (2 3)) ((5 2) (5 3)) ((3 2) (4 2)) ((0 2) (0 3))
                  ((4 1) (5 1)) ((2 1) (2 2)) ((1 1) (1 2)) ((4 0) (5 0))
                  ((3 0) (3 1)) ((1 0) (2 0)) ((0 0) (0 1))))


(define B3 '((1 0 5 2 4 0 1 6)
             (0 2 0 3 4 1 5 4)
             (3 6 6 1 2 2 2 2)
             (5 5 6 6 3 1 3 6)
             (2 3 0 4 1 0 5 5)
             (3 1 5 4 6 4 4 0)
             (5 1 4 2 6 3 3 0)))

(define B4 '((3 6 5 2 4 0 0 3 8 7)
             (2 2 4 2 7 4 8 5 8 4)
             (0 5 4 6 1 1 6 2 8 8)
             (5 0 7 3 4 5 0 1 1 8)
             (5 1 8 7 1 7 4 6 3 6)
             (0 3 6 5 3 7 4 6 3 5)
             (3 1 8 3 0 8 6 6 2 7)
             (2 2 1 4 0 6 1 7 5 5)
             (0 1 7 8 7 2 4 3 0 2)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Define an auxiliary helper function for testing purposes.
;; You don't have to examine this section too closely, though
;; you should understand how to use the function below.

;; lists-equiv?: (listof X) (listof Y) (X Y -> boolean) -> boolean
;; Given two lists l1 and l2, determine whether the lists are essentially
;; the same up to reordering, where equivalence of individual elements
;; from the two lists is given from a passed-in predicate.  This function
;; will work as long as one of the two lists contains no duplicates.

;; Examples:
(check-expect (lists-equiv? '(1 2 3) '("2" "3" "1") 
                            (lambda (x y) (string=? (number->string x) y)))
              true)
(check-expect (lists-equiv? '(1 2 3 4) '(2 3 4 5) =) false)

(define (lists-equiv? l1 l2 comp)
  ;; The approach is a bit sneaky, but very succinct.  Check that
  ;; every element of l1 appears somewhere in l2 (in terms of comp),
  ;; and that every elements of l2 appears somewhere in l1.
  (and (= (length l1) (length l2))
       (andmap (lambda (x1) (ormap (lambda (x2) (comp x1 x2)) l2)) l1)
       (andmap (lambda (x2) (ormap (lambda (x1) (comp x1 x2)) l1)) l2)))

;; Tests:
(check-expect (lists-equiv? '(1 2 3 4 5) '(5 2 4 1 3) =) true)
(check-expect (lists-equiv? '(1 5 10 15 20) '(21 16 9 4 0)
                            (lambda (x y) (< (abs (- x y)) 2))) true)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Here are the functions you need to write.

;is-used? (lisof int int) (listof pair) -> boolean
;; Given an (x,y) position in a dominosa board and a list of pairs
;; of positions, produce true if (x,y) is found anywhere in the list
;; of pairs of positions and false otherwise.

(define (is-used? pos pairs)      
  (cond [(empty? pairs) false]
        [(and (= (first pos) (first (first (first pairs))))
              (= (second pos) (second (first (first pairs))))) true]
        [else (is-used? pos (rest pairs))]))

(check-expect (is-used? '(0 3) '(((0 1) (1 0)) ((0 3) (3 0)))) true)
(check-expect (is-used? '(0 0) empty) false)
(check-expect (is-used? '(5 6) '(((1 2)(3 5))((3 4)(2 5))((6 3)(2 5))((2 7)(3 1)))) false)

;first-open int int (listof pair) -> (list int int)
;; Given the dimensions of a dominosa board and a list of pairs,
;; produce an (x,y) position in the board which is not currently
;; being used by any dominoes (i.e., for which is-used? produces
;; false), or false if all board cells are being used. 
(define (first-open width height pairs) 
  (first-open-gen (make-grid width height 0 0) pairs))

(define (first-open-gen list pairs)
  (cond [(empty? list) empty]
        [(not (is-used? (first list) pairs)) (first list)]
        [(is-used? (first list) pairs) (first-open-gen (rest list) pairs)]
        [else empty]))

(define (make-grid width height h w)
  (cond 
    [(= h height) empty]
    [(= w width) (make-grid width height (+ 1 h) 0)]
    [else (cons (list w h) (make-grid width height h (+ 1 w)))]))

(check-expect (first-open 1 1 '(((0 0)(0 0)))) empty)
(check-expect (first-open 5 5 empty) '(0 0))
(check-expect (first-open 1 1 empty) '(0 0))

;; Test indirectly that the resulting position is, in fact, open,
;; regardless of which position is actually returned.
(check-expect (is-used? 
               (first-open 2 3 '(((0 0) (0 1)) ((1 0) (1 1))))
               '(((0 0) (0 1)) ((1 0) (1 1)))) false)

(check-expect (is-used? 
               (first-open 5 5 '(((0 0) (0 1)) ((1 0) (1 1))))
               '(((0 0) (0 1)) ((1 0) (1 1)))) false)

(check-expect (is-used? 
               (first-open 4 5 '(((0 0) (0 1)) ((1 0) (1 1))))
               '(((0 0) (0 1)) ((1 0) (1 1)))) false)

;; Given a current dominosa configuration and two (x,y) positions
;; representing the adjacent squares in a single domino, determine
;; whether it would be legal to use these two squares as a new
;; domino.  Assume that pos is a legal position that's not being
;; used yet.
;; [Check that other-pos is also legal and unused, and
;; that the resulting domino is not already used somewhere else on
;; the board.]
(define (is-legal-pair? cfn pos other-pos) 
  (cond [(and (not (is-used? other-pos (config-pairs cfn)))
              (not (member (list pos other-pos) (config-pairs cfn))) 
              (and (< (second other-pos) (length (config-board cfn))) (< (first other-pos) (length (first (config-board cfn))))
                   (>= (second other-pos) 0) (>= (first other-pos) 0))) true]
        [else false]))


;(define (is-legal-pair? cfn pos other-pos)
;  (local [(define (generate-used-dominoes config)
;           (foldr (lambda (x y)(cons (check-domino (choose-domino (config-board cfn) (first x) (second x))) y))
;                  empty
;                  (config-pairs config)))]
;    
;    (cond [(and (not (member (check-domino (choose-domino (config-board cfn) pos other-pos)) (generate-used-dominoes cfn)))
;                (and (< (second other-pos) (length (config-board cfn))) (< (first other-pos) (length (first (config-board cfn))))
;                (>= (second other-pos) 0) (>= (first other-pos) 0)))
;                (not (is-used? other-pos (config-pairs cfn)))]
;          )
;    )
;  )


(check-expect (is-legal-pair?
               (make-config B0 
                            '(((0 0) (0 1)) ((1 0) (1 1)))
                            '((1 1)))
               '(2 1) '(2 0)) true)

(check-expect (is-legal-pair?
               (make-config B0 
                            '(((0 0) (0 1)) ((1 0) (1 1)))
                            '((1 1)))
               '(2 1) '(2 2)) false)

(check-expect (is-legal-pair?
               (make-config B0 
                            '(((0 0) (0 1)) ((1 0) (1 1)))
                            '((1 1)))
               '(2 1) '(1 1)) true)

(check-expect (is-legal-pair?
               (make-config B0 
                            '(((0 0) (0 1)) ((1 0) (1 1)))
                            '((1 1)))
               '(2 1) '(3 1)) false)

(check-expect (is-legal-pair?
               (make-config B0 
                            '(((0 0) (0 1)) ((1 0) (1 1)))
                            '((1 1)))
               '(2 0) '(2 1)) true)



;; Given a current dominosa configuration, find a set of adjacent
;; configurations for recursive exploration.  
;; [Find the first square on the
;; board that doesn't belong to any domino.  Generate the coordinates
;; of the four adjacents of that square to the north, south, west
;; and east.  This function should produce the subset of those
;; adjacents that are considered legal pairs above.]
(define (neighbours cfn) 
  (filter (lambda (x) (not (empty? x)))
          (list (direction-chooser 'north cfn (get-first-space cfn))
                (direction-chooser 'east cfn (get-first-space cfn))
                (direction-chooser 'south cfn (get-first-space cfn))
                (direction-chooser 'west cfn (get-first-space cfn)))))

(define (get-first-space cfn)  
  (first-open (length (first(config-board cfn))) (length (config-board cfn)) (config-pairs cfn))) ;gets the first space not covered (2,1)

(define (direction-chooser direction cfn space)
  (cond [(symbol=? direction 'north) (config-maker space (list (first space) (- (second space) 1)) cfn)] ;2,0
        [(symbol=? direction 'south) (config-maker space (list (first space) (+ (second space) 1)) cfn)] ;2,2
        [(symbol=? direction 'east)  (config-maker space (list (- (first space) 1) (second space)) cfn)] ;1,1
        [(symbol=? direction 'west) (config-maker space  (list (+ (first space) 1) (second space)) cfn)])) ;3,1


(define (config-maker space dir-space cfn)
  (cond [(not (is-legal-pair? cfn space dir-space)) empty]
        [(empty? (config-pairs cfn)) (make-config (config-board cfn) (list (list space dir-space)) 
                                                  (remove (check-domino (choose-domino (config-board cfn) space dir-space)) (config-free cfn)))]
        
        [else (make-config (config-board cfn) (append (list (list space dir-space)) (config-pairs cfn)) 
                           (remove (check-domino (choose-domino (config-board cfn) space dir-space)) (config-free cfn)))]))

(define (choose-domino board space dir-space)
  (local 
    [(define (find-domino board h w)
       (cond [(= 0 h) (find-domino (first board) -1 w)] 
             [(> h 0) (find-domino (rest board) (sub1 h) w)]
             [(= 0 w) (first board)]
             [else (find-domino (rest board) -1 (sub1 w))]))]
    
    (list (find-domino board (second space) (first space)) (find-domino board (second dir-space) (first dir-space)))))

(define (check-domino domino)
  (cond [(> (first domino) (second domino)) (list (second domino) (first domino))]
        [else domino]))


(check-expect (neighbours
               (make-config B0 
                            '(((0 0) (0 1)) ((1 0) (1 1)))
                            '((1 1))))
              (list
               (make-config B0
                            '(((2 0) (2 1)) ((0 0) (0 1)) ((1 0) (1 1)))
                            empty)))

;; Construct a complete set of double-n dominoes.
;; [You must solve this
;; question using two nested calls to the abstract list function
;; build-list (see the help desk documentation if you need more
;; information about this function).]
(define (make-double-n n)
  (foldr append empty (build-list (+ 1 n) (lambda (x) (build-list (- (+ 1 n) x) (lambda (y) (list x (+ x y))))))))


(check-expect (lists-equiv? (make-double-n 2)
                            '((0 0) (0 1) (0 2) (1 1) (1 2) (2 2)) equal?)
              true)




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; solve-dominosa: board -> (union (listof pair) false)

;; Solve a dominosa puzzle, given the initial board.  Use
;; the recursive graph-searching methodology presented in
;; Module 10.  The code is similar, but not identical, to
;; find-route and find-route/list on Slides 58 and 59 of
;; the handout.  You shouldn't need to modify this function;
;; if you correctly implement neighbours above, this function
;; will do the right thing with it.

;; Examples: 
;; [use list-equiv? to permit flexibility.  This way, if your
;; code produces the correct result in a different order than
;; mine, we'll still consider it to be correct.]
(check-expect (solve-dominosa '((0 1))) false)
;; The nested use of lists-equiv? allows the pairs to be
;; reordered arbitrarily, and the two positions to be reordered
;; within each pair.
(check-expect 
 (lists-equiv? (solve-dominosa B0) B0-soln
               (lambda (x y) (lists-equiv? x y equal?))) true)

(define (solve-dominosa board)
  (local
    [;; find-route: config -> (union (listof pair) false)
     ;; Search outward from this configuration to see if
     ;; there's a path to a solution.
     (define (find-route cfn)
       (cond
         [(empty? (config-free cfn)) (config-pairs cfn)]
         [else (find-route/list (neighbours cfn))]))
     
     ;; find-route/list: (listof config) -> (union (listof pair) false)
     ;; Search outward from this list of configurations
     ;; to see if any one of them leads to a solution.
     ;; Stop as soon as a solution is found, or produce
     ;; false if you run out of options.
     (define (find-route/list loc)
       (cond
         [(empty? loc) false]
         [else
          (local
            [(define r (find-route (first loc)))]
            (cond
              [(cons? r) r]
              [else (find-route/list (rest loc))]))]))]
    (find-route (make-config board
                             empty 
                             (make-double-n (sub1 (length board)))))))

;; Tests:

(check-expect 
 (lists-equiv? (solve-dominosa B1) B1-soln
               (lambda (x y) (lists-equiv? x y equal?))) true)
(check-expect 
 (lists-equiv? (solve-dominosa B2) B2-soln
               (lambda (x y) (lists-equiv? x y equal?))) true)
(check-expect (solve-dominosa '((3 3 3 3) (3 3 3 3) (3 3 3 3))) false)
