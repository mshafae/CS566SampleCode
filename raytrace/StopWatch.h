/*
 * Copyright (c) 2003-2015 Michael Shafae.
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
 * $Id: StopWatch.h 5665 2015-04-03 23:02:04Z mshafae $
 *
 */

#ifndef _STOPWATCH_H_
#define _STOPWATCH_H_

#include <iostream>
#include <string>

// nanoseconds to seconds
#define ns2s( x ) (x) / 1e9
// microseconds to seconds
#define mus2s( x ) (x) / 1e6
// milliseconds to seconds
#define ms2s( x ) (x) / 1e3

#ifdef __APPLE__

// In nanoseconds
#include <mach/mach_time.h>
#define UNITS "ns"
#define toseconds( x ) ns2s( (x) )
typedef uint64_t stopwatch_t;
typedef mach_timebase_info_data_t timebase_t;
// Timebase represents how many clicks there are per nanosecond
#define __getTimeBaseInfo(x) mach_timebase_info(&x)
// This returns an absolute number of clicks but not nanoseconds
#define __start( x )  x = mach_absolute_time( )
#define __stop( x ) x = mach_absolute_time( )
// Take the clicks and convert to nanoseconds using the timebase information
#define __elapsed( x ) x = (_stop - _start) * timebaseInfo.numer / timebaseInfo.denom
#define __lap( x, y ) x = (y - _lastLap) * timebaseInfo.numer / timebaseInfo.denom

#elif _WIN32

// You have to inspect the timebase to figure out the units.
#include <windows.h>
#define UNITS "??"
typedef LARGE_INTEGER stopwatch_t;
typedef LARGE_INTEGER timebase_t;
// Timebase is expressed as a number of clicks per second. The hardware
// must support a high resolution timer so this value may be zero.
#define __getTimeBaseInfo(x) QueryPerformanceFrequency(&x)
#define __start( x ) QueryPerformanceCounter(&x)
#define __stop( x ) QueryPerformanceCounter(&x)
#define __elapsed( x ) x = _stop.QuadPart - _start.QuadPart) / timebaseInfo
#define __lap( x, y ) x = (y.QuadPart - _lastLap.QuadPart) / timebaseInfo

#elif __linux__
// This doesn't work with gcc 4.4, but does with gcc 4.2
// Very similar to FreeBSD
// In nanoseconds
/*
This file requires compiler and library support for the upcoming ISO C++ standard, C++0x. This support is currently experimental, and must be enabled with the -std=c++0x or -std=gnu++0x compiler options.
*/
#include <cstdint>
// nanoseconds
#define UNITS "ns"
#define toseconds( x ) ns2s( (x) )
typedef uint64_t stopwatch_t;
typedef uint64_t timebase_t;
// clock_gettime can take a number of parameters as to which clock you
// wish to query. In this case, we're querying the real-time clock.
#define __gethrtime( x ) { struct timespec tp; clock_gettime( CLOCK_REALTIME, &tp ); x = tp.tv_sec * 1000000000LL + tp.tv_nsec; }
// clock_gettime fills the timespec data structure with seconds and
// nanoseconds. We just set our timebaseInfo variable to 1 just to
// keep things similar to the other platforms.
#define __getTimeBaseInfo(x) (x = 1LL)
#define __start( x ) __gethrtime(x)
#define __stop( x ) __gethrtime(x)
// We can comment out the division by the timebaseInfo since 
// Linux returns actual time units rather than clicks.
#define __elapsed( x ) x = (_stop - _start) // / timebaseInfo
#define __lap( x, y ) x = (y - _lastLap) // / timebaseInfo

#elif SOLARIS

// In nanoseconds
#include <sys/time.h>
#define UNITS "ns"
#define toseconds( x ) ns2s( (x) )
typedef hrtime_t stopwatch_t;
typedef hrtime_t timebase_t;
#define __getTimeBaseInfo(x) (x)
#define __start( x )  x = gethrtime( )
#define __stop( x ) x = gethrtime( )
#define __elapsed( x ) x = (_stop - _start)
#define __lap( x, y ) x = (y - _lastLap) 

#elif __FreeBSD__

// In nanoseconds
#include <sys/time.h>
// nanoseconds
#define UNITS "ns"
#define toseconds( x ) ns2s( (x) )
typedef u_int64_t stopwatch_t;
typedef u_int64_t timebase_t;
// clock_gettime can take a number of parameters as to which clock you
// wish to query. In this case, we're querying the real-time clock.
#define __gethrtime( x ) \
{ \
  struct timespec tp; \
  clock_gettime( CLOCK_REALTIME, &tp ); \
  // sum seconds with nanoseconds to get nanoseconds
  // Can you say overflow? This is risky and needs to be cleaned.
  x = tp.tv_sec * 1000000000LL + tp.tv_nsec; \
}
// clock_gettime fills the timespec data structure with seconds and
// nanoseconds. We just set our timebaseInfo variable to 1 just to
// keep things similar to the other platforms.
#define __getTimeBaseInfo(x) (x = 1LL)
#define __start( x ) __gethrtime(x)
#define __stop( x ) __gethrtime(x)
// We can comment out the division by the timebaseInfo since 
// FreeBSD returns actual time units rather than clicks.
#define __elapsed( x ) x = (_stop - _start) // / timebaseInfo
#define __lap( x, y ) x = (y - _lastLap) // / timebaseInfo

#endif

class StopWatch{
private:
  stopwatch_t _start, _stop, _lastLap, _elapsed;
  timebase_t timebaseInfo;
public:
  StopWatch( ){
    __getTimeBaseInfo(timebaseInfo);
  }  

  ~StopWatch( ){ };
  
  void start( ){
    __start( _start );
    _lastLap = _start;
  }
  
  stopwatch_t stop( ){
    __stop( _stop );
    __elapsed( _elapsed );
    return( _elapsed );
  }

  stopwatch_t lap( ){
    stopwatch_t _checkpoint;
    __start( _checkpoint );
    __lap( _elapsed, _checkpoint );
    _lastLap = _checkpoint;
    return( _elapsed );
  }

  stopwatch_t elapsed( ){
    return( _elapsed );
  }

  std::ostream& write( std::ostream& out ) const{
    out << _elapsed << " " << UNITS << std::endl;
    out << toseconds( _elapsed ) << " seconds " << std::endl;
    return( out );
  };
  
  std::string units( ){
    return( std::string( UNITS ) );
  }

};

#endif
