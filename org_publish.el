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

;; Install dependencies
(package-install 'htmlize)

(require 'ox-publish)

;; Define the publishing project
(setq org-publish-project-alist
      (list
       (list "studies"
             :makeindex t
             :recursive t
             :base-directory "/home/sidd/vimwiki/studies/"
             :publishing-directory "./src/notes"
             :publishing-function 'org-html-publish-to-html)
       (list "static"
        :recursive t
        :base-directory "/home/sidd/vimwiki/studies/"
        :base-extension "jpg\\|gif\\|png"
        :publishing-directory "./src/notes"
        :publishing-function 'org-publish-attachment)))

(org-publish-all t)

(message "build finished!")
