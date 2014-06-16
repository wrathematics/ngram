#!/bin/sh

xelatex cover.tex
xelatex cover.tex
Rscript -e "tools::compactPDF('.', gs_quality='ebook')"
rm *.aux *.bbl *.blg *.log *.out *.toc *.idx *.lof *.lot *.ind *.ilg
