;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-lambda-reader.ss" "lang")((modname xml) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Skeleton code for A10Q1.  Replace this with your own header, and
;; fill in the relevant fragments of code and functions below.
;;

(define-struct stag (name attrs))
(define-struct etag (name))

;; An attribute is of the form (list n t), where n and t are strings.
;; A start-tag is (make-stag n a), where n in a string and a is a
;;   (listof attribute).
;; An end-tag is (make-etag n), where n is a string.
;; A tag is a start-tag or an end-tag.

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Basic helper functions to extract tokens from a list of characters,
;; inspired by the code on Slides 35 and 36 of Module 10.  
;;

;; get-token-until: (char -> boolean) (listof char) -> (listof char)
;; Produce the prefix of the passed-in list of characters consisting
;; of all characters up to but not including the first one which
;; satisfies the predicate break?.  Assume that we will find a
;; character that satisfies the predicate before we run out of list.

;; Examples:
;(check-expect (get-token-until char-alphabetic? '(#\a #\1 #\2)) empty)
;(check-expect (get-token-until char-alphabetic? '(#\1 #\a #\b #\2 #\3 #\4)) '(#\1))

(define (get-token-until break? a-chl)
  (cond
    [(break? (first a-chl)) empty]
    [else (cons (first a-chl) (get-token-until break? (rest a-chl)))]))

;; Tests:
;(check-expect (get-token-until char-alphabetic? '(#\1 #\2 #\a #\b #\3 #\4 #\c)) '(#\1 #\2))

;; remove-token-while: (char -> boolean) (listof char) -> (listof char)
;; Produce the suffix of the passed-in list consisting of all
;; characters beginning with the first one which does not satisfy
;; the predicate while?.  (This is slightly different from 
;; remove-token in the notes, which produces the suffix starting
;; *after* the first character that satisfies the predicate.)

;; Examples:
;(check-expect (remove-token-while char-alphabetic? '(#\a #\1 #\2)) '(#\1 #\2))
;(check-expect (remove-token-while char-alphabetic? '(#\1 #\a)) '(#\1 #\a))

(define (remove-token-while while? a-chl)
  (cond
    [(empty? a-chl) empty]
    [(while? (first a-chl)) (remove-token-while while? (rest a-chl))]
    [else a-chl]))

; Tests:
;(check-expect (remove-token-while char-alphabetic? '(#\a #\b #\c #\1 #\d #\2)) '(#\1 #\d #\2))
;(check-expect (remove-token-while char-alphabetic? '(#\a #\b #\c)) empty)


;get-token-after (char->boolean) (listof char) -> (listof char)
;a function that pruduces all charecters after to the chareter that satisfies the predicate
;examples
(check-expect (get-token-after char-alphabetic? (list #\1 #\r #\2)) (list #\2))

(define (get-token-after break? a-chl)
  (cond
    [(empty? a-chl) empty]
    [(break? (first a-chl)) (rest a-chl)]
    [else (get-token-after break? (rest a-chl))]))

;tests
(check-expect (get-token-after char-alphabetic? (list #\1 #\5 #\2)) empty)


;; parse-tag-loc: (listof char) -> (union stag etag)
;; a function that takes in a list of charecters and parses an XML start tag or end tag
;; Examples:
(check-expect (parse-tag-loc (list #\< #\a #\>)) (make-stag "a" empty))

(define (parse-tag-loc loc)
  (cond [(empty? loc) empty]
        [else 
         
         ((lambda (token)
            (cond [(empty? token) empty]
                  [(char=? (first token) #\/) (make-etag (list->string (rest token)))]  
                  [else (make-stag (list->string token) empty)]
                  ))
          
          (filter (lambda (y) (not (char=? #\space y)))
                  (get-token-after (lambda (x) (char=? x #\<))
                                   (get-token-until (lambda (x) (char=? x #\>)) loc))
                  ))]))

;tests
(check-expect (parse-tag-loc (string->list "</xml>")) (make-etag "xml"))
(check-expect (parse-tag-loc (string->list "<          c          >")) (make-stag "c" empty))
(check-expect (parse-tag-loc (string->list "<     /69        >")) (make-etag "69"))
(check-expect (parse-tag-loc empty) empty)

;; parse-tag: string -> tag
;; Consume the first XML tag found in the input string and return it
;; as a tag according to the data definition above.

;; Examples:
(check-expect (parse-tag "<a>") (make-stag "a" empty))

(define (parse-tag s)
  (parse-tag-loc (string->list s)))




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; There's no specific work for you to do with these next two functions.
;; These functions serve two purposes.  The function get-all-tags calls
;; parse-tag-loc above, and you should ensure that your implementation 
;; of parse-tag-loc is compatible with get-all-tags (that is, the tests
;; for get-all-tags should work).  The function parse-xml is mainly useful
;; to you in the solution to 1(b), since it makes it easy to generate
;; interested test cases for balanced-tags?.
;;

;; get-all-tags: (listof char) -> (listof tag)
;; Given a full XML document represented as a list of characters,
;; produce the associated list of XML tags.  You must make sure
;; that your parse-tag-loc function above is compatible with this
;; function in the sense that these tests pass.

;; Examples:
(check-expect (get-all-tags empty) empty)
(check-expect (get-all-tags (string->list "<a><b></b><c></c><d>"))
              (list (make-stag "a" empty)
                    (make-stag "b" empty)
                    (make-etag "b")
                    (make-stag "c" empty)
                    (make-etag "c")
                    (make-stag "d" empty)))

(define (get-all-tags loc)
  (local
    [(define start 
       (remove-token-while 
        (lambda (c) (not (char=? c #\<))) loc))]
    (cond
      [(empty? start) empty]
      [else (cons (parse-tag-loc start)
                  (get-all-tags 
                   (rest (remove-token-while 
                          (lambda (c) (not (char=? c #\>))) start))))])))

;; Tests:
(check-expect (get-all-tags (string->list "  <  a  >     <   /a    >  "))
              (list (make-stag "a" empty)
                    (make-etag "a")))
(check-expect (get-all-tags (string->list "</a></a></a><bbb><cccccc>"))
              (list (make-etag "a") (make-etag "a") (make-etag "a")
                    (make-stag "bbb" empty) (make-stag "cccccc" empty)))

;; parse-xml: string -> (listof tag)
;; Given a full XML document represented as a string,
;; produce the associated list of XML tags.

;; Examples:
(check-expect (parse-xml "") empty)
(check-expect (parse-xml "<a><b></b><c></c><d>")
              (list (make-stag "a" empty)
                    (make-stag "b" empty)
                    (make-etag "b")
                    (make-stag "c" empty)
                    (make-etag "c")
                    (make-stag "d" empty)))

(define (parse-xml s)
  (get-all-tags (string->list s)))

;; Tests:
;; Examples are adequate here.  The main testing will be done in
;; get-all-tags.

;; balanced-tags?: (listof (union etags stags)) -> boolean
;; a function that takes in a list of tags and checks if the tags are properly nested

;; Examples:
(check-expect (balanced-tags? (list (make-stag "a" empty) (make-stag "b" empty) (make-etag "b") (make-etag "a"))) true)

(define (balanced-tags? lot) 
  (cond [(empty? lot) true]
        [(and (stag? (first lot)) (etag? (first (reverse lot)))
              (string=? (stag-name (first lot)) (etag-name (first (reverse lot)))))
        (balanced-tags? (reverse (rest (reverse (rest lot)))))]
        [else false]
        
        
        ))

;tests
(check-expect (balanced-tags? (list (make-stag "c" empty) (make-stag "d" empty) (make-etag "d") (make-etag "c"))) true)
(check-expect (balanced-tags? empty) true)
(check-expect (balanced-tags? (list (make-etag "a")(make-etag "b")(make-etag "c")(make-etag "d")(make-etag "e"))) false)
(check-expect (balanced-tags? (list (make-etag "c" ) (make-etag "d" ) (make-stag "d" empty) (make-stag "c" empty))) false)
