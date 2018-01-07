#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import os.path

# This is a tiny script to help you creating a CSV file from a face
# database with a similar hierarchie:
#
#  philipp@mango:~/facerec/data/at$ tree
#  .
#  |-- README
#  |-- s1
#  |   |-- 1.pgm
#  |   |-- ...
#  |   |-- 10.pgm
#  |-- s2
#  |   |-- 1.pgm
#  |   |-- ...
#  |   |-- 10.pgm
#  ...
#  |-- s40
#  |   |-- 1.pgm
#  |   |-- ...
#  |   |-- 10.pgm
#

script_path = os.path.abspath(os.path.dirname(__file__))

if __name__ == "__main__":
    BASE_PATH = os.path.join(script_path, "att_faces")
    SEPARATOR = ";"

    with open("att_faces/at.txt", 'w') as fh:
        label = 0
        for dirname, dirnames, filenames in os.walk(BASE_PATH):
            for subdirname in dirnames:
                subject_path = os.path.join(dirname, subdirname)
                for filename in os.listdir(subject_path):
                    abs_path = "%s%s%s" % (subject_path, os.path.sep, filename)
                    # print "%s%s%d" % (abs_path, SEPARATOR, label)
                    fh.write(abs_path)
                    fh.write(SEPARATOR)
                    fh.write(str(label))
                    fh.write("\n")
                label = label + 1