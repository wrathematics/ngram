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
#' @param decreasing
#' Should the sorted order be in descending order?
#' 
#' @seealso \code{\link{ngram-class}}, \code{\link{ngram}}
#' 
#' @examples
#' library(ngram)
#' 
#' str = "A B A C A B B"
#' ng = ngram(str)
#' get.ngrams(ng)[ng_order(ng)]
#' 
#' @keywords Tokenization
#' @name getters
#' @rdname getters
NULL



#' @rdname getters
#' @export
setGeneric(name="ng_order", function(ng, decreasing=FALSE) standardGeneric("ng_order"), package="ngram")

#' @useDynLib ngram R_ng_corpus_order
#' @rdname getters
#' @export
setMethod("ng_order", signature(ng="ngram"),
  function(ng, decreasing = FALSE)
  {
    ngo = .Call(R_ng_corpus_order, ng@ngl_ptr, ng@ngsize)
    order(ngo, decreasing=!decreasing)
  }
)



#' @rdname getters
#' @export
setGeneric(name="get.ngrams", function(ng) standardGeneric("get.ngrams"), package="ngram")

#' @useDynLib ngram R_ng_extract_ngrams
#' @rdname getters
#' @export
setMethod("get.ngrams", signature(ng="ngram"),
  function(ng)
  {
    .Call(R_ng_extract_ngrams, ng@ngl_ptr, ng@ngsize)
  }
)



#' @rdname getters
#' @export
setGeneric(name="get.string", function(ng) standardGeneric("get.string"), package="ngram")

#' @useDynLib ngram R_ng_extract_str
#' @rdname getters
#' @export
setMethod("get.string", signature(ng="ngram"),
  function(ng)
  {
    .Call(R_ng_extract_str, ng@str_ptr, ng@strlen)
  }
)



#' @rdname getters
#' @export
setGeneric(name="get.nextwords", function(ng) standardGeneric("get.nextwords"), package="ngram")

#' @rdname getters
#' @export
setMethod("get.nextwords", signature(ng="ngram"),
  function(ng)
  {
    stop("Not yet implemented")
  }
)
