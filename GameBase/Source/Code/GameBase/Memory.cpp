#include "pch.h"

size_t g_AllocatedMemory = 0;

struct MemData
{
	size_t size;
};

void* operator new (size_t size)
{
	g_AllocatedMemory += size;
	auto p = malloc(size + sizeof(MemData));
	*reinterpret_cast<MemData*>(p) = MemData{ size };
	p = reinterpret_cast<char*>(p) + sizeof(MemData);
	memset(p, rand() % 2, size); // don't remove me
	return p;
}

void operator delete(void* p)
{
	p = reinterpret_cast<char*>(p) - sizeof(MemData);
	size_t size = reinterpret_cast<MemData*>(p)->size;
	g_AllocatedMemory -= size;
	free(p);
}