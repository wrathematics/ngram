title_case <- function(x) gsub(x, pattern="(^|[[:space:]])([[:alpha:]])", replacement="\\1\\U\\2", perl=TRUE)



#' Text Summary
#' 
#' @param string
#' An input string.
#' @param wordlen_max,senlen_max,syllen_max
#' The maximum lengths of words/sentences/syllables to consider.
#' 
#' @return
#' A list of class \code{string_summary}.
#' 
#' @examples
#' x <- "a b a c a b b"
#' 
#' string.summary(x)
#' 
#' @keywords Summarize
#' @export
string.summary <- function(string, wordlen_max=10, senlen_max=10, syllen_max=10)
{
  assert_that(is.string(string))
  assert_that(is.count(wordlen_max))
  assert_that(is.count(senlen_max))
  assert_that(is.count(syllen_max))
  
  
  wordlen_max <- as.integer(wordlen_max)
  if (is.na(wordlen_max))
    stop("Argument 'wordlen_max' must be a positive integer.")
  
  senlen_max <- as.integer(senlen_max)
  if (is.na(senlen_max))
    stop("Argument 'senlen_max' must be a positive integer.")
  
  syllen_max <- as.integer(syllen_max)
  if (is.na(syllen_max))
    stop("Argument 'syllen_max' must be a positive integer.")
  
  
  ret <- .Call(R_stringsummary, string, wordlen_max, senlen_max, syllen_max)
  class(ret) <- "string_summary"
  
  ret
}



spacenames <- function(x)
{
  maxlen <- max(sapply(names(x), nchar))
  names <- title_case(x=names(x))
  spacenames <- simplify2array(lapply(names, function(str) paste0(str, ":", paste0(rep(" ", maxlen-nchar(str)), collapse=""))))
}



#' @method print string_summary
#' @export
print.string_summary <- function(x, ...)
{
  sn <- spacenames(x)
  
  len <- length(x)
  indx <- (len-2):len
  y <- x[indx]
  x <- x[-indx]
  
  sn_x <- sn[-indx]
  cat(paste(sn_x, x, sep=" ", collapse="\n"), "\n")
  
  sn_y <- sn[indx]
  for (i in 1:length(y))
  {
    tab <- table(y[i])
    names <- names(tab)
    dimnames(tab) <- NULL
#    cat(sn_y[i])
    cat(paste(sn_y[i], paste0(names, collapse=" "), sep=" ", collapse="\n"), "\n")
    cat(paste(paste(rep(" ", nchar(sn_y[1])), collapse=""), paste0(tab, collapse=" "), sep=" ", collapse="\n"), "\n")
  }
  
  invisible()
}
