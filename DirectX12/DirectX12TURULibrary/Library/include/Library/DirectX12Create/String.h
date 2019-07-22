#pragma once

#include <string>


	/// <summary>
	/// stringをwstringへ変換します
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
inline std::wstring StringtoWString(const std::string& name) {
	std::wstring newname(name.begin(), name.end());
	return newname;
}