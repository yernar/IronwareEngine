/*!
 * \file Vertex.cpp
 *
 * \author Yernar Aldabergenov
 * \date March 2021
 *
 *
 */
#include "Vertex.h"

Vertex::Vertex( uint8_t* data, const VertexLayout& layout ) :
	pData( data ),
	layout( layout )
{
	assert( pData != nullptr );
}

VertexByteBuffer::VertexByteBuffer( VertexLayout layout ) :
	layout( std::move( layout ) )
{}