/** @file
  Ciropkt implementation

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

#include "ciropkt.h"

//// STATIC FUNCTIONS

/** Convert packet to buffer */
static res_t pktBufferize(const packet_t *p, uint8_t *buf, const size_t len)
{
  if (len < pkt_LENGTH(p->data_size))
   return EMemory;
   
  buf[0] = p->address;
  buf[1] = p->command;
  
  memcpy((uint8_t *)buf + pkt_HEADERSIZE, (uint8_t *)p->data, p->data_size);
  
  buf[pkt_HEADERSIZE + p->data_size] = p->crc; 

  return Ok;
}

/** Convert buffer to packet */
static res_t pktDebufferize(packet_t *p, const uint8_t *buf, size_t len)
{
  if (len < pkt_LENGTH(1))
    return EPartial;

  p->address = buf[0];
  p->command = buf[1];  
  p->crc = buf[len-1];

  return pktUpdate(p, buf + pkt_HEADERSIZE, len - pkt_EXTRASIZE);
}

/** Obtain packet CRC */
static res_t pktCrc(const packet_t *p, uint8_t *crc)
{
  uint8_t temp[pkt_MAXSPACE];
  res_t r = pktBufferize(p, temp, sizeof(temp));
  if (r != Ok)
    return r;

  *crc = ~crc8(temp, pkt_HEADERSIZE + p->data_size);
  return Ok;
}

//// PUBLIC FUNCTIONS

res_t pktUpdate(packet_t *p, const void *dat, const size_t len)
{
  if (len > pkt_MAXDATASIZE)
    return EMemory;

  memcpy(p->data, dat, len);

  p->data_size = len;
}

bool pktCheck(const packet_t *p)
{
  uint8_t crc;
  uint8_t r = pktCrc(p,&crc);
  if (r != Ok)
    return false;

  return (crc == p->crc);
}

res_t pktRefresh(packet_t *p)
{
  return pktCrc(p, &p->crc);  
}

uint8_t pktSerialize(const packet_t *p, uint8_t *buf, size_t *len)
{
  if (*len < pkt_LENGTH(p->data_size) + 1)
    return EMemory;
    
  uint8_t temp[pkt_MAXSPACE];
  uint8_t res = pktBufferize(p, temp, sizeof(temp));
  if (res != Ok)
    return res;
    
  *len = cobs_encode(temp, pkt_LENGTH(p->data_size), buf);

  return Ok;
}

res_t pktDeserialize(packet_t *p, const uint8_t *buf, size_t len)
{
  uint8_t temp[pkt_MAXSPACE];
  
  uint8_t l = cobs_decode(buf, len, temp);
  if (!l)
    return EData;

  res_t r = pktDebufferize(p, temp, l);
  if (r != Ok)
    return r;
    
  return Ok;
}
