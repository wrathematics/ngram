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

