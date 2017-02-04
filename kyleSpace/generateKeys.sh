#!/bin/bash

for i in {1..10}
do
   ssh-keygen -t rsa -N "" -f /home/kyle/Desktop/Developement/CSC521/CSC-521-Projects/kyleSpace/keys/id_rsa
   cat /home/kyle/Desktop/Developement/CSC521/CSC-521-Projects/kyleSpace/keys/id_rsa.pub >> /home/kyle/Desktop/Developement/CSC521/CSC-521-Projects/kyleSpace/keys/allKeys

   rm /home/kyle/Desktop/Developement/CSC521/CSC-521-Projects/kyleSpace/keys/id_rsa
   rm /home/kyle/Desktop/Developement/CSC521/CSC-521-Projects/kyleSpace/keys/id_rsa.pub
done

   sed -e s/ssh-rsa\ //g -i /home/kyle/Desktop/Developement/CSC521/CSC-521-Projects/kyleSpace/keys/allKeys
   sed -e s/\ kyle@kyle-VirtualBox//g -i /home/kyle/Desktop/Developement/CSC521/CSC-521-Projects/kyleSpace/keys/allKeys
