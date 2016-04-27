PREFIX ?= /usr
PACKAGES = libxfce4panel-1.0 gtk+-3.0
TARGET = litecontrolcenter
liblitecontrolcenter.so:
	gcc -Wall -shared -o liblitecontrolcenter.so -fPIC litecc.c `pkg-config --cflags --libs $(PACKAGES)`

clean:
	-@rm *.so

.PHONY: clean

all: liblitecontrolcenter.so litecontrolcenter.desktop
