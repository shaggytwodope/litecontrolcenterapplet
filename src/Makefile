PREFIX ?= /usr
PACKAGES = libxfce4panel-1.0 gtk+-3.0
TARGET = litecontrolcenter
liblitecontrolcenter.so:
	gcc -Wall -shared -o liblitecontrolcenter.so -fPIC litecontrolcenter.c `pkg-config --cflags --libs $(PACKAGES)`



.PHONY: deps

all: liblitecontrolcenter.so litecontrolcenter.desktop
