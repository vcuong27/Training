#pragma once

#include "Sprite2D.h"

class Enermy : public Sprite2D
{
public:
	Enermy(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture);
	~Enermy();

private:

};
