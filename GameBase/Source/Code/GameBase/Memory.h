#pragma once

void* operator new (size_t size);
void operator delete(void* p);

extern size_t g_AllocatedMemory;