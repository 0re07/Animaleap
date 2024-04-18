#include "MaterialBase.h"
#include "RendererBase.h"

RendererBase::RendererBase(int& modelId, MaterialBase& MaterialBase) :
	modelId_(modelId), materialBase_(MaterialBase)
{
}

RendererBase::~RendererBase()
{
}

