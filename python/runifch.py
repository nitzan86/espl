#!/usr/bin/python

import sys
import subprocess
from dirwatch import Dirwatch

if __name__ == '__main__':

    command = sys.argv[1]
    
    def f (changed_files, removed_files):
        print changed_files
        print 'Removed', removed_files
        for fileName in changed_files:
            subprocess.call(command + " " + fileName, shell=True)

    dirs = sys.argv[2:]
    if not dirs:
        dirs = ["."]

    
    Dirwatch(dirs, f, 1).watch()