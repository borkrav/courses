;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname poem) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
; a line is either
; * (cons n empty) where n is a string
; * (cons n nelos) where nelos is a non-empty list of strings

;A poem is either: 
;* empty
;* (cons l p) where l is a line and p is a poem

;;my-line-fn: line -> any
;(define (my-line-fn line)
;  (cond [(empty? (rest line))...]
;        [else (first line)...
;              ...(my-line-fn (rest line))...]))

;;my-poem-fn: poem -> any
;(define (my-poem-fn poem)
;  (cond [(empty? poem)...]
;        [else (my-line-fn (first poem)) ...
;              ...(my-poem-fn (rest poem))...]))


;count-syllables line -> nat
;a function that takes in a line and produces the number of syllables it contains
;example
(check-expect (count-syllables (cons "a" empty)) 1)
(check-expect (count-syllables (cons "a" (cons "b" empty))) 2)

(define (count-syllables line)
  (cond [(empty? (rest line)) 1]
        [else (+ 1 (count-syllables (rest line)))]))

;tests
(check-expect (count-syllables (cons "aa" (cons "bb" (cons "cc" (cons "dd" (cons "ee" (cons "ff" (cons "gg" empty)))))))) 7)
(check-expect (count-syllables (cons "aa" empty)) 1)

;syllabic-structure: poem -> listof nat
;a function that takes in a poem and returns how many syllables are in each line
;examples
(check-expect (syllabic-structure (list (list "a" "b") (list "c" "d") (list "e" "f"))) (list 2 2 2))
(check-expect (syllabic-structure (list (list "To" "fig-" "ure" "the" "inch-" "es" "you’ve" "run,")
                                        (list "Or" "to" "find" "the" "slug" "mass" "of" "the" "sun,")
                                        (list "For-" "get" "your" "a-" "ver-" "sion") 
                                        (list "To" "u-" "nit" "con-" "ver-" "sion.") 
                                        (list "Just" "mul-" "ti-" "ply" "(wise-" "ly!)" "by" "1."))) 
              (list 8 9 6 6 8))

(define (syllabic-structure poem)
  (cond [(empty? poem) empty]
        [else (cons (count-syllables (first poem)) (syllabic-structure (rest poem)))]))

;tests
(check-expect (syllabic-structure (list)) (list))
(check-expect (syllabic-structure (list (list "aa") (list "bb") (list "cc") (list "gg" "qq"))) (list 1 1 1 2))

;length-of-list: listof any -> nat
;a function that determines the length of any given list
;examples
(check-expect (length-of-list (list 2 3 4 5 6)) 5)
(check-expect (length-of-list (list)) 0)

(define (length-of-list list)
  (cond [(empty? list ) 0]
        [else (+ 1 (length-of-list (rest list)))]))

;tests
(check-expect (length-of-list (list 1 2 3 4 5 6 7 8 9 10)) 10)
(check-expect (length-of-list (list (list) (list) (list))) 3)
(check-expect (length-of-list (list "A")) 1)



;has-limerick-syllables?: poem -> boolean
;a function that takes in a poem and checks whether or not it has the syllabic structure of a limerick
;examples
(check-expect (has-limerick-syllables? (list (list "To" "fig-" "ure" "the" "inch-" "es" "you’ve" "run,")
                                             (list "Or" "to" "find" "the" "slug" "mass" "of" "the" "sun,")
                                             (list "For-" "get" "your" "a-" "ver-" "sion") 
                                             (list "To" "u-" "nit" "con-" "ver-" "sion.") 
                                             (list "Just" "mul-" "ti-" "ply" "(wise-" "ly!)" "by" "1.")))
              true)
(check-expect (has-limerick-syllables? (list (list "a" "b") (list "c" "d") (list "e" "f"))) false)

(define (has-limerick-syllables? input-poem)
  (cond [(and (= 5 (length-of-list (syllabic-structure input-poem)))
              (or (= 8 (first (syllabic-structure input-poem)))
                  (= 9 (first (syllabic-structure input-poem))))
              (or (= 8 (second (syllabic-structure input-poem)))
                  (= 9 (second (syllabic-structure input-poem))))
              (or (= 5 (third (syllabic-structure input-poem)))
                  (= 6 (third (syllabic-structure input-poem))))
              (or (= 5 (fourth (syllabic-structure input-poem)))
                  (= 6 (fourth (syllabic-structure input-poem))))
              (or (= 8 (fifth (syllabic-structure input-poem)))
                  (= 9 (fifth (syllabic-structure input-poem))))) true]
        [else false]))

