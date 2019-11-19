/**
 * file: ciropkt.js
 *
 *  Ciropkt functions and definitions
 *
 *  Serialized packet : |address|command|sequence|----data----|crc|
 */

const crc = require('crc');
const cobs = require('cobs')

/** Maximum data in packet */
const pkt_MAXDATASIZE = 100;

/** Header size: address, command and sequence */
const pkt_HEADERSIZE = 3;

/** Crc size: 1 byte */
const pkt_CRCSIZE = 1;

/** Extra size in packet besides data */
const pkt_EXTRASIZE = pkt_HEADERSIZE + pkt_CRCSIZE;

/** Calculate total unserialized packet bytes for given payload data size */
var pkt_LENGTH = d => pkt_HEADERSIZE + d + pkt_CRCSIZE;

/** Max unserialized space that a packet can take */
const pkt_MAXSPACE = pkt_LENGTH(pkt_MAXDATASIZE);

class Packet {
  constructor() {
    this._address = 0;
    this._command = 0;
    this._sequence = 0;
    this._data = Buffer.alloc(0);
    this._crc = 0;
  }

  setAddress(address) { this._address = address; }
  getAddress() { return this._address; }

  setCommand(command) { this._command = command; }
  getCommand() { return this._command; }

  setSequence(sequence) { this._sequence = sequence; }
  getSequence() { return this._sequence; }

  _bufferize()
  {
    var buf = Buffer.alloc(pkt_LENGTH(this._data.length));

    buf[0] = this._address;
    buf[1] = this._command;
    buf[2] = this._sequence;

    this._data.copy(buf, pkt_HEADERSIZE);

    buf[pkt_LENGTH(this._data.length) - 1] = this._crc;

    return buf;
  }

  _debufferize(buf)
  {
    if (buf.length < pkt_LENGTH(0))
      return false;

    this._address = buf[0];
    this._command = buf[1];
    this._sequence = buf[2];
    this._crc = buf[buf.length - 1];

    return this.update(buf.subarray(pkt_HEADERSIZE, buf.length - pkt_CRCSIZE));
  }

  _checksum()
  {
    var tmp = this._bufferize();
    var c = crc.crc8(tmp.subarray(0, pkt_LENGTH(this._data.length)- pkt_CRCSIZE));
    return ~(c) & 0xFF;
  }

  update(data)
  {
    if (data.length > pkt_MAXDATASIZE)
      return false;

    this._data = data;
    return true;
  }

  check()
  {
    return (this._checksum() == this._crc);
  }

  refresh()
  {
    this._crc = this._checksum();
  }

  serialize()
  {
    return cobs.encode(this._bufferize());
  }

  deserialize(buf)
  {
    return this._debufferize(cobs.decode(buf));
  }
}

module.exports.Packet = Packet;

/// Tests
// pkt = new Packet();
// pkt.setAddress(1);
// pkt.setCommand(1);
// pkt.update(Buffer.from([0x08, 0x01, 0x18, 0x01, 0x28, 0x01]));
// console.log(pkt.check());
// pkt.refresh();
// console.log(pkt);
//
// pktser = pkt.serialize();
//
// pkt2 = new Packet();
// pkt2.deserialize(pktser);
// console.log(pkt2);
// console.log(pkt2.check());
