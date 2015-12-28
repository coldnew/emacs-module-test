;;; benchmark.el --- sc benchmark test

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
(require 's)                          ; elisp implementation
(require 'sc-core)                     ; c     implementation

(defvar test-str "                                                              Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enimad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.                                                  ")

;;; benchmark test
(defun sc-bench (str count)
  (message "\ncalculating: s-trim-left")
  (benchmark count `(s-trim-left ,str))
  (message "\ncalculating: sc-trim-left")
  (benchmark count `(sc-trim-left ,str))

  (message "\ncalculating: s-trim-right")
  (benchmark count `(s-trim-right ,str))
  (message "\ncalculating: sc-trim-right")
  (benchmark count `(sc-trim-right ,str))

  (message "\ncalculating: s-trim")
  (benchmark count `(s-trim ,str))
  (message "\ncalculating: sc-trim")
  (benchmark count `(sc-trim ,str)))

(sc-bench test-str 100)

;;; benchmark.el ends here
