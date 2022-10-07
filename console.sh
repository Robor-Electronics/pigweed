#
# start pigweed console (currently optimized for osx)
#

export PROJECT_DIR=~/Projects/vanremmen/uv-controller
# get usb
until usb=`ls /dev/tty.usb*`; do
  echo "no usb, retry..."
  sleep  0.1
done

echo usb is ${usb}

# start pigweed console
pw rpc -d ${usb} -b 115200 --proto-globs ${PROJECT_DIR}/ext/robor/uv-controller-rpc/protos/*.proto ${PROJECT_DIR}/src/application/common/rpc/protos/*.proto --serial-debug
