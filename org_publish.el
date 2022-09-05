(require 'ox-publish)

;; Define the publishing project
(setq org-publish-project-alist
      (list
       ;; (list "studies"
       ;;       :recursive t
       ;;       :base-directory "/home/sidd/vimwiki/studies/"
       ;;       :publishing-directory "./src/notes"
       ;;       :publishing-function 'org-html-publish-to-html)
       (list "static"
        :recursive t
        :base-directory "/homr/sidd/vimwiki/studies/"
        :base-extension "c\\|cc\\|css\\|js\\|png\\|jpg\\|jpeg\\|svg\\|gif\\|pdf\\|mp3\\|swf\\|zip\\|gz\\|txt\\|el\\|tar.gz\\|c\\|cpp\\|sh"
        :publishing-directory "./src/notes"
        :publishing-function 'org-publish-attachment)))

(org-publish-all t)
