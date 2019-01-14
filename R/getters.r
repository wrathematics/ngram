#' ngram Getters
#' 
#' Some simple "getters" for \code{ngram} objects. Necessary since the internal
#' representation is not a native R object.
#' 
#' \code{ngram.order} returns an R vector with the original corpus order of the ngrams.
#'
#' \code{get.ngrams()} returns an R vector of all n-grams.
#' 
#' \code{get.nextwords()} does nothing at the moment; it will be implemented in
#' future releases.
#' 
#' \code{getnstring()} recovers the input string as an R string.
#' 
#' @param ng 
#' An ngram object.
#' 
#' @seealso \code{\link{ngram-class}}, \code{\link{ngram}}
#' 
#' @examples
#' library(ngram)
#' 
#' str <- "A B A C A B B"
#' ng <- ngram(str)
#' get.ngrams(ng)[ngram.order(ng)]
#' 
#' @keywords Tokenization
#' @include ngram.r
#' @name getters
#' @rdname getters
NULL

#' @rdname getters
#' @export
setGeneric(name="ngram.order",
  function(ng, decreasing=FALSE)
    standardGeneric("ngram.order"),
  package="ngram"
)

#' @rdname getters
#' @export
setMethod("ngram.order", signature(ng="ngram"),
  function(ng, decreasing = FALSE)
  {
    ngo = .Call(ng_corpus_order, ng@ngl_ptr, ng@ngsize)
    order(ngo,decreasing=!decreasing)
  }
)



#' @rdname getters
#' @export
setGeneric(name="get.ngrams", 
  function(ng) 
    standardGeneric("get.ngrams"), 
  package="ngram"
)

#' @rdname getters
#' @export
setMethod("get.ngrams", signature(ng="ngram"),
  function(ng)
  {
    .Call(ng_extract_ngrams, ng@ngl_ptr, ng@ngsize)
  }
)



#' @rdname getters
#' @export
setGeneric(name="get.string", 
  function(ng) 
    standardGeneric("get.string"), 
  package="ngram"
)

#' @rdname getters
#' @export
setMethod("get.string", signature(ng="ngram"),
  function(ng)
  {
    .Call(ng_extract_str, ng@str_ptr, ng@strlen)
  }
)



#' @rdname getters
#' @export
setGeneric(name="get.nextwords", 
  function(ng) 
    standardGeneric("get.nextwords"), 
  package="ngram"
)

#' @rdname getters
#' @export
setMethod("get.nextwords", signature(ng="ngram"),
  function(ng)
    stop("Not yet implemented")
)
