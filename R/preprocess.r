#' Basic Text Preprocessor
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
#' Option to change the case of the text. Value should be "upper",
#' "lower", or NULL (no change).
#' @param remove.punct
#' Logical; should punctuation be removed?
#' @param remove.numbers
#' Logical; should numbers be removed?
#' @param fix.spacing
#' Logical; should multi/trailing spaces be collapsed/removed.
#' 
#' @return 
#' \code{concat()} returns
#' 
#' @examples
#' library(ngram)
#' 
#' x <- "Watch  out    for snakes!  111"
#' preprocess(x)
#' preprocess(x, remove.punct=TRUE, remove.numbers=TRUE)
#' 
#' @keywords Preprocessing
#' @export
preprocess <- function(x, case="lower", remove.punct=FALSE, remove.numbers=FALSE, fix.spacing=TRUE)
{
  assert_that(is.string(x))
  assert_that(is.string(case))
  assert_that(is.scalar(remove.punct) && is.logical(remove.punct))
  assert_that(is.scalar(remove.numbers) && is.logical(remove.numbers))
  assert_that(is.scalar(fix.spacing) && is.logical(fix.spacing))
  
  
  ### Case
  if (!is.null(case))
  {
    case <- match.arg(tolower(case), c("lower", "upper"))
    if (case == "lower")
      x <- tolower(x)
    else if (case == "upper") 
      x <- toupper(x)
  }
  
  ### Punctuation and numbers
  if (remove.punct)
    rempunct <- "[[:punct:]]"
  else
    rempunct <- ""
  
  if (remove.numbers)
    remnum <- "\\d"
  else
    remnum <- ""
  
  pattern <- paste0("(", paste(rempunct, remnum, sep="|"), ")")
  x <- gsub(x, pattern=pattern, replacement="")
  
  ### Spacing
  if (fix.spacing)
  {
    x <- gsub(x, pattern="(\\t| +)", replacement=" ")
    x <- sub(pattern=" +$", replacement="", x=x)
  }
  
  return( x )
}
