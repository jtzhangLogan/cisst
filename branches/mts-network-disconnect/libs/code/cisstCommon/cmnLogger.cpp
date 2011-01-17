/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-    */
/* ex: set filetype=cpp softtabstop=4 shiftwidth=4 tabstop=4 cindent expandtab: */

/*
  $Id$

  Author(s):  Anton Deguet
  Created on: 2004-08-31

  (C) Copyright 2004-2010 Johns Hopkins University (JHU), All Rights
  Reserved.

--- begin cisst license - do not edit ---

This software is provided "as is" under an open source license, with
no warranty.  The complete license can be found in license.txt and
http://www.cisst.org/cisst/license.txt.

--- end cisst license ---

*/


#include <fstream>

#include <cisstCommon/cmnLogger.h>
#include <cisstCommon/cmnClassRegister.h>


cmnLogger::cmnLogger(const std::string & defaultLogFileName):
    Mask(CMN_LOG_ALLOW_ALL),
    LoDMultiplexerStreambuf()
{
    LoDMultiplexerStreambuf.AddChannel(*(DefaultLogFile(defaultLogFileName)), CMN_LOG_ALLOW_DEFAULT);
}


cmnLogger * cmnLogger::Instance(void)
{
    // create a static variable, i.e. singleton
    static cmnLogger instance;
    return &instance;
}


void cmnLogger::SetMaskInstance(cmnLogMask mask)
{
    CMN_LOG_INIT_VERBOSE << "Class cmnLogger: SetMask: overall mask set to \"" << cmnLogMaskToString(mask) << "\"" << std::endl;
    Mask = mask;
}


cmnLogMask cmnLogger::GetMaskInstance(void)
{
    return Mask;
}


cmnLogger::StreamBufType * cmnLogger::GetMultiplexerInstance(void)
{
    return &(LoDMultiplexerStreambuf);
}


std::ofstream * cmnLogger::DefaultLogFile(const std::string & defaultLogFileName)
{
    static std::ofstream defaultLogFile(defaultLogFileName.c_str());
    return &defaultLogFile;
}


void cmnLogger::HaltDefaultLogInstance(void)
{
    LoDMultiplexerStreambuf.RemoveChannel(*(DefaultLogFile()));
}


void cmnLogger::ResumeDefaultLogInstance(cmnLogMask newMask)
{
    LoDMultiplexerStreambuf.AddChannel(*(DefaultLogFile()), newMask);
}


void cmnLogger::AddChannelInstance(std::ostream & outputStream, cmnLogMask mask)
{
    LoDMultiplexerStreambuf.AddChannel(outputStream, mask);
}


void cmnLogger::RemoveChannelInstance(std::ostream & outputStream)
{
    LoDMultiplexerStreambuf.RemoveChannel(outputStream);
}


bool cmnLogger::SetMaskClass(const std::string & className, cmnLogMask mask)
{
    return cmnClassRegister::SetLogMaskClass(className, mask);
}


bool cmnLogger::SetMaskClassAll(cmnLogMask mask)
{
    return cmnClassRegister::SetLogMaskClassAll(mask);
}


bool cmnLogger::SetMaskClassMatching(const std::string & stringToMatch, cmnLogMask mask)
{
    return cmnClassRegister::SetLogMaskClassMatching(stringToMatch, mask);
}
