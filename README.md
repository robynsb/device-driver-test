# Robin Char Device

Trying to create a simple char device running on a Raspberry Pi 3B+ using the book LDD3 as reference.

## Installation and Usage

The dependencies of this project are as described in the `shell.nix` file.

Check and update `driver-config.sh`.

Using nix, change your PWD to the root of the repo and then:
```bash
nix-shell
make
./deploy-driver.sh
```

See driver 
```bash
demsg -w
```
