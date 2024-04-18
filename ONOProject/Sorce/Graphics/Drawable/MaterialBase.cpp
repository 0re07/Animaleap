#include <cassert>
#include "MaterialBase.h"

MaterialBase::MaterialBase()
{

}

MaterialBase::~MaterialBase()
{
}

void MaterialBase::Init(void)
{

}

void MaterialBase::SetTextures(int slot, int texDiffuse)
{
	if (texture_.count(slot) == 0)
	{
		texture_.emplace(slot, texDiffuse);
	}
	else
	{
		texture_[slot] = texDiffuse;
	}
}


