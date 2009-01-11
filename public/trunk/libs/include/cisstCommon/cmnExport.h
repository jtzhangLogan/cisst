/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-    */
/* ex: set filetype=cpp softtabstop=4 shiftwidth=4 tabstop=4 cindent expandtab: */

/*
  $Id: cmnExport.h 20 2009-01-08 16:09:57Z adeguet1 $

  Author(s):  Anton Deguet
  Created on: 2001-11-04

  (C) Copyright 2001-2007 Johns Hopkins University (JHU), All Rights
  Reserved.

--- begin cisst license - do not edit ---

This software is provided "as is" under an open source license, with
no warranty.  The complete license can be found in license.txt and
http://www.cisst.org/cisst/license.txt.

--- end cisst license ---
*/


/*! \file
    \brief Macros to export the symbols of cisstCommon (in a Dll).
*/

// check if this module is build as a DLL
#ifdef cisstCommon_EXPORTS
#define CISST_THIS_LIBRARY_AS_DLL
#endif

// include common defines
#include <cisstCommon/cmnExportMacros.h>

// avoid impact on other modules
#undef CISST_THIS_LIBRARY_AS_DLL

