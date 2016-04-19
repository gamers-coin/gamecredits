#GameCredits integration/staging tree
================================
Copyright (c) 2009-2011 Bitcoin Developers<br>
Copyright (c) 2011-2013 Litecoin Developers<br>
Copyright (c) 2013-2014 GamersCoin Developers<br>
Copyright (c) 2015-2016 GameCredits Developers<br>

![GameCredits](http://i.imgur.com/OFViLxH.png)

#What is GameCredits?
----------------
[![GameCredits](http://i.imgur.com/aA99Ryn.jpg)](https://www.youtube.com/watch?v=ls8ad6G5ejA)

A new and exciting Open Source Gaming currency that will revolutionize in-game purchases and bring developers a monetization based on fair-play rules.

GameCredits is a lite version of Bitcoin using scrypt as a proof-of-work algorithm.
 - 1.5 minute block targets
 - subsidy halves in 840k blocks
 - ~84 million total coins
 - 25 coins per block
 - 1 blocks to retarget difficulty

# We :heart: Pull Requests!
Seriously, we really do.  It doesn't matter whether you're fixing a typo or overhauling a major area of the code base.  You will be showered in :thumbsup: :thumbsup: :thumbsup:<br>

#License
-------
![GameCredits](http://i.imgur.com/Nfb8DQx.png)

GameCredits is released under the terms of the MIT license. See `COPYING` for more
information or see http://opensource.org/licenses/MIT.

#Development process
-------------------

Developers work in their own trees, then submit pull requests when they think
their feature or bug fix is ready.

If it is a simple/trivial/non-controversial change, then one of the GameCredits
development team members simply pulls it.

If it is a *more complicated or potentially controversial* change, then the patch
submitter will be asked to start a discussion (if they haven't already) on the
[mailing list](https://bitcointalk.org/index.php?topic=1266597.0).

The patch will be accepted if there is broad consensus that it is a good thing.
Developers should expect to rework and resubmit patches if the code doesn't
match the project's coding conventions (see `doc/coding.txt`) or are
controversial.

#Compiling the GameCredits daemon from source on Debian
-----------------------------------------------------
The process for compiling the GameCredits daemon, gamecreditsd, from the source code is pretty simple. This guide is based on the latest stable version of Debian Linux, though it should not need many modifications for any distro forked from Debian, such as Ubuntu and Xubuntu.

###Update and install dependencies

```
apt-get update && apt-get upgrade
apt-get install ntp git build-essential libssl-dev libdb-dev libdb++-dev libboost-all-dev libqrencode-dev autoconf automake pkg-config unzip

wget http://miniupnp.free.fr/files/download.php?file=miniupnpc-1.8.tar.gz && tar -zxf download.php\?file\=miniupnpc-1.8.tar.gz && cd miniupnpc-1.8/
make && make install && cd .. && rm -rf miniupnpc-1.8 download.php\?file\=miniupnpc-1.8.tar.gz
```
Note: Debian testing and unstable require libboost1.54-all-dev.

###Compile the daemon
```
git clone https://github.com/gamecredits-project/GameCredits
```

###Compile gamecreditsd with own Berkeley DB
```
cd GameCredits
./autogen.sh
./configure
make
cd src
strip gamecreditsd
```

###Compile gamecreditsd with Berkeley DB 4.8 Recommended
```
cd GameCredits
./autogen.sh
./bdb48.sh
make
cd src
strip gamecreditsd
```

###Add a user and move gamecreditsd
```
adduser gamecredits && usermod -g users gamecredits && delgroup gamecredits && chmod 0701 /home/gamecredits
mkdir /home/gamecredits/bin
cp ~/GameCredits/src/gamecreditsd /home/gamecredits/bin/gamecreditsd
chown -R gamecredits:users /home/gamecredits/bin
cd && rm -rf GameCredits
```

###Run the daemon
```
su gamecredits
cd && bin/gamecreditsd
```

On the first run, gamecreditsd will return an error and tell you to make a configuration file, named gamecredits.conf, in order to add a username and password to the file.
```
nano ~/.gamecredits/gamecredits.conf && chmod 0600 ~/.gamecredits/gamecredits.conf
```
Add the following to your config file, changing the username and password to something secure: 
```
daemon=1
rpcuser=<username>
rpcpassword=<secure password>
server=1
listen=1
txindex=1
#txindex will record every transaction from the blockchain to your offline db
#it's an optional thing. It takes a lot longerr to sync that way 0 if you don't care
rpcport=40001
port=40002
rpcallowip=127.0.0.1
addnode=194.135.81.138
addnode=46.105.118.15:40002
addnode=142.4.218.175:40002
addnode=216.146.143.177:40002
addnode=73.9.181.217:3215
addnode=54.201.183.106:32088
addnode=204.68.122.11:40002
addnode=77.249.199.235:39207
addnode=195.154.223.134:40002
addnode=37.187.144.36:24935
addnode=204.11.237.233:42230
addnode=5.9.20.83:40002
addnode=98.115.147.74:34277
addnode=108.61.10.90:40002
addnode=104.236.84.230:40002
addnode=108.163.197.58:58809
addnode=192.99.0.112:33324
addnode=162.255.117.105:64504
addnode=192.99.47.172:30023
addnode=167.160.36.126:32975
addnode=89.36.212.56:49931
addnode=5.196.20.189:53825
addnode=104.255.67.131:52418
addnode=38.129.236.35:55566
addnode=89.216.241.17:50126
```

You can just copy the username and password provided by the error message when you first ran gamecreditsd.

Run gamecreditsd once more to start the daemon! 

###Optional Download GameCredits bootstrap
```
cd /home/gamecredits/.gamecredits/
wget http://gmc.cryptocloudhosting.org/bootstrap/bootstrap.zip
unzip bootstrap.zip
```

###Using gamecreditsd
```
gamecreditsd help
```

The above command will list all available functions of the GameCredits daemon. To safely stop the daemon, execute GameCreditsd stop. 

#Testing
-------

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test. Please be patient and help out, and
remember this is a security-critical project where any mistake might cost people
lots of money.
