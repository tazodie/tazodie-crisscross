#!/bin/sh

wc -l `find ../source | grep -v .svn | grep -v vcproj | grep -v .dsp | grep -v Makefile`