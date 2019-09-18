# Ciropkt

Ciropkt is a simple serial packet library.

## Packet

A packet contains the following information:
* Address
* Command
* CRC
* Data size
* Data

Bufferized, the packet will be as follows:
| Address (1 byte) | Command (1 byte) | CRC (1 byte) | Data (n bytes) |

When serialized, the library will use COBS encoding to serialize the bufferized packet.
