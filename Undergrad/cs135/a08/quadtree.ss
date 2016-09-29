;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-lambda-reader.ss" "lang")((modname quadtree) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
(define-struct quadnode (key val nw ne sw se))

;quadtree-add: posn string -> quadtree
;a function that takes in a position and a string and enters it as a new node inside the GPS quad tree.
;example
(check-expect (quadtree-add (make-posn 10 20) "aaa" (make-quadnode (make-posn 0 0) "origin" empty empty empty empty))
              (make-quadnode (make-posn 0 0) "origin" empty (make-quadnode (make-posn 10 20) "aaa" empty empty empty empty) empty empty))

(define (quadtree-add position info tree)
  (cond [(empty? tree) (make-quadnode position info empty empty empty empty)]
        
        [(or (and (< (posn-x position) (posn-x (quadnode-key tree)))
                  (> (posn-y position) (posn-y (quadnode-key tree)))) 
             (and (< (posn-x position) (posn-x (quadnode-key tree)))
                  (= (posn-y position) (posn-y (quadnode-key tree)))) )
         
         (make-quadnode (quadnode-key tree)
                        (quadnode-val tree) 
                        (quadtree-add position info (quadnode-nw tree)) 
                        (quadnode-ne tree)
                        (quadnode-sw tree) 
                        (quadnode-se tree))]
        
        [(or (and (> (posn-x position) (posn-x (quadnode-key tree)))
                  (> (posn-y position) (posn-y (quadnode-key tree))))
             (and (> (posn-x position) (posn-x (quadnode-key tree)))
                  (= (posn-y position) (posn-y (quadnode-key tree))))
             (and (= (posn-x position) (posn-x (quadnode-key tree)))
                  (> (posn-y position) (posn-y (quadnode-key tree)))))
         
         (make-quadnode (quadnode-key tree)
                        (quadnode-val tree) 
                        (quadnode-nw tree)  
                        (quadtree-add position info (quadnode-ne tree))
                        (quadnode-sw tree) 
                        (quadnode-se tree))]
             
        [(and (< (posn-x position) (posn-x (quadnode-key tree)))       
              (< (posn-y position) (posn-y (quadnode-key tree)))) 
         
         (make-quadnode (quadnode-key tree)
                        (quadnode-val tree) 
                        (quadnode-nw tree)  
                        (quadnode-ne tree)
                        (quadtree-add position info (quadnode-sw tree))
                        (quadnode-se tree))]
        
        [(or (and (> (posn-x position) (posn-x (quadnode-key tree)))    
                  (> (posn-y position) (posn-y (quadnode-key tree))))
             (and (= (posn-x position) (posn-x (quadnode-key tree)))    
                  (> (posn-y position) (posn-y (quadnode-key tree)))))
         
         (make-quadnode (quadnode-key tree)
                        (quadnode-val tree) 
                        (quadnode-nw tree)  
                        (quadnode-ne tree)
                        (quadnode-sw tree)
                        (quadtree-add position info (quadnode-se tree)))]))

;quadtree-search: posn quadtree -> (union boolean string)
;a function that traverses a quadtree until it finds a specified node, and returns either the string value of the node or false if the node does not exist
;examples
(check-expect (quadtree-search (make-posn 10 20) (make-quadnode (make-posn 0 0) "origin" empty empty empty empty))
              false)

(define (quadtree-search position tree)
  (cond [(empty? tree) false]
        [(and (= (posn-x position) (posn-x (quadnode-key tree)))
                  (= (posn-y position) (posn-y (quadnode-key tree))))
         (quadnode-val tree)]
        
        [(or (and (< (posn-x position) (posn-x (quadnode-key tree)))
                  (> (posn-y position) (posn-y (quadnode-key tree)))) 
             (and (< (posn-x position) (posn-x (quadnode-key tree)))
                  (= (posn-y position) (posn-y (quadnode-key tree)))) )
         
         (quadtree-search position (quadnode-nw tree))]
        
        [(or (and (> (posn-x position) (posn-x (quadnode-key tree)))
                  (> (posn-y position) (posn-y (quadnode-key tree))))
             (and (> (posn-x position) (posn-x (quadnode-key tree)))
                  (= (posn-y position) (posn-y (quadnode-key tree))))
             (and (= (posn-x position) (posn-x (quadnode-key tree)))
                  (> (posn-y position) (posn-y (quadnode-key tree)))))
         
         (quadtree-search position (quadnode-ne tree))]
             
        [(and (< (posn-x position) (posn-x (quadnode-key tree)))       
              (< (posn-y position) (posn-y (quadnode-key tree)))) 
         
         (quadtree-search position (quadnode-sw tree))]
        
        [(or (and (> (posn-x position) (posn-x (quadnode-key tree)))    
                  (> (posn-y position) (posn-y (quadnode-key tree))))
             (and (= (posn-x position) (posn-x (quadnode-key tree)))    
                  (> (posn-y position) (posn-y (quadnode-key tree)))))
         
         (quadtree-search position (quadnode-se tree))]
        ))
