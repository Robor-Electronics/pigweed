#
# start pigweed console (currently optimized for osx)
#

export PROJECT_DIR=~/Projects/vanremmen/uv-controller
# get usb
# - /dev/tty.usbmodem2301  -> usb from the HMI
# - /dev/tty.usbserial-240 -> modbus usb convertor
until usb=`ls /dev/tty.usbmodem*`; do
  echo "no usb, retry..."
  sleep  0.1
done

echo usb is ${usb}

# start pigweed console
pw rpc -d ${usb} -b 115200 --proto-globs ${PROJECT_DIR}/ext/robor/uv-controller-rpc/protos/*.proto ${PROJECT_DIR}/src/application/common/rpc/protos/*.proto --serial-debug
