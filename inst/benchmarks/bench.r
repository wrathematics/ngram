library(tau)
library(ngram)

x <- ngram::rcorpus(50000)

tautime <- system.time(pt1 <- textcnt(x, n=3, split=" ", method="string"))[3]
ngtime <- system.time(pt2 <- get.phrasetable(ngram(x, n=3)))[3]

cat("tau: ", tautime, "\n")
cat("ngram: ", ngtime, "\n")
cat("tau/ngram: ", tautime/ngtime, "\n")
