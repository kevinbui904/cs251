;; DO NOT CHANGE THESE TESTS.

;; Module to include testing code
(use-modules (srfi srfi-64))

;; Basic tests

(let ((x (seq 10 28)) (y (inf-seq 15)))
  (test-equal "basics1" 10 (car x))
  (test-equal "basics2" 11 (car ((cdr x))))
  (test-equal "basics3" 15 (car y))
  (test-equal "basics4" 16 (car ((cdr y))))
  (test-equal "basics5"  '(15 16 17 18 19 20) (first-n y 6))
  (test-equal "basics6" 22 (nth y 8)))

(test-equal "filter-mult1" '(3 5) (first-n (filter-multiples (inf-seq 2) 2) 2) )
(test-equal "filter-mult2"  '(4 5 7 8 10 11) (first-n (filter-multiples (inf-seq 3) 3) 6))
(test-equal "filter-mult3"  '(5 7 8 9 10 11 13 14 15 16 17 19) (first-n (filter-multiples (inf-seq 5) 6) 12))
(test-equal "filter-mult4"  '(5 6 8 9 10 11 12 13 15 16 17 18 19) (first-n (filter-multiples (seq 5 30) 7) 13))

;; Advanced tests (edge cases)

(test-equal "neg-inf-seq1" -3 (car (inf-seq -3)))
(test-equal "neg-inf-seq2" -2 (car ((cdr (inf-seq -3)))))
(test-equal "first-n-edge1" '(3 4) (first-n (seq 3 4) 20))
(test-equal "first-n-edge2" '() (first-n (seq 3 2) 20))

(test-assert "nth-edgh1" (not (nth (seq 3 2) 5)))
(test-assert "nth-edge2" (not (nth (seq 3 5) 25)))

(test-equal "filter-mult-first-n-edge"  '(5 6 8 9 10 11 12 13 15 16 17 18 19 20 22 23 24 25 26 27 29 30) (first-n (filter-multiples (seq 5 30) 7) 500))

(test-equal "primes1" '(2 3 5 7 11 13 17 19 23 29) (first-n (primes) 10))
(test-equal "primes2" 71 (nth (primes) 20))
