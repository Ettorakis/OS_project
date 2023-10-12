#!/bin/bash

cd ~/Desktop/progetto/poky/
echo ""
echo "****************************************"
echo "SOURCE oe-init-build-env"
echo "****************************************"
source oe-init-build-env build_qemuarm


echo ""
echo "****************************************"
echo "EXEC bitbake"
echo "****************************************"
bitbake core-image-minimal

echo ""
echo "****************************************"
echo "EXEC command_long"
echo "****************************************"
#command_begin="exec /home/mattia/Desktop/progetto/poky/build_qemuarm/tmp/work/x86_64-linux/qemu-system-native/4.2.0-r0/qemu-4.2.0/arm-softmmu/qemu-system-arm -device virtio-net-device,netdev=net0,mac=52:54:00:12:34:02 -netdev tap,id=net0,ifname=tap0,script=no,downscript=no -drive id=disk0,file=/home/mattia/Desktop/progetto/poky/build_qemuarm/tmp/deploy/images/qemuarm/"
root_fs=$(ls /home/mattia/Desktop/progetto/poky/build_qemuarm/tmp/deploy/images/qemuarm | grep "rootfs.ext4")
#command_end=",if=none,format=raw -device virtio-blk-device,drive=disk0 -show-cursor -device VGA,edid=on -device qemu-xhci -device usb-tablet -device usb-kbd -object rng-random,filename=/dev/urandom,id=rng0 -device virtio-rng-pci,rng=rng0  -nographic -machine virt,highmem=off -cpu cortex-a15 -m 256 -serial mon:stdio -serial null -kernel /home/mattia/Desktop/progetto/poky/build_qemuarm/tmp/deploy/images/qemuarm/zImage -append 'root=/dev/vda rw console=ttyS0 mem=256M ip=192.168.7.2::192.168.7.1:255.255.255.0 console=ttyAMA0 '"
#command="$command_begin$root_fs$command_end"
exec sudo /home/mattia/Desktop/progetto/poky/build_qemuarm/tmp/work/x86_64-linux/qemu-system-native/4.2.0-r0/qemu-4.2.0/arm-softmmu/qemu-system-arm -device virtio-net-device,netdev=net0,mac=52:54:00:12:34:02 -netdev tap,id=net0,ifname=tap0,script=no,downscript=no -drive id=disk0,file=/home/mattia/Desktop/progetto/poky/build_qemuarm/tmp/deploy/images/qemuarm/$root_fs,if=none,format=raw -device virtio-blk-device,drive=disk0 -show-cursor -device VGA,edid=on -device qemu-xhci -device usb-tablet -device usb-kbd -object rng-random,filename=/dev/urandom,id=rng0 -device virtio-rng-pci,rng=rng0 -nographic -machine virt,highmem=off -cpu cortex-a15 -m 256 -serial mon:stdio -serial null -kernel /home/mattia/Desktop/progetto/poky/build_qemuarm/tmp/deploy/images/qemuarm/zImage -append 'root=/dev/vda rw console=ttyS0 mem=256M ip=192.168.7.2::192.168.7.1:255.255.255.0 console=ttyAMA0 '

