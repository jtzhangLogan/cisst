/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-    */
/* ex: set filetype=cpp softtabstop=4 shiftwidth=4 tabstop=4 cindent expandtab: */

/*
  $Id: mtsProxyBaseServer.cpp 145 2009-03-18 23:32:40Z mjung5 $

  Author(s):  Min Yang Jung
  Created on: 2009-03-17

  (C) Copyright 2009 Johns Hopkins University (JHU), All Rights
  Reserved.

--- begin cisst license - do not edit ---

This software is provided "as is" under an open source license, with
no warranty.  The complete license can be found in license.txt and
http://www.cisst.org/cisst/license.txt.

--- end cisst license ---
*/

#include <cisstMultiTask/mtsProxyBaseServer.h>

CMN_IMPLEMENT_SERVICES(mtsProxyBaseServer);

mtsProxyBaseServer::mtsProxyBaseServer() 
{
}

mtsProxyBaseServer::~mtsProxyBaseServer()
{
}

void mtsProxyBaseServer::Init(void)
{
    try {
        IceCommunicator = Ice::initialize();

        //std::string ObjectIdentityName = TaskManagerCommunicatorIdentity;
        //std::string ObjectAdapterName = TaskManagerCommunicatorIdentity + "Adapter";

        //IceAdapter = IceCommunicator->createObjectAdapterWithEndpoints(
        //        ObjectAdapterName.c_str(), // the name of the adapter
        //        // instructs the adapter to listen for incoming requests 
        //        // using the default protocol (TCP) at port number 10000
        //        "default -p 10000");

        //// Create a servant for TaskManager interface
        //Ice::ObjectPtr object = new mtsProxyBaseServer::TaskManagerChannelI;

        //// Inform the object adapter of the presence of a new servant
        //IceAdapter->add(object, IceCommunicator->stringToIdentity(ObjectIdentityName));
        
        InitSuccessFlag = true;
        CMN_LOG_CLASS(3) << "Server proxy initialization success. " << std::endl;
        return;
    } catch (const Ice::Exception& e) {
        CMN_LOG_CLASS(3) << "Server proxy initialization error: " << e << std::endl;
    } catch (const char * msg) {
        CMN_LOG_CLASS(3) << "Server proxy initialization error: " << msg << std::endl;
    }

    if (IceCommunicator) {
        InitSuccessFlag = false;
        try {
            IceCommunicator->destroy();
        } catch (const Ice::Exception& e) {
            CMN_LOG_CLASS(3) << "Server proxy initialization failed: " << e << std::endl;
        }
    }
}

void mtsProxyBaseServer::StartProxy(mtsTaskManager * callingTaskManager)
{
    // Initialize Ice object.
    // Notice that a worker thread is not created right now.
    Init();

    if (InitSuccessFlag) {
        //mtsTaskManagerProxyCommon::communicator = IceCommunicator;

        // Create a worker thread here and returns immediately.
        Arguments.Runner = &mtsProxyBaseServer::Runner;
        Arguments.proxy = this;
        Arguments.taskManager = callingTaskManager;

        WorkerThread.Create<ProxyWorker, ThreadArguments *>(
            &ProxyWorkerInfo, &ProxyWorker::Run, &Arguments, "C-PRX");
    }
}

void mtsProxyBaseServer::Runner(ThreadArguments * arguments)
{
    mtsTaskManager * TaskManager = arguments->taskManager;
    mtsProxyBaseServer * ProxyServer = 
        dynamic_cast<mtsProxyBaseServer*>(arguments->proxy);
    Ice::CommunicatorPtr ic = ProxyServer->GetIceCommunicator();

    try {
        // Activate the adapter. The adapter is initially created in a 
        // holding state. The server starts to process incoming requests
        // from clients as soon as the adapter is activated.
        ProxyServer->GetIceAdapter()->activate();

        // Blocking call
        ic->waitForShutdown();
    } catch (const Ice::Exception& e) {
        CMN_LOG_CLASS_AUX(ProxyServer, 3) << "Proxy initialization error: " << e << std::endl;
    } catch (const char * msg) {
        CMN_LOG_CLASS_AUX(ProxyServer, 3) << "Proxy initialization error: " << msg << std::endl;        
    }

    ProxyServer->OnThreadEnd();
}

void mtsProxyBaseServer::OnThreadEnd()
{
    if (IceCommunicator) {
        try {
            IceCommunicator->destroy();
            RunningFlag = false;

            CMN_LOG_CLASS(3) << "Proxy cleanup succeeded." << std::endl;
        } catch (const Ice::Exception& e) {
            CMN_LOG_CLASS(3) << "Proxy cleanup failed: " << e << std::endl;
        }
    }    
}

//-----------------------------------------------------------------------------
// From SLICE definition
//void mtsProxyBaseServer::TaskManagerChannelI::ShareTaskInfo(
//    const ::mtsTaskManagerProxy::TaskInfo& clientTaskInfo,
//    ::mtsTaskManagerProxy::TaskInfo& serverTaskInfo, 
//    const ::Ice::Current&)
//{
//    // Get the names of tasks' being managed by the peer TaskManager.
//    mtsTaskManagerProxy::TaskNameSeq::const_iterator it = clientTaskInfo.taskNames.begin();
//    for (; it != clientTaskInfo.taskNames.end(); ++it) {
//        CMN_LOG_CLASS_AUX(mtsTaskManager::GetInstance(), 5) << 
//            "CLIENT TASK NAME: " << *it << std::endl;
//    }
//
//    // Send my information to the peer ('peers' in the future).
//    mtsTaskManager::GetInstance()->GetNamesOfTasks(serverTaskInfo.taskNames);
//}
//-----------------------------------------------------------------------------