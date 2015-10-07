#' Character Splitter
#' 
#' A utility function for use with n-gram modeling.  This function
#' splits a string without spaces into one useable with \code{ngram()}.
#' 
#' @param string
#' An input string.
#' @param spacechar
#' The character to represent a space.
#' 
#' @return
#' A string.
#' 
#' @examples
#' x <- "abacabb"
#' charsplitter(x)
#' 
#' y <- "split at every character, preserve spaces"
#' charsplitter(y)
#' 
#' @export
charsplitter <- function(string, spacechar="_")
{
  string <- gsub(string, pattern=" +", replacement=spacechar)
  split <- strsplit(string, split="")[[1]]
  paste0(split, collapse=" ")
}
