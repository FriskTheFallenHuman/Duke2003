#ifndef NX_FOUNDATION_NXMATH_XBOX
#define NX_FOUNDATION_NXMATH_XBOX
/*----------------------------------------------------------------------------*\
|
|					Public Interface to NVIDIA PhysX Technology
|
|							     www.nvidia.com
|
\*----------------------------------------------------------------------------*/
/** \addtogroup foundation
  @{
*/

#include <ppcintrinsics.h> //for fpmin,fpmax, sqrt etc

NX_INLINE NxF32 NxMath::max(NxF32 a,NxF32 b)
{
	return __fself(a-b, a, b);
}

NX_INLINE NxF64 NxMath::max(NxF64 a,NxF64 b)
{
	return fpmax(a, b);
}

NX_INLINE NxF32 NxMath::min(NxF32 a,NxF32 b)
{
	return __fself(a-b, b, a);
}

NX_INLINE NxF64 NxMath::min(NxF64 a,NxF64 b)
{
	return fpmin(a, b);
}

NX_INLINE NxF32 NxMath::sqrt(NxF32 a)
{
	return __fsqrts(a);
}

NX_INLINE NxF64 NxMath::sqrt(NxF64 a)
{
	return __fsqrt(a);
}

NX_INLINE bool NxMath::isFinite(NxF32 f)
{
	return (0 == ((_FPCLASS_SNAN | _FPCLASS_QNAN | _FPCLASS_NINF | _FPCLASS_PINF) & _fpclass(f) ));
}

NX_INLINE bool NxMath::isFinite(NxF64 f)
{
	return (0 == ((_FPCLASS_SNAN | _FPCLASS_QNAN | _FPCLASS_NINF | _FPCLASS_PINF) & _fpclass(f) ));
}	

#endif
//NVIDIACOPYRIGHTBEGIN
///////////////////////////////////////////////////////////////////////////
// Copyright (c) 2010 NVIDIA Corporation
// All rights reserved. www.nvidia.com
///////////////////////////////////////////////////////////////////////////
//NVIDIACOPYRIGHTEND