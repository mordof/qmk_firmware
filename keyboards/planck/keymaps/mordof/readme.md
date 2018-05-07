# The Default Planck Layout



# To install

- make sure keyboard is in 'bootloader' state (button underneath).
- use dfu-programmer 0.7.2. the repo only has 0.6.1 and doesn't pick up the kb.
- run these commands in the qmk_firmware folder

make planck/rev4:mordof
dfu-programmer atmega32u4 erase
dfu-programmer atmega32u4 flash planck_rev4_mordof.hex
