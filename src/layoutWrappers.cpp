#include "rsbml.h"

#ifdef USE_LAYOUT
#if LIBSBML_VERSION >= 50000

Layout_t *LayoutModelPlugin_createLayout(LayoutModelPlugin_t *plugin) {
  return plugin->createLayout();
}

int LayoutModelPlugin_getNumLayouts(LayoutModelPlugin_t *plugin) {
  return plugin->getNumLayouts();
}
Layout_t *LayoutModelPlugin_getLayout(LayoutModelPlugin_t *plugin,
                                      unsigned int index)
{
  return plugin->getLayout(index);
}

int SBase_enablePackage(SBase_t *sbase, const char *pkgURI,
                        const char *pkgPrefix, Rboolean flag)
{
  return sbase->enablePackage(pkgURI, pkgPrefix, flag);
}

#endif
#endif
