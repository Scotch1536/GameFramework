#include "GameFramework/Components/CStaticMeshComponent.h"
#include "GameFramework/Components/CCameraComponent.h"
#include "GameFramework/Actor/CActorGenerator.h"
#include "GameFramework/Actor/CActor.h"

#include "CFighter.h"
#include "CSkyDome.h"
#include "CAttachObject.h"

#include "CMainGameLevel.h"

void CMainGameLevel::Init()
{
	CComponent* buf;

	CFighter& fighter= *new CFighter(*this);

	CSkyDome& skyDome= *new CSkyDome(*this);
	skyDome.GetComponent<CStaticMeshComponent>(buf);
	XMFLOAT3 min , max;
	min = max = { 0.0f,0.0f,0.0f };

	for(auto& mesh : dynamic_cast<CStaticMeshComponent*>(buf)->GetModel().GetMeshes())
	{
		for(auto& vertex : mesh.Vertices)
		{
			if(min.x > vertex.Pos.x)min.x = vertex.Pos.x;
			else if(max.x < vertex.Pos.x)max.x = vertex.Pos.x;

			if(min.y > vertex.Pos.y)min.y = vertex.Pos.y;
			else if(max.y < vertex.Pos.y)max.y = vertex.Pos.y;

			if(min.z > vertex.Pos.z)min.z = vertex.Pos.z;
			else if(max.z < vertex.Pos.z)max.z = vertex.Pos.z;
		}
	}

	new CActorGenerator(*this , [&] { return new CAttachObject(*this); } , min , max , 1.0f);

	fighter.GetComponent<CCameraComponent>(buf);
	RequestSetCamera(*dynamic_cast<CCameraComponent*>(buf));
}