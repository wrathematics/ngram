library(ngram)

x <- "a b a c a b b"

# taken from NGramTokenizer(x, Weka_control(min=2, max=4))
truth <-
c("a b a c", "b a c a", "a c a b", "c a b b", "a b a", "b a c", 
"a c a", "c a b", "a b b", "a b", "b a", "a c", "c a", "a b", 
"b b")

test <- ngram_asweka(x, min=2, max=4)

stopifnot(all.equal(truth, test))
