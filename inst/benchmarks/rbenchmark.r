library(rbenchmark)
library(tau)
library(ngram)

x <- ngram::rcorpus(50000)

reps <- 15
cols <- c("test", "replications", "elapsed", "relative")

benchmark(tau=textcnt(x, n=3, split=" ", method="string"), ngram=get.phrasetable(ngram(x, n=3)), replications=reps, columns=cols)

