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
 * $Id: ShadingRecord.h 5861 2015-06-08 17:46:13Z mshafae $
 *
 */

#include <GFXMath.h>
#include <GFXExtra.h>

#include "Material.h"
 
#ifndef _SHADING_RECORD_H_
#define _SHADING_RECORD_H_

class ShadingRecord{
public:
  ShadingRecord( );
  ShadingRecord(const bool didhit, const float tValue, const Point3& hitPoint, const Vec3& normal, Material* material);

  ShadingRecord(const ShadingRecord& sr);

  ShadingRecord& operator =(const ShadingRecord& sr);

  bool didHit( ) const{
    return _didHit;
  }

  float tValue( ) const{
    return _tValue;
  }

  Point3 hitPoint( ) const{
    return _hitPoint;
  }

  Vec3 normalAtPoint( ) const{
    return _normal;
  }

  Material* material( ) const{
    return _material;
  }

  void setHit(bool hit){
    _didHit = hit;
  }

  void setTValue(const float tValue){
    _tValue = tValue;
  }
  
  void setHitPoint(const Point3& hitPoint){
    _hitPoint = hitPoint;
  }

  void setNormalAtPoint(const Vec3& normal){
    _normal = normal;
  }

  void setMaterial(Material* material){
    _material = material;
  }

  std::ostream& write( std::ostream &out ) const {
    out << "Shading Record:" << std::endl;
    out << "\tDid hit?: " << _didHit << std::endl;
    out << "\tT value: " << _tValue << std::endl;
    out << "\tHit point: " << _hitPoint << std::endl;
    out << "\tNormal: " << _normal << std::endl;
    out << "\tMaterial: " << *_material << std::endl;
    return out;
  }
private:
  bool _didHit;
  float _tValue;
  Point3 _hitPoint;
  Vec3 _normal;
  Material* _material;
};

std::ostream& operator <<( std::ostream &out, const ShadingRecord &sr );

#endif
