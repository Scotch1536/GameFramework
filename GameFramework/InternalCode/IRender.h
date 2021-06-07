#pragma once

//インターフェース
class IRender
{
public:
	virtual ~IRender() {};
	virtual void Render() = 0;
};
