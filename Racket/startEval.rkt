#lang racket

;storage lists
(define stack '())
(define const_stack '())
(define computed '())
(define local_stack '())
(define temp_stack '())
(define functions '())
(define currentLambda '())

;unary ops
(define u_op '())
(define u_op_ '())
(define u_opr '())

;binary ops
(define bin_op '())
(define bin_op_ '())
(define bin_opr '())

;body ops
(define body_op '())

;func op
(define func_op '())
(define func_opr '())

;lambda ops
(define lam_op '())
(define lam_op_ '())

;if ops
(define if_op '())
(define if_op_ '())
(define if_opr '())

;let ops
(define let_op '())
(define let_op_ '())

;helper variables 
(define bind '())
(define result '())
(define varItem '())
(define temp '())
(define tmp '())
(define params '())
(define nons '())
(define fos #f)
(define help_stack '())

;unary operators
(define unary_op '(car cdr pair? quote))

;binary operators
(define binary_op '(= >= < > <= cons + - * /  equal?))

(define (startEval program)
  (reader program))

;main reader which routes the path of the program
(define (reader program)
  (if (not (null? program))
      (cond
        ;if the last computation was the storage of a lambda function, then we should try looking for a value for this function
        ((eq? fos #t)
         (begin
           (set! fos #f)
           ;we then execute the last lambda function and return its result if the program is at its end or continue computing the rest
           (cond
             ((= (length program) 1)
              (begin
                (set! result (executeFunction result program))
                result))
             (else
              (begin
                (set! func_opr (length (list-ref result 0)))
                (set! result (executeFunction result (take program (length (list-ref result 0)))))
                
                (reader (list-tail program func_opr)))))))

        ((= (length program) 1) (self-eval (car program)))

        ((foundFunc? (car program) functions)
         (begin
           (if (null? (cdr program))
               0
               (begin
                 (set! func_op (retrieve (car program) functions))
                 (set! params (take (cdr program) (length (car func_op))))))
          
           (set! result (executeFunction func_op params))
          
           (reader (list-tail program (+ 1 (length params))))))
           
        ((found? (car program) unary_op)
         (begin
           
           (if (null? (cdr program))
               0
               (set! u_op (list-ref program 1)))
           (cond
             ((list? u_op) (set! u_op (parser u_op))))
           (set! result (callFunction (car program) (self-eval u_op) '() '()))
           
           (set! u_op '())
           (reader (list-tail program 2))))

        ((or (eq? 'var (list-ref program 0)) (eq? 'const (list-ref program 0)))
         (begin
           (if (null? (cdr program))
               0
               (begin
                 (set! bin_op (list-ref program 1))
                 (set! bin_op_ (list-ref program 2))))
           (cond
             ((list? bin_op) (set! bin_op (parser bin_op)))
             ((list? bin_op_) (set! bin_op_ (parser bin_op_))))
           (set! result (callFunction (car program) bin_op bin_op_ '()))
           (set! computed (cons result computed))
           (set! bin_op_ '())
           (set! bin_op '())
           (reader (list-tail program 3))))
        ((found? (car program) binary_op)
         (begin
           (if (null? (cdr program))
               0
               (begin
                 (set! bin_op (list-ref program 1))
                 (set! bin_op_ (list-ref program 2))))
           (cond
             ((list? bin_op) (set! bin_op (parser bin_op)))
             ((list? bin_op_) (set! bin_op_ (parser bin_op_))))
           (set! result (callFunction (car program) (self-eval bin_op) (self-eval bin_op_) '()))
           (set! computed (cons result computed))
           (set! bin_op_ '())
           (set! bin_op '())
           (reader (list-tail program 3))))

        ((eq? 'if (list-ref program 0))   
         (begin
           (if (null? (cdr program))
               0
               (begin
                 (set! if_op (list-ref program 1))
                 (set! if_op_ (list-ref program 2))
                 (set! if_opr (list-ref program 3))))
           
           (cond
             ((list? if_op) (set! if_op (reader if_op))))

           (set! if_op (self-eval if_op))
           
           (if (not (not if_op))
               (set! result (self-eval if_op_))
               (set! result (self-eval if_opr)))
           
           (set! result (self-eval result))
           
           (set! computed (cons result computed))
           
           (reader (list-tail program 4))))

        ((or (eq? 'let (list-ref program 0)) (eq? 'letrec (list-ref program 0)))
         (begin
           (if (null? (cdr program))
               0
               (begin
                 (set! let_op (list-ref program 1))
                 (set! let_op_ (list-ref program 2))))           

           
           (compute-bindings let_op)
           (set! result (self-eval let_op_))  
           (reader (list-tail program 3))))

        ((and (pair? (car program)) (eq? 'lambda (caar program)))
         (begin
           (if (null? (cadr program))
               0
               (begin
                 (set! lam_op (list-ref (car program) 1))
                 (set! lam_op_ (list-ref (car program) 2))))
           (set! result (createFunction lam_op lam_op_))
           (set! fos #t)
           (reader (cdr program)))))
      result))

;this function executes lambda or user defined functions
(define (executeFunction program values)
  (define sub_stack (compFunctionBindings (car program) values '()))
  (define nons 0)
  (set! temp_stack (append sub_stack temp_stack))
  
  (define len (length (list-ref program 0)))
  
  (set! nons (reader (list-ref program 1)))
  
  (set! computed nons)
  (set! temp_stack (list-tail temp_stack (length sub_stack)))
  computed)

;this helps (compFunctionBindings) compute, store and return bindings
(define (addBinding bName bValue storage)
   (if (not (declared? bName storage))
         (begin
           (set! varItem (list bName bValue))
           (set! storage (cons varItem storage))
           (set! varItem '())
           storage)
         (cond
          ((declared? bName storage)
            (begin
              (set! nons (removeBinding bName storage))
              (set! varItem (list bName bValue))
              (set! nons (cons varItem nons))
              (set! storage nons)
              (set! varItem '())
              storage)))))

;this computes the variable-value bindings for the execution of a function about to occur
(define (compFunctionBindings vName vValue storage)
  (if (null? vName)
      storage
      (cond
        ((null? vValue)
          (begin
            (set! storage (addBinding (car vName) 0 storage))
            ;(debug storage)
            (compFunctionBindings (cdr vName) (self-eval vValue) storage)))
        (else
          (begin
            (set! storage (addBinding (car vName) (self-eval (car vValue)) storage))
            ;(debug storage)
            (compFunctionBindings (cdr vName) (self-eval (cdr vValue)) storage))))))

;used by let and letrec to compute bindings for the execution of the code in the body 
(define (compute-bindings items)
  (if (null? items)
      #f
      (begin
        (set! bind (car items))
        (set! temp (car bind))
        (set! tmp (cadr bind))
        (cond
          ((and (pair? tmp) (eq? (car tmp) 'lambda))
           (begin
             (createBinding temp (cdr tmp) 'func)
             (compute-bindings (cdr items))))
          (else
           (set! tmp (self-eval tmp))
           (createBinding temp tmp 'local)
           (compute-bindings (cdr items)))))))

;helper for printing and debugging
(define (debug msg)
  (if (empty? msg)
  (writeln "DEBUGGING")
  (writeln msg)))

;this creates a lambda function binding and returns it
(define (createFunction parameters body)
  (set! currentLambda (cons (list parameters body) currentLambda))
  (car currentLambda))

;this is the secondary parser which reads lists and solves them directly by calling the primitives function
(define (parser program)
    (if (> (length program) 1)
        (cond
          ((found? (car program) unary_op)
           (begin
             (cond
               ((< (length (cdr program)) 1) (writeln "Provided with no operands") 0)
               ((> (length (cdr program)) 1) (writeln "Provided with more operands than needed.") 0))

             
             (set! u_op_ (self-eval (cadr program)))
             ;(writeln (car program))
             
             (set! u_opr (callFunction (car program) u_op_ '() '()))
             u_opr))
          
          ((found? (car program) binary_op)
          (begin
            (cond
               ((< (length (cdr program)) 2) (writeln "Provided with less operands than required") 0)
               ((> (length (cdr program)) 2) (writeln "Provided with more operands than needed.") 0))
            ;(writeln program)
             (set! bin_opr (callFunction (car program) (self-eval (cadr program)) (self-eval (caddr program)) '()))
             bin_opr))
          (else (reader program)))
        program))

;this function helps with finding the simplest form of the item passed to it. Helps with functions, variables, numbers, complex items
(define (self-eval item)
  (cond
     ((and (pair? item) (declared? (car item) functions))
     (begin
       (set! tmp (retrieve (car item) functions))
       (set! tmp (executeFunction tmp (list-tail item 1))))
       tmp)
    ((declared? item temp_stack)
     (begin       
       (set! varItem (retrieve item temp_stack))
       varItem))
    ((declared? item local_stack)
     (begin
       (set! varItem (retrieve item local_stack))
       varItem))
    ((declared? item stack)
     (begin
       (set! varItem (retrieve item stack))
       varItem))
    ((declared? item const_stack)
     (begin
       (set! varItem (retrieve item const_stack))
       varItem))
    ((number? item)
     item)
    ((list? item)
     (parser item))
    (else item)))

;this checks if an item stored in word exists in a storage list (for variable type bindings)
(define (found? word  keywords)
  (if (<= (length keywords) 0)
      #f
      (cond
        ((eq? (car keywords) word) #t)
        (else (found? word (cdr keywords))))))

;this checks if a function id stored in word exists in a function storage list (for function type bindings)
(define (foundFunc? word  keywords)
  (if (<= (length keywords) 0)
      #f
      (cond
        ((eq? (caar keywords) word) #t)
        (else (found? word (cdr keywords))))))

;this function calls and returns the evaluated value of the primitive functions with their values
(define (callFunction oprtr op1 op2 op3)
  (cond
    ((equal? oprtr 'quote) (quasiquote (unquote op1)))
    ((equal? oprtr 'car) (car op1))
    ((equal? oprtr 'cdr) (cdr op1))
    ((equal? oprtr 'cons) (cons op1 op2))
    ((equal? oprtr 'pair?) (pair? op1))
    ((equal? oprtr 'equal?) (equal? op1 op2))
    ((or (equal? oprtr 'const) (equal? oprtr 'var)) (createBinding op1 op2 oprtr))
    ((equal? oprtr '+) (+ op1 op2))
    ((equal? oprtr '-) (- op1 op2))
    ((equal? oprtr '*) (* op1 op2))
    ((equal? oprtr '/) (/ op1 op2))
    ((equal? oprtr '=) (= op1 op2))
    ((equal? oprtr '<) (< op1 op2))
    ((equal? oprtr '<=) (<= op1 op2))
    ((equal? oprtr '>) (> op1 op2))
    ((equal? oprtr '>=) (>= op1 op2))
    (else 0)))

;this retrieves the value of a binding stored in a storage list 
(define (retrieve item storage)
  (if (null? storage)
      #f
      (if (equal? item (caar storage))
          (list-ref (car storage) 1)
          (retrieve item (cdr storage)))))

;this creates bindings in specific storage lists based on the value of the key variable
(define (createBinding bName bValue key)
  (cond
    ((equal? key 'var)
     (if (and (not (declared? bName stack)) (not (declared? bName const_stack)))
         (begin
           (set! varItem (list bName bValue))
           (set! stack (cons varItem stack))
           (set! varItem '())
           bValue)
         (cond
           ((declared? bName stack)
            (begin
              (set! help_stack (removeBinding bName stack))
              (set! varItem (list bName bValue))
              (set! help_stack (cons varItem help_stack))
              (set! stack help_stack)
              (set! varItem '())
              bValue))
           ((declared? bName const_stack) "Redefinition of constants is not allowed."))))

    ((equal? key 'const)
     (if (and (not (declared? bName stack)) (not (declared? bName const_stack)))
         (begin
           (set! varItem (list bName bValue))
           (set! const_stack (cons varItem const_stack))
           (set! varItem '())
           bValue)
         "Redefinition of variables is not allowed."))

    ((equal? key 'local)
     (if (not (declared? bName local_stack))
         (begin
           (set! varItem (list bName bValue))
           (set! local_stack (cons varItem local_stack))
           (set! varItem '())
           bValue)
         "Redefinition of locals is not allowed."))

    ((equal? key 'func)
     (if (not (declared? bName functions))
         (begin
           (set! varItem (list bName bValue))
           (set! functions (cons varItem functions))
           (set! varItem '())
           functions)
         "Redefinition of functions is not allowed."))
    
    ((equal? key 'temp)
     (if (not (declared? bName temp_stack))
         (begin
           (set! varItem (list bName bValue))
           (set! temp_stack (cons varItem temp_stack))
           (set! varItem '())
           bValue)
         (cond
          ((declared? bName temp_stack)
            (begin
              (set! nons (removeBinding bName temp_stack))
              (set! varItem (list bName bValue))
              (set! nons (cons varItem nons))
              (set! temp_stack nons)
              (set! varItem '())
              bValue)))))))

;this checks if an 'item' is declared in a 'storage' list
(define (declared? item storage)
  (if (null? storage)
      #f
      (if (equal? item (list-ref (car storage) 0))
          #t
          (declared? item (cdr storage)))))

;this checks if an item is in a storage list and removes it by returning all of the items excluding that item
(define (removeBinding item storage)
  (if (null? storage)
      '()
      (if (equal? item (caar storage))
          (cdr storage)
          (cons (car storage) (removeBinding item (cdr storage))))))

(provide startEval)

;Written tests of functionalities
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;comment these out before using this file with an external file;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(writeln (startEval '(var a 15)))
(newline)
(writeln (startEval '(var a 5)))
(newline)
(writeln (startEval '(const c 9)))
(newline)
(writeln (startEval '(var b (+ a (+ c (* c a))))))
(newline)
(writeln (startEval '(= c 9)))
(newline)
(writeln (startEval '(quote c)))
(newline)
(writeln (startEval '(cons (cons 4 5) 6)))
(newline)
(writeln (startEval '(pair? (cons (cons 4 5) 6))))
(newline)
(writeln (startEval '(if (> b a) (quote b) (quote a))))
(newline)
(writeln (startEval '(let ((x 3) (y 2) (z 2)) (* (+ x y) z))))
(newline)
(writeln (startEval '((lambda (x y) (if (<= x y) (* x y) (* x 2)))
                      26 25)))
(newline)
(writeln (startEval '((lambda (x) (* (* x x) x)) 2)))
(newline)
(writeln (startEval '(let ((func (lambda (x y) (+ (* x x) y)))) (func 10 2))))
(newline)
(writeln (startEval '(func 12 5)))
(newline)
(writeln (startEval '(let ((fact (lambda (x) (if (= x 0) (quote 1) (* x (fact (- x 1)))))))
                       (fact 10))))
(newline)
;(writeln (startEval '(fact 3)))
;(newline)