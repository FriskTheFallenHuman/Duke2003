/*=============================================================================
	XeD3DVertexBuffer.h: XeD3D vertex buffer RHI definitions.
	Copyright 1998-2011 Epic Games, Inc. All Rights Reserved.
=============================================================================*/

#if USE_XeD3D_RHI

/** vertex buffer resource */
class FXeVertexBuffer : public FXeGPUResource
{
public:
	/** default constructor */
	FXeVertexBuffer(DWORD InUsageFlags)
	:	FXeGPUResource(new IDirect3DVertexBuffer9, InUsageFlags)
	{
	}

	/** constructor initialized w/ existing D3D resource */
	FXeVertexBuffer(IDirect3DVertexBuffer9* InResource, DWORD InUsageFlags)
	:	FXeGPUResource(InResource, InUsageFlags)
	{
	}

	/** 
	 * Sets D3D header and allocates memory for the resource 
	 *
	 * @param Size - total size of the vertex buffer in bytes
	 * @param ResourceArray - optional interface to source data array
	 */
	void AllocVertexBuffer(UINT Size, FResourceArrayInterface* ResourceArray);

	/**
	 * @return Resource type name.
	 */
	virtual TCHAR* GetTypeName() const
	{
		return TEXT("VertexBuffer");
	}
};

/*-----------------------------------------------------------------------------
RHI vertex buffer type
-----------------------------------------------------------------------------*/
typedef TXeGPUResourceRef<IDirect3DVertexBuffer9,FXeVertexBuffer> FVertexBufferRHIRef;
typedef FXeVertexBuffer* FVertexBufferRHIParamRef;

#endif
