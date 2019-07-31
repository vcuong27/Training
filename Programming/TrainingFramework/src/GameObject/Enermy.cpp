#include "Enermy.h"


Enermy::Enermy(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture)
	:Sprite2D(model, shader, texture)
{

}

Enermy::~Enermy()
{
}