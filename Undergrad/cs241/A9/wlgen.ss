#lang scheme
;; Assignment 9 Problem 1 (partial solution)
;;
;; Author:  Gordon V. Cormack
;; Modified: Matt McPherrin and Ondrej Lhotak (update for Scheme 4.x)
;; Version: 081110.1
;;

(require (lib "string.ss" "srfi" "13"))

;;
;; Helper functions and data structures
;;

(define labelCounter 0)

(define T     ;; table of terminal symbols, needed for reading WLI format
  (make-immutable-hash 
   '(("BOF") ("BECOMES") ("COMMA") ("ELSE") ("EOF") ("EQ") ("GE") ("GT") ("ID")
             ("IF") ("INT") ("LBRACE") ("LE") ("LPAREN") ("LT") ("MINUS") ("NE")
             ("NUM") ("PCT") ("PLUS") ("PRINTLN") ("RBRACE") ("RETURN") ("RPAREN") 
             ("SEMI") ("SLASH") ("STAR") ("WAIN") ("WHILE")) ))

(define (read-parse lhs)          ;; read and return wli parse tree
  (define line (read-line))
  (define r (rest (string-tokenize line)))
  (cons line
        (if (hash-ref T lhs #f) 
            empty
            (map read-parse r))))

(define (gen-symbols t)                ;; compute symbols defined in t 
  (match (string-tokenize (first t))
    [(list "S" "BOF" "procedure" "EOF") 
     (gen-symbols (third t))]         ;; recurse on "procedure"
    [(list "procedure" "INT" "WAIN" "LPAREN" "dcl" "COMMA" "dcl" "RPAREN" "LBRACE" "dcls" "statements" "RETURN" "expr" "SEMI" "RBRACE") 
     (append (list (gen-symbols (fifth t)) (gen-symbols (seventh t))) (gen-symbols (list-ref t 9)))]  ;; recurse on "dcl" and "dcl"
    [(list "dcls" "dcls" "dcl" "BECOMES" "NUM" "SEMI")
     (append (list (gen-symbols (third t))) (gen-symbols (second t)))]
    [(list "dcls") empty]
    [(list "dcl" "INT" "ID")
     (gen-symbols (third t))]         ;; recurse on "ID"
    [(list "ID" name) name]))               ;; return lexeme for "ID"





(define (gen-code t)                   ;; returns code tree
  (define test 0)
  (define exit 0)
  (match (string-tokenize (first t))
    [(list "S" "BOF" "procedure" "EOF")
     (list   
      (cond [(boolean=? (check-mult-dcl symbols) true) (fprintf (current-error-port) "ERROR")]
            [else 
             ;(printf ".import print\n")
             (print-conventions)
             (push-reg 31)
             (gen-code (third t))
             (pop-reg 31)
             (printf "jr $31\n") 
             (dump-symbol-table symbols)]))]
    
    
    [(list "procedure" "INT" "WAIN" "LPAREN" "dcl" "COMMA" "dcl" "RPAREN" "LBRACE" "dcls" "statements" "RETURN" "expr" "SEMI" "RBRACE")
     
     ;save values of variables into registers
     
     (loadAdrVarReg (get-id-name (fifth t)) 3)
     (storeAdrInReg 1 3)
     (loadAdrVarReg (get-id-name (seventh t)) 3)
     (storeAdrInReg 2 3)
     
     (gen-code (list-ref t 9))
     (gen-code (list-ref t 10))
     (gen-code (list-ref t 12))]  ;; (gen-code (thirteenth t))
    
    
    [(list "statements" "statements" "statement")
     (gen-code (second t))
     (gen-code (third t))]
    
    [(list "statements")
     (printf "")]
    
    [(list "statement" "PRINTLN" "LPAREN" "expr" "RPAREN" "SEMI")
     (gen-code (fourth t))
     (printf "add $1, $3, $0\n")
     (printf "lis $4\n")
     (printf ".word print\n")
     (printf "jalr $4\n")]
    
    
    
    [(list "expr" "term")
     (gen-code (second t))]
    
    [(list "term" "factor")
     (gen-code (second t))]
    
    [(list "factor" "ID")
     (gen-code (second t))]
    
    [(list "factor" "LPAREN" "expr" "RPAREN")
     (gen-code (third t))]
    
    
    [(list "factor" "NUM")
     (gen-code (second t))]
    
    
    [(list "expr" "expr" "PLUS" "term")
     (gen-code (second t))
     (push-reg 3)
     (gen-code (fourth t))
     (pop-reg 4)
     (printf "add $3, $4, $3\n")]
    
    [(list "expr" "expr" "MINUS" "term")
     (gen-code (second t))
     (push-reg 3)
     (gen-code (fourth t))
     (pop-reg 4)
     (printf "sub $3, $4, $3\n")]
    
    [(list "term" "term" "STAR" "factor")
     (gen-code (second t))
     (push-reg 3)
     (gen-code (fourth t))
     (pop-reg 4)
     (printf "mult $4, $3\n")
     (printf "mflo $3\n")]
    
    [(list "term" "term" "SLASH" "factor")
     (gen-code (second t))
     (push-reg 3)
     (gen-code (fourth t))
     (pop-reg 4)
     (printf "div $4, $3\n")
     (printf "mflo $3\n")]
    
    [(list "term" "term" "PCT" "factor")
     (gen-code (second t))
     (push-reg 3)
     (gen-code (fourth t))
     (pop-reg 4)
     (printf "div $4, $3\n")
     (printf "mfhi $3\n")]
    
    [(list "ID" name)
     (cond
       [(member name symbols) (fetch-var name)]
       [else (error "ERROR")])]
    
    [(list "dcls" "dcls" "dcl" "BECOMES" "NUM" "SEMI")
     (gen-code (second t))
     (loadAdrVarReg (get-id-name (third t)) 4)
     (gen-code (fifth t))
     (storeAdrInReg 3 4)]
    
    [(list "statement" "ID" "BECOMES" "expr" "SEMI")
     (loadAdrVarReg (get-id-name (second t)) 5)
     (gen-code (fourth t))
     (storeAdrInReg 3 5)]
    
    [(list "dcls") (printf "")]
    
    [(list "NUM" value) 
     (printf "lis $3\n")
     (printf ".word ~a\n" value)]
    
    
    [(list "test" "expr" "LT" "expr")
     (gen-code (second t))
     (push-reg 3)
     (gen-code (fourth t))
     (pop-reg 4)
     (printf "slt $3, $4, $3\n")]
    
    [(list "test" "expr" "EQ" "expr")
     (gen-code (second t))
     (push-reg 3)
     (gen-code (fourth t))
     (pop-reg 4)
     (printf "slt $5, $4, $3\n")
     (printf "slt $6, $3, $4\n")
     (printf "add $3, $6, $5\n")
     (printf "slt $3, $3, $11\n")]
    
    [(list "test" "expr" "NE" "expr")
     (gen-code (second t))
     (push-reg 3)
     (gen-code (fourth t))
     (pop-reg 4)
     (printf "slt $5, $4, $3\n")
     (printf "slt $6, $3, $4\n")
     (printf "add $3, $6, $5\n")
     (printf "slt $3, $0, $3\n")]
    
    [(list "test" "expr" "GT" "expr")
     (gen-code (second t))
     (push-reg 3)
     (gen-code (fourth t))
     (pop-reg 4)
     (printf "slt $3, $3, $4\n")]
    
    [(list "test" "expr" "LE" "expr")
     (gen-code (second t))
     (push-reg 3)
     (gen-code (fourth t))
     (pop-reg 4)
     (printf "add $3, $11, $3\n")
     (printf "slt $3, $4, $3\n")]
    
    [(list "test" "expr" "GE" "expr")
     (gen-code (second t))
     (push-reg 3)
     (gen-code (fourth t))
     (pop-reg 4)
     (printf "add $4, $11, $4\n")
     (printf "slt $3, $3, $4\n")]
    
    [(list "statement" "WHILE" "LPAREN" "test" "RPAREN" "LBRACE" "statements" "RBRACE")
     (set! test labelCounter)
     (set! labelCounter (add1 labelCounter))
     (set! exit labelCounter)
     (set! labelCounter (add1 labelCounter))
     (printf "L~a:\n" test)
     (gen-code (fourth t))
     (printf "beq $3, $0, L~a\n" exit)
     (gen-code (seventh t))
     (printf "beq $0, $0, L~a\n" test)
     (printf "L~a:\n" exit)]
    
    [(list "statement" "IF" "LPAREN" "test" "RPAREN" "LBRACE" "statements" "RBRACE" "ELSE" "LBRACE" "statements" "RBRACE")
     (set! test labelCounter)
     (set! labelCounter (add1 labelCounter))
     (set! exit labelCounter)
     (set! labelCounter (add1 labelCounter))
     (gen-code (fourth t))
     (printf "beq $3, $0, L~a\n" exit)
     (gen-code (seventh t))
     (printf "beq $0, $0, L~a\n" test)
     (printf "L~a:\n" exit)
     (gen-code (list-ref t 10))
     (printf "L~a:\n" test)]   
    ))



(define (get-id-name t)
  (match (string-tokenize (first t))
    [(list "dcl" "INT" "ID") 
     (get-id-name (third t))]
    [(list "ID" name) name]))

(define (loadAdrVarReg name register)
  (printf "lis $~a\n" register)
  (printf ".word V~a\n" name))

(define (storeAdrInReg a b)
  (printf "sw $~a, 0($~a)\n" a b))

(define (fetch-var name)
  (printf "lis $4\n")
  (printf ".word V~a\n" name)
  (printf "lw $3, 0($4)\n"))

(define (push-reg reg)
  (printf "sw $~a, -4($30)\n" reg)
  (printf "sub $30, $30, $14\n"))

(define (pop-reg reg)
  (printf "add $30, $30, $14\n")
  (printf "lw $~a, -4($30)\n" reg))

(define (dump-symbol-table table)
  (cond [(empty? table) (printf "")]
        [else (printf "V~a: .word 0\n" (first table)) (dump-symbol-table (rest table))]))

(define (print-conventions)
  (printf "lis $14\n")
  (printf ".word 4\n")
  (printf "lis $11\n")
  (printf ".word 1\n")
  (printf "lis $12\n")
  (printf ".word 2\n"))





(define (print-code c)                      ;; flatten and output assembly code
  (cond
    [(pair? c) (print-code (first c)) (print-code (rest c))]
    [(string? c) (display c)]
    [else empty]))



(define (check-mult-dcl list) ;checks the symbol table for duplicate declarations
  (cond [(equal? (remove-duplicates list) list) false]
        [else true]))





;;
;; Main Program
;;

(define parse-tree (read-parse "S"))        ;; read in wli format parse tree
(define symbols (gen-symbols parse-tree))   ;; extract list of symbol definitinos
(define code-tree (gen-code parse-tree))    ;; generate code
(void (print-code code-tree))                      ;; flatten and output code