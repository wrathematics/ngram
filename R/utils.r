#' Concatenate
#' 
#' This is a utility for concatenating strings together.  This is
#' handy because if you want to generate the n-grams for several different
#' texts, you must first put them into a single string.
#' 
#' @param ... 
#' Input text(s).
#' @param collapse 
#' A character to separate the input strings if a vector of
#' strings is supplied; otherwisethis does nothing.
#' @param rm.spaces 
#' logical; determines if spaces should be removed from the
#' final string.
#' 
#' @return 
#' A string.
#' 
#' @seealso \code{\link{Preprocess}}
#' 
#' @examples
#' \dontrun{
#' library(ngram)
#' 
#' words <- c("a", "b", "c")
#' wordcount(words)
#' concat(words)
#' }
#' 
#' @name Concatenate
#' @rdname concat
#' @export
concat <- function(..., collapse="", rm.spaces=FALSE)
{
  l <- list(...)
  
  str <- paste(sapply(l, paste, collapse=collapse), collapse=collapse)
  
  if (rm.spaces)
    str <- gsub(x=str, pattern=" ", replacement="")
  
  return( str )
}



#' Preprocessing
#' 
#' A simple text preprocessor for use with the \code{ngram()} function.
#' 
#' The input text \code{x} must already be in the correct form for
#' \code{ngram()}, i.e., a single string (character vector of length 1).
#' 
#' The \code{case} argument can take 3 possible values: \code{NULL}, in which
#' case nothing is done, or \code{lower} or \code{upper}, wherein the case of
#' the input text will be made lower/upper case, repesctively.
#' 
#' @param x 
#' Input text.
#' @param case 
#' Option to change the case of the text. See Details section for
#' appropriate values.
#' @param split.at.punct 
#' logical; determines if spaces should be inserted
#' before and after punctuation (making them individual characters for an
#' n-gram model).
#' 
#' @return 
#' \code{concat()} returns
#' 
#' @seealso \code{\link{Concatenate}}
#' 
#' @examples
#' \dontrun{
#' library(ngram)
#' 
#' x <- "Watch  out    for snakes!  "
#' preprocess(x)
#' preprocess(x, case="upper", split.at.punct=TRUE)
#' }
#' 
#' @name Preprocess
#' @rdname preprocess
#' @export
preprocess <- function(x, case=NULL, split.at.punct=FALSE)
{
  if (!is.null(case))
  {
    case <- match.arg(tolower(case), c("lower", "upper"))
    if (case == "lower")
      x <- tolower(x)
    else if (case == "upper") 
      x <- toupper(x)
  }
  
  if (split.at.punct)
    x <- gsub(x=x, pattern="([[:punct:]])", replacement=" \\1 ")
  
  # fix spacing
  x <- gsub(pattern="(\\t| +)", replacement=" ", x=x)
  # remove trailing whitespace
  x <- sub(pattern=" +$", replacement="", x=x)
  
  return( x )
}



#' Wordcount
#' 
#' \code{wordcount()} counts words.  Currently a "word" is a clustering of
#' characters separated from another clustering of charactersby at least 1
#' space.  That is the law.
#' 
#' @param x 
#' A string or ngram object.
#' 
#' @return 
#' A count.
#' 
#' @seealso \code{\link{Preprocess}}
#' 
#' @examples
#' \dontrun{
#' library(ngram)
#' 
#' words <- c("a", "b", "c")
#' wordcount(words)
#' str <- concat(words)
#' wordcount(str)
#' }
#' 
#' @name Wordcount
#' @rdname wordcount
NULL

#' @rdname wordcount
#' @export
setGeneric(name="wordcount", 
  function(x) 
    standardGeneric("wordcount"), 
  package="ngram"
)

#' @rdname wordcount
#' @export
setMethod("wordcount", signature(x="character"),
  function(x)
  {
    if (length(x) > 1)
      return( sum(sapply(x, wordcount)) )
    
    sep <- ' '
    .Call(R_ngram_wordcount, x, sep, nchar(sep), PACKAGE="ngram")
  }
)

#' @rdname wordcount
#' @export
setMethod("wordcount", signature(x="ngram"),
  function(x)
  {
    ret <- wordcount(x=get.string(x))
    
    return( ret )
  }
)

