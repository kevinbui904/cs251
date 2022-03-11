(letrec ((sum (lambda (x)
                (if (= x 0)
                    0
                    (+ x (sum (- x 1)))))))
  (sum 5))
(- 10 1);
(= 0.0 0)