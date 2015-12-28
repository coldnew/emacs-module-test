;;; test.el --- sc test

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
(require 'sc-core)                    ; c     implementation

(ert-deftest trim-left ()
  "Test remove whitespace at the begining of str."
  (should (string= (sc-trim-left " aa") "aa"))
  (should (string= (sc-trim-left "   你好") "你好"))
  (should (string= (sc-trim-left "abc") "abc")))

(ert-deftest trim-right ()
  "Test remove whitespace at the end of str."
  (should (string= (sc-trim-right " aa") " aa"))
  (should (string= (sc-trim-right "你好   ") "你好"))
  (should (string= (sc-trim-right "abc   ") "abc")))

(ert-deftest trim ()
  "Test remove whitespace at the begining and end of str."
  (should (string= (sc-trim " aa  ") "aa"))
  (should (string= (sc-trim "  你好   ") "你好"))
  (should (string= (sc-trim "abc   ") "abc"))
  (should (string= (sc-trim "ab") "ab")))

;;; test.el ends here
