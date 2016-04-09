#! /bin/env python

import argparse
import os.path

def read_roms(roms):
    cart8 = []
    cart16 = []

    for r in roms:
        with open(r, "rb") as romfile:
            data = romfile.read()
            rom = {
                'title': os.path.splitext(os.path.basename(r))[0],
                'data': data,
                'size': len(data)
            }
            if rom['size'] == 8192: # Standard 8KB rom.
                cart8.append(rom)
            elif rom['size'] == 16384: # Standard 16KB rom.
                cart16.append(rom)
            else:
                raise Exception("Bad rom file: " + r)
    return cart8, cart16

def build_menu(cart8, cart16):
    i = 1
    out = ""
    for c in cart8:
        out = out + 'CART_8KB({0}, "{1}"),\n'.format(i, c['title'])
        i = i + 1
    if len(cart8) // 2 == 1:
        # 16 KB carts have to start at an even offset.
        i = i + 1
    for c in cart16:
        out = out + 'CART_16KB({0}, "{1}"),\n'.format(i + 1, c['title'])
        i = i + 2
    print(out[0:-2]) # Remove the last coma & newline.

def build_cart(menu, cart8, cart16):
    # TODO
    pass

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-m", "--menu", help="Selects the initial game selection program.", default="menu.bin")
    parser.add_argument("-c", "--config", help="Produce a configuration file for the game selection program instead of the cartridge file.", action="store_true", default = False)
    parser.add_argument("FILE", nargs="*")

    args = parser.parse_args()

    cart8, cart16 = read_roms(args.FILE)

    if args.config:
        build_menu(cart8, cart16)
    else:
        build_cart(args.menu, cart8, cart16)
