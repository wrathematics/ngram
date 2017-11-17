library(ngram)

x = "a b a c a b b"

test = get.phrasetable(ngram(x, 2))
truth <- data.frame(
  ngrams = c("a b ", "b a ", "c a ", "a c ", "b b "), 
  freq = c(2, 1, 1, 1, 1),
  prop = c(1/3, 1/6, 1/6, 1/6, 1/6),
  stringsAsFactors=FALSE
)

stopifnot(all.equal(test, truth))



test = get.phrasetable(ngram(x, 3))
truth <- data.frame(
  ngrams = c("a b a ", "a c a ", "b a c ", "a b b ", "c a b "), 
  freq = c(1, 1, 1, 1, 1),
  prop = c(1/5, 1/5, 1/5, 1/5, 1/5),
  stringsAsFactors=FALSE
)

stopifnot(all.equal(test, truth))
