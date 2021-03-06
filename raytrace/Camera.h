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
 * $Id: Camera.h 5856 2015-06-06 22:48:38Z mshafae $
 *
 */

#include <iostream>

#include <GFXMath.h>
#include <GFXExtra.h>

#ifndef _CAMERA_H_
#define _CAMERA_H_

enum{
  CAMERA_NULL = 0,
  CAMERA_ORTHO,
  CAMERA_SIMPLE_PERSPECTIVE,
  CAMERA_PERSPECTIVE
};

class Camera{
public:
  Camera( ): _type(CAMERA_NULL){ };
  Camera(uint type, Point3& position, Point3& lookAt, Vec3& up);
  Camera(const Camera& c);

  virtual ~Camera( ){ };

  virtual Camera& operator =(const Camera& rhs);
  
  Point3 position( ) const;
  Point3 lookAt( ) const;
  Vec3 gaze( ) const;
  Vec3 up( ) const;
  Vec3 right( ) const;

  Mat4 lookAtMatrix( ) const;
    
  uint type( ) const { return _type; };

  std::ostream& write(std::ostream &out) const;
  
protected :
  Point3 _position;
  Point3 _lookAt;
  Vec3 _up;
  uint _type;  
};

// Basic I/O
std::ostream& operator <<( std::ostream &out, const Camera &c );

class OrthographicCamera : public Camera{
public:
  OrthographicCamera(Point3& position, Point3& lookAt, Vec3& up);
  ~OrthographicCamera( );
  
  OrthographicCamera& operator =(const OrthographicCamera& rhs);  
};

#endif
