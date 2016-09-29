;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-lambda-reader.ss" "lang")((modname inorder) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
(define-struct node (key val left right))

(define a-tree (make-node 5 "a"
                          (make-node 3 "b"
                                     (make-node 1 "d" empty empty)
                                     (make-node 4 "e" empty empty))
                          (make-node 7 "c" 
                                     (make-node 6 "f" empty empty)
                                     (make-node 9 "g" empty empty)
                                     )
                          ))

(define test-tree (make-node 5 "am" 
                             (make-node 3 "" 
                                        (make-node 2 "I" empty empty)
                                        empty)
                             (make-node 8 "ready." empty empty)))

;values-inorder: bst -> string
;a function that takes in a binary search tree and does an inorder traversal of the tree, outputting the values in an appeneded string
;examples
(check-expect (values-inorder a-tree) "d b e a f c g")

(define (values-inorder tree)
  
  (cond  
    [(empty? tree) ""]
    [(and (empty? (node-left tree)) (empty? (node-right tree))) (node-val tree)]
    
    [(and (empty? (node-left tree)) (not(empty? (node-right tree)))) 
     
     (string-append 
      (node-val tree)
      " "
      (values-inorder (node-right tree)))]
    
    [(and (not (empty? (node-left tree))) (empty? (node-right tree))) 
     
     (string-append 
      (values-inorder (node-left tree))
      " "
      (node-val tree))]
    
    [else (string-append 
           (values-inorder (node-left tree))
           " "
           (node-val tree)
           " "
           (values-inorder (node-right tree)))]))


(check-expect (values-inorder a-tree) "d b e a f c g")
(check-expect (values-inorder test-tree) "I am ready.")


