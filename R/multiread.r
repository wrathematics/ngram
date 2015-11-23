#' Multiread
#' 
#' Read in a collection of text files.
#' 
#' The \code{extension} argument is not a general regular
#' expression pattern, but a simplified pattern.  For example,
#' the pattern \code{*.txt} is really equivalent to 
#' \code{*[.]txt$} as a regular expression.  If you need more
#' complicated patterns, you should directly use the \code{dir()}
#' function.
#' 
#' @param path
#' The base file path to search.
#' @param extension
#' An extension or the "*" wildcard (for everything).  For example, 
#' to read in files ending \code{.txt}, you could specify 
#' \code{extension="txt"}.  For the purposes of this function,
#' each of \code{*.txt}, \code{*txt}, \code{.txt}, and \code{txt}
#' are treated the same.
#' @param recursive
#' Logical; should the search include all subdirectories?
#' @param ignore.case
#' Logical; should case be ignored in the extension? For example, if
#' \code{TRUE}, then \code{.r} and \code{.R} files are treated the
#' same.
#' @param prune.empty
#' Logical; should empty files be removed from the returned list?
#' @param pathnames
#' Logical; should the full path be included in the names of the
#' returned list.
#' 
#' @return
#' A named list of strings, where the names are the file names.
#' 
#' @examples
#' \dontrun{
#' path <- system.file(package="ngram")
#' 
#' ### Read all files in the base path
#' multiread(path, extension="*")
#' 
#' ### Read all .r/.R files recursively (warning: lots of text)
#' multiread(path, extension="r", recursive=TRUE, ignore.case=TRUE)
#' 
#' }
#' 
#' @keywords Utility
#' @export
multiread <- function(path=".", extension="txt", recursive=FALSE, ignore.case=FALSE, prune.empty=TRUE, pathnames=TRUE)
{
  assert_that(is.string(path))
  assert_that(is.string(extension))
  assert_that(is.scalar(recursive) && is.logical(recursive))
  assert_that(is.scalar(ignore.case) && is.logical(ignore.case))
  assert_that(is.scalar(prune.empty) && is.logical(prune.empty))
  assert_that(is.scalar(pathnames) && is.logical(pathnames))
  
  if (extension == "*")
    pattern <- extension
  else
  {
    if (grepl(extension, pattern="[.]"))
      extension <- gsub(extension, pattern="([*]|[.])", replacement="")
    
    pattern <- paste0("*[.]", extension, "$")
  }
  
  files <- dir(path=path, pattern=pattern, recursive=recursive, ignore.case=ignore.case, include.dirs=FALSE, full.names=TRUE)
  
  text <- lapply(lapply(files, readLines), concatenate)
  names(text) <- files
  
  if (prune.empty)
    text <- text[-which(text == "")]
  
  if (!pathnames)
     names(text) <- gsub(names(text), pattern="^.*\\/", replacement="")
  
  text
}
