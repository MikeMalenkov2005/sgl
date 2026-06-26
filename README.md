# Simple Game Library

Simple Game Library (SGL) is a minimalistic C library for developing games.

## C Standard

SGL is implemented with ANSI C and `long long` extension.

## Text Format

All SGL functions that take text strings use UTF-8 format. To make it more
consistant across platforms SGL provides a macro replacing the standard `fopen`
function on Windows making it accept UTF-8 file path.

