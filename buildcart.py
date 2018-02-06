#! /bin/env python3

import argparse
import os.path
import sys

def read_file(name):
    d = {}
    with open(name, "rb") as f:
        data = f.read()
        d = {
            'title': os.path.splitext(os.path.basename(name))[0],
            'data': data,
            'size': len(data)
        }
    return d

def read_roms(roms):
    cart8 = []
    cart16 = []

    for r in roms:
        rom = read_file(r)
        if rom['size'] == 8192: # Standard 8KB rom.
            cart8.append(rom)
        elif rom['size'] == 16384: # Standard 16KB rom.
            cart16.append(rom)
        else:
            print("[WARNING] Ignoring a bad ROM file: " + r)
        cart8.sort(key = lambda x: x['title'])
        cart16.sort(key = lambda x: x['title'])
    return cart8, cart16

def build_menu(output, cart8, cart16):
    i = 1
    for c in cart8:
        c['out'] = 'CART_8KB({0}, "{1}")'.format(i, c['title'])
        i = i + 1
    # 16 KB carts have to start at an even offset.
    if len(cart8) % 2 == 0:
       i = i + 1
    for c in cart16:
        c['out'] = 'CART_16KB({0}, "{1}")'.format(i+1, c['title']) # 16KB games start in the second bank.
        i = i + 2
    carts = cart8 + cart16
    carts.sort(key = lambda x: x['title'])

    output.write('#include "menu.h"\n'.encode('utf-8'))
    output.write('const GAME_INFO games[] = {\n'.encode('utf-8'))
    output.write(',\n'.join([c['out'] for c in carts]).encode('utf-8'))
    output.write('\n};\n'.encode('utf-8'))
    output.write('const unsigned int num_games = '.encode('utf-8'))
    output.write(str(len(carts)).encode('utf-8'))
    output.write(';'.encode('utf-8'))

def build_cart(menu, output, cart8, cart16):
    m = read_file(menu)
    output.write(m['data'])
    for c in cart8:
        output.write(c['data'])
    if len(cart8) // 2 == 1:
        # Extra padding for 16 KB carts alignment.
        output.write(bytes(8192))
    for c in cart16:
        output.write(c['data'])

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-m", "--menu", help="Selects the initial game selection program.", default="menu.bin")
    parser.add_argument("-c", "--config", help="Produce a configuration file for the game selection program instead of the cartridge file.", action="store_true", default = False)
    parser.add_argument("-o", "--output", help="Filename of the file that will store the results of the operation")
    parser.add_argument("FILE", nargs="*")

    args = parser.parse_args()

    cart8, cart16 = read_roms(args.FILE)

    with open(args.output, "wb") as out:
        if args.config:
            build_menu(out, cart8, cart16)
        else:
            build_cart(args.menu, out, cart8, cart16)
