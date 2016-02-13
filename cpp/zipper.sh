#!/bin/bash

# List of patterns to exclude useless files and folders
EXCLUDED="*.git* *build* *bin* *.pro.user"
# Make zip archive
zip -r hashcode2016-src.zip hashcode2016 -x ${EXCLUDED}


