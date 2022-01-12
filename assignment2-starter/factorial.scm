(define fact
  (lambda (n)
    (if (equal? n 1)
        1
        (* n (fact (- n 1))))))

,tr (fact 5)

