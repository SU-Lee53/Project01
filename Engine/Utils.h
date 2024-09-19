#pragma once

class Utils
{
public:
	static bool StartsWith(string str, string comp);
	static bool StartsWith(wstring str, wstring comp);

	static void Replace(OUT string& str, string comp, string rep);
	static void Replace(OUT wstring& str, wstring comp, wstring rep);

	static wstring ToWString(string value);
	static string ToString(wstring value);

	static string FileToBuf(ifstream& is);

	static void MakeQuadGeometry(OUT shared_ptr<class VAO>& vao);
	static void MakeCubeGeometry(OUT shared_ptr<class VAO>& vao);

	glm::mat4 GetMatrixWithoutTranslate(glm::mat4 m);

};

