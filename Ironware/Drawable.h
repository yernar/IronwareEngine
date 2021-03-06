/*!
 * \file Drawable.h
 * \date 2020/09/23 5:49
 *
 * \author Yernar Aldabergenov
 * Contact: yernar.aa@gmail.com
 *
 * \brief A header that contains a drawable class
 *
 * \note It contains: pIndexBuffer, as it's needed to get its count.
 * *				  binds collection that stores various bindable types in it.
*/
#pragma once

#include "Graphics.h"
#include "Bindable.h"
#include "CommonMacros.h"
#include "RenderTechnique.h"

#include <DirectXMath.h>

#include <memory>

class RenderGraph;
class TechniqueProbe;
class Material;
struct aiMesh;

/*!
 * \class Drawable
 *
 * \ingroup Drawables
 *
 * \brief A drawable abstract class that controls(partly) the graphics pipeline and provides
 * * an interface for the other geometry object types
 *
 * \author Yernar Aldabergenov
 *
 * \date September 2020
 *
 * Contact: yernar.aa@gmail.com
 *
 */
class Drawable
{
public:
	Drawable() = default;
	Drawable( Graphics& gfx, const Material& mat, const aiMesh& mesh, float scale = 1.f ) noexcept;
	Drawable( const Drawable& ) = delete;
	virtual ~Drawable() = default;

	virtual DirectX::XMMATRIX GetTransformXM() const noexcept = 0;
	void AddTechnique( RenderTechnique tech_in ) noexcept;
	void Submit( size_t channelFilter ) const noexcept;
	void Bind( Graphics& gfx ) const IFNOEXCEPT;
	void Accept( class TechniqueProbe& probe );
	UINT GetIndexCount() const IFNOEXCEPT;
	void LinkTechniques( RenderGraph& rg );

protected:
	std::shared_ptr<class IndexBuffer> pIndices;
	std::shared_ptr<class VertexBuffer> pVertices;
	std::shared_ptr<class PrimitiveTopology> pTopology;

private:
	std::vector<RenderTechnique> techniques;
};