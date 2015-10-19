library(ngram)

x <- "watch out! a snake!"

test <- suppressWarnings(splitter(x, split.char=FALSE, split.space=FALSE, split.punct=FALSE))
truth <- x
stopifnot(all.equal(test, truth))

test <- splitter(x, split.char=TRUE, split.space=TRUE, split.punct=TRUE)
truth <- "w a t c h _ o u t ! _ a _ s n a k e !"
stopifnot(all.equal(test, truth))

test <- splitter(x, split.char=TRUE, split.space=FALSE, split.punct=FALSE)
truth <- "w a t c h o u t ! a s n a k e !"
stopifnot(all.equal(test, truth))

test <- splitter(x, split.char=TRUE, split.space=TRUE, split.punct=FALSE)
truth <- "w a t c h _ o u t ! _ a _ s n a k e !"
stopifnot(all.equal(test, truth))

test <- splitter(x, split.char=TRUE, split.space=FALSE, split.punct=TRUE)
truth <- "w a t c h o u t ! a s n a k e !"
stopifnot(all.equal(test, truth))

test <- splitter(x, split.char=FALSE, split.space=TRUE, split.punct=FALSE)
truth <- "watch _ out! _ a _ snake!"
stopifnot(all.equal(test, truth))

test <- splitter(x, split.char=FALSE, split.space=FALSE, split.punct=TRUE)
truth <- "watch out ! a snake !"
stopifnot(all.equal(test, truth))

test <- splitter(x, split.char=FALSE, split.space=TRUE, split.punct=TRUE)
truth <- "watch _ out ! _ a _ snake !"
stopifnot(all.equal(test, truth))

