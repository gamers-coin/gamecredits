#Gamerscoin integration/staging tree
================================
Copyright (c) 2009-2013 Bitcoin Developers<br>
Copyright (c) 2011-2013 Litecoin Developers<br>
Copyright (c) 2011-2014 Gamerscoin Developers<br>

![Gamerscoin](https://raw.githubusercontent.com/gamers-coin/gamers-coinv3/01d1ca6d63b565ea46dcee3b6552b030d57d1187/src/qt/res/icons/bitcoin.png)![Gamerscoin](http://i.imgur.com/Nfb8DQx.png)

#What is Gamerscoin?
----------------

Gamerscoin is a lite version of Bitcoin using scrypt as a proof-of-work algorithm.
 - 2.5 minute block targets
 - subsidy halves in 840k blocks (~4 years)
 - ~84 million total coins
 - 50 coins per block
 - 1 blocks to retarget difficulty
 - KGW Implemented

[![tip for next commit](http://game4commit.gamers-coin.org/projects/12.svg)](http://game4commit.gamers-coin.org/projects/12)

#License
-------

Gamerscoin is released under the terms of the MIT license. See `COPYING` for more
information or see http://opensource.org/licenses/MIT.

#Development process
-------------------

Developers work in their own trees, then submit pull requests when they think
their feature or bug fix is ready.

If it is a simple/trivial/non-controversial change, then one of the Gamerscoin
development team members simply pulls it.

If it is a *more complicated or potentially controversial* change, then the patch
submitter will be asked to start a discussion (if they haven't already) on the
[mailing list](http://sourceforge.net/mailarchive/forum.php?forum_name=bitcoin-development).

The patch will be accepted if there is broad consensus that it is a good thing.
Developers should expect to rework and resubmit patches if the code doesn't
match the project's coding conventions (see `doc/coding.txt`) or are
controversial.

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/bitcoin/bitcoin/tags) are created
regularly to indicate new official, stable release versions of Gamerscoin.

#Compiling the Gamerscoin daemon from source on Debian
-----------------------------------------------------
The process for compiling the Gamerscoin daemon, gamerscoind, from the source code is pretty simple. This guide is based on the latest stable version of Debian Linux, though it should not need many modifications for any distro forked from Debian, such as Ubuntu and Xubuntu.

###Update and install dependencies

```
apt-get update && apt-get upgrade
apt-get install ntp git build-essential libssl-dev libdb-dev libdb++-dev libboost-all-dev libqrencode-dev

wget http://miniupnp.free.fr/files/download.php?file=miniupnpc-1.8.tar.gz && tar -zxf download.php\?file\=miniupnpc-1.8.tar.gz && cd miniupnpc-1.8/
make && make install && cd .. && rm -rf miniupnpc-1.8 download.php\?file\=miniupnpc-1.8.tar.gz
```
Note: Debian testing and unstable require libboost1.54-all-dev.

###Compile the daemon
```
git clone https://github.com/gamers-coin/gamers-coinv3.git
```

###Compile gamerscoind
```
cd gamers-coinv3/src/
make -f makefile.unix USE_UPNP=1 USE_QRCODE=1 USE_IPV6=1
strip gamerscoind
```

###Add a user and move gamerscoind
```
adduser gamerscoin && usermod -g users gamerscoin && delgroup gamerscoin && chmod 0701 /home/gamerscoin
mkdir /home/gamerscoin/bin
cp ~/gamers-coinv3/src/gamerscoind /home/gamerscoin/bin/gamerscoind
chown -R gamerscoin:users /home/gamerscoin/bin
cd && rm -rf gamers-coinv3
```

###Run the daemon
```
su gamerscoin
cd && bin/gamerscoind
```

On the first run, gamerscoind will return an error and tell you to make a configuration file, named gamerscoin.conf, in order to add a username and password to the file.
```
nano ~/.gamerscoin/gamerscoin.conf && chmod 0600 ~/.gamerscoin/gamerscoin.conf
```
Add the following to your config file, changing the username and password to something secure: 
```
daemon=1
rpcuser=<username>
rpcpassword=<secure password>
```

You can just copy the username and password provided by the error message when you first ran gamerscoind.

Run gamerscoind once more to start the daemon! 

###Using gamerscoind
```
gamerscoind help
```

The above command will list all available functions of the Gamerscoin daemon. To safely stop the daemon, execute Gamerscoind stop. 

#Testing
-------

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test. Please be patient and help out, and
remember this is a security-critical project where any mistake might cost people
lots of money.

### Automated Testing

Developers are strongly encouraged to write unit tests for new code, and to
submit new unit tests for old code.

Unit tests for the core code are in `src/test/`. To compile and run them:

    cd src; make -f makefile.unix test

Unit tests for the GUI code are in `src/qt/test/`. To compile and run them:

    qmake BITCOIN_QT_TEST=1 -o Makefile.test bitcoin-qt.pro
    make -f Makefile.test
    ./gamerscoin-qt_test

