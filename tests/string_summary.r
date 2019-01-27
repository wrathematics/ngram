library(ngram)

check_same = function(test, truth) stopifnot(identical(test, truth))

x = "a b a c a b b"
test = string.summary(x)
check_same(test$chars, 13L)
check_same(test$letters, 7L)
check_same(test$whitespace, 6L)
check_same(test$punctuation, 0L)
check_same(test$digits, 0L)
check_same(test$words, 7L)
check_same(test$sentences, 0L)
check_same(test$lines, 1L)

y = "I am the very model of a modern major general.\nI have information vegetable, animal, and mineral."
test = string.summary(y)
check_same(test$chars, 97L)
check_same(test$letters, 77L)
check_same(test$whitespace, 16L)
check_same(test$punctuation, 4L)
check_same(test$digits, 0L)
check_same(test$words, 17L)
check_same(test$sentences, 2L)
check_same(test$lines, 2L)
