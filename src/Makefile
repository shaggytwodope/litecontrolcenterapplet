PREFIX ?= /usr
PACKAGES = libxfce4panel-1.0 gtk+-3.0
TARGET = lite-controlcenter-applet
version = 1.1

liblitecc:
	gcc -s -Wall -shared -o $(TARGET).so -fPIC $(TARGET).c `pkg-config --cflags --libs $(PACKAGES)`

deb:
	sed -i "/Version:/c\Version: $(version)" debian/DEBIAN/control
	install -d debian/usr/lib/x86_64-linux-gnu/xfce4/panel/plugins/
	install -d debian/usr/share/xfce4/panel/plugins/
	install -d debian/usr/share/doc/lite-controlcenter-applet
	install -m 755 $(TARGET).so debian/usr/lib/x86_64-linux-gnu/xfce4/panel/plugins/
	gzip -c --best debian/DEBIAN/changelog >debian/DEBIAN/changelog.Debian.gz
	install -m 644  debian/DEBIAN/changelog.Debian.gz debian/usr/share/doc/lite-controlcenter-applet
	rm debian/DEBIAN/changelog.Debian.gz
	install -m 644 debian/DEBIAN/copyright debian/usr/share/doc/lite-controlcenter-applet
	install $(TARGET).desktop debian/usr/share/xfce4/panel/plugins/
	fakeroot dpkg-deb --build debian $(TARGET)_$(version).deb
	rm -rf debian/usr


clean:
	-@rm *.so

.PHONY: clean

all: liblitecc deb
