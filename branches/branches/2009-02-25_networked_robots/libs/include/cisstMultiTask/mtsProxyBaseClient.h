/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-    */
/* ex: set filetype=cpp softtabstop=4 shiftwidth=4 tabstop=4 cindent expandtab: */

/*
  $Id: mtsProxyBaseClient.h 142 2009-03-11 23:02:34Z mjung5 $

  Author(s):  Min Yang Jung
  Created on: 2009-04-10

  (C) Copyright 2009 Johns Hopkins University (JHU), All Rights
  Reserved.

--- begin cisst license - do not edit ---

This software is provided "as is" under an open source license, with
no warranty.  The complete license can be found in license.txt and
http://www.cisst.org/cisst/license.txt.

--- end cisst license ---
*/

#ifndef _mtsProxyBaseClient_h
#define _mtsProxyBaseClient_h

#include <cisstMultiTask/mtsProxyBaseCommon.h>
#include <cisstOSAbstraction/osaSleep.h>

#include <cisstMultiTask/mtsExport.h>

/*!
  \ingroup cisstMultiTask

  TODO: add class summary here
*/

template<class _argumentType>
class CISST_EXPORT mtsProxyBaseClient: public mtsProxyBaseCommon<_argumentType> {

 public:
    typedef mtsProxyBaseCommon<_argumentType> BaseType;

protected:
    const std::string EndpointInfo;
    const std::string CommunicatorID;
    Ice::ObjectPrx ProxyObject;

    virtual void CreateProxy() = 0;

    void Init(void)
    {
        try {
            Ice::InitializationData initData;
            initData.logger = new typename BaseType::ProxyLogger();
            initData.properties = Ice::createProperties();
            initData.properties->setProperty("Ice.ImplicitContext", "Shared");
            //initData.properties->load(PropertyFileName);

            this->IceCommunicator = Ice::initialize(initData);
            
            // Create Logger
            this->Logger = this->IceCommunicator->getLogger();
            
            //ProxyObject = IceCommunicator->propertyToProxy(PropertyName);
            //std::string stringfiedProxy = PropertyName + ":default -p 10705";
            std::string stringfiedProxy = CommunicatorID + EndpointInfo;
            ProxyObject = this->IceCommunicator->stringToProxy(stringfiedProxy);

            // If a proxy fails to be created, an exception is thrown.
            CreateProxy();

            this->InitSuccessFlag = true;
            this->Runnable = true;
            
            this->Logger->trace("mtsProxyBaseClient", "Client proxy initialization success");
            return;
        } catch (const Ice::Exception& e) {
            if (this->Logger) {
                this->Logger->trace("mtsProxyBaseClient", "Client proxy initialization error");
                this->Logger->trace("mtsProxyBaseClient", e.what());
            } else {
                std::cout << "mtsProxyBaseClient: Client proxy initialization error." << std::endl;
                std::cout << "mtsProxyBaseClient: " << e.what() << std::endl;
            }
        } catch (const char * msg) {
            if (this->Logger) {
                this->Logger->trace("mtsProxyBaseClient", "Client proxy initialization error");
                this->Logger->trace("mtsProxyBaseClient", msg);
            } else {
                std::cout << "mtsProxyBaseClient: Client proxy initialization error." << std::endl;
                std::cout << "mtsProxyBaseClient: " << msg << std::endl;
            }
        }

        if (!this->InitSuccessFlag) {
            try {
                this->IceCommunicator->destroy();
            } catch (const Ice::Exception& e) {
                this->Logger->trace("mtsProxyBaseClient", "Client proxy clean-up error");
                this->Logger->trace("mtsProxyBaseClient", e.what());
            }
        }
    }

public:
    mtsProxyBaseClient(const std::string & endpointInfo, 
                       const std::string & communicatorID):
        BaseType("", "", BaseType::PROXY_CLIENT),
        EndpointInfo(endpointInfo),
        CommunicatorID(communicatorID)
    {}
    virtual ~mtsProxyBaseClient() {}

    inline const bool IsRunnable() const { return this->Runnable; }

    virtual void Start(_argumentType * callingClass) = 0;

    virtual void OnThreadEnd(void)
    {
        if (this->IceCommunicator) {
            try {
                this->IceCommunicator->destroy();
                this->Runnable = false;

                this->Logger->trace("mtsProxyBaseClient", "Client proxy clean-up success.");
            } catch (const Ice::Exception& e) {
                this->Logger->trace("mtsProxyBaseClient", "Client proxy clean-up failed.");
                this->Logger->trace("mtsProxyBaseClient", e.what());
            }
        }    
    }
};

#endif // _mtsProxyBaseClient_h

