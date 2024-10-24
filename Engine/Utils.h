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

	//static void MakeCubeGeometry(shared_ptr<Geometry<VertexType>> geometry);

	static bool ExportMatrix(ofstream& os, Matrix m);


public:
	// DEBUG IMGUI UTILS
	static FORCEINLINE void ShowMatrix(const Matrix& m)
	{
		float rows_height = ImGui::GetTextLineHeightWithSpacing();

		ImGui::BeginTable("table_nested1", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable);
		ImGui::TableSetupColumn("X");
		ImGui::TableSetupColumn("Y");
		ImGui::TableSetupColumn("Z");
		ImGui::TableSetupColumn("W");
		ImGui::TableHeadersRow();

		ImGui::TableNextRow(ImGuiTableRowFlags_None, rows_height);
		ImGui::TableNextColumn();
		ImGui::Text("%.3f", m._11);
		ImGui::TableNextColumn();
		ImGui::Text("%.3f", m._12);
		ImGui::TableNextColumn();
		ImGui::Text("%.3f", m._13);
		ImGui::TableNextColumn();
		ImGui::Text("%.3f", m._14);

		ImGui::TableNextRow(ImGuiTableRowFlags_None, rows_height);
		ImGui::TableNextColumn();
		ImGui::Text("%.3f", m._21);
		ImGui::TableNextColumn();
		ImGui::Text("%.3f", m._22);
		ImGui::TableNextColumn();
		ImGui::Text("%.3f", m._23);
		ImGui::TableNextColumn();
		ImGui::Text("%.3f", m._24);

		ImGui::TableNextRow(ImGuiTableRowFlags_None, rows_height);
		ImGui::TableNextColumn();
		ImGui::Text("%.3f", m._31);
		ImGui::TableNextColumn();
		ImGui::Text("%.3f", m._32);
		ImGui::TableNextColumn();
		ImGui::Text("%.3f", m._33);
		ImGui::TableNextColumn();
		ImGui::Text("%.3f", m._34);

		ImGui::TableNextRow(ImGuiTableRowFlags_None, rows_height);
		ImGui::TableNextColumn();
		ImGui::Text("%.3f", m._41);
		ImGui::TableNextColumn();
		ImGui::Text("%.3f", m._42);
		ImGui::TableNextColumn();
		ImGui::Text("%.3f", m._43);
		ImGui::TableNextColumn();
		ImGui::Text("%.3f", m._44);

		ImGui::EndTable();
	}
};

