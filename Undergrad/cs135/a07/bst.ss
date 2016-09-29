;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname bst) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
(define-struct node (key val left right))

(define a-tree (make-node 5 'a 
                          (make-node 3 'b 
                                     (make-node 1 'd empty empty)
                                     (make-node 4 'e empty empty))
                          (make-node 7 'c 
                                     (make-node 6 'f empty empty)
                                     (make-node 9 'g empty empty)
                                     )
                          ))

(define b-tree (make-node 5 'a 
                          (make-node 3 'b 
                                     (make-node 1 'd empty empty)
                                     empty)
                          (make-node 7 'c 
                                     empty
                                     (make-node 6 'f empty empty))
                          ))



;follow-directions: bst (listof symbols) -> any
;a function that takes in a binary search tree and a list of directions, traverses the tree using the directons and returns the value in the resulting node
;examples
(check-expect (follow-directions a-tree '(right right)) 'g)
(check-expect (follow-directions a-tree '(left left)) 'd)

(define (follow-directions tree directions)
  (cond  [(empty? tree) empty]
         [(empty? directions) (node-val tree)]
         [(symbol=? 'left (first directions)) (follow-directions (node-left tree) (rest directions))]
         [(symbol=? 'right (first directions)) (follow-directions (node-right tree) (rest directions))]
         )
  )

;tests
(check-expect (follow-directions a-tree '(right left)) 'f)
(check-expect (follow-directions empty '(right left)) empty)

;get-directions bst nat -> (listof symbols)
;a function that takes in a binary search tree and a key, traverses the tree to find the node, and returns the set of directions that were followed
;examples
(check-expect (get-directions a-tree 9) '(right right))
(check-expect (get-directions a-tree 10) 'NotFound)

(define (get-directions tree key)
  (cond[(member 'NotFound (get-directions-list tree key)) 'NotFound]
       [else (get-directions-list tree key)]
       )
  )

;tests
(check-expect (get-directions empty 5) 'NotFound)
(check-expect (get-directions b-tree 0) 'NotFound)

;get-directions-list: bst nat -> (listof symbols)
;a function that takes in a binary search tree and returns a raw direction list, with a 'NotFound appended to the end if the node was never found
;examples
(check-expect (get-directions-list a-tree 9) '(right right))
(check-expect (get-directions-list a-tree 10) '(right right NotFound))

(define (get-directions-list tree key)
  (cond [(empty? tree) (cons 'NotFound empty)] 
        [(= (node-key tree) key) empty]
        [(and (empty? (node-left tree)) (empty? (node-right tree))) (cons 'NotFound empty)]
        [(> (node-key tree) key) (cons 'left (get-directions-list (node-left tree) key))]
        [(< (node-key tree) key) (cons 'right (get-directions-list (node-right tree) key))]
        )
  )

;tests
(check-expect (get-directions-list empty 5) '(NotFound))
(check-expect (get-directions-list b-tree 0) '(left left NotFound))


;no-only-children?: bst -> boolean
;a function that takes in a binary search tree and returns true if the tree does not contain any only children
;examples
(check-expect (no-only-children? a-tree) true)
(check-expect (no-only-children? b-tree) false)

(define (no-only-children? tree)
  (cond [(empty? tree) false]
        [(and (empty? (node-left tree)) (empty? (node-right tree))) true]
        [(or (and (empty? (node-left tree)) (not (empty? (node-right tree))))
             (and (empty? (node-right tree)) (not (empty? (node-left tree))))) false]
        [else (and (no-only-children? (node-left tree))
                   (no-only-children? (node-right tree)))]
        )
  )

;tests
(check-expect (no-only-children? a-tree) true)
(check-expect (no-only-children? b-tree) false)
(check-expect (no-only-children? empty) false)


;update-value: bst nat any -> bst
;a function that takes in a binary search tree, a key and a value, and updates the node with that key with the new value. If the key is not in the tree, a unmodified tree is returned
;examples
(check-expect (update-value a-tree 9 'new) 
              (make-node 5 'a 
                         (make-node 3 'b 
                                    (make-node 1 'd empty empty)
                                    (make-node 4 'e empty empty))
                         (make-node 7 'c 
                                    (make-node 6 'f empty empty)
                                    (make-node 9 'new empty empty)
                                    )
                         ))

(check-expect (update-value a-tree 10 'new) a-tree)

(define (update-value tree key value)
  (cond [(empty? tree) empty]
        [(= (node-key tree) key) (make-node key value (update-value (node-left tree) key value) (update-value (node-right tree) key value))]
        [else (make-node (node-key tree) (node-val tree) (update-value (node-left tree) key value) (update-value (node-right tree) key value))]
        )
  )

;tests
(check-expect (update-value a-tree 9 'new) 
              (make-node 5 'a 
                         (make-node 3 'b 
                                    (make-node 1 'd empty empty)
                                    (make-node 4 'e empty empty))
                         (make-node 7 'c 
                                    (make-node 6 'f empty empty)
                                    (make-node 9 'new empty empty)
                                    )
                         ))

(check-expect (update-value a-tree 10 'new) a-tree)
(check-expect (update-value empty 5 'new) empty)
(check-expect (update-value (make-node 5 'a empty empty) 5 'new) (make-node 5 'new empty empty))


;get-shortest-path: bst nat nat -> (listof nat)         
;a function that takes in a binary search tree and 2 key values, and outputs the sequence of keys for the shortest path between those two keys.
;examples
(check-expect (get-shortest-path a-tree 4 9) '(4 3 5 7 9))

(define (get-shortest-path tree key-1 key-2)
  (make-path (get-path tree key-1) (get-path tree key-2) (find-fork (get-path tree key-1) (get-path tree key-2) 0)))

(check-expect (get-shortest-path a-tree 9 9) '(9))
(check-expect (get-shortest-path empty 5 5) '(0))

(check-expect (get-shortest-path (make-node 64 "sadf"(make-node 59  "gergae" (make-node "grgaeh" 35 empty empty)(make-node "hssdfg" 61 empty empty))(make-node 77 "grgsgr" (make-node 69 "jrdjt" (make-node 65 "asdw" empty empty)(make-node 75 "wasd" empty empty)) (make-node 80  "daws" empty (make-node 99 "asdwa" empty empty))))  99 65) (list 99 80 77 69 65))

(check-expect (get-shortest-path (make-node 64 "sadf"(make-node 59  "gergae" (make-node "grgaeh" 35 empty empty)(make-node "hssdfg" 61 empty empty))(make-node 77 "grgsgr" (make-node 69 "jrdjt" (make-node 65 "asdw" empty empty)(make-node 75 "wasd" empty empty)) (make-node 80  "daws" empty (make-node 99 "asdwa" empty empty))))  99 64) (list 99 80 77 64))


;get-path: bst nat -> (listof nat)
;a function that takes in a binary search tree and a key, and outputs all the keys between the root and the destination key
;examples
(check-expect (get-path a-tree 4) '(5 3 4))
(check-expect (get-path a-tree 9) '(5 7 9))

(define (get-path tree key)
  (cond [(empty? tree) empty]
        [(= (node-key tree) key) (cons (node-key tree) empty)]
        [(> (node-key tree) key) (cons (node-key tree) (get-path (node-left tree) key))]
        [(< (node-key tree) key) (cons (node-key tree) (get-path (node-right tree) key))]
        )
  )

(check-expect (get-path a-tree 4) '(5 3 4))
(check-expect (get-path a-tree 9) '(5 7 9))
(check-expect (get-path empty 0) empty)


;find-fork: (listof nat) (listof nat) -> nat
;a function that takes in two key paths, and returns the key where the two paths branch off
;examples
(check-expect (find-fork '(5 3 4) '(5 7 9) 0) 5)

(define (find-fork path-1 path-2 n)
  (cond [(or (empty? path-1) (empty? path-2)) n] 
        [(= (first path-1) (first path-2)) (find-fork (rest path-1) (rest path-2) (first path-1))]
        [else (find-fork (rest path-1) (rest path-2) n)]
        )
  )

(check-expect (find-fork '(5 3 4) '(5 7 9) 0) 5)
(check-expect (find-fork '(5 3 4 10 15 16) '(5 3 4 10 15 17) 0) 15)
(check-expect (find-fork '(1) '(1) 0) 1)
(check-expect (find-fork '(1 2 3) '(4 5 6) 0) 0)

;make-path: (listof nat) (listof nat) nat -> (listof nat)
;a function that takes in two key paths and the fork key where the two paths branch off, and appends them together into one list of keys
;examples
(check-expect (make-path '(5 3 4) '(5 7 9) 5) '(4 3 5 7 9))

(define (make-path path1 path2 fork)
  (append (shorten-front-path fork (reverse path1))
          (list fork) 
          (shorten-back-path fork path2)
          )
  ) 

(check-expect (make-path '(5 3 4 10 15 16) '(5 3 4 10 15 17) 15) '(16 15 17))
(check-expect (make-path '(5 3 4) '(5 7 9) 5) '(4 3 5 7 9))

;shorten-back-path: nat (listof nat) -> (listof nat)
;a function that takes in the fork key and "to" list of keys, and cuts off everything before the fork key
;examples
(check-expect (shorten-back-path 5 '(5 7 9)) '(7 9))

(define (shorten-back-path n path)
  (cond [(empty? path) empty]
        [(= n (first path)) (rest path)]
        [else (shorten-back-path n (rest path))]
        )
  )

(check-expect (shorten-back-path 3 empty) empty)
(check-expect (shorten-back-path 3 '(5 7 9)) empty)
(check-expect (shorten-back-path 5 '(1 2 5 7 9)) '(7 9))


;shorten-front-path: nat (listof nat) -> (listof nat)
;a function that takes in the fork key and "from" list of keys, and cuts off everything after the fork key
;examples
(check-expect (shorten-front-path 5 '(4 3 5)) '(4 3))

(define (shorten-front-path n path)
  (cond [(empty? path) empty]
        [(= n (first path)) empty]
        [else (cons (first path)(shorten-front-path n (rest path)))]
        )
  )

(check-expect (shorten-front-path 3 empty) empty)
(check-expect (shorten-front-path 3 '(5 7 9)) '(5 7 9))
(check-expect (shorten-front-path 5 '(1 2 5 7 9)) '(1 2))