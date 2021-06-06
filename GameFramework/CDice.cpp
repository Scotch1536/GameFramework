#include "CDice.h"
#include "CStaticMeshComponent.h"

CDice::CDice(CLevel& owner):CActor(owner)
{
	CStaticMeshComponent* staticMesh = new CStaticMeshComponent(*this);
	staticMesh->SetModel("assets/dice/PlayerBox.x" , "assets/dice/");
}