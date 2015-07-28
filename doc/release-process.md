Release Process
====================

###update (commit) version in sources

	contrib/verifysfbinaries/verify.sh
	doc/README*
	share/setup.nsi
	src/clientversion.h (change CLIENT_VERSION_IS_RELEASE to true)

###tag version in git

	git tag -s v(new version, e.g. 0.8.0)

###write release notes. git shortlog helps a lot, for example:

	git shortlog --no-merges v(current version, e.g. 0.7.2)..v(new version, e.g. 0.8.0)

* * *

##perform gitian builds

 From a directory containing the gamecredits source, gitian-builder and gitian.sigs
  
	export SIGNER=(your gitian key, ie bluematt, sipa, etc)
	export VERSION=(new version, e.g. 0.8.0)
	pushd ./gamecredits
	git checkout v${VERSION}
	popd
	pushd ./gitian-builder
        mkdir -p inputs; cd inputs/

 Register and download the Apple SDK (see OSX Readme for details)
	visit https://developer.apple.com/downloads/download.action?path=Developer_Tools/xcode_4.6.3/xcode4630916281a.dmg
 
 Using a Mac, create a tarball for the 10.7 SDK
	tar -C /Volumes/Xcode/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/ -czf MacOSX10.7.sdk.tar.gz MacOSX10.7.sdk

 Fetch and build inputs: (first time, or when dependency versions change)

	wget 'http://miniupnp.free.fr/files/download.php?file=miniupnpc-1.9.20140701.tar.gz' -O miniupnpc-1.9.20140701.tar.gz
	wget 'https://www.openssl.org/source/openssl-1.0.1k.tar.gz'
	wget 'http://download.oracle.com/berkeley-db/db-4.8.30.NC.tar.gz'
	wget 'http://zlib.net/zlib-1.2.8.tar.gz'
	wget 'ftp://ftp.simplesystems.org/pub/png/src/history/libpng16/libpng-1.6.8.tar.gz'
	wget 'https://fukuchi.org/works/qrencode/qrencode-3.4.3.tar.bz2'
	wget 'https://downloads.sourceforge.net/project/boost/boost/1.55.0/boost_1_55_0.tar.bz2'
	wget 'https://svn.boost.org/trac/boost/raw-attachment/ticket/7262/boost-mingw.patch' -O \ 
	     boost-mingw-gas-cross-compile-2013-03-03.patch
	wget 'https://download.qt-project.org/official_releases/qt/5.2/5.2.0/single/qt-everywhere-opensource-src-5.2.0.tar.gz'
	wget 'https://download.qt-project.org/archive/qt/4.8/4.8.6/qt-everywhere-opensource-src-4.8.6.tar.gz'
	wget 'https://protobuf.googlecode.com/files/protobuf-2.5.0.tar.bz2'
	wget 'https://github.com/mingwandroid/toolchain4/archive/10cc648683617cca8bcbeae507888099b41b530c.tar.gz'
	wget 'http://www.opensource.apple.com/tarballs/cctools/cctools-809.tar.gz'
	wget 'http://www.opensource.apple.com/tarballs/dyld/dyld-195.5.tar.gz'
	wget 'http://www.opensource.apple.com/tarballs/ld64/ld64-127.2.tar.gz'
	wget 'http://pkgs.fedoraproject.org/repo/pkgs/cdrkit/cdrkit-1.1.11.tar.gz/efe08e2f3ca478486037b053acd512e9/cdrkit-1.1.11.tar.gz'
	wget 'https://github.com/theuni/libdmg-hfsplus/archive/libdmg-hfsplus-v0.1.tar.gz'
	wget 'http://llvm.org/releases/3.2/clang+llvm-3.2-x86-linux-ubuntu-12.04.tar.gz' -O \
	     clang-llvm-3.2-x86-linux-ubuntu-12.04.tar.gz
        wget 'https://raw.githubusercontent.com/theuni/osx-cross-depends/master/patches/cdrtools/genisoimage.diff' -O \
	     cdrkit-deterministic.patch
	cd ..
	./bin/gbuild ../gamecredits/contrib/gitian-descriptors/boost-linux.yml
	mv build/out/boost-*.zip inputs/
	./bin/gbuild ../gamecredits/contrib/gitian-descriptors/deps-linux.yml
	mv build/out/gamecredits-deps-*.zip inputs/
	./bin/gbuild ../gamecredits/contrib/gitian-descriptors/qt-linux.yml
	mv build/out/qt-*.tar.gz inputs/
	./bin/gbuild ../gamecredits/contrib/gitian-descriptors/boost-win.yml
	mv build/out/boost-*.zip inputs/
	./bin/gbuild ../gamecredits/contrib/gitian-descriptors/deps-win.yml
	mv build/out/gamecredits-deps-*.zip inputs/
	./bin/gbuild ../gamecredits/contrib/gitian-descriptors/qt-win.yml
	mv build/out/qt-*.zip inputs/
	./bin/gbuild ../gamecredits/contrib/gitian-descriptors/protobuf-win.yml
	mv build/out/protobuf-*.zip inputs/
	./bin/gbuild ../gamecredits/contrib/gitian-descriptors/gitian-osx-native.yml
	mv build/out/osx-*.tar.gz inputs/
	./bin/gbuild ../gamecredits/contrib/gitian-descriptors/gitian-osx-depends.yml
	mv build/out/osx-*.tar.gz inputs/
	./bin/gbuild ../gamecredits/contrib/gitian-descriptors/gitian-osx-qt.yml
	mv build/out/osx-*.tar.gz inputs/

 SHA256 hashes of intermediate inputs will be different for each project based on gamecredits.
 
 Build gamecreditsd and gamecredits-qt on Linux32, Linux64, and Win32:
  
	./bin/gbuild --commit gamecredits=v${VERSION} ../gamecredits/contrib/gitian-descriptors/gitian-linux.yml
	./bin/gsign --signer $SIGNER --release ${VERSION} --destination ../gitian.sigs/ ../gamecredits/contrib/gitian-descriptors/gitian-linux.yml
	pushd build/out
	zip -r gamecredits-${VERSION}-linux-gitian.zip *
	mv gamecredits-${VERSION}-linux-gitian.zip ../../../
	popd
	./bin/gbuild --commit gamecredits=v${VERSION} ../gamecredits/contrib/gitian-descriptors/gitian-win.yml
	./bin/gsign --signer $SIGNER --release ${VERSION}-win --destination ../gitian.sigs/ ../gamecredits/contrib/gitian-descriptors/gitian-win.yml
	pushd build/out
	zip -r gamecredits-${VERSION}-win-gitian.zip *
	mv gamecredits-${VERSION}-win-gitian.zip ../../../
	popd
    ./bin/gbuild --commit gamecredits=v${VERSION} ../gamecredits/contrib/gitian-descriptors/gitian-osx-gamecredits.yml
    ./bin/gsign --signer $SIGNER --release ${VERSION}-osx --destination ../gitian.sigs/ ../gamecredits/contrib/gitian-descriptors/gitian-osx-gamecredits.yml
	pushd build/out
	mv GameCredits-Qt.dmg ../../../
	popd
	popd

  Build output expected:

  1. linux 32-bit and 64-bit binaries + source (gamecredits-${VERSION}-linux-gitian.zip)
  2. windows 32-bit and 64-bit binaries + installer + source (gamecredits-${VERSION}-win-gitian.zip)
  3. OSX installer (GameCredits-Qt.dmg)
  4. Gitian signatures (in gitian.sigs/${VERSION}[-win|-osx]/(your gitian key)/

repackage gitian builds for release as stand-alone zip/tar/installer exe

**Linux .tar.gz:**

	unzip gamecredits-${VERSION}-linux-gitian.zip -d gamecredits-${VERSION}-linux
	tar czvf gamecredits-${VERSION}-linux.tar.gz gamecredits-${VERSION}-linux
	rm -rf gamecredits-${VERSION}-linux

**Windows .zip and setup.exe:**

	unzip gamecredits-${VERSION}-win-gitian.zip -d gamecredits-${VERSION}-win
	mv gamecredits-${VERSION}-win/*/gamecredits-*-setup.exe .
	zip -r gamecredits-${VERSION}-win.zip gamecredits-${VERSION}-win
	rm -rf gamecredits-${VERSION}-win

###Next steps:

* Code-sign Windows -setup.exe (in a Windows virtual machine using signtool)
 Note: only Gavin has the code-signing keys currently.

* upload builds to SourceForge

* create SHA256SUMS for builds, and PGP-sign it

* update gamecredits.org version
  make sure all OS download links go to the right versions
  
* update download sizes on gamecredits.org/_templates/download.html

* update forum version

* update wiki download links

* update wiki changelog: [https://en.gamecredits.it/wiki/Changelog](https://en.gamecredits.it/wiki/Changelog)

Commit your signature to gitian.sigs:

	pushd gitian.sigs
	git add ${VERSION}/${SIGNER}
	git add ${VERSION}-win/${SIGNER}
	git commit -a
	git push  # Assuming you can push to the gitian.sigs tree
	popd

-------------------------------------------------------------------------

### After 3 or more people have gitian-built, repackage gitian-signed zips:

From a directory containing gamecredits source, gitian.sigs and gitian zips

	export VERSION=(new version, e.g. 0.8.0)
	mkdir gamecredits-${VERSION}-linux-gitian
	pushd gamecredits-${VERSION}-linux-gitian
	unzip ../gamecredits-${VERSION}-linux-gitian.zip
	mkdir gitian
	cp ../gamecredits/contrib/gitian-downloader/*.pgp ./gitian/
	for signer in $(ls ../gitian.sigs/${VERSION}/); do
	 cp ../gitian.sigs/${VERSION}/${signer}/gamecredits-build.assert ./gitian/${signer}-build.assert
	 cp ../gitian.sigs/${VERSION}/${signer}/gamecredits-build.assert.sig ./gitian/${signer}-build.assert.sig
	done
	zip -r gamecredits-${VERSION}-linux-gitian.zip *
	cp gamecredits-${VERSION}-linux-gitian.zip ../
	popd
	mkdir gamecredits-${VERSION}-win-gitian
	pushd gamecredits-${VERSION}-win-gitian
	unzip ../gamecredits-${VERSION}-win-gitian.zip
	mkdir gitian
	cp ../gamecredits/contrib/gitian-downloader/*.pgp ./gitian/
	for signer in $(ls ../gitian.sigs/${VERSION}-win/); do
	 cp ../gitian.sigs/${VERSION}-win/${signer}/gamecredits-build.assert ./gitian/${signer}-build.assert
	 cp ../gitian.sigs/${VERSION}-win/${signer}/gamecredits-build.assert.sig ./gitian/${signer}-build.assert.sig
	done
	zip -r gamecredits-${VERSION}-win-gitian.zip *
	cp gamecredits-${VERSION}-win-gitian.zip ../
	popd

- Upload gitian zips to SourceForge

- Announce the release:

  - Add the release to gamecredits.org: https://github.com/project-gamecredits/gamecredits.org/tree/master/_releases

  - Release sticky on bitcointalk: https://bitcointalk.org/index.php?board=1.0

  - Gamecredits-development mailing list

  - Optionally reddit /r/Gamecredits, ...

- Celebrate 
