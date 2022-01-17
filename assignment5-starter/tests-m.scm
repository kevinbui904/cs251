;; DO NOT CHANGE THESE TESTS.

;; Module to include testing code
(use-modules (srfi srfi-64))

;; Basic tests

(test-equal "curry1" 30 ((((curry3 *) 2) 3) 5))
(test-equal "uncurry1" 30 ((uncurry3 (curry3 *)) 2 3 5))
(test-equal "uncurry2" '(9 8 7) ((uncurry3 (curry3 list)) 9 8 7))

(test-equal "myfilter1" '(1 3 4) (my-filter positive? '(1 -2 3 4 -5)))
(test-equal "myfilter2" '() (my-filter positive? '(-1 -2 -3 -4 -5)))

(test-equal "set1" '(1 2 3 4 5 6 7) (sort (union '(1 2 3) '(4 5 6 7)) <))
(test-equal "set2" '(1 2 3 4 6) (sort (union '(1 2 3) '(4 3 6 2)) <))

(test-equal "set5" '() (intersect '(1 2 3) '(4 5 6 7)))
(test-equal "set6" '(2 3) (sort (intersect '(1 2 3) '(4 3 6 2)) <))

(test-equal "exists1" #t (exists (lambda (x) (< x 3)) '(9 2 1 8 7)))
(test-equal "exists2" #t (not (exists (lambda (x) (< x -5)) '(-1 0 1))))

;; Advanced tests

(define curry-plus
    (lambda ()
        (lambda (x)
            (lambda (y)
                (+ x y)))))

(define curry-plus-four
    (lambda ()
        (lambda (x)
            (lambda (y)
              (lambda (z)
                  (lambda (w)
                    (+ x y z w)))))))

(test-equal "myfilter3" '() (my-filter positive? '()))


(test-equal "uncurry3" 8 ((uncurry (curry-plus)) 3 5))
(test-equal "uncurry4" 19 ((uncurry (curry-plus-four)) 1 3 5 10))

(test-equal "set3" '(1 2 3 4 5) (sort (union '(1 2 3 4 5) '(1 2 3 4 5)) <))
(test-equal "set4" '(6 7 8) (sort (union '(6 7 8) '()) <))

(test-equal "set7" '(1 2 3 4 5) (sort (intersect '(1 2 3 4 5) '(1 2 3 4 5))< ))
(test-equal "set8" '() (sort (intersect '(1 2 3 4 5) '()) <))

(test-assert "exists3-ne" (not (exists (lambda (x) (< x 3)) '())))
