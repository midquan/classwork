#!/bin/bash
# 1 = ip address 2 = skeleton key 3 = user 4 = dictionary 
# example of using arguments to a script
nc -zv $1 100-13000 2>&1 | grep succeeded > ports 
python3 ports.py ports $1 $2 $3 
python3 dictionary.py $1 FoundPort $2 $3 $4 
python3 bufferoverflow $1 FoundPort  
curl $1:FoundPort
