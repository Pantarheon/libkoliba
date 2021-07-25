# Installing Koliba

The way to install the koliba library depends on the
operating system.

## Raspberry Pi

On the 32-bit `raspi` system you can take advantage
of parts of the code being re-written in the `arm-eabi-32`
assembly language. To replace the corresponding C code
with assembly language, change to the [src](./src)
directory and type,

``` /bin/sh
chmod +x arm-eabi-32-prep.sh
./arm-eabi-32-prep-sh
```

Then use `make` as described in the Unix/Linux section below.

## Unix/Linux and similar

Switch to the [src](./src) directory. Then if all you want
is to compile and install the koliba library, type,

``` /bin/sh
sudo make install
```

