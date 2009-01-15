/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-    */
/* ex: set filetype=cpp softtabstop=4 shiftwidth=4 tabstop=4 cindent expandtab: */

/*
  $Id: SineGeneratorPython.i,v 1.3 2007/05/31 20:52:46 anton Exp $

  Author(s): Peter Kazanzides
  Created on: 2005-12-21

  (C) Copyright 2005-2007 Johns Hopkins University (JHU), All Rights
  Reserved.

--- begin cisst license - do not edit ---

This software is provided "as is" under an open source license, with
no warranty.  The complete license can be found in license.txt and
http://www.cisst.org/cisst/license.txt.

--- end cisst license ---
*/


%module SineGeneratorPython

%mutable;

%header %{
    #include "cisstCommon/cisstCommon.i.h"
    #include "SineGenerator.h"
%}


%import "cisstCommon/cisstCommon.i"

%include "SineGenerator.h"

