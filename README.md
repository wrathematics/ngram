# ngram

This is an R package for constructing n-grams, as well as generating 
new text based on the n-gram structure of a given text input.

The original purpose for the package was to combine the book
"Modern Applied Statistics in S" with the collected works of H. P.
Lovecraft and generate amusing nonsense.  This resulted in the post
[Modern Applied Statistics in R'lyeh](http://librestats.com/2014/07/01/modern-applied-statistics-in-rlyeh/).
I had originally tried several other available R packages to do this,
but they were taking hours on a subset of the full combined corpus 
to preprocess the data into a somewhat inconvenient format.  However,
the the ngram package can do the preprocessing into the desired
format in well under a second (with about half of the preprocessing
time spent on copying data for R coherency).

The package is mostly C, with the returned object (to R) being an
external pointer.  In fact, the underlying C code can be compiled
as a standalone library.  There is some minimal compatibility
with exporting the data to proper R data structures, but it is 
incomplete at this time.



## Installation

Using the devtools package: 

```r
library(devtools)
install_github("wrathematics/ngram")
```

An older version of this package is also available on the CRAN.

