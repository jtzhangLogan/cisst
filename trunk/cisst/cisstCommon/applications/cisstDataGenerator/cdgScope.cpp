/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-    */
/* ex: set filetype=cpp softtabstop=4 shiftwidth=4 tabstop=4 cindent expandtab: */

/*
  $Id$

  Author(s):  Anton Deguet
  Created on: 2010-09-06

  (C) Copyright 2010-2012 Johns Hopkins University (JHU), All Rights
  Reserved.

--- begin cisst license - do not edit ---

This software is provided "as is" under an open source license, with
no warranty.  The complete license can be found in license.txt and
http://www.cisst.org/cisst/license.txt.

--- end cisst license ---

*/

#include "cdgScope.h"

const std::string cdgScopeNames[] = {"global",
                                     "class",
                                     "base-class",
                                     "typedef",
                                     "member",
                                     "code"};

const std::string & cdgScope::GetScopeName(void) const
{
    return cdgScopeNames[this->GetScope()];
}


cdgScope::cdgScope(unsigned int lineNumber):
    LineNumber(lineNumber)
{
}


void cdgScope::GenerateLineComment(std::ostream & outputStream) const
{
    outputStream << "/* source line: " << LineNumber << " */" << std::endl;
}
