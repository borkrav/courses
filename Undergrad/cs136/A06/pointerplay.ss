#lang scheme

(provide (struct-out node) pprint preset)
(define-struct node (data left right) #:mutable)

(define counter 0)
(define alist (list (list empty 'null)))

(define (traverse x plst)
  (cond
    [(or (empty? x) (assv x alist) (assv x plst)) plst]
    [else (set! counter (add1 counter))
          (let ([res (traverse (node-left x)
                               (cons (list x counter) plst))])
            (traverse (node-right x) res))]))

(define (preset)
  (set! counter 0)
  (set! alist (list (list empty 'null))))

(define (pprint label x)
  (let ([res (traverse x empty)])
    (set! alist (append res alist))
    (for-each print-item res)
    (printf "~a:\t#~a\n" label (second (assv x alist)))))

(define (print-item p)
  (printf "#~a:\t~a\t#~a\t#~a\n"
          (second p)
          (node-data (first p))
          (second (assv (node-left (first p)) alist))
          (second (assv (node-right (first p)) alist))))


