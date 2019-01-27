library(ngram)

x = "a b a c a b b"
test = wordcount(x)
truth = 7L
stopifnot(identical(test, truth))

y = "I am the very model of a modern major general. I have information vegetable, animal, and mineral."
test = wordcount(y)
truth = 17L
stopifnot(identical(test, truth))
