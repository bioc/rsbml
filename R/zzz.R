.onLoad <- function(libname, pkgname)
{
  if(.Platform$OS.type == "windows"){
     temp <- Sys.getenv("PATH")
     Sys.setenv(PATH = paste(normalizePath(file.path(libname, pkgname, "libs")), 
                               file.path(Sys.getenv("R_HOME"), "modules", fsep="\\"), temp, sep=";"))
     on.exit(Sys.setenv(PATH = temp))
  }
  library.dynam("rsbml", pkgname, libname)
}
