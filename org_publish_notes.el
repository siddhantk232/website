;; WARN: This script no longer works because of the relative link to my private notes directory that
;; is only available on my computer.
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
      org-export-with-section-numbers nil     ;; remove section numbering
      org-html-head "<link rel=\"apple-touch-icon\" sizes=\"180x180\" href=\"/assets/favicon/apple-touch-icon.png\">
      <link rel=\"icon\" type=\"image/png\" sizes=\"32x32\" href=\"/assets/favicon/favicon-32x32.png\">
      <link rel=\"icon\" type=\"image/png\" sizes=\"16x16\" href=\"/assets/favicon/favicon-16x16.png\">
      <link rel=\"manifest\" href=\"/assets/manifest.json\">
      <link rel=\"stylesheet\" href=\"/css/base.css\" />
      <link rel=\"stylesheet\" href=\"/css/prism-monokai.css\" />
      ")



;; Define the publishing project
(setq org-publish-project-alist
      (list
       (list "studies"
             :makeindex t
             :recursive t
             :base-directory "../../vimwiki/studies" ;; on CI
             :publishing-directory "./site/notes"
             :html-html5-fancy t
             :with-toc t
             :time-stamp-file nil
             :html-preamble "
              <header>
                  <div >
                    <a id=\"home_url\" href=\"/\">home</a>
                    <ul class=\"nav\">
                      <li  class='md-enable'><a href=\"/\">home</a></li>
                      <li><a  href=\"/posts\">posts</a></li>
                      <li><a  class=\"active\" href=\"/notes\">notes</a></li>
                      <li><a  href=\"/about\">about</a></li>
                    </ul>
                  </div>
              </header>
             "
             :with-author t
             :publishing-function 'org-html-publish-to-html)
       (list "static"
        :recursive t
        :base-directory "../../vimwiki/studies" ;; on CI
        :base-extension "jpg\\|gif\\|png\\|c\\|cpp\\|py"
        :publishing-directory "./site/notes"
        :publishing-function 'org-publish-attachment)))

(org-publish-all t)

(message "build finished!")
