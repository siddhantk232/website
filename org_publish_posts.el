;; Set the package installation directory so that packages aren't stored in the
;; ~/.emacs.d/elpa path.
(require 'package)
(setq package-user-dir (expand-file-name "./.packages"))
(setq package-archives '(("melpa" . "https://melpa.org/packages/")
                         ("elpa" . "https://elpa.gnu.org/packages/")))

;; Initialize the package system
(package-initialize)
(unless package-archive-contents
  (package-refresh-contents))

(require 'ox-publish)

;; Install dependencies
(package-install 'htmlize)
(require 'htmlize)

(setq org-html-htmlize-output-type 'css)

(setq org-html-validation-link nil            ;; Don't show validation link
      org-html-head-include-scripts nil       ;; Use our own scripts
      org-html-head-include-default-style nil ;; Use our own styles
      org-html-head "<link rel=\"stylesheet\" type=\"text/css\" href=\"https://gongzhitaao.org/orgcss/org.css\"/>")


;; Define the publishing project
(setq org-publish-project-alist
      (list
       (list "studies"
             :makeindex t
             :recursive t
             :base-directory "./posts" ;; on CI
             :publishing-directory "./site/posts"
             :html-html5-fancy t
             :with-toc t
             :time-stamp-file nil
             :with-author t
             :publishing-function 'org-html-publish-to-html)))

(org-publish-all t)

(message "build finished!")
