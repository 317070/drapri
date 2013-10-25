#!/usr/bin/env python
"""Build documentation using epydoc, and create an archive including
non generated documentation.

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
import re
import sys
import shutil

from epydoc.cli import cli

from distutils.sysconfig import get_python_lib
from distutils.archive_util import make_archive
from distutils import dir_util

# where the source doc files are located, as well as epydoc configuration file
sourcedocdir = os.path.join('..', '..', 'src', 'smartcard', 'doc')
sourceexampledir = os.path.join('..', '..', 'src', 'smartcard', 'Examples')
configfile = os.path.join('..', '..', 'src', 'smartcard', 'doc', 'epydoc.cfg')

# this is where the doc is copied and generated with epydoc
targetgenerateddir = os.path.join('..', '..', 'generated')
targetdocdir = os.path.join(targetgenerateddir, 'doc')
targetepydocdir = os.path.join(targetdocdir, 'epydoc')

# the smartcard module must be installed to run epydoc
smartcardpackagedir = os.path.join(get_python_lib(), 'smartcard')

# check that we are in the correct directory
assert os.path.exists(sourcedocdir), "Can't find directory: " + sourcedocdir

# remove an already existing 'generated' directory
if os.path.isdir(targetgenerateddir):
    shutil.rmtree(targetgenerateddir)
os.makedirs(targetgenerateddir)

# this pattern is searched in html files to include sourceforge logo for
# pyscard
searchterm = '>pyscard</th>'
placeholder = re.compile(searchterm)
sourceforgelogo = '<a href="http://sourceforge.net/projects/pyscard">\
<img src="http://sflogo.sourceforge.net/sflogo.php?group_id=196342&amp;\
type=11" width="120" height="30" alt="Get pyscard at SourceForge.net. \
Fast, secure and Free Open Source software downloads" /></a>'


# looks for placeholder and insert sourceforge logo if found
def insertSourceForgeLogo(file):
    try:
        fileToSearch = open(file, 'r')
        data = fileToSearch.read()
        data = data.split('\n')
        for line in data:
            bFound = placeholder.search(line)
            if (bFound):
                break
        fileToSearch.close()
    except IOError:
        print "No such file:", file
        return
    if bFound:
        fileToReplace = open(file, 'w')
        for line in data:
            fileToReplace.write(line + '\n')
            if placeholder.search(line):
                fileToReplace.write(sourceforgelogo)
        fileToReplace.close()

# build documentation package for pyscard
if os.path.exists(smartcardpackagedir):
    os.makedirs(targetepydocdir)
    sys.argv = \
        ['--html', '--output', targetepydocdir, '--config=' + configfile]
    cli()
    dir_util.copy_tree(sourcedocdir, targetdocdir, preserve_mode=0, verbose=1)
    dir_util.copy_tree(
        sourceexampledir,
        os.path.join(targetdocdir, 'Examples'),
        preserve_mode=0,
        verbose=1)

    # remove subversion directories (*//.svn)
    files = os.walk(os.path.join(targetdocdir))
    dirstodelete = []
    for dirpath, dn, fn in files:
        if '.svn' in dirpath[-4:] and \
            dirpath not in dirstodelete: dirstodelete.append(dirpath)
    for dir in dirstodelete:
        dir_util.remove_tree(dir)

    # insert sourceforge pyscard logo in html pages
    files = os.walk(os.path.join(targetdocdir))
    htmlfiles = []
    for dirpath, dn, filenames in files:
        for filename in filenames:
            root, ext = os.path.splitext(filename)
            if '.html' == ext:
                htmlfiles.append(os.path.join(dirpath, filename))
    for file in htmlfiles:
        insertSourceForgeLogo(file)
else:
    print "Can't find " + smartcardpackagedir

# zip documentation
make_archive(
    os.path.join(targetgenerateddir, 'pyscard-doc'),
    'zip',
    root_dir=targetgenerateddir,
    base_dir='doc')
