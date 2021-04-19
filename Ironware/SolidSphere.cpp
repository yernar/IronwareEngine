/*!
 * \file SolidSphere.cpp
 *
 * \author Yernar Aldabergenov
 * \date November 2020
 *
 *
 */
#include "SolidSphere.h"
#include "BindableCommon.h"
#include "GraphicsExceptionMacros.h"
#include "Vertex.h"
#include "Sphere.h"

SolidSphere::SolidSphere( Graphics& gfx, float radius )
{
	namespace dx = DirectX;

	struct Vertex
	{
		dx::XMFLOAT3 pos;
	};
	auto model = Sphere::Make<Vertex>();
	model.Transform( dx::XMMatrixScaling( radius, radius, radius ) );
	VertexByteBuffer vbuff(
		VertexLayout{}
		.Append( VertexLayout::ElementType::Position3D )
	);
	for( auto& v : model.vertices )
	{
		vbuff.EmplaceBack( v.pos );
	}
	const std::wstring& sphereTag = L"$sphere." + std::to_wstring( radius );
	AddBind( VertexBuffer::Resolve( gfx, sphereTag, vbuff ) );
	AddBind( IndexBuffer::Resolve( gfx, sphereTag, model.indices ) );

	auto pVertexShader = VertexShader::Resolve( gfx, L"SolidVS.cso" );
	auto pVertexShaderBytecode = pVertexShader->GetBytecode();
	AddBind( std::move( pVertexShader ) );

	AddBind( PixelShader::Resolve( gfx, L"SolidPS.cso" ) );

	const auto pixCBuff = PixelConstantBuffer<dx::XMFLOAT3A>::Resolve( gfx, color );
	pPixelCBuff = pixCBuff.get();
	AddBind( pixCBuff );

	AddBind( InputLayout::Resolve( gfx, vbuff.GetLayout(), pVertexShaderBytecode ) );

	AddBind( PrimitiveTopology::Resolve( gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST ) );

	AddBind( std::make_shared<TransformCBuffer>( gfx, *this ) );
}

void SolidSphere::UpdateColor( Graphics& gfx, const DirectX::XMFLOAT3A& col ) noexcept
{
	color = col;
	pPixelCBuff->Update( gfx, color );
}