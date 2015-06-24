/*
 * Copyright (c) 2005-2015 Michael Shafae
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
 * $Id: RayFactory.h 5861 2015-06-08 17:46:13Z mshafae $
 *
 */

#include <iostream>
#include <utility>

#include <GFXMath.h>
#include <GFXExtra.h>

#include "Camera.h"
#include "ViewPlane.h"

#ifndef _RAYFACTORY_H_
#define _RAYFACTORY_H_

class RayFactory{
public:
  RayFactory( );

  RayFactory(const Camera& c, const ViewPlane& vp);

  ~RayFactory( );

  Ray next(uint* px, uint* py);

  bool hasMoreRays( );

  std::ostream& write(std::ostream& out) const{
    out << "RayFactory:" << std::endl;
    out << "\tRay Count: " << _rayCount << std::endl;
    out << _camera << std::endl;
    out << _viewPlane << std::endl;
    return out;
  }
private:
  Camera _camera;
  ViewPlane _viewPlane;
  unsigned long _rayCount;
  // Fill me in!
};

// Basic I/O
std::ostream& operator <<( std::ostream &out, const RayFactory &rf ){
  rf.write(out);
  return out;
}

#endif
