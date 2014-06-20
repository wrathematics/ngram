ng.extract.ngrams <- function(ng)
{
  .Call("ng_extract_ngrams", ng@ng_ptr, ng@ngsize, PACKAGE="ngram")
}



setMethod("get.ngrams", signature(ng="ngram"),
  function(ng)
    ng.extract.ngrams(ng=ng)
)



ng.extract.str <- function(ng)
{
  .Call("ng_extract_str", ng@str_ptr, ng@strlen, PACKAGE="ngram")
}



setMethod("get.string", signature(ng="ngram"),
  function(ng)
    ng.extract.str(ng=ng)
)



setMethod("get.nextwords", signature(ng="ngram"),
  function(ng)
    stop("Not yet implemented")
)

