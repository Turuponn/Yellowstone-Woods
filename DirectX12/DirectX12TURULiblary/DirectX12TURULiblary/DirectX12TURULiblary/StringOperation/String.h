#pragma once

#include <string>


	/// <summary>
	/// string��wstring�֕ϊ����܂�
	/// </summary>
	/// <param name="name"></param>
	/// <returns>[out]</returns>
inline std::wstring StringtoWString(const std::string& name) {
	std::wstring newname(name.begin(), name.end());
	return newname;
}