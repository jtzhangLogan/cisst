/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-    */
/* ex: set filetype=cpp softtabstop=4 shiftwidth=4 tabstop=4 cindent expandtab: */

/*
  $Id$

  Author(s):  Peter Kazanzides, Anton Deguet

  (C) Copyright 2007 Johns Hopkins University (JHU), All Rights Reserved.

--- begin cisst license - do not edit ---

This software is provided "as is" under an open source license, with
no warranty.  The complete license can be found in license.txt and
http://www.cisst.org/cisst/license.txt.

--- end cisst license ---
*/


#include <cisstMultiTask/mtsFunctionQualifiedReadOrWrite.h>
#include <cisstMultiTask/mtsCommandQualifiedReadOrWriteBase.h>
#include <cisstMultiTask/mtsDeviceInterface.h>
#include <cisstMultiTask/mtsRequiredInterface.h>

template <class _argumentType>
mtsFunctionQualifiedReadOrWrite<_argumentType>::~mtsFunctionQualifiedReadOrWrite()
{}

// specialize for Read using "mtsGenericObject &"
template <>
bool mtsFunctionQualifiedReadOrWrite<mtsGenericObject>::Bind(const mtsDeviceInterface * interface, const std::string & commandName)
{
    if (interface) {
        Command = interface->GetCommandQualifiedRead(commandName);
    }
    return interface && (Command != 0);
}


template <>
bool mtsFunctionQualifiedReadOrWrite<mtsGenericObject>::AddToRequiredInterface(mtsRequiredInterface & intfc, const std::string & commandName,
                                bool isRequired)
{ 
    return intfc.AddCommandPointer(commandName, Command, isRequired);
}


template <class _argumentType>
mtsCommandBase::ReturnType mtsFunctionQualifiedReadOrWrite<_argumentType>::operator()(const mtsGenericObject & qualifier,
                                                                                      ArgumentType& argument) const
{
    return Command ? Command->Execute(qualifier, argument) : mtsCommandBase::NO_INTERFACE;
}


template <class _argumentType>
const mtsGenericObject * mtsFunctionQualifiedReadOrWrite<_argumentType>::GetArgument1Prototype(void) const
{
    if (this->Command) {
        return this->Command->GetArgument1Prototype();
    }
    return 0;
}


template <class _argumentType>
const mtsGenericObject * mtsFunctionQualifiedReadOrWrite<_argumentType>::GetArgument2Prototype(void) const
{
    if (this->Command) {
        return this->Command->GetArgument2Prototype();
    }
    return 0;
}


template <class _argumentType>
void mtsFunctionQualifiedReadOrWrite<_argumentType>::ToStream(std::ostream & outputStream) const {
    if (this->Command != 0) {
        outputStream << "mtsFunctionQualifiedReadOrWrite for " << *Command;
    } else {
        outputStream << "mtsFunctionQualifiedReadOrWrite not initialized";
    }
}


// force instantiation
template class mtsFunctionQualifiedReadOrWrite<mtsGenericObject>;

