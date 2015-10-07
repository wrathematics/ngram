library(shiny)
library(ngram)


shinyServer(function(input, output, session){
  localstate <- reactiveValues()
  localstate$ng <- NULL
  localstate$tb <- capture.output(cat("
    Input the text you want to process in the box on the left.
  "))
  
  observeEvent(input$button_process, {
    
    ### Fit
    if (nchar(input$inputbox) > 1e7)
    {
      stop("Please keep text sizes under 10 Mib, or about 10 
      million characters.  The ngram package can handle much
      more, but please be polite to our generous hosting
      provider.")
    }
    
    if (!is.null(localstate$ng))
    {
      localstate$ng <- NULL
      invisible(gc())
    }
    
    localstate$ng <- ngram(str=input$inputbox, n=input$the_n_in_ngram)
    out <- gsub(x=capture.output(print(localstate$ng)), pattern="\\[1\\]|\"", replacement="")
    localstate$tb <- capture.output(cat(paste0("PROCESSED:  ", out, ".")))
  })
  
  ### Inspect
  observeEvent(input$button_inspect, {
    if (is.null(localstate$ng))
      stop("You must first process some input text.")
    else
      localstate$tb <- HTML(paste(capture.output(print(localstate$ng, output="truncated")), collapse="<br/>"))
  })
  
  ### Babble
  observeEvent(input$button_babble, {
    if (is.null(localstate$ng))
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
      
      localstate$tb <- capture.output(cat(babble(ng=localstate$ng, genlen=input$babble_len, seed=seed)))
    }
  })
  
  
  output$text <- renderUI({
    localstate$tb
  })
})


