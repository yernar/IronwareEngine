/*!
 * \file FrameExecutor.cpp
 *
 * \author Yernar Aldabergenov
 * \date May 2021
 *
 *
 */
#include "FrameExecutor.h"
#include "BindableCommon.h"

void FrameExecutor::Execute( Graphics& gfx ) const IFNOEXCEPT
{
	DepthStencilState::Resolve( gfx, DepthStencilState::StencilMode::Off )->Bind( gfx );
	rqs[0].Execute( gfx );

	DepthStencilState::Resolve( gfx, DepthStencilState::StencilMode::Write )->Bind( gfx );
	NullPixelShader::Resolve( gfx )->Bind( gfx );
	rqs[1].Execute( gfx );

	DepthStencilState::Resolve( gfx, DepthStencilState::StencilMode::Mask )->Bind( gfx );
	rqs[2].Execute( gfx );
}

void FrameExecutor::Reset() noexcept
{
	for( auto& q : rqs )
	{
		q.Reset();
	}
}