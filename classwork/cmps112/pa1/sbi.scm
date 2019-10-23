#!/afs/cats.ucsc.edu/courses/cmps112-wm/usr/racket/bin/mzscheme -qr
;; $Id: sbi.scm,v 1.3 2016-09-23 18:23:20-07 - - $
;;
;; NAME
;;    sbi.scm - silly basic main-programreter
;;
;; SYNOPSIS
;;    sbi.scm filename.sbir
;;
;; DESCRIPTION
;;    The file mentioned in argv[1] is read and assumed to be an SBIR
;;    program, which is the executed.  Currently it is only printed.
;;
;; PARTNERS
;;    Daniel Lung dlung@ucsc.edu
;;    Michael Quan midquan@ucsc.edu

(define *stderr* (current-error-port))

(define *run-file*
    (let-values
        (((dirpath basepath root?)
            (split-path (find-system-path 'run-file))))
        (path->string basepath))
)

(define (die list)
    (for-each (lambda (item) (display item *stderr*)) list)
    (newline *stderr*)
    (exit 1)
)

(define (usage-exit)
    (die `("Usage: " ,*run-file* " filename"))
)

(define (readlist-from-inputfile filename)
    (let ((inputfile (open-input-file filename)))
         (if (not (input-port? inputfile))
             (die `(,*run-file* ": " ,filename ": open failed"))
             (let ((program (read inputfile)))
                  (close-input-port inputfile)
                         program))))

(define (write-program-by-line filename program)
    (map (lambda (line) 
        (cond 
            ((null? (cdr line))
                (void))
            ((pair? (cadr line))
                (void))  
            (else (hash-set! *label-table* (cadr line) line))
        )
    ) program)
)

(define (main arglist)
    (if (or (null? arglist) (not (null? (cdr arglist))))
        (usage-exit)
        (let* ((sbprogfile (car arglist))
               (program (readlist-from-inputfile sbprogfile)))
              (write-program-by-line sbprogfile program)             ;PROVIDED BY EXAMPLE DO NOT TOUCH
              (main-program 1 program))))                                    ;RUNS ACTUAL MAIN PROGRAM FUNCTION

(define *function-table* (make-hash))
(define *label-table* (make-hash))
(define *variable-table* (make-hash))
              
(define (function-get key)
    (hash-ref *function-table* key))
(define (function-put! key value)
    (hash-set! *function-table* key value))

(for-each
    (lambda (pair)
            (function-put! (car pair) (cadr pair)))
    `(

        (+      ,+)
        (-      ,-)
        (*      ,*)
        (/      ,(lambda (x y) (/ (+ x 0.0) (+ y 0.0))))             ;CONVERT TO FLOAT
        (%      ,(lambda (x y) (- x (* (/ x y) y))))
        (^      ,expt)
        (<>     ,(lambda (x y) (not (= x y))))
        (<=     ,<=) 
        (>=     ,>=) 
        (=         ,=) 
        (>         ,>)
        (<        ,<)
        (abs    ,abs)
        (acos   ,acos)
        (asin   ,asin)
        (atan   ,atan)
        (cos    ,cos)
        (exp    ,exp)
        (floor  ,floor)
        (log    ,log)
        (round  ,round)
        (sin    ,sin)
        (sqrt   ,sqrt)
        (ceil   ,ceiling)
        (log2   ,(lambda (x) (/ (log x) (log 2.0))))
        (log10  ,(lambda (x) (/ (log x) (log 10.0))))
        (tan    ,tan)
        (trunc  ,truncate)
))

(define (variable-get key)
    (hash-ref *variable-table* key))
(define (variable-put! key value)
    (hash-set! *variable-table* key value))
    
(for-each
    (lambda (vpair)
            (variable-put! (car vpair) (cadr vpair)))    
    `(
        (e        2.718281828459045235360287471352662497757247093)
        (pi        3.141592653589793238462643383279502884197169399)
))                                                                    ;TABLES INITIALIZED

(define (evalexpr expr)
    (if (symbol? expr)
        (if(hash-has-key? *variable-table* expr)
            (hash-ref *variable-table* expr)
            (printf "Error: ~s variable not found ~n" expr)
        )
        (if    (number? expr)
            expr
            (let ((op (function-get (car expr))) (tail (cdr expr)))
                (apply op (map evalexpr tail)))
        )
    )
)


(define (main-program line-count program)                         ;TAIL RECURSIVE FUNCTION TO READ LINE BY LINE
    (if (> line-count (length program))
        (exit 1)                                                  ;DONE, EOF
        (void))
    
    (let ((line (list-ref program (- line-count 1))))
        (if (null? (cdr line))
            (main-program (+ line-count 1) program)
            (void)
        )
        (cond 
            ((hash-has-key? *label-table* (cadr line))
                (let ((state (caddr line)))
                    (statement-functions state line-count program)
                )
            )
            (else
                (let ((state (cadr line)))
                    (statement-functions state line-count program)
                )
            )
        )
    )
)

(define (statement-functions state line-count program)
    (if (eqv? (car state) 'if)                                    ;IF FUNCTION
        (main-program (comp-opers state line-count) program)
        (void))
                    
    (if (eqv? (car state) 'goto)                                ;GOTO FUNCTION
        (main-program (car (hash-ref *label-table* (cadr state))) program)
        (void))
    (if (eqv? (car state) 'print)                            ;PRINT FUNCTION
        (cond
        ((null? (cdr state)) (printf "~n"))
        
        ((string? (cadr state))
            (if (null? (cddr state))
                (printf "~s" (cadr state))
                (printf "~s~s" (cadr state) (evalexpr(caddr state)))
            )
            (printf "~n")
        )
        
        (else
            (printf "~s~n" (evalexpr (cadr state)))
        )
    )
        (void)
    )
    
    (if (eqv? (car state) 'dim)                            ;DIM FUNCTION
        (hash-set! *variable-table* (cadr state)
            (make-vector (evalexpr (caaddr state))))
        (void)
    )
    
    (if (eqv? (car state) 'input)                        ;INPUT FUNCTION
        (let ((in (read))) (hash-set! *variable-table* (cadr state) in))
        (void)
    )
    
    (if (eqv? (car state) 'let)                            ;LET FUNCTION
        (if(pair? (cadr state))
            (if (vector? (hash-ref *variable-table* (caadr state)))
                (vector-set! (hash-ref *variable-table* (caadr state))
                    (cadadr state) (evalexpr (caddr state)))
                (printf "Error: array not found ~n")
            )
            (hash-set! *variable-table* (cadr state)
                (evalexpr (caddr state)))
        )
        (void)
    )
    (main-program (+ line-count 1) program)
)
; STOP
                                        
(define (comp-opers state line-count)                        ;OPERATOR FUNCTIONS FOR IF
    (let ((op (caadr state)))

        (cond 
;            ((hash-has-key? *function-table*)
;                (let ((hash-ref *function-table* (car expr)))        
;            )
            ((eqv? op '>)                                    ;>
                (operator line-count op state)
            )
            ((eqv? op '<)                                    ;<
                (operator line-count op state)
            )
            ((eqv? op '=)                                    ;=
                (operator line-count op state)
            )
            ((eqv? op '>=)                                    ;>=
                (operator line-count op state)
            )
            ((eqv? op '<=)                                    ;<=
                (operator line-count op state)
            )
            ((eqv? op '<>)                                    ;<>
                (operator line-count op state)
            )
            (else                                            ;NO MATCH
                (+ line-count 1)))
    )
)
(define (operator line-count op state)                        ;COMPARE EXPRESSION FUNCTION
    (if ((hash-ref *function-table* op) (evalexpr (cadadr state))
        (evalexpr (car (cddadr state))))
            (car (hash-ref *label-table* (caddr state)))
        (+ line-count 1)
    )
)

(main (vector->list (current-command-line-arguments)))






















