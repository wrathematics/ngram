library(shiny)


about.thisapp <- HTML("
  <p>
  This 
  <a href='http://www.rstudio.com/products/shiny/'>shiny</a> 
  app uses 
  <a href='https://github.com/wrathematics/ngram'>the ngram package</a>, 
  where you can also find the 
  <a href='https://github.com/wrathematics/ngram/tree/master/inst/ngram'>source</a>
  for this shiny app.
  <br><br>
  
  Hosting is generously provided by 
  <a href='https://www.shinyapps.io/'>RStudio</a>.
  </p>"
)



shinyUI(
  fluidPage(
    titlePanel("Fun with Markov Chains"),
    fluidRow(
    sidebarPanel(
      sliderInput("the_n_in_ngram", "Number of words per 'gram' (n)", 1, 10, 3, step=1, ticks=TRUE),
      tags$textarea(id="inputbox", rows=8, cols=60, "a b a c a b b"),
      actionButton("button_process", "Process"),
      actionButton("button_inspect", "Inspect"),
      sliderInput("babble_len", "Number of words to 'babble'", 10, 250, 150, step=10, ticks=TRUE),
      actionButton("button_babble", "Babble")
    ),
    mainPanel(
      tabsetPanel(
        tabPanel("Results", htmlOutput("text")),
        tabPanel("About", helpText(about.thisapp))
      )
    )
  ))
)

