# Ciropkt

Ciropkt is a simple serial packet library.

## Packet

A packet contains the following information:
* Address
* Command
* Sequence
* CRC
* Data size
* Data

Bufferized, the packet will be as follows:
| Address (1 byte) | Command (1 byte) | Sequence (1 byte) | --- Data (n bytes) --- | CRC (1 byte) |

When serialized, the library will use COBS encoding to serialize the bufferized packet.
