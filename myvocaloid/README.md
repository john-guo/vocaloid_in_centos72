Ubuntu:

sudo apt-get install build-essential
sudo apt-get install libavutil-dev
sudo apt-get install libavcodec-dev
sudo apt-get install libavformat-dev
sudo apt-get install libgrpc++-dev
sudo apt-get install protobuf-compiler
sudo apt-get install protobuf-compiler-grpc

make

mkdir bin

"copy vocaloid runtime to bin"

ln -fs libVocSDKLinux.so.3.0.0  libVocSDKLinux.so
ln -fs libVocSDKLinux.so.3.0.0  libVocSDKLinux.so.3

cp server bin
cd bin
export LD_LIBRARY_PATH=`pwd`
./server