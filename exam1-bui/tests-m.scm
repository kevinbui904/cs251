;;Written by Thien K. M. Bui 
;;testing scripts are copied from Prof James Ryan assignemt6-starter code
;Last editted 01/21/22

;; Module to include testing code
(use-modules (srfi srfi-64))

;tests reverse-reverse

(test-equal "reverse-reverse1" '(4 7 99 88 2 1) (reverse-reverse '((1 2) (88 99) (7 4))))
(test-equal "reverse-reverse2" '(6 5 4 3 2 1) (reverse-reverse '((1 2) (3 4) (5 6))))
(test-equal "reverse-reverse-empty" '() (reverse-reverse '()))
(test-equal "reverse-reverse-empty-middle" '(99 88 2 1) (reverse-reverse '((1 2) () (88 99)) ))
(test-equal "reverse-reverse-empty-end" '(14 77 4 1) (reverse-reverse '((1 4) (77 14) ()) ))

;search
(test-assert "search1" (search '(1 2 3) 1))
(test-assert "search2" (not (search '(1 2 3) 7)))
(test-assert "search3" (search '((1 2) (2 4) (8 3)) 8))
(test-assert "search4" (search '(1 (2 (3 4 7) 3)) 4))

(test-assert "search5" (search '(1 (2 (a 4 7) 3)) 'a))
(test-assert "search6" (search '((1 2) (2 4) (a 3)) 'a))
(test-assert "search7" (search '((1 (3 10 2)) (2 4) (8 3)) 10))


;index
(test-equal "index1" 0 (index '(1 2 3 4 5) 1))
(test-equal "index2" 2 (index '(1 2 3 4 5) 3))
(test-equal "index3" 1 (index '((1 2) (3 4)) '(3 4)))
(test-assert "index4" (not (index '(1 2 3 4 5) 99)))
(test-assert "index5" (not (index '() 1)))
(test-assert "index6" (not (index '((1 2) (3 4)) 4)))

(test-equal "index7" 0 (index '((a b) (3 4)) '(a b)))
(test-equal "index8" 1 (index '(1 c 3 4 5) 'c))



;indices
(test-equal "indices1" '(3 7 8) (indices '(1 4 3 2 5 6 3 2 2 1) 2))
(test-equal "indices2" '(2) (indices '(1 2 3 4 5) 3))
(test-equal "indices3" '() (indices '(1 2 3 4 5) 99))
(test-equal "indices4" '() (indices '() 1))

;indices-lazy
(test-equal "indices-lazy1" 0 (car (indices-lazy (make-lazy '(1 2 1 2 3)) 1)))
(test-equal "indices-lazy2" 2 (car ((cdr (indices-lazy (make-lazy '(1 2 1 2 3)) 1)))))
(test-assert "indicies-lazy3-none" (not  (indices-lazy (make-lazy '(1 2 1 2 3)) 44)))

(test-equal "indices-lazy4" 2 (car(indices-lazy (make-lazy '(1 2 a 2 3)) 'a)))

;reverse-lazy-list
(test-equal "reverse-lazy-list1" '(5 4 3 2 1) (reverse-lazy-list (make-lazy '(1 2 3 4 5))))
(test-assert "reverse-lazy-list2" (not (reverse-lazy-list (make-lazy '()))))
(test-equal "reverse-lazy-list3" '(1) (reverse-lazy-list (make-lazy '(1))))

;curry5-reverse-list
(test-equal "curry5-reverse-list1" '(5 4 3 2 1) (((((curry5-reverse-list 1) 2) 3) 4) 5))

;sum-every-nth
(test-equal "sum-every-nth1" 3 (sum-every-nth '(0 0 1 8 0 1 4 0 1) 3))
(test-equal "sum-every-nth2" 3 (sum-every-nth '(1 1 1) 1))
(test-equal "sum-every-nth3" 0 (sum-every-nth '() 1))
(test-equal "sum-every-nth4" 0 (sum-every-nth '(1 2 3 4) 66))
(test-equal "sum-every-nth5" 0 (sum-every-nth '(1 2 3 4) 0))
(test-equal "sum-every-nth6" 51 (sum-every-nth '(1 0 1 0 48 0 1 0) -2))

;sum-every-nth-lazy
(test-equal "sum-every-nth-lazy1" 3 (sum-every-nth-lazy (make-lazy '(0 0 1 0 99 1 0 0 1)) 3))
(test-equal "sum-every-nth-lazy2" 3 (sum-every-nth-lazy (make-lazy '(1 1 1)) 1))
(test-equal "sum-every-nth-lazy3" 0 (sum-every-nth-lazy (make-lazy '()) 1))
(test-equal "sum-every-nth-lazy4" 0 (sum-every-nth-lazy (make-lazy '(1 4 1 0 1 0 1)) 66))
(test-equal "sum-every-nth-lazy5" 0 (sum-every-nth-lazy (make-lazy '(1 0 1 3 1 0 1)) 0))
(test-assert "sum-every-nth-lazy6" (not (sum-every-nth-lazy (make-lazy '(1 0 1 0 1 0 1)) -1)))

;my-sum-optimized
(test-equal "my-sum-optimized" 15 (my-sum-optimized '(1 2 3 4 5)))
(test-equal "my-sum-optimized2" 9 (my-sum-optimized '(1 2 -3 4 5)))



