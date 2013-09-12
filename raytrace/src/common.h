/* Your Name Here
 * somebody at something dot TLD
 * CS 566
 * September 20XX
 *
 */
/*
 * Copyright (c) 2005-2013 Michael Shafae
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met: 
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * $Id: common.h 4419 2013-09-12 04:16:46Z mshafae $
 *
 */
 
#include <iostream>

#ifndef _COMMON_H_
#define _COMMON_H_

#define SQR(x) ((x)*(x))

#ifndef MAX
#define MAX(x,y) ((x)>(y)?(x):(y))
#define MIN(x,y) ((x)<(y)?(x):(y))
#endif

typedef unsigned int uint;
typedef unsigned char uchar;


#define DELETEIFNOTNULL(pointer){ \
  if (pointer){ delete pointer; pointer = 0;} \
}

#define fopen_error(fname) { \
 std::cerr<<"Failed to open file "<<fname<<endl; \
 exit(0); \
}

#define fatal_error(err_string) { \
 std::cerr<<err_string<<endl; \
 exit(0); \
}


/* For use in hash_map */
struct eqint
{
  bool operator()(int n1, int n2) const
  {
    return n1 == n2;
  }
};


// Returns a random number between min and max, with the indicated precission between limits
double rangerand(double min, double max, int steps=10000);


// Description of the log levels:
// 0 - No debugging at all. Not even critical messages. No messages should be leveled at 0.
// 1 - Critical messages
// 2 - INFORMATIONAL : High level Information, eq coord of a created plane
// 3 - Low level info, eq about an image/vector  created

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 2
#endif

#define LOG(n, format, arg...) if (DEBUG_LEVEL >= (n)) fprintf(stderr, format , ## arg)
#define LOG2(n, arg) if (DEBUG_LEVEL >= (n)) cerr << arg << endl

#endif //_COMMON_H_

