;Written by Thien K. M. Bui
;Programming Languages Carleton College Winter '22
;Last updated 01/19/22

;seq
;param: two integers (first last)
;return: lazy list containing integer value from first to last
(define seq 
    (lambda (first last)
        (if (> first last) 
            #f
            ;return a procedure in cdr that if invoked, calls seq
            (cons first (lambda () (seq (+ first 1) last))))))

;inf-seq
;param: one integer (first)
;return: lazy list of integer from first to infinity
(define inf-seq 
    (lambda (first)
        (cons first (lambda () (inf-seq (+ first 1))))))

;first-n
;param: lazy-list and an integer (n)
;return: Scheme list containing the first n values in the lazy list 
;e.g. (first-n (seq 1 3) 2) --> (1 2)
(define first-n 
    (lambda (lazy n)
        ;if lazy is empty or n is 0
        (if (or (null? lazy) (= n 0))
            '()
            (first-n-helper lazy n '()))))

;first-n-helper
;param: lazy-list lazy, integer n, scheme-list current_list
;return: Scheme list containing the first n values in the lazy list 
;NOTE: use this helper to tail-optimize first-n
(define first-n-helper 
    (lambda (lazy n current_list)
        (if (or (= n 0) (not lazy))
            ;base case, if n is 0 or if we're at the end of lazy (last member of a lazy list is #f)
            current_list
            (first-n-helper ((cdr lazy)) (- n 1) (append current_list (list (car lazy)))))))

;nth 
;param: lazy-list lazy and integer n
;return: nth value of the lazy-list
(define nth 
    (lambda (lazy n)
        (cond 
            ((not lazy) #f)
            ;clause below must go after (not lazy) because otherwise we'd be trying to call car on a #f
            ((= n 1) (car lazy))
            (else (nth ((cdr lazy)) (- n 1))))))

;filter-multiples
;param: lazy-list lazy and integer n
;return: lazy-list of all integers in lazy not-divisible by n

(define filter-multiples
    (lambda (lazy n)
       (filter-multiples-helper lazy n '())
       ))

;  (if (or (not lazy) (= (modulo (car lazy) n) 0))
;         (cons '() (filter-multiples ((cdr lazy)) n))
;         (cons (car lazy) (filter-multiples ((cdr lazy)) n)))
;filter-multiples-helper (for tail optimization)
;param: lazy-list lazy, integer n, return-lazy-list return_lazy
;return: lazy-list of all integers in lazy not-divisible by n
(define filter-multiples-helper
    (lambda (lazy n return_lazy)
        (cond 
            ((not lazy) '())
            ((= (modulo (car lazy) n) 0)  (filter-multiples-helper ((cdr lazy)) n  (append '() return_lazy)))
            (else (filter-multiples-helper ((cdr lazy)) n  (append return_lazy (car lazy))))
        )))