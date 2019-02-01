/** @file
  Ciropkt commands and packets.

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

#include <stdint.h>

#ifndef CIROPKT_CMD_H
#define CIROPKT_CMD_H

#ifdef __cplusplus
extern "C" {
#endif

/** Commands */
typedef enum
{
  cmd_CPGInitQuery,
  cmd_CPGInfoQuery,
  cmd_CPGInfoReply,
}cmds_e;

/** CPG info structure */
typedef struct CPGInfoReply CPGInfoReply;
struct CPGInfoReply
{
  uint8_t cpg_id;
  uint8_t cpg_count;
  uint8_t cpg_sequence;
};

typedef struct CPGInfoQuery CPGInfoQuery;
struct CPGInfoQuery
{
  uint8_t cpg_sequence;
};

/** CPG info structure */
typedef struct CPGInitQuery CPGInitQuery;
struct CPGInitQuery
{
  uint8_t cpg_channel;
  uint32_t cpg_address;
};

#ifdef __cplusplus
}
#endif

#endif // CIROPKT_CMD_H


