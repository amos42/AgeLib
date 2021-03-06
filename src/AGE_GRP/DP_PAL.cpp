/*#################################################################
-------------------------------------------------------------------

                             AGE (Ver 1.0)
                       (* =================== *)
                           Amos Game Engine

 Author         : Chu, Kyong-min( Amos )

 Date           : 1997/02/08
 C Compiler     : WATCOM 10.5
 Assembler      : WASM 10.5

-------------------------------------------------------------------
###################################################################*/

#include "age_grp.h"


U8 dp_pal[ 256 ][ 3 ] = {
    {0x00,0x00,0x00}, {0x00,0x00,0xAA}, {0x00,0xAA,0x00}, {0x00,0xAA,0xAA}, 
    {0xAA,0x00,0x00}, {0xAA,0x00,0xAA}, {0xAA,0x55,0x00}, {0xAA,0xAA,0xAA}, 
    {0x55,0x55,0x55}, {0x55,0x55,0xFF}, {0x55,0xFF,0x55}, {0x55,0xFF,0xFF}, 
    {0xFF,0x55,0x55}, {0xFF,0x55,0xFF}, {0xFF,0xFF,0x55}, {0xFF,0xFF,0xFF}, 
    {0xEF,0xEF,0xEF}, {0xDF,0xDF,0xDF}, {0xD3,0xD3,0xD3}, {0xC3,0xC3,0xC3}, 
    {0xB7,0xB7,0xB7}, {0xAB,0xAB,0xAB}, {0x9B,0x9B,0x9B}, {0x8F,0x8F,0x8F}, 
    {0x7F,0x7F,0x7F}, {0x73,0x73,0x73}, {0x67,0x67,0x67}, {0x57,0x57,0x57}, 
    {0x4B,0x4B,0x4B}, {0x3B,0x3B,0x3B}, {0x2F,0x2F,0x2F}, {0x23,0x23,0x23}, 
    {0xFF,0x00,0x00}, {0xEF,0x00,0x00}, {0xE3,0x00,0x00}, {0xD7,0x00,0x00}, 
    {0xCB,0x00,0x00}, {0xBF,0x00,0x00}, {0xB3,0x00,0x00}, {0xA7,0x00,0x00}, 
    {0x9B,0x00,0x00}, {0x8B,0x00,0x00}, {0x7F,0x00,0x00}, {0x73,0x00,0x00}, 
    {0x67,0x00,0x00}, {0x5B,0x00,0x00}, {0x4F,0x00,0x00}, {0x40,0x00,0x00}, 
    {0xFF,0xDA,0xDA}, {0xFF,0xBA,0xBA}, {0xFF,0x9F,0x9F}, {0xFF,0x7F,0x7F}, 
    {0xFF,0x5F,0x5F}, {0xFF,0x40,0x40}, {0xFF,0x20,0x20}, {0xFF,0x00,0x00}, 
    {0xFC,0xA8,0x5C}, {0xFC,0x98,0x40}, {0xFC,0x88,0x20}, {0xFC,0x78,0x00}, 
    {0xE4,0x6C,0x00}, {0xCC,0x60,0x00}, {0xB4,0x54,0x00}, {0x9C,0x4C,0x00}, 
    {0xFC,0xFC,0xD8}, {0xFC,0xFC,0xB8}, {0xFC,0xFC,0x9C}, {0xFC,0xFC,0x7C}, 
    {0xFC,0xF8,0x5C}, {0xFC,0xF4,0x40}, {0xFC,0xF4,0x20}, {0xFC,0xF4,0x00}, 
    {0xE4,0xD8,0x00}, {0xCC,0xC4,0x00}, {0xB4,0xAC,0x00}, {0x9C,0x9C,0x00}, 
    {0x84,0x84,0x00}, {0x70,0x6C,0x00}, {0x58,0x54,0x00}, {0x40,0x40,0x00}, 
    {0xD0,0xFC,0x5C}, {0xC4,0xFC,0x40}, {0xB4,0xFC,0x20}, {0xA0,0xFC,0x00}, 
    {0x90,0xE4,0x00}, {0x80,0xCC,0x00}, {0x74,0xB4,0x00}, {0x60,0x9C,0x00}, 
    {0xD8,0xFC,0xD8}, {0xBC,0xFC,0xB8}, {0x9C,0xFC,0x9C}, {0x80,0xFC,0x7C}, 
    {0x60,0xFC,0x5C}, {0x40,0xFC,0x40}, {0x20,0xFC,0x20}, {0x00,0xFC,0x00}, 
    {0x00,0xFF,0x00}, {0x00,0xEF,0x00}, {0x00,0xE3,0x00}, {0x00,0xD7,0x00}, 
    {0x07,0xCB,0x00}, {0x07,0xBF,0x00}, {0x07,0xB3,0x00}, {0x07,0xA7,0x00}, 
    {0x07,0x9B,0x00}, {0x07,0x8B,0x00}, {0x07,0x7F,0x00}, {0x07,0x73,0x00}, 
    {0x07,0x67,0x00}, {0x07,0x5B,0x00}, {0x07,0x4F,0x00}, {0x04,0x40,0x00}, 
    {0xDA,0xFF,0xFF}, {0xB8,0xFC,0xFC}, {0x9C,0xFC,0xFC}, {0x7C,0xFC,0xF8}, 
    {0x5C,0xFC,0xFC}, {0x40,0xFC,0xFC}, {0x20,0xFC,0xFC}, {0x00,0xFC,0xFC}, 
    {0x00,0xE4,0xE4}, {0x00,0xCC,0xCC}, {0x00,0xB4,0xB4}, {0x00,0x9C,0x9C}, 
    {0x00,0x84,0x84}, {0x00,0x70,0x70}, {0x00,0x58,0x58}, {0x00,0x40,0x40}, 
    {0x5C,0xBC,0xFC}, {0x40,0xB0,0xFC}, {0x20,0xA8,0xFC}, {0x00,0x9C,0xFC}, 
    {0x00,0x8C,0xE4}, {0x00,0x7C,0xCC}, {0x00,0x6C,0xB4}, {0x00,0x5C,0x9C}, 
    {0xDA,0xDA,0xFF}, {0xBA,0xBF,0xFF}, {0x9F,0x9F,0xFF}, {0x7F,0x80,0xFF}, 
    {0x5F,0x60,0xFF}, {0x40,0x40,0xFF}, {0x20,0x25,0xFF}, {0x00,0x05,0xFF}, 
    {0x00,0x00,0xFF}, {0x00,0x00,0xEF}, {0x00,0x00,0xE3}, {0x00,0x00,0xD7}, 
    {0x00,0x00,0xCB}, {0x00,0x00,0xBF}, {0x00,0x00,0xB3}, {0x00,0x00,0xA7}, 
    {0x00,0x00,0x9B}, {0x00,0x00,0x8B}, {0x00,0x00,0x7F}, {0x00,0x00,0x73}, 
    {0x00,0x00,0x67}, {0x00,0x00,0x5B}, {0x00,0x00,0x4F}, {0x00,0x00,0x40}, 
    {0xF0,0xDA,0xFF}, {0xE5,0xBA,0xFF}, {0xDA,0x9F,0xFF}, {0xD0,0x7F,0xFF}, 
    {0xCA,0x5F,0xFF}, {0xBF,0x40,0xFF}, {0xB5,0x20,0xFF}, {0xAA,0x00,0xFF}, 
    {0x9A,0x00,0xE5}, {0x80,0x00,0xCF}, {0x75,0x00,0xB5}, {0x60,0x00,0x9F}, 
    {0x50,0x00,0x85}, {0x45,0x00,0x70}, {0x35,0x00,0x5A}, {0x2A,0x00,0x40}, 
    {0xFF,0xDA,0xFF}, {0xFF,0xBA,0xFF}, {0xFF,0x9F,0xFF}, {0xFF,0x7F,0xFF}, 
    {0xFF,0x5F,0xFF}, {0xFF,0x40,0xFF}, {0xFF,0x20,0xFF}, {0xFF,0x00,0xFF}, 
    {0xE0,0x00,0xE5}, {0xCA,0x00,0xCF}, {0xB5,0x00,0xB5}, {0x9F,0x00,0x9F}, 
    {0x85,0x00,0x85}, {0x6F,0x00,0x70}, {0x5A,0x00,0x5A}, {0x40,0x00,0x40}, 
    {0xFF,0xEA,0xDF}, {0xFF,0xE0,0xD0}, {0xFF,0xDA,0xC5}, {0xFF,0xD5,0xBF}, 
    {0xFF,0xCF,0xB0}, {0xFF,0xC5,0xA5}, {0xFF,0xBF,0x9F}, {0xFF,0xBA,0x90}, 
    {0xFF,0xB0,0x80}, {0xFF,0xA5,0x70}, {0xFF,0x9F,0x60}, {0xF0,0x95,0x5F}, 
    {0xEA,0x8F,0x5A}, {0xDF,0x8A,0x55}, {0xD0,0x80,0x50}, {0xCA,0x7F,0x4F}, 
    {0xBF,0x7A,0x4A}, {0xB5,0x70,0x45}, {0xAA,0x6A,0x40}, {0xA0,0x65,0x3F}, 
    {0x9F,0x60,0x3A}, {0x90,0x5F,0x35}, {0x8A,0x5A,0x30}, {0x80,0x50,0x2F}, 
    {0x75,0x4F,0x2A}, {0x6F,0x4A,0x25}, {0x5F,0x40,0x20}, {0x55,0x3F,0x1F}, 
    {0x4A,0x3A,0x1A}, {0x40,0x30,0x1A}, {0x3A,0x2F,0x15}, {0x2A,0x20,0x0F}, 
    {0x00,0x00,0x00}, {0xF0,0xD0,0x40}, {0xF0,0xC0,0x30}, {0xD0,0xA0,0x20}, 
    {0xC0,0x80,0x10}, {0xA0,0x60,0x00}, {0x90,0x40,0x10}, {0x80,0x30,0x00}, 
    {0xC7,0x2B,0x2B}, {0xC7,0x4F,0x2B}, {0xC7,0x77,0x2B}, {0xC7,0x9F,0x2B}, 
    {0xC7,0xC7,0x2B}, {0x9F,0xC7,0x2B}, {0x77,0xC7,0x2B}, {0x4F,0xC7,0x2B}, 
    {0x2B,0xC7,0x33}, {0x2B,0xC7,0x5F}, {0x2B,0xC7,0x8B}, {0x2B,0xC7,0xB7}, 
    {0x2B,0xAB,0xC7}, {0x2B,0x7F,0xC7}, {0x2B,0x53,0xC7}, {0x2F,0x2B,0xC7}, 
    {0x5B,0x2B,0xC7}, {0x87,0x2B,0xC7}, {0xB3,0x2B,0xC7}, {0xC7,0x2B,0xAF}, 
    {0xC7,0x2B,0x83}, {0xC7,0x2B,0x57}, {0xC7,0x2B,0x2B}, {0xFF,0xFF,0xFF}, 
};


