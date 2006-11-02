#!/bin/sh

gcc -E -dM - </dev/null | sort
