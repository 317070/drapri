#!/usr/bin/env python
"""Remove pyscard from site-packages

__author__ = "http://www.gemalto.com"

Copyright 2001-2012 gemalto
Author: Jean-Daniel Aussel, mailto:jean-daniel.aussel@gemalto.com

This file is part of pyscard.

pyscard is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

pyscard is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with pyscard; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
"""


import os
import os.path

from distutils.sysconfig import get_python_lib


def _rmdir(path):
    for file in os.listdir(path):
        item = os.path.join(path, file)
        if os.path.isdir(item) and not os.path.islink(item):
            print 'deleting ', item
            _rmdir(item)
        else:
            print 'deleting ', item
            os.remove(item)
    print 'deleting ', path
    os.rmdir(path)

smartcardpackagedir = os.path.join(get_python_lib(1), 'smartcard')
if os.path.exists(smartcardpackagedir):
    _rmdir(smartcardpackagedir)
