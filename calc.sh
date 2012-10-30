#!/bin/bash

canwork=0

if [ $# -eq 0 ]
then
  canwork=0
else
  canwork=1
fi

if [ $canwork -eq 0 ]
then
  printf "\033[34musage: calc.sh expression\033[0m\n"
else
  itop.out -s "$1" | eval.out -s
fi
