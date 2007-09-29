library(rsbml)
doc <- rsbml_read(system.file("sbml", "GlycolysisLayout.xml",
                            package = "rsbml"))
dom <- rsbml_dom(doc)
