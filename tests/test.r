library(ngram)

x <- "a b a c a b b"
ng <- ngram(x)

test <- babble(ng, seed=1234)
truth <- "b a c a b a c a b b c a b a c a b b b b c a b b a c a b b b a c a b a c a b a c a b b b b b b b a c a b a c a b b a b b b b a b b b a c a b a c a b a c a b b b a c a b b b b b b b b c a b a c a b b a b a c a b b b a c a b b a c a b a c a b b a c a b a c a b a c a b a c a b a c a b b a b a c a b a c "

stopifnot(all.equal(test, truth))
