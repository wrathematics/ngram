library(shiny)


about.thisapp <- HTML("
  <p>
  This 
  <a href='http://www.rstudio.com/products/shiny/'>shiny</a> 
  app uses 
  <a href='https://github.com/wrathematics/ngram'>the ngram package</a>, 
  where you can also find the source for this shiny app.
  </p>
  
  <p>
  The ngram package contains utilities for constructing n-grams, 
  as well as generating new text based on the n-gram structure of 
  a given text input.
  The original purpose for the package was to combine the book
  <i>Modern Applied Statistics in S</i> with the collected works of H. P.
  Lovecraft and generate amusing nonsense.  This resulted in the post
  <a href='http://librestats.com/2014/07/01/modern-applied-statistics-in-rlyeh/'>Modern Applied Statistics in R'lyeh</a>.
  </p>
")



shinyUI(
  fluidPage(
    titlePanel("Fun with Markov Chains"),
    fluidRow(
      sidebarPanel(
        sliderInput("the_n_in_ngram", "Number of words per 'gram' (n)", 1, 10, 2, step=1, ticks=TRUE),
        tags$textarea(id="inputbox", rows=8, cols=40, "a b a c a b b"),
        br(),
        actionButton("button_process", "Process"),
        actionButton("button_inspect", "Inspect"),
        sliderInput("babble_len", "Number of words to 'babble'", 10, 250, 150, step=10, ticks=TRUE),
        textInput("ng_seed", "Seed", ""),
        br(),br(),
        actionButton("button_babble", "Babble")
      ),
      mainPanel(
        tabsetPanel(
          tabPanel("Results", htmlOutput("text")),
          tabPanel("About", helpText(about.thisapp))
        )
      )
    )
  )
)

