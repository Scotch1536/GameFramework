#include "CTextureData.h"
#include "../ExternalCode/CDirectxGraphics.h"
#include "Shader.h"

bool CTextureData::Load(std::string filePath)
{
	ID3D11Device* device = CDirectXGraphics::GetInstance()->GetDXDevice();
	ID3D11DeviceContext* devicecontext = CDirectXGraphics::GetInstance()->GetImmediateContext();

	bool sts = CreateSRVfromFile(filePath, device, devicecontext, &mResource, &mSRV);
	if (!sts)
	{
		MessageBox(nullptr, "CreateSRVfromfile ÉGÉâÅ[", "error!!", MB_OK);
		return false;
	}
	return true;
}

CTextureData::~CTextureData()
{

}