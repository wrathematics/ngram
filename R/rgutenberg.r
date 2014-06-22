#setMethod("ngram", signature(x="book"),
#  function(x, n=2)
#  {
#    str <- rgutenberg::text(words=x, with.license=FALSE)
#    
#    return( ngram(x=str, n=n) )
#  }
#)

#setMethod("wordcount", signature(x="book"),
#  function(x, n=2)
#  {
#    str <- rgutenberg::text(words=x)
#    
#    return( ngram(x=str, n=n) )
#  }
#)
