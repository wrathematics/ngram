test <- function(ng, genlen=1)
{
  .Call("ng_test", ng@ng_ptr, ng@ngsize, as.integer(genlen))
}
