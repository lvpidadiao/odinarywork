;;; melpa emacs package install
(require 'package)
(add-to-list 'package-archives
              '("melpa" . "https://melpa.org/packages/") t)
(package-initialize)
;;; melpa emacs package install end



;;; enable flycheck
;;; enable flycheck end

(require 'cedet)
