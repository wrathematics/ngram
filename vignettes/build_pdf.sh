#!/bin/sh

### Fix versioning in vignette, rebuild cover
PKGVER=`grep "Version:" ../DESCRIPTION | sed -e "s/Version: //"`
sed -i -e "s/myversion{.*}/myversion{${PKGVER}}/" ngram-guide.Rnw

cd cover
./build_cover.sh
cd ..


### Rebuild vignette
rm *.aux *.bbl *.blg *.log *.out *.toc
Rscript -e "knitr::knit('ngram-guide.Rnw')"
pdflatex ngram-guide.tex
bibtex ngram-guide
pdflatex ngram-guide.tex
pdflatex ngram-guide.tex
Rscript -e "tools::compactPDF('ngram-guide.pdf', gs_quality='ebook')"
rm -f *.aux *.bbl *.blg *.log *.out *.toc *.dvi
rm -f Sweavel.sty
rm -f ngram-guide.tex

#mv -f *.pdf ../inst/doc/
#cp -f *.Rnw ../inst/doc/

