/** @file
  CRC8 calculation

  8-bit with 0x97 polynomial

  @date 2019-01-31
  @author pepemanboy

  Copyright 2019 Cirotec Automation

  Permission is hereby granted, free of charge, to any person obtaining a copy 
  of this software and associated documentation files (the "Software"), to deal 
  in the Software without restriction, including without limitation the rights 
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
  copies of the Software, and to permit persons to whom the Software is 
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in 
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
  SOFTWARE.
*/

//// INCLUDES

#include "crc8.h"

//// PUBLIC FUNCTIONS

uint8_t crc8(const void *dat, size_t len) 
{
  uint8_t *d = (uint8_t *)dat;
  uint32_t t;
  uint8_t icrc;
  
  --len;
  icrc = 1;
  t = d[0];
  while (len--)
    t = d[icrc++] ^ _crc_tb0x97[t];
  
  return _crc_tb0x97[t];
}
