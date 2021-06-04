#include "CLevel.h"

CLevel::CLevel(CGame& owner):mOwnerInterface(owner)
{
	mOwnerInterface.LoadLevel(*this);
}

void CLevel::DestroyActor(CActor& target)
{
	for(auto itr = mActors.begin(); itr != mActors.end(); ++itr)
	{
		if((*itr).get() == &target)
		{
			mActors.erase(itr);
			break;
		}
	}
	mActors.shrink_to_fit();
}