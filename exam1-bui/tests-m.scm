;; DO NOT CHANGE THESE TESTS.

;; Module to include testing code
(use-modules (srfi srfi-64))

;; Helper functions for testing

(define make-lazy
  (lambda (lst)
    (if (null? lst)
        #f
        (cons (car lst)
            (lambda () (make-lazy (cdr lst)))))))

(define make-eager
  (lambda (lazy-list)
    (cond
      ((not lazy-list)
          '())
      ((not ((cdr lazy-list)))
          (list (car lazy-list)))
      (else
          (cons (car lazy-list) (make-eager ((cdr lazy-list))))))))

;; reverse-reverse

(test-equal "reverse-reverse1" '(3 14 12 -4 -2 8) (reverse-reverse '((8 -2) (-4 12) (14 3))) )
(test-equal "reverse-reverse2" '(-9 4 2 28) (reverse-reverse '((28 2) (4 -9))) )
(test-equal "reverse-reverse3" '() (reverse-reverse '()) )
(test-equal "reverse-reverse4" '(11 22 99 88 0 133) (reverse-reverse '((133 0) () (88 99 22 11))) )
(test-equal "reverse-reverse5" '() (reverse-reverse '(() () () ())) )

;; search

(test-equal "search1" #t (search '(1 23 2 22 1 3) 1) )
(test-equal "search2" #f (search '(1 23 2 22 1 3) 10) )
(test-equal "search3" #f (search '() 9) )
(test-equal "search4" #t (search '((1 2 4 2 2) () (8 19)) 8) )
(test-equal "search5" #t (search '(99 ((1 2) (3 4 7) 3) 44 33 2) 4) )
; (test-equal "search6" #t (search '((1 2) 3) '(1 2)) )  ; 2021-01-27 I removed this test case
(test-equal "search6" #t #t)  ; Here's a freebie to get back to 45 total

;; index

(test-equal "index1" 1 (index '(0 1 4 4 5) 1) )
(test-equal "index2" 3 (index '(1 2 3 4 5) 4) )
(test-equal "index3" 1 (index '((44 66 22) (8 8)) '(8 8)) )
(test-equal "index4" #f (index '(98 2 3 4 5) 99) )
(test-equal "index5" #f (index '() 99) )
(test-equal "index6" #f (index '(() (1 2 3 4)) 3) )

;; indices

(test-equal "indices1" '(2 3 6 7 8 9) (indices '(44 4 2 2 536 3 2 2 2 2) 2) )
(test-equal "indices2" '(0) (indices '(3) 3) )
(test-equal "indices3" '() (indices '(1 4 5) 42) )
(test-equal "indices4" '(0 4 5) (indices '(42 1 4 5 42 42) 42) )
(test-equal "indices5" '() (indices '() 0) )

;; indices-lazy

(test-equal "indices-lazy1" '(1 3 5) (make-eager (indices-lazy (make-lazy '(0 1 2 1 2 1 3 4)) 1)) )
(test-equal "indices-lazy2" '(1) (make-eager (indices-lazy (make-lazy '(6 33)) 33)) )
(test-equal "indices-lazy3" '() (make-eager (indices-lazy (make-lazy '(12 4)) 33)) )
(test-equal "indices-lazy4" '() (make-eager (indices-lazy (make-lazy '()) 33)) )


;; reverse-lazy-list (can't use reverse!)

(test-equal "reverse-lazy-list1" '(1 1 1 5 3 42) (reverse-lazy-list (make-lazy '(42 3 5 1 1 1))) )
(test-equal "reverse-lazy-list2" '(2 2 2 2 343 2 2 3 2 0) (reverse-lazy-list (make-lazy '(0 2 3 2 2 343 2 2 2 2))) )
(test-equal "reverse-lazy-list3" '(1) (reverse-lazy-list (make-lazy '(1))) )
(test-equal "reverse-lazy-list4" '() (reverse-lazy-list (make-lazy '())) )

;; curry5-reverse-list

(test-equal "curry5-reverse-list1" '(9 8 77 3 5) (((((curry5-reverse-list 5) 3) 77 ) 8) 9) )
(test-equal "curry5-reverse-list2" '(0 0 0 0 0) (((((curry5-reverse-list 0) 0) 0 ) 0) 0) )

;; sum-every-nth

(test-equal "sum-every-nth1" 2 (sum-every-nth '(0 0 0 1 0 0 0 1 0) 4) )
(test-equal "sum-every-nth2" 1917 (sum-every-nth '(2 3 2 34 2 34 2 1838) 1) )
(test-equal "sum-every-nth3" 0 (sum-every-nth '() 1) )
(test-equal "sum-every-nth4" 0 (sum-every-nth '(1 1 1) 4) )
(test-equal "sum-every-nth5" 0 (sum-every-nth '(1 1 1 1 1 1) 0) )
(test-equal "sum-every-nth6" 7 (sum-every-nth '(0 0 2 0 3 0 2 99) -2) )
(test-equal "sum-every-nth7" 0 (sum-every-nth '(0 2 0 3 0 2 99) -19) )

;; sum-every-nth-lazy

(test-equal "sum-every-nth-lazy1" 2 (sum-every-nth-lazy (make-lazy '(0 0 0 1 0 0 0 1 0)) 4) )
(test-equal "sum-every-nth-lazy2" 1917 (sum-every-nth-lazy (make-lazy '(2 3 2 34 2 34 2 1838)) 1) )
(test-equal "sum-every-nth-lazy3" 0 (sum-every-nth-lazy (make-lazy '()) 1) )
(test-equal "sum-every-nth-lazy4" 0 (sum-every-nth-lazy (make-lazy '(1 1 1)) 4) )
(test-equal "sum-every-nth-lazy5" 0 (sum-every-nth-lazy (make-lazy '(1 1 1 1 1 1)) 0) )
(test-equal "sum-every-nth-lazy6" #f (sum-every-nth-lazy (make-lazy '(0 0 2 0 3 0 2 99)) -2) )


;; No tests for my-sum-optimized, because you define your own function
;; signature. If you didn't receive feedback from me on this one, your
;; solution is solid.
