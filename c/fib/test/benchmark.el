;;; benchmark.el --- fib benchmark test

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

(require 'ert)
(require 'fib)                          ; elisp implementation
(require 'fib-core)                     ; c     implementation

;;; benchmark test
(defun fib-bench (n count)
  (message "\ncalculating: fib-c")
  (benchmark count `(fib-c ,n))
  (message "\ncalculating: fib-loop-c")
  (benchmark count `(fib-loop-c ,n))
  (message "\ncalculating: fib-elisp")
  (benchmark count `(fib-elisp ,n))
  (message "\ncalculating: fib-loop-elisp")
  (benchmark count `(fib-loop-elisp ,n)))

(fib-bench 30 100)

;;; benchmark.el ends here
