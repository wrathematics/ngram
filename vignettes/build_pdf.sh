#!/bin/sh

PKGVER=`grep "Version:" ../DESCRIPTION | sed -e "s/Version: //"`
sed -i -e "s/myversion{.*}/myversion{${PKGVER}}/" ngram-guide.Rnw


rm *.aux *.bbl *.blg *.log *.out *.toc
pdflatex ngram-guide.Rnw
bibtex ngram-guide
pdflatex ngram-guide.Rnw
pdflatex ngram-guide.Rnw
Rscript -e "tools::compactPDF('ngram-guide.pdf', gs_quality='ebook')"
rm *.aux *.bbl *.blg *.log *.out *.toc *.dvi

mv -f *.pdf ../inst/doc/
cp -f *.Rnw ../inst/doc/
