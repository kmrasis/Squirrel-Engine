#  Script to generate makefiles and compile source code

# Currently Hard coded
SOURCE_DIR=$(cd $(dirname $0) && pwd)
BUILD_DIR=$(cd $(dirname $0) && pwd)/build

if [ ! -d ${BUILD_DIR} ]; then
    mkdir ${BUILD_DIR}
fi

echo "Source Dir: ${SOURCE_DIR}"
echo "Build Dir: ${BUILD_DIR}"

while true; do
read -p "Do you want to continue? (y/n) " yn

case ${yn} in 
    [yY] ) break;;
    [nN] ) echo "Aborted" && exit 0;;
    * )    echo "Invalid response";;
esac
done


# Generate MakeFiles
cmake -S${SOURCE_DIR} -B${BUILD_DIR}

# compile
pushd ${BUILD_DIR}
    make ${MAKE_FlAGS}
popd >> /dev/null
