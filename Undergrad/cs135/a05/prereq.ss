;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname prereq) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
;a course is
; * n, where n is a symbol

;a grade is
; * n, where n is an integer in the range of [0, 100]

;a course-record is a structure (make-course-record course grade), where
; * course is a symbol
; * grade is an integer in the range of [0, 100]
;(define-struct course-record (couse grade)) creates:
; * constructor make-course-record
; * selectors course-record-couse and course-record-grade
; * type predicate course-record?

(define-struct course-record (course grade))

;;my-course-record-fn: course-record -> any
;(define (my-course-record-fn record)
;  ... (course-record-course record) ...
;  ... (course-record-grade record) ...)

;a prereq is a structure (make-prereq course prereq-course min-grade), where
; * course is a symbol
; * prereq-course is a symbol
; * min-grade is an integer in the range of [0, 100]
; (define-struct prereq (course prereq-course min-grade)) creates:
; * constructor make-prereq
; * selectors prereq-course, prereq-prereq-course, prereq-min-grade
; * type predicate prereq?

(define-struct prereq (course prereq-course min-grade))

;;my-prereq-fn: prereq -> any
;(define (my-prereq-fn course)
;  ... (prereq-course course) ...
;  ... (prereq-prereq-course course) ...
;  ... (prereq-min-grade course) ...

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; a prereqlist is 
; * empty
; * (cons n b) where n is a prereq, and b is a prereqlist

;;my-prereqlist-fn: prereqlist -> any
;(define (my-prereq-list-fn list)
;  (cond [(empty? list) ... ]
;        [else ... (first list) ...
;              ... (my-prereq-list-fn (rest list)) ... ]))

; a trascript is
; * empty
; * (cons n b) where n is a course-record and b is a transcript

;;my-transcript-fn: transcript -> any
;(define (my-transcript-fn list)
;  (cond [(empty? list) ... ]
;        [else ... (first list) ...
;              ... (my-trascript-fn (rest list)) ... ]))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


; stuff used for testing

;; a prereq-list used for testing
(define test-list (cons (make-prereq 'CS136 'CS135 60) 
                        (cons (make-prereq 'CS136 'CS100 80)
                              (cons (make-prereq 'CS341 'CS240 50)
                                    (cons (make-prereq 'CS341 'CS245 50) 
                                          (cons (make-prereq 'CS341 'MATH239 50)
                                                (cons (make-prereq 'CS900 'MATH900 100)
                                                      (cons (make-prereq 'MATH1000 'MATH999 99)
                                                            (cons (make-prereq 'MATH1000 'MATH998 99)
                                                                  (cons (make-prereq 'MATH1000 'MATH997 99)
                                                                        empty))))))))))

;; a transcript used for testing
(define test-tscript (cons (make-course-record 'CS100 100) 
                           (cons (make-course-record 'CS135 100) 
                                 (cons (make-course-record 'CS240 100) 
                                       (cons (make-course-record 'CS245 100) 
                                             (cons (make-course-record 'MATH239 100)
                                                   (cons (make-course-record 'MATH900 99)
                                                         empty)))))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;list-prereqs: course prereqlist -> prereqlist
;a function that takes in a course and a prereqlist and outputs another prereqlist, for the course given
;examples
(check-expect (list-prereqs 'CS341 test-list)
              (cons (make-prereq 'CS341 'CS240 50)
                    (cons (make-prereq 'CS341 'CS245 50) 
                          (cons (make-prereq 'CS341 'MATH239 50)
                                empty))))


(define (list-prereqs course list)
  (cond [(empty? list) empty]
        
        [(symbol=? course 
                   (prereq-course (first list))) 
         (cons (first list) 
               (list-prereqs course (rest list)))]
        
        [else (list-prereqs course (rest list))]))

;tests
(check-expect (list-prereqs 'CS341 test-list) 
              (cons (make-prereq 'CS341 'CS240 50)
                    (cons (make-prereq 'CS341 'CS245 50) 
                          (cons (make-prereq 'CS341 'MATH239 50)
                                empty))))

(check-expect (list-prereqs 'CS136 test-list) 
              (cons (make-prereq 'CS136 'CS135 60) (cons (make-prereq 'CS136 'CS100 80) empty)))

(check-expect (list-prereqs 'CS100 test-list) empty)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;meets-prereqs: course prereq-list transcript -> boolean
; a function that takes in a course, a prereq-list and a transcript. It checks if the transcript has the required prerequisite values for a specific course, and outputs a boolean
;examples
(check-expect (meets-prereqs 'CS136 test-list test-tscript) true)

(define (meets-prereqs course list tscript)
  (cond [(empty? (list-prereqs course list)) true]
        
        [(not (<= (prereq-min-grade (first (list-prereqs course list)))
                  (mark-finder (prereq-prereq-course (first (list-prereqs course list))) tscript)))
         false]
        
        [else (meets-prereqs course (rest (list-prereqs course list)) tscript)]))

;tests
(check-expect (meets-prereqs 'CS341 test-list test-tscript) true)
(check-expect (meets-prereqs 'CS900 test-list test-tscript) false)


;mark-finder: course transcript -> grade
; a function that takes in a course and a transcript and returns the grade for that course. If the course is not on the trascript, a mark of zero is returned
;examples
(check-expect (mark-finder 'CS100 test-tscript) 100)

(define (mark-finder course-name tscript)
  (cond [(empty? tscript) 0]
        [(symbol=? course-name (course-record-course (first tscript))) (course-record-grade (first tscript))] 
        [else (mark-finder course-name (rest tscript))]))

;tests
(check-expect (mark-finder 'MATH900 test-tscript) 99)
(check-expect (mark-finder 'CS135 test-tscript) 100)
(check-expect (mark-finder 'MATH239 test-tscript) 100)
(check-expect (mark-finder 'AAAA666 test-tscript) 0)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;missing-prereqs: course prereqlist transcript -> listof courses
; a function that takes in a course, a prereq-list and a transcript. It checks if the transcript has the required prerequisite values for a specific course, and outputs a listof courses that contains all the missing courses

;examples
(check-expect (missing-prereqs 'CS136 test-list test-tscript) empty)
(check-expect (missing-prereqs 'CS341 test-list test-tscript) empty)


(define (missing-prereqs course list tscript)
  (cond [(empty? (list-prereqs course list)) empty]
        
        [(not (<= (prereq-min-grade (first (list-prereqs course list))) 
                  (mark-finder (prereq-prereq-course (first (list-prereqs course list))) tscript))) 
         (cons (prereq-prereq-course (first (list-prereqs course list))) 
               (missing-prereqs course (rest (list-prereqs course list)) tscript))]
        
        [else (missing-prereqs course (rest (list-prereqs course list)) tscript)]))

;tests
(check-expect (missing-prereqs 'CS900 test-list test-tscript) (cons 'MATH900 empty))
(check-expect (missing-prereqs 'MATH1000 test-list test-tscript) (cons 'MATH999 (cons 'MATH998 (cons 'MATH997 empty))))
(check-expect (missing-prereqs 'CS136 test-list test-tscript) empty)
(check-expect (missing-prereqs 'CS341 test-list test-tscript) empty)
