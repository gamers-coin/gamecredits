set -o errexit

if [ -d "../src/leveldb" ]; then
    echo leveldb...
    cd ../src/leveldb
    make memenv_test TARGET_OS=OS_WINDOWS_CROSSCOMPILE \
     OPT="${ADDITIONALCCFLAGS}"
    echo
    cd ../../easywinbuilder
fi

cd ../$EWBLIBS

echo db...
cd $BERKELEYDB
cd build_unix
../dist/configure --disable-replication --enable-mingw --enable-cxx \
 CXXFLAGS="${ADDITIONALCCFLAGS}" \
 CFLAGS="${ADDITIONALCCFLAGS}"
sed -i 's/typedef pthread_t db_threadid_t;/typedef u_int32_t db_threadid_t;/g' db.h  # workaround, see https://bitcointalk.org/index.php?topic=45507.0
make
cd ..
cd ..
echo

echo  openssl...
cd $OPENSSL
export CC="gcc ${ADDITIONALCCFLAGS}"
./config
make
cd ..
echo

cd ../easywinbuilder