#pragma once

struct RTTI
{
	bool operator == (const RTTI& other) const
	{
		return this == &other;
	}
};

struct RTTIObject
{
	virtual const RTTI& GetRTTI() const = 0;
};

#define DEFINE_RTTI \
	static RTTI s_RTTI; \
	virtual const RTTI& GetRTTI() const override;

#define IMPLEMENT_RTTI(Classname) \
	RTTI Classname::s_RTTI; \
	const RTTI& Classname::GetRTTI() const \
	{ \
		return s_RTTI; \
	} \
	