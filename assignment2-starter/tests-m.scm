;; Do not change these tests! We will be using the 
;; original files to grade, so changing the tests will
;; only make your own preliminary testing inaccurate.

;; Module to include testing code
(use-modules (srfi srfi-64))

;; Basic tests for sum
(test-equal 10 (sum '(4 5 0 1)))
(test-equal 5 (sum '(4 5 0 1 -2 -3)))
(test-equal 3 (sum '(3)))

;; Basic tests for keep-first-n
(test-equal '(a b c) (keep-first-n 3 '(a b c d e)))
(test-equal '(a b) (keep-first-n 2 '(a b c d e)))
(test-equal '(a b c d e) (keep-first-n 5 '(a b c d e)))
(test-equal '(a) (keep-first-n 1 '(a b c d e)))
(test-equal '(d) (keep-first-n 1 '(d)))

;; Advanced test for sum (assignment specifies that 0
;; should be returned for the empty list)
(test-equal 0 (sum '()))


;; Advanced tests for keep-first-n (assignment specifies 
;; that the empty list should be returned when n is 
;; negative or larger than the length of the input list)
(test-equal '() (keep-first-n 6 '(a b c d e)))
(test-equal '() (keep-first-n -1 '(a b c d e)))
(test-equal '() (keep-first-n 0 '(a b c)))
