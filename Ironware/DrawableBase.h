/*!
 * \file DrawableBase.h
 * \date 2020/09/25 14:34
 *
 * \author Yernar Aldabergenov
 * Contact: yernar.aa@gmail.com
 *
 * \brief A header that contains a (drawable) drawablebase class
 *
 * \note Index Buffer needs to be set separately for every geometry object type
*/
#pragma once

#include "Drawable.h"
#include "IndexBuffer.h"

/*!
 * \class DrawableBase
 *
 * \ingroup Drawables
 *
 * \brief A CRTP class for managing static binds in the graph pipeline
 *
 * \author Yernar Aldabergenov
 *
 * \date September 2020
 *
 * Contact: yernar.aa@gmail.com
 *
 */
template<typename T>
class DrawableBase : public Drawable
{
protected:
	/**
	 * @brief Checks if staticbinds is already initialized. Use this function to check
	 * * in drawables if the reusable bindables are already added into the staticbinds
	 * @return boolean value that answers to the question :)
	*/
	static __forceinline bool IsStaticInitialized() { return !staticBinds.empty(); }

	static void AddStaticBind( std::unique_ptr<Bindable> bind ) noexcept( !IS_DEBUG );
	void AddStaticIndexBufferBind( std::unique_ptr<class IndexBuffer> ibuf ) noexcept;

	/**
	 * @brief Sets index buffer from staticbinds. It's needed when you're going to draw
	 * * a drawable, as drawindexed requires indexcount
	*/
	void SetIndexFromStatic() noexcept( !IS_DEBUG );

private:
	__forceinline const std::vector<std::unique_ptr<Bindable>>& GetStaticBinds() const noexcept override { return staticBinds; }

private:
	static std::vector<std::unique_ptr<Bindable>> staticBinds;
};

#include "DrawableBase.tpp"