(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(column-number-mode t)
 '(fringe-mode 0 nil (fringe))
 '(inhibit-startup-screen t)
 '(package-selected-packages '(go-mode))
 '(tool-bar-mode nil))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(default ((t (:inherit nil :extend nil :stipple nil :background "white" :foreground "black" :inverse-video nil :box nil :strike-through nil :overline nil :underline nil :slant normal :weight normal :height 90 :width normal :foundry "PfEd" :family "DejaVu Sans Mono")))))

(when (>= emacs-major-version 24)
  (progn
    ;; load emacs 24's package system.
    (require 'package)
    ;; Add MELPA repository.
    (add-to-list 'package-archives '("melpa" . "https://melpa.org/packages/") t))
  (when (< emacs-major-version 27) (package-initialize)))

(global-set-key (kbd "M-q") 'fill-paragraph)
(setq-default fill-column 60)
(global-set-key (kbd "M-z") 'compile)
(global-set-key (kbd "C-c l") 'goto-line)
(global-set-key (kbd "C-x x") 'copy-to-register)
(global-set-key (kbd "C-x g") 'insert-register)
(global-set-key (kbd "C-c b") 'balance-windows-area)
(put 'upcase-region 'disabled nil)

(put 'downcase-region 'disabled nil)
(setq compile-command "make")

;; Split windows in the (emacs-22) way
(setq split-height-threshold nil)
;;(setq split-width-threshold most-positive-fixnum)
(setq split-width-threshold 0)
;;(setq split-width-threshold nil);;(not!)
