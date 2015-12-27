;;; fib.el --- fibonacci emacs-lisp implementation

;; Copyright (C) 2015 by Yen-Chin, Lee

;; Author: Yen-Chin, Lee <coldnew.tw@gmail.com>

;; This program is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation, either version 3 of the License, or
;; (at your option) any later version.

;; This program is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.

;; You should have received a copy of the GNU General Public License
;; along with this program.  If not, see <http://www.gnu.org/licenses/>.

;;; Commentary:

;;; Code:

(defun fib-elisp (n)
  "Calculate Fibonacci number with recursive function call."
  (if (= 0 n) 0
    (if (= 1 n) 1
      (+ (fib-elisp (- n 1)) (fib-elisp (- n 2))))))

(defun fib-loop-elisp (n)
  "Calculate Fibonacci number with loop."
  (let ((a 0)
        (b 1)
        (tmp 0))
    (dotimes (i n 0)
      (setq tmp a)
      (setq a b)
      (setq b (+ tmp b)))
    a))

(provide 'fib)
;;; fib.el ends here
