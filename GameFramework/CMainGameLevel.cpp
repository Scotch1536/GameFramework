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

	CFighter& fighter = *new CFighter(*this);
	fighter.Transform.Location.z = -500.0f;

	CSkyDome& skyDome = *new CSkyDome(*this);
	fighter.Transform.AttachTransform(skyDome.Transform);
	skyDome.Transform.AddOption(CTransform::EOption::LOCATION_ONLY);
	skyDome.GetComponent<CStaticMeshComponent>(buf);
	XMFLOAT3 min , max;
	min = max = { 0.0f,0.0f,0.0f };
	CStaticMeshComponent& skyDomeMesh = dynamic_cast<CStaticMeshComponent&>(*buf);

	for(auto& mesh : skyDomeMesh.GetModel().GetMeshes())
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

	min.x *= (skyDomeMesh.Transform.Scale.x / 2.0f);
	min.y *= (skyDomeMesh.Transform.Scale.y / 2.0f);
	min.z *= (skyDomeMesh.Transform.Scale.z / 2.0f);
	max.x *= (skyDomeMesh.Transform.Scale.x / 2.0f);
	max.y *= (skyDomeMesh.Transform.Scale.y / 2.0f);
	max.z *= (skyDomeMesh.Transform.Scale.z / 2.0f);

	new CActorGenerator(*this , [&] { return new CAttachObject(*this); } , min , max , 15.0f);

	fighter.GetComponent<CCameraComponent>(buf);
	RequestSetCamera(*dynamic_cast<CCameraComponent*>(buf));
}

void CMainGameLevel::Tick()
{

}