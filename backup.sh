#!/bin/bash
name_dir=$(date +'%Y-%m-%d--%T')
#echo "nome cartella " $name_dir
mkdir ~/Desktop/backup/$name_dir
#cd $name_dir

#copia da qemu
cp /home/vboxuser/tutorialYocto/poky/build_qemuarm/tmp/work/x86_64-linux/qemu-system-native/4.2.0-r0/qemu-4.2.0/hw/misc/virt_sha.c ~/Desktop/backup/$name_dir

#copia virt.c
cp /home/vboxuser/tutorialYocto/poky/build_qemuarm/tmp/work/x86_64-linux/qemu-system-native/4.2.0-r0/qemu-4.2.0/hw/arm/virt.c ~/Desktop/backup/$name_dir

#copia da recipes-driver
cp /home/vboxuser/tutorialYocto/poky/meta-example/recipes-example/virt-sha/files/virt-sha.c ~/Desktop/backup/$name_dir

#copia Kconfig e Makefile.objs da misc
cp ~/tutorialYocto/poky/build_qemuarm/tmp/work/x86_64-linux/qemu-system-native/4.2.0-r0/qemu-4.2.0/hw/misc/Kconfig ~/Desktop/backup/$name_dir

cp ~/tutorialYocto/poky/build_qemuarm/tmp/work/x86_64-linux/qemu-system-native/4.2.0-r0/qemu-4.2.0/hw/misc/Makefile.objs ~/Desktop/backup/$name_dir

#copia config-devices.mak
cp ~/tutorialYocto/poky/build_qemuarm/tmp/work/x86_64-linux/qemu-system-native/4.2.0-r0/qemu-4.2.0/arm-softmmu/config-devices.mak ~/Desktop/backup/$name_dir

#copia arm-softmmu.mak
cp ~/tutorialYocto/poky/build_qemuarm/tmp/work/x86_64-linux/qemu-system-native/4.2.0-r0/qemu-4.2.0/default-configs/arm-softmmu.mak ~/Desktop/backup/$name_dir

#copia local.conf 
cp ~/tutorialYocto/poky/build_qemuarm/conf/local.conf ~/Desktop/backup/$name_dir

#copia cartella ricette
cp -R ~/tutorialYocto/poky/meta-example ~/Desktop/backup/$name_dir 

ls -l ~/Desktop/backup
