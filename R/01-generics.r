setGeneric(name="ngram", 
  function(x, n=2, ...) 
    standardGeneric("ngram"), 
  package="ngram"
)

setGeneric(name="babble", 
  function(ng,  ...) 
    standardGeneric("babble"), 
  package="ngram"
)

setGeneric(name="get.ngrams", 
  function(ng, ...) 
    standardGeneric("get.ngrams"), 
  package="ngram"
)

setGeneric(name="get.string", 
  function(ng, ...) 
    standardGeneric("get.string"), 
  package="ngram"
)

setGeneric(name="get.nextwords", 
  function(ng, ...) 
    standardGeneric("get.nextwords"), 
  package="ngram"
)

setGeneric(name="wordcount", 
  function(x, ...) 
    standardGeneric("wordcount"), 
  package="ngram"
)

