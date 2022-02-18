; Written by Thien K. M. Bui
; Last editted 01/13/2021
; HW04 CS251 Carleton College Winter '22

;gen-list
;param: start stop
;return: list from integer start to integer stop, inclusive

(define gen-list
    (lambda (start stop) 
        (cond 
            ((> start stop) ())
            ((= start stop) (list stop))
            (else (append (list start )(gen-list (+ start 1) stop))))))

;pair-sum
;param: list sum
;return: true if there are 2 adjacent integers adding up to sum, otherwise false
(define pair-sum?
    (lambda (list sum) 
        ;check 2 elements at a time
        (cond
            ;end of list
            ((= (length (cdr list)) 0) #f)
            ((= (+ (car list) (car (cdr list))) sum) #t)
            (else (pair-sum? (cdr list) sum)))))

;gen-lazy-list
;param: start stop
;return: lazy list of integers from start to stop, inclusive
(define gen-lazy-list
  (lambda (start stop)
    (if (> start stop)
        #f
        (cons start
            (lambda () (gen-lazy-list (+ start 1) stop))))))

;pair-sum-lazy
;param: lazy_list sum 
;return: true if there are 2 adjacent integers adding up to sum, otherwise false 
(define pair-sum-lazy? 
    (lambda (lazy_list sum)
        (cond 
            ;if calling the lazy list returns false, it's at the end
            ((not ((cdr lazy_list))) #f)
            ((= (+ (car lazy_list) (car ((cdr lazy_list)))) sum) #t)
            (else (pair-sum-lazy? ((cdr lazy_list)) sum)))))

;make-lazy
;param: list 
;return: lazy list with all elements from list
(define make-lazy 
    (lambda (list) 
        (if (= (length list) 0)
        #f 
        (cons (car list) 
            (lambda () (make-lazy (cdr list)))))))