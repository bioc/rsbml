.First.lib <- function(libname, pkgname)
{
  if(.Platform$OS.type == "windows"){
     if(!exists("Sys.setenv", baseenv())) Sys.setenv <- base::Sys.putenv
     temp <- Sys.getenv("PATH")
     Sys.putenv(PATH = paste(normalizePath(file.path(libname, pkgname, "libs")), 
                               file.path(Sys.getenv("R_HOME"), "modules", fsep="\\"), temp, sep=";"))
     on.exit(Sys.setenv(PATH = temp))
  }
  library.dynam("rsbml", pkgname, libname)
}
