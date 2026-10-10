// SPDX-License-Identifier: LGPL-2.1-or-later

#include <FCGlobal.h>

#pragma once

#ifndef DesignExport
# ifdef Design_EXPORTS
#  define DesignExport FREECAD_DECL_EXPORT
# else
#  define DesignExport FREECAD_DECL_IMPORT
# endif
#endif

#ifndef DesignGuiExport
# ifdef DesignGui_EXPORTS
#  define DesignGuiExport FREECAD_DECL_EXPORT
# else
#  define DesignGuiExport FREECAD_DECL_IMPORT
# endif
#endif
