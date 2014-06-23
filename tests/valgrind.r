### Checks for memory leaks
library(ngram)

x <- "A B A C A B B"
ng <- ngram(x)
#y <- babble(ng, genlen=5, seed=1234)

rm(x)
quiet <- gc()
