#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include <assert.h>
#include "Resource.h"

Resource::Resource(void)
{
	type_ = TYPE::NONE;
	path_ = "";

	numX_ = -1;
	numY_ = -1;
	sizeX_ = -1;
	sizeY_ = -1;

	handleId_ = -1;
	handleIds_ = {};
}

Resource::Resource(TYPE type, const std::string& path)
{
	type_ = type;
	path_ = path;

	numX_ = -1;
	numY_ = -1;
	sizeX_ = -1;
	sizeY_ = -1;

	handleId_ = -1;
	handleIds_ = {};
}

Resource::Resource(TYPE type, const std::string& path, int numX, int numY, int sizeX, int sizeY)
{
	type_ = type;
	path_ = path;
	numX_ = numX;
	numY_ = numY;
	sizeX_ = sizeX;
	sizeY_ = sizeY;

	handleId_ = -1;
	handleIds_ = {};
}

Resource::~Resource(void)
{
}

void Resource::Load(void)
{

	switch (type_)
	{
	case Resource::TYPE::IMG:
		// ‰æ‘œ
		handleId_ = LoadGraph(path_.c_str());
		assert(handleId_ > -1);
		break;

	case Resource::TYPE::IMGS:
		// •¡”‰æ‘œ
		handleIds_.resize(numX_ * numY_);
		LoadDivGraph(
			path_.c_str(),
			numX_ * numY_,
			numX_, numY_,
			sizeX_, sizeY_,
			handleIds_.data());

		for (const auto& handleId : handleIds_)
		{
			assert(handleId > -1);
		}

		
		break;

	case Resource::TYPE::MODEL:
		// ƒ‚ƒfƒ‹
		handleId_ = MV1LoadModel(path_.c_str());
		assert(handleId_ > -1);
		break;

	case Resource::TYPE::EFFEKSEER:

		handleId_ = LoadEffekseerEffect(path_.c_str());
		assert(handleId_ > -1);
		break;
	case Resource::TYPE::SOUND:

		handleId_ = LoadSoundMem(path_.c_str());
		assert(handleId_ > -1);
		break;

	}

}

void Resource::Release(void)
{

	switch (type_)
	{
	case Resource::TYPE::IMG:
		DeleteGraph(handleId_);
		break;

	case Resource::TYPE::IMGS:
	{
		for (auto& id : handleIds_)
		{
			DeleteGraph(id);
		}

	}
		break;

	case Resource::TYPE::MODEL:
	{
		MV1DeleteModel(handleId_);
		auto ids = duplicateModelIds_;
		int count = 0;
		for (auto id : ids)
		{
			MV1DeleteModel(id);
			count++;
		}
	}
		break;

	case Resource::TYPE::EFFEKSEER:

		DeleteEffekseerEffect(handleId_);
		break;

	}

}

void Resource::CopyHandle(std::vector<int>& imgs)
{
	
	int num = numX_ * numY_;
	for (int i = 0; i < num; i++)
	{
		if (imgs[i] < 0)
		{
			return;
		}
		imgs[i] = handleIds_[i];
	}

}
