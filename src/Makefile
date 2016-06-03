PREFIX ?= /usr
PACKAGES = libxfce4panel-1.0 gtk+-3.0
TARGET = lite-controlcenter-applet
ARCH=$(shell dpkg-architecture -qDEB_HOST_ARCH)
HOSTARCH=$(shell dpkg-architecture -qDEB_HOST_MULTIARCH)
VERSION = 1.1

liblitecc:
	gcc -s -Wall -shared -o $(TARGET).so -fPIC $(TARGET).c `pkg-config --cflags --libs $(PACKAGES)`

deb:
	sed -i "/Version:/c\Version: $(VERSION)" debian/DEBIAN/control
	sed -i "/Architecture:/c\Architecture: $(ARCH)" debian/DEBIAN/control
	install -d debian/usr/lib/$(HOSTARCH)/xfce4/panel/plugins/
	install -d debian/usr/share/xfce4/panel/plugins/
	install -d debian/usr/share/doc/lite-controlcenter-applet
	install -m 755 $(TARGET).so debian/usr/lib/$(HOSTARCH)/xfce4/panel/plugins/
	gzip -c --best debian/DEBIAN/changelog >debian/DEBIAN/changelog.Debian.gz
	install -m 644  debian/DEBIAN/changelog.Debian.gz debian/usr/share/doc/lite-controlcenter-applet
	rm debian/DEBIAN/changelog.Debian.gz
	install -m 644 debian/DEBIAN/copyright debian/usr/share/doc/lite-controlcenter-applet
	install $(TARGET).desktop debian/usr/share/xfce4/panel/plugins/
	fakeroot dpkg-deb --build debian $(TARGET)_$(VERSION)_$(ARCH).deb
	rm -rf debian/usr


clean:
	-@rm *.so

.PHONY: clean

all: liblitecc deb
