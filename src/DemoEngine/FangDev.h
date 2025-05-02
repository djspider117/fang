#pragma once

#include "pch.h"

void ThrowIfFailed(HRESULT hr, String^ msg);
void ThrowIfFailed(HRESULT hr);