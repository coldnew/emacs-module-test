;;; test.el --- fib test

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

(ert-deftest zero-to-ten ()
  "input 0 ~ 10"
  (dotimes (n 11 0)
    (should (= (fib-elisp n) (fib-c n)))
    (should (= (fib-loop-elisp n) (fib-loop-c n)))))

;;; test.el ends here
