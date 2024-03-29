# ngram

* **Version:** 3.2.2
* **License:** [BSD 2-Clause](https://opensource.org/license/bsd-2-clause/)
* **Project home**: https://github.com/wrathematics/ngram
* **Bug reports**: https://github.com/wrathematics/ngram/issues
* **Author:** Drew Schmidt and Christian Heckendorf


**ngram** is an R package for constructing n-grams ("tokenizing"), as well as generating new text based on the n-gram structure of a given text input ("babbling").  The package can be used for serious analysis or for creating "bots" that say amusing things.  See details section below for more information.

The package is designed to be extremely fast at tokenizing, summarizing, and babbling tokenized corpora.  Because of the architectural design, we are also able to handle very large volumes of text, with performance scaling very nicely.  Benchmarks and example usage can be found in the package vignette.



## Package Details

The original purpose for the package was to combine the book "Modern Applied Statistics in S" with the collected works of H. P. Lovecraft and generate amusing nonsense.  This resulted in the post [Modern Applied Statistics in R'lyeh](https://librestats.com/2014/07/01/modern-applied-statistics-in-rlyeh/).  I had originally tried several other available R packages to do this, but they were taking hours on a subset of the full combined corpus to preprocess the data into a somewhat inconvenient format.  However, the the ngram package can do the preprocessing into the desired format in well under a second (with about half of the preprocessing time spent on copying data for R coherency).

The package is mostly C, with the returned object (to R) being an external pointer.  In fact, the underlying C code can be compiled as a standalone library.  There is some minimal compatibility with exporting the data to proper R data structures, but it is incomplete at this time.

For more information, see the package vignette.



## Installation

You can install the stable version from CRAN using the usual `install.packages()`:

```r
install.packages("ngram")
```

The development version is maintained on GitHub:

```r
remotes::install_github("wrathematics/ngram")
```



## Example Usage

Here we present a few simple examples on how to use the **ngram** package.  See the package vignette for more detailed information on package usage.


### Tokenization, Summarizing, and Babbling

Let's take the sequence

```r
x <- "a b a c a b b"
```

Eagle-eyed readers will recognize this as the blood code from Mortal Kombat, but you can pretend it's something boring like an amino acid sequence or something.  We can form the n-gram structure of this sequence with the `ngram` function:

```r
library(ngram)

ng <- ngram(x, n=3)
```

There are various ways of printing the object.

```r
ng
# [1] "An ngram object with 5 3-grams"

print(ng, output="truncated")
# a b a 
# c {1} | 
# 
# a c a 
# b {1} | 
# 
# b a c 
# a {1} | 
# 
# a b b 
# NULL {1} | 
# 
# c a b 
# b {1} | 
```

With `output="truncated"`, only the first 5 n-grams will be shown (here there are only 5 total).  To see all (in the case of having more than 5), you can set `output="full"`.

There are several "getter" functions, but they are incomplete (see Notes section below).  Perhaps the most useful of them generates a "phrase table", or a list of n-grams by their frequency and proportion in the input text:

```r
get.phrasetable(ng)
#   ngrams freq      prop
# 1    a b    2 0.3333333
# 2    b a    1 0.1666667
# 3    c a    1 0.1666667
# 4    a c    1 0.1666667
# 5    b b    1 0.1666667
```

Finally, we can use the glory of Markov Chains to babble new sequences:

```r
babble(ng=ng, genlen=12)
# [1] "a b b c a b b a b a c a "
```

For reproducibility, use the `seed` argument:

```r
babble(ng=ng, genlen=12, seed=1234)
# [1] "a b a c a b b a b b a b "
```

At this time, we note that the seed may not guarantee the same results across machines. Currently only Solaris produces different values from mainstream platforms (Windows, Mac, Linux, FreeBSD), but potentially others could as well.


### Weka-Like Tokenization

There is also a tokenizer that behaves identically to the one in the **RWeka** package (only the **ngram** one is *significantly* faster!).  Using the same sequence `x` as above:

```r
ngram::ngram_asweka(x, min=2, max=3)
##  [1] "a b a" "b a c" "a c a" "c a b" "a b b" "a b"   "b a"   "a c"   "c a"  
## [10] "a b"   "b b"
```