;tests
(check-expect (has-limerick-syllables? (list (list "1" "2" "3" "4" "5" "6" "7" "8") 
                                             (list "1" "2" "3" "4" "5" "6" "7" "8")
                                             (list "1" "2" "3" "4" "5")
                                             (list "1" "2" "3" "4" "5")
                                             (list "1" "2" "3" "4" "5" "6" "7" "8")))
              true)

(check-expect (has-limerick-syllables? (list (list "1" "2" "3" "4" "5" "6" "7" "8" "9") 
                                             (list "1" "2" "3" "4" "5" "6" "7" "8" "9")
                                             (list "1" "2" "3" "4" "5" "6")
                                             (list "1" "2" "3" "4" "5" "6")
                                             (list "1" "2" "3" "4" "5" "6" "7" "8" "9")))
              true)


(check-expect (has-limerick-syllables? (list (list "1" "2" "3" "4" "5" "6" "7" "8" "9") 
                                             (list "1" "2" "3" "4" "5" "6" "7" "8" "9")
                                             (list "1" "2" "3" "4" "5" "6" "7" "8" "9")))
              false)

(check-expect (has-limerick-syllables? (list))
              false)


;poem->string: poem -> string
;a function that takes in a poem and returns it in string form
;examples 
(check-expect (poem->string (list (list "To" "fig-" "ure" "the" "inch-" "es" "you’ve" "run,")
                                  (list "Or" "to" "find" "the" "slug" "mass" "of" "the" "sun,")
                                  (list "For-" "get" "your" "a-" "ver-" "sion") 
                                  (list "To" "u-" "nit" "con-" "ver-" "sion.") 
                                  (list "Just" "mul-" "ti-" "ply" "(wise-" "ly!)" "by" "1.")))
              "To figure the inches you’ve run, \nOr to find the slug mass of the sun, \nForget your aversion \nTo unit conversion. \nJust multiply (wisely!) by 1. \n")

(check-expect (poem->string (list (list "a" "b") (list "c" "d") (list "e" "f"))) "a b \nc d \ne f \n")

(define (poem->string poem)
  (cond [(empty? poem) ""]
        [else (string-append (convert-line (first poem)) " \n" (poem->string (rest poem)))]))

;tests
(check-expect (poem->string (list (list "1" "2-" "3" "4-" "5" "6-" "7" "8-" "9") 
                                  (list "1-" "2" "3-" "4" "5-" "6" "7-" "8" "9")
                                  (list "1" "2-" "3-" "4-" "5" "6-" "7" "8" "9")))
              "1 23 45 67 89 \n12 34 56 78 9 \n1 2345 67 8 9 \n")

(check-expect (poem->string (list)) "")


;convert-line: line -> string
;a function that takes in a line and returns it in string form
;examples
(check-expect (convert-line (list "To" "fig-" "ure" "the" "inch-" "es" "you’ve" "run,")) "To figure the inches you’ve run,")
(check-expect (convert-line (list "a" "b")) "a b")

(define (convert-line line-input)
  (cond [(empty? (rest line-input)) (first line-input)]
        [else (cond [(hyphen-checker (string->list (first line-input))) 
                     (string-append (list->string (convert-word (string->list (first line-input)))) (convert-line (rest line-input)))]
                    
                    [else (string-append (first line-input) " " (convert-line (rest line-input)))])
              ]
        )
  )

;tests
(check-expect (convert-line (list "a-" "b-" "c-" "d-" "e-" "f-")) "abcdef-")
(check-expect (convert-line (list "a" "b" "c" "d-" "e-" "f")) "a b c def")
(check-expect (convert-line (list "a")) "a")



;word-input: listof char -> listof char
;a function that takes in a list of char, removes the "-", and returns the list of char
;examples
(check-expect (convert-word (string->list "Hi-")) (string->list "Hi"))

(define (convert-word word-input)
  (cond [(empty? word-input) empty ]
        [(char=? #\- (first word-input)) empty ]
        [else (cons (first word-input) (convert-word (rest word-input)))]))

;tests
(check-expect (convert-word (string->list "aa-")) (string->list "aa"))
(check-expect (convert-word (list)) empty)



;word-input: listof char -> boolean
;a function that takes in a list of char, returns true if there is a hyphen
;examples
(check-expect (hyphen-checker (string->list "Hi-")) true)

(define (hyphen-checker word-input)
  (cond [(empty? word-input) false ]
        [(char=? #\- (first word-input)) true ]
        [else (hyphen-checker (rest word-input))]))

(check-expect (hyphen-checker (string->list "aaaaa-")) true)
(check-expect (hyphen-checker (string->list "aaaaa")) false)
(check-expect (hyphen-checker (list)) false)



