/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-    */
/* ex: set filetype=cpp softtabstop=4 shiftwidth=4 tabstop=4 cindent expandtab: */

/*
  $Id$

  Author(s):  Anton Deguet
  Created on: 2009-04-13

  (C) Copyright 2009-2013 Johns Hopkins University (JHU), All Rights
  Reserved.

--- begin cisst license - do not edit ---

This software is provided "as is" under an open source license, with
no warranty.  The complete license can be found in license.txt and
http://www.cisst.org/cisst/license.txt.

--- end cisst license ---

*/


/*!
  \file
  \brief Defines mtsGenericObject
*/

#ifndef _mtsGenericObject_h
#define _mtsGenericObject_h

#include <cisstCommon/cmnGenericObject.h>
#include <cisstCommon/cmnDataFunctions.h>
#include <cisstCommon/cmnSerializer.h>
#include <cisstCommon/cmnDeSerializer.h>

#include <cisstMultiTask/mtsMacros.h>

// Always include last!
#include <cisstMultiTask/mtsExport.h>

#include <string>
#include <iostream>


/*!
  \brief Base class for data object in cisstMultiTask.

  \ingroup cisstMultiTask

  \sa cmnGenericObject
*/
class CISST_EXPORT mtsGenericObject: public cmnGenericObject {

    typedef cmnGenericObject BaseType;

    /*! Time stamp.  When used in conjunction with mtsStateTable, the
      time stamp will be automatically updated using
      AutomaticTimeStamp. */
    CMN_DECLARE_MEMBER_AND_ACCESSORS(double, Timestamp);

    /*! Turn on/off automatic timestamping by the state table.  All
      objects stored in a state table can be automatically timestamped
      at the end of the Run method (see mtsTask and derived classes).
      If this flag is set to false, data objects will have to be
      timestamped manually.  This flag is set to true by default. */
    CMN_DECLARE_MEMBER_AND_ACCESSORS(bool, AutomaticTimestamp);

    /*! General flag used to indicate if the data is valid.  This flag
      has to be updated by the user.  This data member is initialized
      to false by the constructor. */
    CMN_DECLARE_MEMBER_AND_ACCESSORS(bool, Valid);

public:

    /*! Constructor, initialize Timestamp to 0 and Valid flag to
      false. */
    inline mtsGenericObject(void):
        TimestampMember(0.0),
        AutomaticTimestampMember(true),
        ValidMember(false)
    {}

    /*! Constructor with initialization for each member */
    inline mtsGenericObject(double timestamp, bool automaticTimestamp, bool valid):
        TimestampMember(timestamp),
        AutomaticTimestampMember(automaticTimestamp),
        ValidMember(valid)
    {}

    /*! Copy constructor */
    inline mtsGenericObject(const mtsGenericObject & other):
        cmnGenericObject(),
        TimestampMember(other.TimestampMember),
        AutomaticTimestampMember(other.AutomaticTimestampMember),
        ValidMember(other.ValidMember)
    {}

    /*! Destructor.  Does nothing specific. */
    inline virtual ~mtsGenericObject(void)
    {}

    /*! Set timestamp if AutomaticTimeStamp is set to true. This is
      only meaningful if the derived class contains a timestamp and
      overrides this method.
      \param timeStamp time stamp in seconds
      \returns true if time stamp was set. */
    bool SetTimestampIfAutomatic(double timestamp);

    /*! Human readable text output.  This method only streams the data
      members of mtsGenericObject, i.e. the Timestamp and Valid flag.
      It should be called by any derived class re-implementing
      ToStream. */
    virtual void ToStream(std::ostream & outputStream) const;

    /*! Raw text output to stream */
    virtual void ToStreamRaw(std::ostream & outputStream, const char delimiter = ' ',
                             bool headerOnly = false, const std::string & headerPrefix = "") const;

    /*! Read from an unformatted text input (e.g., one created by ToStreamRaw).
      Returns true if successful. */
    virtual bool FromStreamRaw(std::istream & inputStream, const char delimiter = ' ');

    /*! Binary serialization */
    virtual void SerializeRaw(std::ostream & outputStream) const;

    /*! Binary deserialization */
    virtual void DeSerializeRaw(std::istream & inputStream);

    /* documented in base class */
    size_t ScalarNumber(void) const;
    bool ScalarNumberIsFixed(void) const;

    /* documented in base class */
    double Scalar(const size_t index) const throw (std::out_of_range);

    /* documented in base class */
    std::string ScalarDescription(const size_t index, const std::string & userDescription = "") const throw (std::out_of_range);
};

void CISST_EXPORT cmnDataCopy(mtsGenericObject & destination, const mtsGenericObject & source);

void CISST_EXPORT cmnDataSerializeBinary(std::ostream & outputStream, const mtsGenericObject & data) throw (std::runtime_error);

void CISST_EXPORT cmnDataDeSerializeBinary(std::istream & inputStream, mtsGenericObject & data,
                                           const cmnDataFormat & remoteFormat, const cmnDataFormat & localFormat) throw (std::runtime_error);

void CISST_EXPORT cmnDataSerializeText(std::ostream & outputStream, const mtsGenericObject & data, const char delimiter) throw (std::runtime_error);

std::string CISST_EXPORT cmnDataSerializeTextDescription(const mtsGenericObject & data, const char delimiter, const std::string & userDescription = "");

void CISST_EXPORT cmnDataDeSerializeText(std::istream & inputStream, mtsGenericObject & data, const char delimiter) throw (std::runtime_error);

bool CISST_EXPORT cmnDataScalarNumberIsFixed(const mtsGenericObject & data);

size_t CISST_EXPORT cmnDataScalarNumber(const mtsGenericObject & data);

double CISST_EXPORT cmnDataScalar(const mtsGenericObject & data, const size_t index) throw (std::out_of_range);

std::string CISST_EXPORT cmnDataScalarDescription(const mtsGenericObject & data, const size_t index, const std::string & userDescription = "") throw (std::out_of_range);

#if CISST_HAS_JSON
void CISST_EXPORT cmnDataToJSON(const mtsGenericObject & data, Json::Value & jsonValue);
void CISST_EXPORT cmnDataFromJSON(mtsGenericObject & data, const Json::Value & jsonValue) throw (std::runtime_error);
#endif // CISST_HAS_JSON

#endif // _mtsGenericObject_h

