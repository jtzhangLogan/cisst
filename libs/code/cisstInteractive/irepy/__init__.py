# -*- tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
# ex: set softtabstop=4 shiftwidth=4 tabstop=4 expandtab:

#  $Id: __init__.py,v 1.6 2007/04/26 19:33:57 anton Exp $
#
#  Author(s):	Andrew LaMora
#  Created on: 2004-04-30
#
#  (C) Copyright 2004-2007 Johns Hopkins University (JHU), All Rights
#  Reserved.

# --- begin cisst license - do not edit ---
# 
# This software is provided "as is" under an open source license, with
# no warranty.  The complete license can be found in license.txt and
# http://www.cisst.org/cisst/license.txt.
# 
# --- end cisst license ---

#------------------------------------------
# Import the IRE libraries
#------------------------------------------
import ireMain

import threading

class IreThread(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)
    def run(self):
        ireMain.launchIrePython()


#------------------------------------------
# function:  launch
#
# command-line command to launch the ire
#------------------------------------------
def launch():
	ireMain.launchIrePython()


#------------------------------------------
# Global statements
#------------------------------------------

#from pkgutil import extend_path
#__path__ = extend_path(__path__, __name__)

print "Welcome to the IRE!"
print "Use irepy.launch() to launch the IRE GUI"
#ireMain.launchIrePython()


