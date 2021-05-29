rm -r build
mkdir build
cd build
cmake .. && make
cd ..
cp build/libcpp-file-manager.a samples/libcpp-file-manager.a
