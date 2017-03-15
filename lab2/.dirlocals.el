    ;; The 'nil' configuration applies to all modes.
    ((nil . ((indent-tabs-mode . t)
            (tab-width . 4)))
     (haskell-mode . (
            ;; Highlight leading space characters in Haskell files.
            (eval . (highlight-regexp "^ *")))))
