#!/bin/bash
name_dir=$(date +'%Y-%m-%d--%T')
#echo "nome cartella " $name_dir
mkdir ~/Desktop/progetto/backup/$name_dir
#cd $name_dir

#copia da qemu
cp ~/Desktop/progetto/poky/build_qemuarm/tmp/work/x86_64-linux/qemu-system-native/4.2.0-r0/qemu-4.2.0/hw/misc/virt_sha.c ~/Desktop/progetto/backup/$name_dir

#copia virt.c
cp ~/Desktop/progetto/poky/build_qemuarm/tmp/work/x86_64-linux/qemu-system-native/4.2.0-r0/qemu-4.2.0/hw/arm/virt.c ~/Desktop/progetto/backup/$name_dir

#copia da recipes-driver
cp ~/Desktop/progetto/poky/meta-example/recipes-example/virt-sha/files/virt-sha.c ~/Desktop/progetto/backup/$name_dir

#copia Kconfig e Makefile.objs da misc
cp ~/Desktop/progetto/poky/build_qemuarm/tmp/work/x86_64-linux/qemu-system-native/4.2.0-r0/qemu-4.2.0/hw/misc/Kconfig ~/Desktop/progetto/backup/$name_dir

cp ~/Desktop/progetto/poky/build_qemuarm/tmp/work/x86_64-linux/qemu-system-native/4.2.0-r0/qemu-4.2.0/hw/misc/Makefile.objs ~/Desktop/progetto/backup/$name_dir

#copia config-devices.mak
cp ~/Desktop/progetto/poky/build_qemuarm/tmp/work/x86_64-linux/qemu-system-native/4.2.0-r0/qemu-4.2.0/arm-softmmu/config-devices.mak ~/Desktop/progetto/backup/$name_dir

#copia arm-softmmu.mak
cp ~/Desktop/progetto/poky/build_qemuarm/tmp/work/x86_64-linux/qemu-system-native/4.2.0-r0/qemu-4.2.0/default-configs/arm-softmmu.mak ~/Desktop/progetto/backup/$name_dir

#copia local.conf 
cp ~/Desktop/progetto/poky/build_qemuarm/conf/local.conf ~/Desktop/progetto/backup/$name_dir

#copia cartella ricette
cp -R ~/Desktop/progetto/poky/meta-example ~/Desktop/progetto/backup/$name_dir 

ls -l ~/Desktop/progetto/backup
