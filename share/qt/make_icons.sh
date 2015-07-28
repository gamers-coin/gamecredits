#!/bin/bash
# create multiresolution windows icon, and pixmaps
# variables
ICON_SRC=../pixmaps/gamecredits1024.png
ICON_DST=../../src/qt/res/icons/gamecredits.ico
ICON_SRC_TEST=../../src/qt/res/icons/gamecredits_testnet.png
ICON_DST_TEST=../../src/qt/res/icons/gamecredits_testnet.ico
# create base for all mainnet icons
convert ${ICON_SRC} -resize 16x16 ../pixmaps/gamecredits16.png
convert ${ICON_SRC} -resize 32x32 ../pixmaps/gamecredits32.png
convert ${ICON_SRC} -resize 48x48 gamecredits-48.png
convert ${ICON_SRC} -resize 64x64 ../pixmaps/gamecredits64.png
convert ${ICON_SRC} -resize 128x128 ../pixmaps/gamecredits128.png
convert ${ICON_SRC} -resize 256x256 ../pixmaps/gamecredits256.png
convert ${ICON_SRC} -resize 512x512 ../pixmaps/gamecredits512.png
cp ../pixmaps/gamecredits256.png ../../src/qt/res/icons/gamecredits.png
# create mainnet windows icon with all variant sizes
convert ../pixmaps/gamecredits16.png ../pixmaps/gamecredits32.png gamecredits-48.png ../pixmaps/gamecredits256.png ${ICON_DST}
cp ../pixmaps/gamecredits16.png ../../src/qt/res/icons/toolbar.png
# create base for all testnet icons 
convert ${ICON_SRC} -colorspace Gray ../pixmaps/Tgamecredits1024.png
convert ../pixmaps/Tgamecredits1024.png -resize 256x256 ${ICON_SRC_TEST}
convert ${ICON_SRC_TEST} -resize 16x16 gamecredits-test-16.png
convert ${ICON_SRC_TEST} -resize 32x32 gamecredits-test-32.png
convert ${ICON_SRC_TEST} -resize 48x48 gamecredits-test-48.png
cp ${ICON_SRC_TEST} gamecredits-test-256.png
# create testnet windows icon with all varient sizes
convert gamecredits-test-16.png gamecredits-test-32.png gamecredits-test-48.png gamecredits-test-256.png ${ICON_DST_TEST}
cp gamecredits-test-16.png ../../src/qt/res/icons/toolbar_testnet.png
# create pixmap ico and xpm files
convert ../pixmaps/gamecredits16.png ../pixmaps/favicon.ico
cp ${ICON_DST} ../pixmaps/gamecredits.ico
convert ../pixmaps/gamecredits16.png ../pixmaps/gamecredits16.xpm
convert ../pixmaps/gamecredits32.png ../pixmaps/gamecredits32.xpm
convert ../pixmaps/gamecredits64.png ../pixmaps/gamecredits64.xpm
convert ../pixmaps/gamecredits128.png ../pixmaps/gamecredits128.xpm
convert ../pixmaps/gamecredits256.png ../pixmaps/gamecredits256.xpm
# create apple icns file, use libicns 8.2.1 not the default
mv ../pixmaps/gamecredits64.png ../pixmaps/tempgamecredits64.png
png2icns ../../src/qt/res/icons/gamecredits.icns ../pixmaps/gamecredits*.png
mv ../pixmaps/tempgamecredits64.png ../pixmaps/gamecredits64.png
# clean up
rm gamecredits-48.png
rm gamecredits-test-*.png
rm ../pixmaps/Tgamecredits1024.png
