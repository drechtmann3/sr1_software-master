Instructions for transferring files between computers using SCP with ubuntu

**********************************************
ON YOUR COMPUTER:
#network setup (need root)
ifconfig 192.168.0.1

#connection to SBC
telnet 192.168.0.50

#set up ssh server in ubuntu (only needs to be done once) (need root)
apt-get install openssh-server
***********************************************

**********************************************
IN THE SBC SHELL (you'll be there after using telnet):
#change to the directory that holds solar jackets programs
cd /usr/sjbin

#(if it doesn't exist, create the directory first) 
mkdir /usr/sjbin

#grab compiled program from your computer (example for matt's system)
scp matt@192.168.0.1:/home/matt/solarjackets/src/main ./main

#now you can run the binary.
**********************************************
