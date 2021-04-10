/*!
 * \file Drawable.cpp
 *
 * \author Yernar Aldabergenov
 * \date September 2020
 *
 * 
 */
#include "Drawable.h"
#include "GraphicsExceptionMacros.h"
#include "IndexBuffer.h"
#include "Bindable.h"

#include <cassert>

void Drawable::Draw( Graphics& gfx ) const IFNOEXCEPT
{
	for( auto& b : binds )
	{
		b->Bind( gfx );
	}
	for( auto& b : GetStaticBinds() )
	{
		b->Bind( gfx );
	}
	gfx.DrawIndexed( pIndexBuffer->GetCount() );
}

Bindable* Drawable::AddBind( std::unique_ptr<Bindable> bind ) IFNOEXCEPT
{
	// Check if there was an attempt to bind IndexBuffer without AddIndexBufferBind
	assert( "*Must* use AddIndexBufferBind to bind index buffer" && typeid( *bind ) != typeid( IndexBuffer ) );
	binds.push_back( std::move( bind ) );
	return binds.back().get();
}

Bindable* Drawable::AddIndexBufferBind( std::unique_ptr<IndexBuffer> ibuf ) IFNOEXCEPT
{
	assert( "Attempting to add index buffer a second time" && pIndexBuffer == nullptr );
	pIndexBuffer = ibuf.get();
	binds.push_back( std::move( ibuf ) );
	return binds.back().get();
}