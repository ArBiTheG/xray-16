#include "stdafx.h"
#pragma hdrstop

#include "sh_atomic.h"
#include "ResourceManager.h"

// Atomic
//SVS::~SVS								()			{	_RELEASE(vs);		dxRenderDeviceRender::Instance().Resources->_DeleteVS			(this);	}
//SPS::~SPS								()			{	_RELEASE(ps);		dxRenderDeviceRender::Instance().Resources->_DeletePS			(this);	}
//SState::~SState							()			{	_RELEASE(state);	dxRenderDeviceRender::Instance().Resources->_DeleteState		(this);	}
//SDeclaration::~SDeclaration				()			{	_RELEASE(dcl);		dxRenderDeviceRender::Instance().Resources->_DeleteDecl		(this);	}

///////////////////////////////////////////////////////////////////////
//	SVS
SVS::SVS() :
	vs(0)
#if defined(USE_DX10) || defined(USE_DX11)
//	,signature(0)
#endif	//	USE_DX10
{
	;
}

SVS::~SVS()
{
    RImplementation.Resources->_DeleteVS(this);
#if defined(USE_DX10) || defined(USE_DX11)
	//_RELEASE(signature);
	//	Now it is release automatically
#endif	//	USE_DX10
#ifdef USE_OGL
	CHK_GL(glDeleteProgram(vs));
#else
	_RELEASE(vs);
#endif // USE_OGL
}


///////////////////////////////////////////////////////////////////////
//	SPS
SPS::~SPS()
{
#ifdef USE_OGL
	CHK_GL(glDeleteProgram(ps));
#else
	_RELEASE(ps);
#endif // USE_OGL
    RImplementation.Resources->_DeletePS(this);
}

#if defined(USE_DX10) || defined(USE_DX11) || defined(USE_OGL)
///////////////////////////////////////////////////////////////////////
//	SGS
SGS::~SGS								()
{
#ifdef USE_OGL
	CHK_GL(glDeleteProgram(gs));
#else
	_RELEASE(gs);
#endif // USE_OGL
    RImplementation.Resources->_DeleteGS(this);
}

#	ifdef USE_DX11
SHS::~SHS								()
{
    _RELEASE(sh);
    RImplementation.Resources->_DeleteHS(this);
}
SDS::~SDS								()
{
    _RELEASE(sh);
    RImplementation.Resources->_DeleteDS(this);
}
SCS::~SCS								()
{
    _RELEASE(sh);
    RImplementation.Resources->_DeleteCS(this);
}
#	endif
#endif	//	USE_DX10

#if defined(USE_DX10) || defined(USE_DX11)
///////////////////////////////////////////////////////////////////////
//	SInputSignature
SInputSignature::SInputSignature(ID3DBlob* pBlob)	{ VERIFY(pBlob); signature=pBlob; signature->AddRef();};
SInputSignature::~SInputSignature		()
{
    _RELEASE(signature);
    RImplementation.Resources->_DeleteInputSignature(this);
}
#endif	//	USE_DX10

///////////////////////////////////////////////////////////////////////
//	SState
SState::~SState()
{
#ifndef USE_OGL
	_RELEASE(state);
#endif // !USE_OGL
    RImplementation.Resources->_DeleteState(this);
}

///////////////////////////////////////////////////////////////////////
//	SDeclaration
SDeclaration::~SDeclaration()
{
    RImplementation.Resources->_DeleteDecl(this);	
#if defined(USE_DX10) || defined(USE_DX11)
	xr_map<ID3DBlob*, ID3DInputLayout*>::iterator iLayout;
	iLayout = vs_to_layout.begin();
	for( ; iLayout != vs_to_layout.end(); ++iLayout)
	{
		//	Release vertex layout
		_RELEASE(iLayout->second);
	}
#else	//	USE_DX10
	//	Release vertex layout
#ifdef USE_OGL
	glDeleteBuffers(1, &dcl);
#else
	_RELEASE(dcl);
#endif // USE_OGL
#endif	//	USE_DX10
}
