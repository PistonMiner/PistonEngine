#pragma once

#include "layer.h"
#include "../BatchRenderer2D.h"

namespace PistonEngine { namespace graphics {
	
	class TileLayer : public Layer
	{
	public:
		TileLayer(Shader* shader);
		~TileLayer();
	
	};
	
} }