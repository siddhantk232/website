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
