/*=============================================================================
D3DUtil.h: D3D RHI utility definitions.
Copyright 1998-2011 Epic Games, Inc. All Rights Reserved.
=============================================================================*/

#if USE_XeD3D_RHI

/**
* Encapsulates a reference to a FXeGPUResource derived object
* D3DType is provided for automatic casting as D3D resource
*/
template<typename D3DType, typename XeGPUResourceType>
class TXeGPUResourceRef
{
public:
	TXeGPUResourceRef():
		Reference(NULL)
	{}

	TXeGPUResourceRef(XeGPUResourceType* InReference,UBOOL bAddRef = TRUE)
	{
		Reference = InReference;
		if(Reference && bAddRef)
		{
			Reference->AddRef();
		}
	}

	TXeGPUResourceRef(const TXeGPUResourceRef& Copy)
	{
		Reference = Copy.Reference;
		if(Reference)
		{
			Reference->AddRef();
		}
	}

	~TXeGPUResourceRef()
	{
		if(Reference)
		{
			Reference->Release();
		}
	}

	TXeGPUResourceRef& operator=(XeGPUResourceType* InReference)
	{
		XeGPUResourceType* OldReference = Reference;
		Reference = InReference;
		if(Reference)
		{
			Reference->AddRef();
		}
		if(OldReference)
		{
			OldReference->Release();
		}
		return *this;
	}

	TXeGPUResourceRef& operator=(const TXeGPUResourceRef& InPtr)
	{
		return *this = InPtr.Reference;
	}

	UBOOL operator==(const TXeGPUResourceRef& Other) const
	{
		return Reference == Other.Reference;
	}
	UBOOL operator==(XeGPUResourceType* Other)
	{
		return Reference == Other;
	}

	XeGPUResourceType* operator->() const
	{
		return Reference;
	}

	operator XeGPUResourceType*() const
	{
		return Reference;
	}

	/** auto casting accessor for D3D resource */
	operator D3DType*() const
	{
		return Reference ? (D3DType*)Reference->Resource : NULL;
	}

	// RHI reference interface.

	friend UBOOL IsValidRef(const TXeGPUResourceRef& Ref)
	{
		return Ref.Reference != NULL;
	}

	void SafeRelease()
	{
		*this = NULL;
	}

	DWORD GetRefCount() const
	{
		return Reference ? Reference->GetRefCount() : 0;
	}

protected:
	XeGPUResourceType* Reference;
};

/**
* Checks that the given result isn't a failure.  If it is, the application exits with an appropriate error message.
* @param	Result - The result code to check
* @param	Code - The code which yielded the result.
* @param	Filename - The filename of the source file containing Code.
* @param	Line - The line number of Code within Filename.
*/
extern void VerifyD3DResult(HRESULT Result,const ANSICHAR* Code,const ANSICHAR* Filename,UINT Line);

/**
* A macro for using VerifyD3DResult that automatically passes in the code and filename/line.
*/
#if DO_CHECK
#define VERIFYD3DRESULT(x) VerifyD3DResult(x,#x,__FILE__,__LINE__);
#else
#define VERIFYD3DRESULT(x) (x);
#endif

/**
* Convert from ECubeFace to D3DCUBEMAP_FACES type
* @param Face - ECubeFace type to convert
* @return D3D cube face enum value
*/
FORCEINLINE D3DCUBEMAP_FACES GetD3DCubeFace(ECubeFace Face)
{
	switch(Face)
	{
	case CubeFace_PosX:
	default:
		return D3DCUBEMAP_FACE_POSITIVE_X;
	case CubeFace_NegX:
		return D3DCUBEMAP_FACE_NEGATIVE_X;
	case CubeFace_PosY:
		return D3DCUBEMAP_FACE_POSITIVE_Y;
	case CubeFace_NegY:
		return D3DCUBEMAP_FACE_NEGATIVE_Y;
	case CubeFace_PosZ:
		return D3DCUBEMAP_FACE_POSITIVE_Z;
	case CubeFace_NegZ:
		return D3DCUBEMAP_FACE_NEGATIVE_Z;
	};
}


/**
 *	Blocks the CPU until the GPU has processed all pending commands and gone idle.
 */
extern void XeBlockUntilGPUIdle();


/** Helper class for moving memory using the GPU. See GGPUMemMove. */
struct FGPUMemMove
{
	/** Constructor */
	FGPUMemMove();

	/** Initializer to begin using this helper object. */
	void Initialize();

	/** Must be called before calling MemMove(). */
	void BeginMemMove();

	/** Must be called after you're done calling MemMove(). */
	void EndMemMove();

	/**
	 * Copies a block of memory using the GPU. The source and destination is allowed to overlap.
	 * @param Dst		Destination base address. Must be aligned to 64 bytes.
	 * @param Src		Source base address. Must be aligned to 64 bytes.
	 * @param NumBytes	Number of bytes to copy. Must be a multiple of 64 bytes.
	 */
	void MemMove( void* Dst, const void* Src, INT NumBytes );

	/** Whether Initialize() has been called successfully. */
	UBOOL IsInitialized()
	{
		return VertexDecl != NULL;
	}

	/** Helper constants. */
	enum
	{
		VertexSize			= 64,	// 8 short4 vectors per input element (vertex)
		VertexElementSize	= 8,	// 1 short4 vector per output element (per memexport eM[n] register)
	};

	/** Vertex declaration used by the GPU transfer. */
	IDirect3DVertexDeclaration9* VertexDecl;

	/** Mem-export constant used by the GPU transfer. */
	GPU_MEMEXPORT_STREAM_CONSTANT MemExportStreamConstant;

	/** Vertex shader used by the GPU transfer. */
	class FMemCopyVertexShader* MemCopyVertexShader;
};

/** Global helper object for (overlapping) memory copy using the GPU. */
extern FGPUMemMove GGPUMemMove;


#endif
