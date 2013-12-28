echo "**********************************************************"
echo "                     BUILD SERVER                         "
echo "**********************************************************"

mkdir -p build/server
mkdir -p build/client
cd build/server
cmake ../../server
make
echo "**********************************************************"
echo "                     BUILD CLIENT                         "
echo "**********************************************************"
cd ../client
cmake ../../client
make
