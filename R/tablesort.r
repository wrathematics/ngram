tablesort <- function(df, sortby.colnum)
{
  if (!is.data.frame(df))
    stop("argument 'df' must be a dataframe")
  
  col <- as.integer(sortby.colnum)
  if (is.na(col))
    stop("argument 'sortby.colnum' must be an integer")
  if (col < 1 || col > ncol(df))
    stop("argument 'sortby.column' must be between 1 and ncol(df)")
  
  df[order(-df[, col]), ]
}
