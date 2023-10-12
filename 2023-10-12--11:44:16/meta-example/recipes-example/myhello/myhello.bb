DESCRIPTION = "Simple helloworld application"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"
SRC_URI = "file://Sha256_library.c  file://Sha256_library.h file://Test_sha256.c file://SafeRegistration.c"
S = "${WORKDIR}"
do_compile() {
	set CFLAGS -g
	${CC} ${CFLAGS} Sha256_library.c Sha256_library.h Test_sha256.c ${LDFLAGS} -o testAndre
	${CC} ${CFLAGS} Sha256_library.c Sha256_library.h SafeRegistration.c ${LDFLAGS} -o ApplicationSha256
	unset CFLAGS
}
do_install() {
	 install -d ${D}${bindir}
	 install -m 0755 testAndre ${D}${bindir}
	 install -m 0755 ApplicationSha256 ${D}${bindir}
}
