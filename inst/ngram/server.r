library(shiny)
library(ngram)


# Shiny buttons record the number of clicks (rather than TRUE/FALSE
# or clicked/not clicked). This function is a little gross, but gets
# the job done of managing the state of buttons in the user's 
# session and each function call.  It returns a vector of logicals 
# that indicate whether or not a button's new state is different 
# from our last known value for it.
# 
# I'm assuming that only one button can be pressed at a time.
buttonfix <- function(session, ...)
{
  vals <- unlist(list(...))
  names <- paste0(".__shinyshim_", 1L:length(vals))
  changed <- rep(FALSE, length(names))
  
  if (!exists(names[1L], envir=session))
  {
    for (i in 1L:length(names))
      assign(x=names[i], value=vals[i], envir=session)
  }
  else
  {
    for (i in 1:length(names))
    {
      nm <- names[i]
      
      val <- get(x=nm, envir=session)
      if (val != vals[i])
      {
        assign(x=nm, value=vals[i], envir=session)
        changed[i] <- TRUE
        break
      }
    }
  }
  
  return(changed)
}



shinyServer(function(input, output, session){
  output$text <- renderUI({
    changed <- buttonfix(session, input$button_process, input$button_inspect, input$button_babble)
    
    ### Process
    if (changed[1L])
    {
      if (exists("ng", envir=session))
      {
        rm(ng, envir=session)
        invisible(gc)
      }
      
      if (nchar(input$inputbox) > 1e7)
      {
        stop("Please keep text sizes under 10 Mib, or about 10 
        million characters.  The ngram package can handle (much)
        more, but please be polite to our generous hosting
        provider.")
      }
      else
      {
        ng <- ngram(x=input$inputbox, n=input$the_n_in_ngram)
        assign(x="ng", value=ng, envir=session)
        out <- gsub(x=capture.output(print(ng)), pattern="\\[1\\]|\"", replacement="")
        capture.output(cat(paste0("PROCESSED:  ", out, ".")))
      }
    }
    ### Inspect
    else if (changed[2L])
    {
      if (!exists("ng", envir=session))
        stop("You must first process some input text.")
      else
        HTML(paste(capture.output(print(get("ng", envir=session), output="truncated")), collapse="<br/>"))
    }
    ### Babble
    else if (changed[3L])
    {
      if (!exists("ng", envir=session))
        stop("You must first process some input text.")
      else
      {
        seed <- input$ng_seed
        if (seed == "")
          seed <- ngram:::getseed()
        else if (is.na(as.character(seed)))
          stop("Seed must be a number.")
        else
          seed <- as.integer(seed)
        
        capture.output(cat(babble(ng=get("ng", envir=session), genlen=input$babble_len, seed=seed)))
      }
    }
    else
    {
      capture.output(cat("
      Input the text you want to process in the box on the left.
      "))
    }
  })
})


