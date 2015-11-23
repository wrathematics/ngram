#' Character Splitter
#' 
#' A utility function for use with n-gram modeling.  This function
#' splits a string based on various options.
#' 
#' Note that choosing \code{split.char=TRUE} necessarily implies 
#' \code{split.punct=TRUE} as well --- but \emph{not} necessarily that
#' \code{split.space=TRUE}.
#' 
#' @param string
#' An input string.
#' @param split.char
#' Logical; should a split occur after every character?
#' @param split.space
#' Logical; determines if spaces should be preserved as characters in
#' the n-gram tokenization.  The character(s) used for spaces are
#' determined by the \code{spacesep} argument.
#' characters.
#' @param spacesep
#' The character(s) to represent a space in the case that
#' \code{split.space=TRUE}.  Should not just be a space(s).
#' @param split.punct
#' Logical; determines if splits should occur at punctuation.
#' 
#' @return
#' A string.
#' 
#' @examples
#' x <- "watch out! a snake!"
#' 
#' splitter(x, split.char=TRUE)
#' splitter(x, split.space=TRUE, spacesep="_")
#' splitter(x, split.punct=TRUE)
#' 
#' 
#' @keywords Preprocessing
#' @export
splitter <- function(string, split.char=FALSE, split.space=TRUE, spacesep="_", split.punct=FALSE)
{
  assert_that(is.string(string))
  assert_that(is.scalar(split.char) && is.logical(split.char))
  assert_that(is.scalar(split.space) && is.logical(split.space))
  assert_that(is.string(spacesep))
  assert_that(is.scalar(split.punct) && is.logical(split.punct))
  
  
  if (!split.char && !split.space && !split.punct)
  {
    warning("No splitting options selected.")
    return(string)
  }
  
  if (nchar(gsub(spacesep, pattern=" +", replacement="")) == 0)
    stop("argument 'spacesep' should not only contain spaces.")
  
  if (split.space)
  {
    # fix spacing
    string <- gsub(x=string, pattern="(\\t| +)", replacement=" ")
    string <- sub(x=string, pattern=" +$", replacement="")
    
    string <- gsub(x=string, pattern="([[:space:]])", replacement=paste0(" ", spacesep, " "))
  }
  
  if (split.char)
  {
    string <- strsplit(string, split="")[[1]]
    string <- paste0(string, collapse=" ")
  }
  
  if (split.punct)
  {
    string <- gsub(x=string, pattern="([[:punct:]])", replacement=" \\1 ")
  }
  
  string <- gsub(x=string, pattern="(\\t| +)", replacement=" ")
  string <- sub(x=string, pattern=" +$", replacement="")
  return(string)
}
