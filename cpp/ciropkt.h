/** @file
  Ciropkt functions and definitions

  Serialized packet : |address|command|sequence|----data----|crc|

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

#include "result.h"
#include "cobs.h"
#include "crc8.h"
#include <string.h>

#ifndef CIROPKT_H
#define CIROPKT_H

#ifdef __cplusplus
extern "C" {
#endif

//// DEFINES

/** Default static initialization value of packet object */
#define pkt_INIT {0, 0, 0, 0, {0}}

/** Declare and initialize a packet variable */
#define pkt_VAR(p) packet_t p = pkt_INIT

/** Maximum data in packet */
#define pkt_MAXDATASIZE 100

/** Header size: address, command, sequence */
#define pkt_HEADERSIZE (3 * sizeof(uint8_t))

/** Crc size: 1 byte */
#define pkt_CRCSIZE sizeof(uint8_t)

/** Extra size in packet besides data */
#define pkt_EXTRASIZE (pkt_HEADERSIZE + pkt_CRCSIZE)

/** Calculate total unserialized packet bytes for given payload data size */
#define pkt_LENGTH(d) (pkt_HEADERSIZE + (d) + pkt_CRCSIZE)

/** Max unserialized space that a packet can take */
#define pkt_MAXSPACE pkt_LENGTH(pkt_MAXDATASIZE)

//// STRUCTURES DEFINITIONS

/** C ciropkt packet object */
typedef struct packet_t packet_t;
struct packet_t
{
    uint8_t address; ///< Slave address
    uint8_t command; ///< Packet command
    uint8_t sequence; ///< Packet sequence
    uint8_t crc; ///< Calculated/received crc

    size_t data_size; ///< Packet used data bytes

    uint8_t data[pkt_MAXDATASIZE]; ///< Internal data buffer
};

//// FORWARD FUNCTIONS DECLARATIONS

/** Update object data and data_size */
pkt_res_t pktUpdate(packet_t *p, const void *dat, const size_t len);

/** Check if pkt has valid CRC */
bool pktCheck(const packet_t *p);

/** Refresh packet CRC */
pkt_res_t pktRefresh(packet_t *p);

/** Serialize packet */
pkt_res_t pktSerialize(const packet_t *p, uint8_t *buf, size_t *len);

/** Deserialize packet */
pkt_res_t pktDeserialize(packet_t *p, const uint8_t *buf, const size_t len);

#ifdef __cplusplus
}
#endif

#endif // CIROPKT_H
