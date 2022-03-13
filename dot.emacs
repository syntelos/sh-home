(custom-set-variables
  ;; custom-set-variables was added by Custom.
  ;; If you edit it by hand, you could mess it up, so be careful.
  ;; Your init file should contain only one such instance.
  ;; If there is more than one, they won't work right.
 '(column-number-mode t)
 '(inhibit-startup-screen t)
 '(scroll-bar-mode nil)
 '(tool-bar-mode nil)
 '(tooltip-mode nil))
(custom-set-faces
  ;; custom-set-faces was added by Custom.
  ;; If you edit it by hand, you could mess it up, so be careful.
  ;; Your init file should contain only one such instance.
  ;; If there is more than one, they won't work right.
 '(default ((t (:inherit nil :stipple nil :background "white" :foreground "black" :inverse-video nil :box nil :strike-through nil :overline nil :underline nil :slant normal :weight normal :height 93 :width normal :foundry "unknown" :family "DejaVu Sans Mono")))))
;
(setq c-basic-offset 4)
(setq-default indent-tabs-mode nil)
(setq default-tab-width 4)
(setq tab-width 4)
(setq tab-stop-list (number-sequence 4 200 4))
;
(add-to-list 'load-path "/home/jdp/src/glasserc/ethan-wspace/lisp")
(require 'ethan-wspace)
(global-ethan-wspace-mode 1)
(ethan-wspace-clean-all-modes)
(setq mode-require-final-newline nil)
;
(autoload 'pic-basic-mode "pic-basic-mode" "Visual Basic mode." t)
(setq auto-mode-alist (append '(("\\.\\(bas\\|BAS\\)$" .
                                 pic-basic-mode)) auto-mode-alist))
;
(setq auto-mode-alist (append '(("\\.\\(lst\\|LST\\)$" .
                                 asm-mode)) auto-mode-alist))
;
(setq auto-mode-alist (cons '("\\.xtm$" . tpl-mode) auto-mode-alist))
(autoload 'tpl-mode "tpl-mode" "Major mode for editing CTemplate files." t)
(add-hook 'tpl-mode-hook '(lambda () (font-lock-mode 1)))
;
(autoload 'jmk-mode "jmk-mode" "JMK mode." t)
(setq auto-mode-alist (append '(("\\.jmk$" .
                                 jmk-mode)) auto-mode-alist))
;
(global-set-key (kbd "M-q") 'fill-paragraph)
(setq-default fill-column 60)
;
(global-set-key (kbd "M-z") 'compile)
(global-set-key (kbd "C-c l") 'goto-line)
(global-set-key (kbd "C-x x") 'copy-to-register)
(global-set-key (kbd "C-x g") 'insert-register)
(global-set-key (kbd "C-x w") 'ethan-wspace-clean-all-modes)
(global-set-key (kbd "C-x t") 'untabify)
(global-set-key (kbd "C-c b") 'balance-windows-area)
(put 'upcase-region 'disabled nil)

(put 'downcase-region 'disabled nil)

;(setq compile-command "ant")

;(add-to-list 'load-path "/home/jdp/src/go/misc/emacs" t)
;(require 'go-mode-load)

;; Split windows in the (emacs-22) way
(setq split-height-threshold nil)
;;(setq split-width-threshold most-positive-fixnum)
(setq split-width-threshold 0)
;;(setq split-width-threshold nil);;(not!)

;; https://github.com/jimhourihan/glsl-mode
(autoload 'glsl-mode "glsl-mode" nil t)
(add-to-list 'auto-mode-alist '("\\.glsl\\'" . glsl-mode))

;;http://svn.clifford.at/openscad/trunk/contrib/scad.el
(autoload 'scad-mode "scad" "Major mode for editing SCAD code." t)
(add-to-list 'auto-mode-alist '("\\.scad$" . scad-mode))
