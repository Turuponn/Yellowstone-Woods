#pragma once

#include <string>


	/// <summary>
	/// string‚ðwstring‚Ö•ÏŠ·‚µ‚Ü‚·
	/// </summary>
	/// <param name="name"></param>
	/// <returns>[out]</returns>
inline std::wstring StringtoWString(const std::string& name) {
	std::wstring newname(name.begin(), name.end());
	return newname;
}