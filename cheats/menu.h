#pragma once
#include "../includes.hpp"

class c_menu : public singleton<c_menu> {
public:
	void draw( bool is_open );
	void menu_setup(ImGuiStyle &style);
	void SkinChanger();
	void LegitTab();
	void DrawMiscTab();
	void DrawVisualsTab();
	float dpi_scale = 1.f;

	ImFont* futura;
	ImFont* futura_large;
	ImFont* futura_small;

	ImFont* gotham;

	ImFont* ico_menu;
	ImFont* ico_bottom;

	float public_alpha;
	IDirect3DDevice9* device;
	float color_buffer[4] = { 1.f, 1.f, 1.f, 1.f };
private:
	struct {
		ImVec2 WindowPadding;
		float  WindowRounding;
		ImVec2 WindowMinSize;
		float  ChildRounding;
		float  PopupRounding;
		ImVec2 FramePadding;
		float  FrameRounding;
		ImVec2 ItemSpacing;
		ImVec2 ItemInnerSpacing;
		ImVec2 TouchExtraPadding;
		float  IndentSpacing;
		float  ColumnsMinSpacing;
		float  ScrollbarSize;
		float  ScrollbarRounding;
		float  GrabMinSize;
		float  GrabRounding;
		float  TabRounding;
		float  TabMinWidthForUnselectedCloseButton;
		ImVec2 DisplayWindowPadding;
		ImVec2 DisplaySafeAreaPadding;
		float  MouseCursorScale;
	} styles;

	bool update_dpi = false;
	bool update_scripts = false;
	void dpi_resize(float scale_factor, ImGuiStyle &style);

	int active_tab_index;
	ImGuiStyle style;
	int width = 850, height = 560;
	float child_height;

	float preview_alpha = 1.f;

	int active_tab;

	int rage_section;
	int legit_section;
	int visuals_section;
	int players_section;
	int misc_section;
	int settings_section;

	// we need to use 'int child' to seperate content in 2 childs
	void draw_ragebot(int child);
	void draw_tabs_ragebot();

	void draw_legit(int child);
	 
	void draw_visuals(int child);
	void draw_tabs_visuals();
	int current_profile = -1;

	void draw_players(int child);
	void draw_tabs_players();

	void draw_misc(int child);
	void draw_tabs_misc();

	void draw_settings(int child);

	void draw_lua(int child);
	void draw_radar(int child);
	void draw_player_list(int child);


	void DrawRageTab();

	std::string preview = crypt_str("None");
};
