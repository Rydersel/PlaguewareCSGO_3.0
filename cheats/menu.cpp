// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <ShlObj_core.h>
#include <unordered_map>
#include "menu.h"
#include "../ImGui/code_editor.h"
#include "../constchars.h"
#include "../cheats/misc/logs.h"
#include "MenuControls.h"



#include <WinInet.h>
#include < urlmon.h >
#pragma comment(lib, "urlmon.lib")




std::string FindURl(std::string paintName)
{
	std::ifstream inFile;
	inFile.open(".\\csgo\\scripts\\items\\items_game_cdn.txt");
	std::string line;
	//int founds = 0;
	unsigned int curLine = 0;
	std::string search = paintName.append("=");
	//string weapon = "aug";
	while (getline(inFile, line)) {
		curLine++;
		if (line.find(search, 0) != std::string::npos)
		{
			return line.substr(line.find(search)).erase(0, search.length());
		}

	}
	return "";
}
static IDirect3DTexture9* some_texture_test;
void DownloadBytes(const char* const szUrl)
{
	char sysdir[MAX_PATH] = { 0 };
	char Path[MAX_PATH] = { 0 };
	GetWindowsDirectory(sysdir, MAX_PATH);
	sprintf(Path, "C:\\test\\image.png", sysdir);
	URLDownloadToFile(NULL, szUrl, Path, 0, NULL);
}


std::string fDownloadBytes(const char* const szUrl)
{
	HINTERNET hOpen = NULL;
	HINTERNET hFile = NULL;
	char* lpBuffer = NULL;
	DWORD dwBytesRead = 0;
	//Pointer to dynamic buffer.
	char* data = 0;
	//Dynamic data size.
	DWORD dataSize = 0;

	hOpen = InternetOpenA("Plague", NULL, NULL, NULL, NULL);
	if (!hOpen) return (char*)"";

	hFile = InternetOpenUrlA(hOpen, szUrl, NULL, NULL, INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE, NULL);

	if (!hFile) {
		InternetCloseHandle(hOpen);
		return (char*)"";
	}

	std::string output;
	do {
		char buffer[2000];
		InternetReadFile(hFile, (LPVOID)buffer, _countof(buffer), &dwBytesRead);
		output.append(buffer, dwBytesRead);
	} while (dwBytesRead);

	InternetCloseHandle(hFile);
	InternetCloseHandle(hOpen);

	return output;
}


static std::string old_link;
void UpdatePic(IDirect3DDevice9* thisptr, std::string link)
{
	if (old_link == link)
		return;
	std::string imData = fDownloadBytes(link.c_str());
	D3DXCreateTextureFromFileInMemoryEx(thisptr
		, imData.data(), imData.length(),
		300, 300, D3DUSAGE_DYNAMIC, 0, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &some_texture_test);

	old_link = link;
}






static const char* zweaponnames(const short id)
{
	switch (id)
	{
	case WEAPON_DEAGLE:
		return "deagle";
	case WEAPON_ELITE:
		return "elite";
	case WEAPON_FIVESEVEN:
		return "fiveseven";
	case WEAPON_GLOCK:
		return "glock";
	case WEAPON_AK47:
		return "ak47";
	case WEAPON_AUG:
		return "aug";
	case WEAPON_AWP:
		return "awp";
	case WEAPON_FAMAS:
		return "famas";
	case WEAPON_G3SG1:
		return "g3sg1";
	case WEAPON_GALILAR:
		return "galilar";
	case WEAPON_M249:
		return "m249";
	case WEAPON_M4A1_SILENCER:
		return "m4a1_silencer";
	case WEAPON_M4A1:
		return "m4a1";
	case WEAPON_MAC10:
		return "mac10";
	case WEAPON_P90:
		return "p90";
	case WEAPON_UMP45:
		return "ump45";
	case WEAPON_XM1014:
		return "xm1014";
	case WEAPON_BIZON:
		return "bizon";
	case WEAPON_MAG7:
		return "mag7";
	case WEAPON_NEGEV:
		return "negev";
	case WEAPON_SAWEDOFF:
		return "sawedoff";
	case WEAPON_TEC9:
		return "tec9";
	case WEAPON_HKP2000:
		return "hkp2000";
	case WEAPON_MP5SD:
		return "mp5sd";
	case WEAPON_MP7:
		return "mp7";
	case WEAPON_MP9:
		return "mp9";
	case WEAPON_NOVA:
		return "nova";
	case WEAPON_P250:
		return "p250";
	case WEAPON_SCAR20:
		return "scar20";
	case WEAPON_SG553:
		return "sg556";
	case WEAPON_SSG08:
		return "ssg08";
	case WEAPON_USP_SILENCER:
		return "usp_silencer";
	case WEAPON_CZ75A:
		return "cz75a";
	case WEAPON_REVOLVER:
		return "revolver";
	case WEAPON_KNIFE:
		return "knife";
	case WEAPON_KNIFE_T:
		return "knife_t";
	case WEAPON_KNIFE_M9_BAYONET:
		return "knife_m9_bayonet";
	case WEAPON_KNIFE_BAYONET:
		return "bayonet";
	case WEAPON_KNIFE_FLIP:
		return "knife_flip";
	case WEAPON_KNIFE_GUT:
		return "knife_gut";
	case WEAPON_KNIFE_KARAMBIT:
		return "knife_karambit";
	case WEAPON_KNIFE_TACTICAL:
		return "knife_tactical";
	case WEAPON_KNIFE_FALCHION:
		return "knife_falchion";
	case WEAPON_KNIFE_SURVIVAL_BOWIE:
		return "knife_survival_bowie";
	case WEAPON_KNIFE_BUTTERFLY:
		return "knife_butterfly";
	case WEAPON_KNIFE_PUSH:
		return "knife_push";
	case WEAPON_KNIFE_URSUS:
		return "knife_ursus";
	case WEAPON_KNIFE_GYPSY_JACKKNIFE:
		return "knife_gypsy_jackknife";
	case WEAPON_KNIFE_STILETTO:
		return "knife_stiletto";
	case WEAPON_KNIFE_WIDOWMAKER:
		return "knife_widowmaker";
	case WEAPON_KNIFE_SKELETON:
		return "knife_skeleton";
	case WEAPON_KNIFE_OUTDOOR:
		return "knife_outdoor";
	case WEAPON_KNIFE_CANIS:
		return "knife_canis";
	case WEAPON_KNIFE_CORD:
		return "knife_cord";
	case WEAPON_KNIFE_CSS:
		return "knife_css";
	case GLOVE_STUDDED_BLOODHOUND:
		return "studded_bloodhound_gloves";
	case GLOVE_T_SIDE:
		return "t_gloves";
	case GLOVE_CT_SIDE:
		return "ct_gloves";
	case GLOVE_SPORTY:
		return "sporty_gloves";
	case GLOVE_SLICK:
		return "slick_gloves";
	case GLOVE_LEATHER_WRAP:
		return "leather_handwraps";
	case GLOVE_MOTORCYCLE:
		return "motorcycle_gloves";
	case GLOVE_SPECIALIST:
		return "specialist_gloves";
	case GLOVE_HYDRA:
		return "studded_hydra_gloves";
	default:
		return "";
	}
}

#include "../../inventory/inventorychanger.h"
#include "../../protobuffs/Protobuffs.h"
#include "../../inventory/items.h"

#include "../../fake-case-opening/menu_part.h"

#include "../../skinchanger/skins.h"




#define ALPHA (ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaBar| ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Float)
#define NOALPHA (ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Float)

std::vector <std::string> files;
std::vector <std::string> scripts;
std::string editing_script;

bool myBool = false;
auto selected_script = 0;
auto loaded_editing_script = false;

static auto menu_setupped = false;
static auto should_update = true;
static const char* items[]{ "Knife", "Gloves", "AK47", "AUG", "AWP", "CZ75-Auto", "Desert Eagle", "Dual Barretas", "Famas", "Five-Seven", "G3SG1", "Galil", "Glock","M249","M4A1-S","M4A4","Mac-10","Mag-7", "MP5-SD", "MP7", "MP9", "Negev", "Nova", "P2000", "P250", "P90", "PP-Bizon", "Revolver", "Sawed Off", "Scar-20", "SSG-08",  "SG-553", "Tec-9", "UMP-45", "USP-S", "XM-104"};
static int selectedItem = 0;
IDirect3DTexture9* all_skins[36];

std::string get_wep(int id, int custom_index = -1, bool knife = true)
{
	if (custom_index > -1)
	{
		if (knife)
		{
			switch (custom_index)
			{
			case 0: return crypt_str("weapon_knife");
			case 1: return crypt_str("weapon_bayonet");
			case 2: return crypt_str("weapon_knife_css");
			case 3: return crypt_str("weapon_knife_skeleton");
			case 4: return crypt_str("weapon_knife_outdoor");
			case 5: return crypt_str("weapon_knife_cord");
			case 6: return crypt_str("weapon_knife_canis");
			case 7: return crypt_str("weapon_knife_flip");
			case 8: return crypt_str("weapon_knife_gut");
			case 9: return crypt_str("weapon_knife_karambit");
			case 10: return crypt_str("weapon_knife_m9_bayonet");
			case 11: return crypt_str("weapon_knife_tactical");
			case 12: return crypt_str("weapon_knife_falchion");
			case 13: return crypt_str("weapon_knife_survival_bowie");
			case 14: return crypt_str("weapon_knife_butterfly");
			case 15: return crypt_str("weapon_knife_push");
			case 16: return crypt_str("weapon_knife_ursus");
			case 17: return crypt_str("weapon_knife_gypsy_jackknife");
			case 18: return crypt_str("weapon_knife_stiletto");
			case 19: return crypt_str("weapon_knife_widowmaker");
			}
		}
		else
		{
			switch (custom_index)
			{
			case 0: return crypt_str("ct_gloves"); //-V1037
			case 1: return crypt_str("studded_bloodhound_gloves");
			case 2: return crypt_str("t_gloves");
			case 3: return crypt_str("ct_gloves");
			case 4: return crypt_str("sporty_gloves");
			case 5: return crypt_str("slick_gloves");
			case 6: return crypt_str("leather_handwraps");
			case 7: return crypt_str("motorcycle_gloves");
			case 8: return crypt_str("specialist_gloves");
			case 9: return crypt_str("studded_hydra_gloves");
			}
		}
	}
	else
	{
		switch (id)
		{
		case 0: return crypt_str("knife");
		case 1: return crypt_str("gloves");
		case 2: return crypt_str("weapon_ak47");
		case 3: return crypt_str("weapon_aug");
		case 4: return crypt_str("weapon_awp");
		case 5: return crypt_str("weapon_cz75a");
		case 6: return crypt_str("weapon_deagle");
		case 7: return crypt_str("weapon_elite");
		case 8: return crypt_str("weapon_famas");
		case 9: return crypt_str("weapon_fiveseven");
		case 10: return crypt_str("weapon_g3sg1");
		case 11: return crypt_str("weapon_galilar");
		case 12: return crypt_str("weapon_glock");
		case 13: return crypt_str("weapon_m249");
		case 14: return crypt_str("weapon_m4a1_silencer");
		case 15: return crypt_str("weapon_m4a1");
		case 16: return crypt_str("weapon_mac10");
		case 17: return crypt_str("weapon_mag7");
		case 18: return crypt_str("weapon_mp5sd");
		case 19: return crypt_str("weapon_mp7");
		case 20: return crypt_str("weapon_mp9");
		case 21: return crypt_str("weapon_negev");
		case 22: return crypt_str("weapon_nova");
		case 23: return crypt_str("weapon_hkp2000");
		case 24: return crypt_str("weapon_p250");
		case 25: return crypt_str("weapon_p90");
		case 26: return crypt_str("weapon_bizon");
		case 27: return crypt_str("weapon_revolver");
		case 28: return crypt_str("weapon_sawedoff");
		case 29: return crypt_str("weapon_scar20");
		case 30: return crypt_str("weapon_ssg08");
		case 31: return crypt_str("weapon_sg556");
		case 32: return crypt_str("weapon_tec9");
		case 33: return crypt_str("weapon_ump45");
		case 34: return crypt_str("weapon_usp_silencer");
		case 35: return crypt_str("weapon_xm1014");
		default: return crypt_str("unknown");
		}
	}
}

IDirect3DTexture9* get_skin_preview(const char* weapon_name, const std::string& skin_name, IDirect3DDevice9* device)
{
	IDirect3DTexture9* skin_image = nullptr;
	std::string vpk_path;

	if (strcmp(weapon_name, crypt_str("unknown")) && strcmp(weapon_name, crypt_str("knife")) && strcmp(weapon_name, crypt_str("gloves"))) //-V526
	{
		if (skin_name.empty() || skin_name == crypt_str("default"))
			vpk_path = crypt_str("resource/flash/econ/weapons/base_weapons/") + std::string(weapon_name) + crypt_str(".png");
		else
			vpk_path = crypt_str("resource/flash/econ/default_generated/") + std::string(weapon_name) + crypt_str("_") + std::string(skin_name) + crypt_str("_light_large.png");
	}
	else
	{
		if (!strcmp(weapon_name, crypt_str("knife")))
			vpk_path = crypt_str("resource/flash/econ/weapons/base_weapons/weapon_knife.png");
		else if (!strcmp(weapon_name, crypt_str("gloves")))
			vpk_path = crypt_str("resource/flash/econ/weapons/base_weapons/ct_gloves.png");
		else if (!strcmp(weapon_name, crypt_str("unknown")))
			vpk_path = crypt_str("resource/flash/econ/weapons/base_weapons/weapon_snowball.png");

	}
	const auto handle = m_basefilesys()->Open(vpk_path.c_str(), crypt_str("r"), crypt_str("GAME"));
	if (handle)
	{
		int file_len = m_basefilesys()->Size(handle);
		char* image = new char[file_len]; //-V121

		m_basefilesys()->Read(image, file_len, handle);
		m_basefilesys()->Close(handle);

		D3DXCreateTextureFromFileInMemory(device, image, file_len, &skin_image);
		delete[] image;
	}

	if (!skin_image)
	{
		std::string vpk_path;

		if (strstr(weapon_name, crypt_str("bloodhound")) != NULL || strstr(weapon_name, crypt_str("hydra")) != NULL)
			vpk_path = crypt_str("resource/flash/econ/weapons/base_weapons/ct_gloves.png");
		else
			vpk_path = crypt_str("resource/flash/econ/weapons/base_weapons/") + std::string(weapon_name) + crypt_str(".png");

		const auto handle = m_basefilesys()->Open(vpk_path.c_str(), crypt_str("r"), crypt_str("GAME"));

		if (handle)
		{
			int file_len = m_basefilesys()->Size(handle);
			char* image = new char[file_len]; //-V121

			m_basefilesys()->Read(image, file_len, handle);
			m_basefilesys()->Close(handle);

			D3DXCreateTextureFromFileInMemory(device, image, file_len, &skin_image);
			delete[] image;
		}
	}

	return skin_image;
}



// setup some styles and colors, window size and bg alpha
// dpi setup
void c_menu::menu_setup(ImGuiStyle& style) //-V688
{
	ImGui::StyleColorsClassic(); // colors setup
	ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_Once); // window pos setup
	ImGui::SetNextWindowBgAlpha(min(style.Alpha, 0.94f)); // window bg alpha setup

	styles.WindowPadding = style.WindowPadding;
	styles.WindowRounding = style.WindowRounding;
	styles.WindowMinSize = style.WindowMinSize;
	styles.ChildRounding = style.ChildRounding;
	styles.PopupRounding = style.PopupRounding;
	styles.FramePadding = style.FramePadding;
	styles.FrameRounding = style.FrameRounding;
	styles.ItemSpacing = style.ItemSpacing;
	styles.ItemInnerSpacing = style.ItemInnerSpacing;
	styles.TouchExtraPadding = style.TouchExtraPadding;
	styles.IndentSpacing = style.IndentSpacing;
	styles.ColumnsMinSpacing = style.ColumnsMinSpacing;
	styles.ScrollbarSize = style.ScrollbarSize;
	styles.ScrollbarRounding = style.ScrollbarRounding;
	styles.GrabMinSize = style.GrabMinSize;
	styles.GrabRounding = style.GrabRounding;
	styles.TabRounding = style.TabRounding;
	styles.TabMinWidthForUnselectedCloseButton = style.TabMinWidthForUnselectedCloseButton;
	styles.DisplayWindowPadding = style.DisplayWindowPadding;
	styles.DisplaySafeAreaPadding = style.DisplaySafeAreaPadding;
	styles.MouseCursorScale = style.MouseCursorScale;

	// setup skins preview
	for (auto i = 0; i < g_cfg.skins.skinChanger.size(); i++)
		if (!all_skins[i])
			all_skins[i] = get_skin_preview(get_wep(i, (i == 0 || i == 1) ? g_cfg.skins.skinChanger.at(i).definition_override_vector_index : -1, i == 0).c_str(), g_cfg.skins.skinChanger.at(i).skin_name, device); //-V810

	menu_setupped = true; 
}

// resize current style sizes
void c_menu::dpi_resize(float scale_factor, ImGuiStyle& style) //-V688
{
	style.WindowPadding = (styles.WindowPadding * scale_factor);
	style.WindowRounding = (styles.WindowRounding * scale_factor);
	style.WindowMinSize = (styles.WindowMinSize * scale_factor);
	style.ChildRounding = (styles.ChildRounding * scale_factor);
	style.PopupRounding = (styles.PopupRounding * scale_factor);
	style.FramePadding = (styles.FramePadding * scale_factor);
	style.FrameRounding = (styles.FrameRounding * scale_factor);
	style.ItemSpacing = (styles.ItemSpacing * scale_factor);
	style.ItemInnerSpacing = (styles.ItemInnerSpacing * scale_factor);
	style.TouchExtraPadding = (styles.TouchExtraPadding * scale_factor);
	style.IndentSpacing = (styles.IndentSpacing * scale_factor);
	style.ColumnsMinSpacing = (styles.ColumnsMinSpacing * scale_factor);
	style.ScrollbarSize = (styles.ScrollbarSize * scale_factor);
	style.ScrollbarRounding = (styles.ScrollbarRounding * scale_factor);
	style.GrabMinSize = (styles.GrabMinSize * scale_factor);
	style.GrabRounding = (styles.GrabRounding * scale_factor);
	style.TabRounding = (styles.TabRounding * scale_factor);
	if (styles.TabMinWidthForUnselectedCloseButton != FLT_MAX) //-V550
		style.TabMinWidthForUnselectedCloseButton = (styles.TabMinWidthForUnselectedCloseButton * scale_factor);
	style.DisplayWindowPadding = (styles.DisplayWindowPadding * scale_factor);
	style.DisplaySafeAreaPadding = (styles.DisplaySafeAreaPadding * scale_factor);
	style.MouseCursorScale = (styles.MouseCursorScale * scale_factor);
}


std::string get_config_dir()
{
	std::string folder;
	static TCHAR path[MAX_PATH];

	if (SUCCEEDED(SHGetFolderPath(NULL, 0x001a, NULL, NULL, path)))
		folder = std::string(path) + crypt_str("\\Plagueware\\Configs\\");

	CreateDirectory(folder.c_str(), NULL);
	return folder;
}

void load_config()
{
	if (cfg_manager->files.empty())
		return;

	cfg_manager->load(cfg_manager->files.at(g_cfg.selected_config), false);
	c_lua::get().unload_all_scripts();

	for (auto& script : g_cfg.scripts.scripts)
		c_lua::get().load_script(c_lua::get().get_script_id(script));

	scripts = c_lua::get().scripts;

	if (selected_script >= scripts.size())
		selected_script = scripts.size() - 1; //-V103

	for (auto& current : scripts)
	{
		if (current.size() >= 5 && current.at(current.size() - 1) == 'c')
			current.erase(current.size() - 5, 5);
		else if (current.size() >= 4)
			current.erase(current.size() - 4, 4);
	}

	for (auto i = 0; i < g_cfg.skins.skinChanger.size(); ++i)
		all_skins[i] = nullptr;

	g_cfg.scripts.scripts.clear();

	cfg_manager->load(cfg_manager->files.at(g_cfg.selected_config), true);
	cfg_manager->config_files();

	eventlogs::get().add(crypt_str("Loaded ") + files.at(g_cfg.selected_config) + crypt_str(" config"), false);
}

void save_config()
{
	if (cfg_manager->files.empty())
		return;

	g_cfg.scripts.scripts.clear();

	for (auto i = 0; i < c_lua::get().scripts.size(); ++i)
	{
		auto script = c_lua::get().scripts.at(i);

		if (c_lua::get().loaded.at(i))
			g_cfg.scripts.scripts.emplace_back(script);
	}

	cfg_manager->save(cfg_manager->files.at(g_cfg.selected_config));
	cfg_manager->config_files();

	eventlogs::get().add(crypt_str("Saved ") + files.at(g_cfg.selected_config) + crypt_str(" config"), false);
}

void remove_config()
{
	if (cfg_manager->files.empty())
		return;

	eventlogs::get().add(crypt_str("Removed ") + files.at(g_cfg.selected_config) + crypt_str(" config"), false);

	cfg_manager->remove(cfg_manager->files.at(g_cfg.selected_config));
	cfg_manager->config_files();

	files = cfg_manager->files;

	if (g_cfg.selected_config >= files.size())
		g_cfg.selected_config = files.size() - 1; //-V103

	for (auto& current : files)
		if (current.size() > 2)
			current.erase(current.size() - 3, 3);
}

void add_config()
{
	auto empty = true;

	for (auto current : g_cfg.new_config_name)
	{
		if (current != ' ')
		{
			empty = false;
			break;
		}
	}

	if (empty)
		g_cfg.new_config_name = crypt_str("config");

	eventlogs::get().add(crypt_str("Added ") + g_cfg.new_config_name + crypt_str(" config"), false);

	if (g_cfg.new_config_name.find(crypt_str(".pw")) == std::string::npos)
		g_cfg.new_config_name += crypt_str(".pw");

	cfg_manager->save(g_cfg.new_config_name);
	cfg_manager->config_files();

	g_cfg.selected_config = cfg_manager->files.size() - 1; //-V103
	files = cfg_manager->files;

	for (auto& current : files)
		if (current.size() > 2)
			current.erase(current.size() - 3, 3);
}

__forceinline void padding(float x, float y)
{
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + x * c_menu::get().dpi_scale);
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + y * c_menu::get().dpi_scale);
}


// title of content child
void child_title(const char* label)
{
	ImGui::PushFont(c_menu::get().futura_large);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 1.f));

	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (12 * c_menu::get().dpi_scale));
	ImGui::Text(label);
	ImGui::PopStyleColor();
	ImGui::PopFont();
}

void draw_combo(const char* name, int& variable, const char* labels[], int count)
{
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 6 * c_menu::get().dpi_scale);
	ImGui::Text(name);
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 5 * c_menu::get().dpi_scale);
	padding(10, 0);
	ImGui::Combo(std::string(crypt_str("##COMBO__") + std::string(name)).c_str(), &variable, labels, count);
}

void draw_combo(const char* name, int& variable, bool (*items_getter)(void*, int, const char**), void* data, int count)
{
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 6 * c_menu::get().dpi_scale);
	ImGui::Text(name);
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 5 * c_menu::get().dpi_scale);
	padding(10, 0);
	ImGui::Combo(std::string(crypt_str("##COMBO__") + std::string(name)).c_str(), &variable, items_getter, data, count);
}

void draw_multicombo(std::string name, std::vector<int>& variable, const char* labels[], int count, std::string& preview)
{
	padding(10, 0);
	ImGui::Text((crypt_str(" ") + name).c_str());
	padding(10, 0);
	auto hashname = crypt_str("##") + name; // we dont want to render name of combo

	for (auto i = 0, j = 0; i < count; i++)
	{
		if (variable[i])
		{
			if (j)
				preview += crypt_str(", ") + (std::string)labels[i];
			else
				preview = labels[i];

			j++;
		}
	}

	if (ImGui::BeginCombo(hashname.c_str(), preview.c_str())) // draw start
	{
		ImGui::Spacing();
		ImGui::BeginGroup();
		{

			for (auto i = 0; i < count; i++)
				ImGui::Selectable(labels[i], (bool*)&variable[i], ImGuiSelectableFlags_DontClosePopups); padding(25, 0);

		}
		ImGui::EndGroup();
		ImGui::Spacing();

		ImGui::EndCombo();
	}

	preview = crypt_str("None"); // reset preview to use later
}

bool LabelClick(const char* label, bool* v, const char* unique_id)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;


	//weapon config setup
	char Buf[64];
	_snprintf(Buf, 62, crypt_str("%s"), label);

	char getid[128];
	sprintf_s(getid, 128, crypt_str("%s%s"), label, unique_id);


	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(getid);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

	const ImRect check_bb(window->DC.CursorPos, ImVec2(label_size.y + style.FramePadding.y * 2 + window->DC.CursorPos.x, window->DC.CursorPos.y + label_size.y + style.FramePadding.y * 2));
	ImGui::ItemSize(check_bb, style.FramePadding.y);

	ImRect total_bb = check_bb;

	if (label_size.x > 0)
	{
		ImGui::SameLine(0, style.ItemInnerSpacing.x);
		const ImRect text_bb(ImVec2(window->DC.CursorPos.x, window->DC.CursorPos.y + style.FramePadding.y), ImVec2(window->DC.CursorPos.x + label_size.x, window->DC.CursorPos.y + style.FramePadding.y + label_size.y));

		ImGui::ItemSize(ImVec2(text_bb.GetWidth(), check_bb.GetHeight()), style.FramePadding.y);
		total_bb = ImRect(ImMin(check_bb.Min, text_bb.Min), ImMax(check_bb.Max, text_bb.Max));
	}

	if (!ImGui::ItemAdd(total_bb, id))
		return false;

	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(total_bb, id, &hovered, &held);
	if (pressed)
		*v = !(*v);

	if (*v)
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(69 / 255.f, 8 / 255.f, 160 / 255.f, 1.f));
	if (label_size.x > 0.0f)
		ImGui::RenderText(ImVec2(check_bb.GetTL().x + 12, check_bb.GetTL().y), Buf);
	if (*v)
		ImGui::PopStyleColor();

	return pressed;

}




void draw_keybind(const char* label, key_bind* key_bind, const char* unique_id)
{
	// reset bind if we re pressing esc
	if (key_bind->key == KEY_ESCAPE)
		key_bind->key = KEY_NONE;

	auto clicked = false;
	auto text = (std::string)m_inputsys()->ButtonCodeToString(key_bind->key);

	if (key_bind->key <= KEY_NONE || key_bind->key >= KEY_MAX)
		text = crypt_str("...");

	// if we clicked on keybind
	if (hooks::input_shouldListen && hooks::input_receivedKeyval == &key_bind->key)
	{
		clicked = true;
		text = crypt_str(". .");
	}

	auto textsize = ImGui::CalcTextSize(text.c_str()).x + 8 * c_menu::get().dpi_scale;
	auto labelsize = ImGui::CalcTextSize(label);

	ImGui::Text(label);
	ImGui::SameLine();

	ImGui::SetCursorPosX(ImGui::GetWindowSize().x - (ImGui::GetWindowSize().x - ImGui::CalcItemWidth()) - max(50 * c_menu::get().dpi_scale, textsize));
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 3 * c_menu::get().dpi_scale);

	if (ImGui::KeybindButton(text.c_str(), unique_id, ImVec2(max(50 * c_menu::get().dpi_scale, textsize), 23 * c_menu::get().dpi_scale), clicked))
		clicked = true;


	if (clicked)
	{
		hooks::input_shouldListen = true;
		hooks::input_receivedKeyval = &key_bind->key;
	}

	static auto hold = false, toggle = false;

	switch (key_bind->mode)
	{
	case HOLD:
		hold = true;
		toggle = false;
		break;
	case TOGGLE:
		toggle = true;
		hold = false;
		break;
	}

	if (ImGui::BeginPopup(unique_id))
	{
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 6 * c_menu::get().dpi_scale);
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ((ImGui::GetCurrentWindow()->Size.x / 2) - (ImGui::CalcTextSize(crypt_str("Hold")).x / 2)));
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 11);

		if (LabelClick(crypt_str("Hold"), &hold, unique_id))
		{
			if (hold)
			{
				toggle = false;
				key_bind->mode = HOLD;
			}
			else if (toggle)
			{
				hold = false;
				key_bind->mode = TOGGLE;
			}
			else
			{
				toggle = false;
				key_bind->mode = HOLD;
			}

			ImGui::CloseCurrentPopup();
		}

		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ((ImGui::GetCurrentWindow()->Size.x / 2) - (ImGui::CalcTextSize(crypt_str("Toggle")).x / 2)));
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 11);
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 9 * c_menu::get().dpi_scale);

		if (LabelClick(crypt_str("Toggle"), &toggle, unique_id))
		{
			if (toggle)
			{
				hold = false;
				key_bind->mode = TOGGLE;
			}
			else if (hold)
			{
				toggle = false;
				key_bind->mode = HOLD;
			}
			else
			{
				hold = false;
				key_bind->mode = TOGGLE;
			}

			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
}

void draw_semitabs(const char* labels[], int count, int& tab, ImGuiStyle& style)
{
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() - (2 * c_menu::get().dpi_scale));

	// center of main child
	float offset = 343 * c_menu::get().dpi_scale;

	// text size padding + frame padding
	for (int i = 0; i < count; i++)
		offset -= (ImGui::CalcTextSize(labels[i]).x) / 2 + style.FramePadding.x * 2;

	// set new padding
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + offset);
	ImGui::BeginGroup();

	for (int i = 0; i < count; i++)
	{
		// switch current tab
		if (ImGui::ContentTab(labels[i], tab == i))
			tab = i;

		// continue drawing on same line 
		if (i + 1 != count)
		{
			ImGui::SameLine();
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + style.ItemSpacing.x);
		}
	}

	ImGui::EndGroup();
}

__forceinline void tab_start()
{
	ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + (20 * c_menu::get().dpi_scale), ImGui::GetCursorPosY() + (5 * c_menu::get().dpi_scale)));
}

__forceinline void tab_end()
{
	ImGui::PopStyleVar();
	ImGui::SetWindowFontScale(c_menu::get().dpi_scale);
}

void lua_edit(std::string window_name)
{
	std::string file_path;

	auto get_dir = [&]() -> void
	{
		static TCHAR path[MAX_PATH];

		if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, NULL, path)))
			file_path = std::string(path) + crypt_str("\\Plagueware\\Scripts\\");

		CreateDirectory(file_path.c_str(), NULL);
		file_path += window_name + crypt_str(".lua");
	};

	get_dir();
	const char* child_name = (window_name + window_name).c_str();

	ImGui::SetNextWindowSize(ImVec2(700, 600), ImGuiCond_Once);
	ImGui::Begin(window_name.c_str(), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
	ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarSize, 5.f);

	static TextEditor editor;

	if (!loaded_editing_script)
	{
		static auto lang = TextEditor::LanguageDefinition::Lua();

		editor.SetLanguageDefinition(lang);
		editor.SetReadOnly(false);

		std::ifstream t(file_path);

		if (t.good()) 
		{
			std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
			editor.SetText(str); // setup script content
		}

		loaded_editing_script = true;
	}

	// dpi scale for font
	// we dont need to resize it for full scale
	ImGui::SetWindowFontScale(1.f + ((c_menu::get().dpi_scale - 1.0) * 0.5f));

	// new size depending on dpi scale
	ImGui::SetWindowSize(ImVec2(ImFloor(800 * (1.f + ((c_menu::get().dpi_scale - 1.0) * 0.5f))), ImFloor(700 * (1.f + ((c_menu::get().dpi_scale - 1.0) * 0.5f)))));
	editor.Render(child_name, ImGui::GetWindowSize() - ImVec2(0, 66 * (1.f + ((c_menu::get().dpi_scale - 1.0) * 0.5f))));

	// seperate code with buttons
	ImGui::Separator();

	// set cursor pos to right edge of window
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetWindowSize().x - (16.f * (1.f + ((c_menu::get().dpi_scale - 1.0) * 0.5f))) - (250.f * (1.f + ((c_menu::get().dpi_scale - 1.0) * 0.5f))));
	ImGui::BeginGroup();

	if (ImGui::CustomButton(crypt_str("Save"), (crypt_str("Save") + window_name).c_str(), ImVec2(125 * (1.f + ((c_menu::get().dpi_scale - 1.0) * 0.5f)), 0), true, c_menu::get().ico_bottom, crypt_str("S")))
	{
		std::ofstream out;

		out.open(file_path);
		out << editor.GetText() << std::endl;
		out.close();
	}

	ImGui::SameLine();

	if (ImGui::CustomButton(crypt_str("Close"), (crypt_str("Close") + window_name).c_str(), ImVec2(125 * (1.f + ((c_menu::get().dpi_scale - 1.0) * 0.5f)), 0)))
	{
		g_ctx.globals.focused_on_input = false;
		loaded_editing_script = false;
		editing_script.clear();
	}

	ImGui::EndGroup();

	ImGui::PopStyleVar();
	ImGui::End();
}










void c_menu::SkinChanger()
{
	static bool active_animation = false;
	static bool preview_reverse = false;
	static float switch_alpha = 1.f;
	static int next_id = -1;
	if (active_animation)
	{
		if (preview_reverse)
		{
			if (switch_alpha == 1.f) //-V550
			{
				preview_reverse = false;
				active_animation = false;
			}

			switch_alpha = math::clamp(switch_alpha + (4.f * ImGui::GetIO().DeltaTime), 0.01f, 1.f);
		}
		else
		{
			if (switch_alpha == 0.01f) //-V550
			{
				preview_reverse = true;
			}

			switch_alpha = math::clamp(switch_alpha - (4.f * ImGui::GetIO().DeltaTime), 0.01f, 1.f);
		}
	}
	else
		switch_alpha = math::clamp(switch_alpha + (4.f * ImGui::GetIO().DeltaTime), 0.0f, 1.f);
	static int pages = 0;
	padding(8, 8);
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.11f, 0.10f, 0.11f, 0.7f));
	ImGui::BeginChild(crypt_str("##SKINCHANGER__TAB"), ImVec2(600, 60));
	if (ImGui::BlssButton("Skin Changer", pages == 4 ? true : false, ImVec2(150, 60))) pages = 4; ImGui::SameLine(0, 0);
	if (ImGui::BlssButton("Inventory", pages == 0 ? true : false, ImVec2(150, 60))) pages = 0; ImGui::SameLine(0, 0);
	if (ImGui::BlssButton("Profile", pages == 1 ? true : false, ImVec2(150, 60))) pages = 1; ImGui::SameLine(0, 0);
	if (ImGui::BlssButton("Case Opener", pages == 2 ? true : false, ImVec2(150, 60))) pages = 2; ImGui::SameLine(0, 0);
	ImGui::EndChild();

	{
		static int lazy_so_yes;

		const char* w[] = { "Inventory Changer", "Profile Changer", "Medals Changer", "Case Opener" };
		if (pages == 0)
		{
			static int index = 0;
			static wskin weaponSkin;

			ImGui::BeginGroup();
			ImGui::BeginChild("Inventory", ImVec2(680, 420));
			padding(0, 25);
			{
				padding(10, 0);
				ImGui::Checkbox("Enable inventory", &g_cfg.inventory.activate_inventory); padding(10, 0);
				ImGui::Checkbox("Enable autorarity", &g_cfg.inventory.autorarity);

				if (weaponSkin.wId == WEAPON_NONE)
					weaponSkin.wId = WEAPON_DEAGLE;
				padding(10, 0);
				if (ImGui::BeginCombo("Weapon", k_inventory_names.at(weaponSkin.wId), ImGuiComboFlags_HeightLargest))
				{
					for (const auto& weapon : k_inventory_names)
					{
						if (ImGui::Selectable(weapon.second, weaponSkin.wId == weapon.first, 0, ImVec2()))
						{
							weaponSkin.wId = weapon.first;
							weaponSkin.paintKit = 0;
							//skinImage = nullptr;
						}
					}
					ImGui::EndCombo();
				}



				auto weaponName = zweaponnames(weaponSkin.wId);
				padding(10, 0);
				ImGui::Text("Skin");
				padding(10, 0);
				if (ImGui::BeginCombo("##Paint Kit", weaponSkin.paintKit > 0 ? _inv.inventory.skinInfo[weaponSkin.paintKit].name.c_str() : "", ImGuiComboFlags_HeightLargest))
				{
					int lastID = ImGui::GetItemID();

					for (auto skin : _inv.inventory.skinInfo)
					{
						for (auto names : skin.second.weaponName)
						{
							if (weaponName != names)
								continue;

							ImGui::PushID(lastID++);

							if (ImGui::Selectable(skin.second.name.c_str(), skin.first == weaponSkin.paintKit, 0, ImVec2()))
								weaponSkin.paintKit = skin.first;

							ImGui::PopID();
						}
					}
					ImGui::EndCombo();
				}
				const char* ww[] = { "common","uncommon","rare","mythical","legendary","ancient","immortal" };
				padding(10, 0);
				ImGui::SliderFloat("Wear", &weaponSkin.wear, 0.f, 1.f);
				padding(10, 0);
				ImGui::SliderInt("Seed", &weaponSkin.seed, 0, 100);

				if (!g_cfg.inventory.autorarity)
					draw_combo(crypt_str("Rarity Color"), weaponSkin.quality, ww, ARRAYSIZE(ww));


				static char skinname[64] = "\0";
				padding(10, 0);
				ImGui::InputInt("Stattrak", &weaponSkin.stattrak);
				padding(10, 0);
				ImGui::InputText(("##skinname"), skinname, sizeof(skinname));


				static int stickerkit[4] = { 0,0,0,0 };


				if (weaponSkin.wId <= 100 && weaponSkin.wId != 42 && weaponSkin.wId != 59)
				{
					padding(10, 0);
					if (ImGui::BeginCombo("Sticker 1", g_Stickers[stickerkit[0]].name.c_str(), ImGuiComboFlags_HeightLargest))
					{
						int lastID = ImGui::GetItemID();

						for (auto skin : fosso)
						{
							{
								ImGui::PushID(lastID++);
								if (ImGui::Selectable(skin.second.name.c_str(), skin.second.paintKit == stickerkit[0], 0, ImVec2()))
									stickerkit[0] = skin.second.paintKit;
								ImGui::PopID();
							}
						}
						ImGui::EndCombo();
					}
					padding(10, 0);
					if (ImGui::BeginCombo("Sticker 2", g_Stickers[stickerkit[1]].name.c_str(), ImGuiComboFlags_HeightLargest))
					{
						int lastID = ImGui::GetItemID();

						for (auto skin : fosso)
						{
							{
								ImGui::PushID(lastID++);
								if (ImGui::Selectable(skin.second.name.c_str(), skin.second.paintKit == stickerkit[1], 0, ImVec2()))
									stickerkit[1] = skin.second.paintKit;
								ImGui::PopID();
							}
						}
						ImGui::EndCombo();
					}

				


				}

				ImGui::BeginChild("Skin preview", ImVec2(680, 200)); {


					if (weaponSkin.wId > 0 && weaponSkin.wId <= 100)
					{
						std::string name(zweaponnames(weaponSkin.wId));
						std::string smallfix = "weapon_" + name + "_" + _inv.inventory.skinInfo[weaponSkin.paintKit].cdnName;
						auto url = FindURl(smallfix);
						{
							UpdatePic(c_menu::get().device, url);
							if (some_texture_test)
							{
								ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPos().x + 5, ImGui::GetCursorPos().y - 20));
								ImGui::Image(some_texture_test, ImVec2(250, 200));
							}

						}
					}
					else
					{
						std::string name(zweaponnames(weaponSkin.wId));
						std::string smallfix = name + "_" + _inv.inventory.skinInfo[weaponSkin.paintKit].cdnName;
						auto url = FindURl(smallfix);
						{
							UpdatePic(c_menu::get().device, url);
							if (some_texture_test) {
								//ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 250);
								ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPos().x + 5, ImGui::GetCursorPos().y - 20));
								ImGui::Image(some_texture_test, ImVec2(250, 200));
							}

						}
					}

				}
				padding(10, 0);
				if (ImGui::Button("Add", ImVec2(ImGui::GetWindowSize().x - 39, 26)))
				{
					weaponSkin.sicker[0] = stickerkit[0];
					weaponSkin.sicker[1] = stickerkit[1];
					weaponSkin.sicker[2] = stickerkit[2];
					weaponSkin.sicker[3] = stickerkit[3];

					std::string str(skinname);
					if (str.length() > 0)
						weaponSkin.name = str;
					g_InventorySkins.insert({ g_csgo.fRandomInt(20000, 200000), weaponSkin });
					_inv.inventory.itemCount = g_InventorySkins.size();
					stickerkit[0] = 0;
					stickerkit[1] = 0;
					stickerkit[2] = 0;
					stickerkit[3] = 0;
					//index = 0;
				}
				padding(10, 0);
				if (ImGui::Button("Apply", ImVec2(ImGui::GetWindowSize().x - 39, 26)))
				{
					m_engine()->ExecuteClientCmd("econ_clear_inventory_images");
					write.SendClientHello();
					write.SendMatchmakingClient2GCHello();
				}
				if (g_InventorySkins.size() > 0)
				{
					padding(10, 0);
					if (ImGui::Button("Delete selected items", ImVec2(ImGui::GetWindowSize().x - 39, 26)))
					{
						// if (g_InventorySkins[index] != NULL)
						g_InventorySkins.erase(index);
						_inv.inventory.itemCount = g_InventorySkins.size();
					}
				}
			}
			ImGui::EndChild();

			ImGui::EndGroup();

			ImGui::SameLine;
			ImGui::BeginChild("Inventory list", ImVec2(680, 100)); {
				ImGui::Text("Inventory List:"); padding(25, 0);

				int i = 0;
				for (auto weapon : g_InventorySkins) {

					std::string weap = zweaponnames(weapon.second.wId);

					std::stringstream whatever;
					whatever << ++i;
					if (ImGui::Selectable(std::string("[" + whatever.str() + " " + weap + "] - [" + (weapon.second.paintKit > 0 ? _inv.inventory.skinInfo[weapon.second.paintKit].name.c_str() : "") + "]").c_str(), index == weapon.first)) {
						index = weapon.first;
					}

				}
				i = 0;
			}
			ImGui::EndChild();



		}

		if (pages == 1)
		{
			ImGui::BeginChild("Profile changer", ImVec2(600, 460));
			{
				ImGui::Checkbox("Enable profile changer", &g_cfg.profilechanger.enable);




				ImGui::InputInt("Friend", &g_cfg.profilechanger.profile_friend);
				ImGui::InputInt("Leader", &g_cfg.profilechanger.profile_leader);
				ImGui::InputInt("Teach", &g_cfg.profilechanger.profile_teach);
				const char* y[] = {
"Off",
"Silver 1",
"Silver 2",
"Silver 3",
"Silver 4",
"Silver elite",
"Silver elite master",
"Gold nova 1",
"Gold nova 2",
"Gold nova 3",
"Gold nova master",
"Master guardian 1",
"Master guardian 2",
"Master guardian elite",
"Distinguished master guardian",
"Legendary eagle",
"Legendary eagle master",
"Supreme master first class",
"The global elite"
				};


				draw_combo(crypt_str("Rank"), g_cfg.profilechanger.profile_rank, y, ARRAYSIZE(y));
				ImGui::InputInt("Wins", &g_cfg.profilechanger.profile_rank_wins);
				ImGui::SliderInt("Level", &g_cfg.profilechanger.profile_lvl, 0, 40);
				ImGui::SliderInt("Level xp", &g_cfg.profilechanger.profile_xp, 0, 5000);

				if (ImGui::Button("Apply", ImVec2(ImGui::GetWindowSize().x - 39, 26)))
				{
					write.SendClientHello();
					write.SendMatchmakingClient2GCHello();
				}


				draw_combo(crypt_str("Rank wing"), g_cfg.profilechanger.r_rank, y, ARRAYSIZE(y));

				ImGui::InputInt("Wins wing", &g_cfg.profilechanger.r_wins);

				if (ImGui::Button("Apply", ImVec2(ImGui::GetWindowSize().x - 39, 26)))
					write.SendClientGcRankUpdate1();


				const char* yy[] = {
"Off",
"Lab rat 1",
"Lab rat 2",
"Sprinting Hare 1",
"Sprinting Hare 2",
"Wild Scout 1",
"Wild Scout Elite",
"Hunter Fox 1",
"Hunter Fox 2",
"Hunter Fox 3",
"Hunter Fox Elite",
"Timber Wolf",
"Ember Wolf",
"Wildfire Wolf",
"The Howling Alpha"
				};
				draw_combo(crypt_str("Rank zone"), g_cfg.profilechanger.t_rank, yy, ARRAYSIZE(yy));



				ImGui::InputInt("Wins zone", &g_cfg.profilechanger.t_wins);

				if (ImGui::Button("Apply", ImVec2(ImGui::GetWindowSize().x - 39, 26)))
					write.SendClientGcRankUpdate2();

				static int paintKit = 874;

				ImGui::Text("Medals:");

				if (ImGui::BeginCombo("##PaintKit_yea", fosso[paintKit].name.c_str(), ImGuiComboFlags_HeightLargest))
				{
					int lastID = ImGui::GetItemID();

					for (auto skin : fosso)
					{
						{
							ImGui::PushID(lastID++);
							if (ImGui::Selectable(skin.second.name.c_str(), skin.second.paintKit == paintKit, 0, ImVec2()))
								paintKit = skin.second.paintKit;
							ImGui::PopID();
						}
					}
					ImGui::EndCombo();
				}
				if (ImGui::Button("Add medal", ImVec2(ImGui::GetWindowSize().x - 39, 26)))
					g_MedalSkins[g_csgo.fRandomInt(200001, 1000000)] = { paintKit , 0 };
				static int wId = 0;


				if (ImGui::Button("Apply medals", ImVec2(ImGui::GetWindowSize().x - 39, 26)))
				{
					paintKit;
					m_engine()->ExecuteClientCmd("econ_clear_inventory_images");
					write.SendClientHello();
					write.SendMatchmakingClient2GCHello();
				}


				if (g_MedalSkins.size() > 0)
				{
					if (ImGui::Button("Delete selected element", ImVec2(ImGui::GetWindowSize().x - 39, 26)))
						g_MedalSkins.erase(wId);

					ImGui::BeginChild("Medals list", ImVec2(328, 460)); {

						int i = 0;
						for (auto weapon : g_MedalSkins) {

							std::stringstream whatever;
							whatever << ++i;
							if (ImGui::Selectable(std::string(whatever.str() + " " + fosso[weapon.second.paintKit].name).c_str(), wId == weapon.first)) {
								wId = weapon.first;
							}
						}
						i = 0;
					}
					ImGui::EndChild();
				}
			}
		}
	}



		//skinchanger 
		if (pages == 2)
			padding(10, 30);
			run_changer();
		static bool drugs = false;
		if (pages == 4)
		{
			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 1.f);
			tab_start();
			ImGui::BeginChild(crypt_str("##SKINCHANGER__CHILD"), ImVec2(600, 500));
			{
				// we need to count our items in 1 line
				auto same_line_counter = 0;
				if (current_profile == -1)
					current_profile = 0;
				// if we didnt choose any weapon
				if (current_profile == -1)
				{
					for (auto i = 0; i < g_cfg.skins.skinChanger.size(); i++)
					{
						// do we need update our preview for some reasons?
						if (!all_skins[i])
						{
							g_cfg.skins.skinChanger.at(i).update();
							all_skins[i] = get_skin_preview(get_wep(i, (i == 0 || i == 1) ? g_cfg.skins.skinChanger.at(i).definition_override_vector_index : -1, i == 0).c_str(), g_cfg.skins.skinChanger.at(i).skin_name, device); //-V810
						}

						// we licked on weapon
						if (ImGui::ImageButton(all_skins[i], ImVec2(107 * dpi_scale, 76 * dpi_scale)))
						{
							next_id = i;
							active_animation = true;
						}

						// if our animation step is half from all - switch profile
						if (active_animation && preview_reverse)
						{
							ImGui::SetScrollY(0);
							current_profile = next_id;
						}

						if (same_line_counter < 2) { // continue push same-line
							ImGui::SameLine();
							same_line_counter++;
						}
						else { // we have maximum elements in 1 line
							same_line_counter = 0;
						}
					}
				}
				else
				{
					// update skin preview bool
					static bool need_update[36];

					// we pressed crypt_str("Save & Close") button
					static bool leave;
					//Select Weapon



					// update if we have nullptr texture or if we push force update
					if (!all_skins[current_profile] || need_update[current_profile])
					{
						all_skins[current_profile] = get_skin_preview(get_wep(current_profile, (current_profile == 0 || current_profile == 1) ? g_cfg.skins.skinChanger.at(current_profile).definition_override_vector_index : -1, current_profile == 0).c_str(), g_cfg.skins.skinChanger.at(current_profile).skin_name, device); //-V810
						need_update[current_profile] = false;
					}

					// get settings for selected weapon
					auto& selected_entry = g_cfg.skins.skinChanger[current_profile];
					selected_entry.itemIdIndex = current_profile;

					ImGui::BeginGroup();
					ImGui::PushItemWidth(260 * dpi_scale);

					// search input later
					static char search_skins[64] = "\0";
					static auto item_index = selected_entry.paint_kit_vector_index;

					if (!current_profile)
					{
						ImGui::Text(crypt_str("Knife"));
						ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 5 * c_menu::get().dpi_scale);
						if (ImGui::Combo(crypt_str("##Knife_combo"), &selected_entry.definition_override_vector_index, [](void* data, int idx, const char** out_text)
							{
								*out_text = game_data::knife_names[idx].name;
								return true;
							}, nullptr, IM_ARRAYSIZE(game_data::knife_names)))
							need_update[current_profile] = true; // push force update
					}
					else if (current_profile == 1)
					{
						ImGui::Text(crypt_str("Gloves"));
						ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 5 * c_menu::get().dpi_scale);
						if (ImGui::Combo(crypt_str("##Glove_combo"), &selected_entry.definition_override_vector_index, [](void* data, int idx, const char** out_text)
							{
								*out_text = game_data::glove_names[idx].name;
								return true;
							}, nullptr, IM_ARRAYSIZE(game_data::glove_names)))
						{
							item_index = 0; // set new generated paintkits element to 0;
							need_update[current_profile] = true; // push force update
						}
					}
					else
						selected_entry.definition_override_vector_index = 0;

					if (current_profile != 1)
					{
						ImGui::Text(crypt_str("Search"));
						ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.f);

						if (ImGui::InputText(crypt_str("##search"), search_skins, sizeof(search_skins)))
							item_index = -1;

						ImGui::PopStyleVar();
					}

					auto main_kits = current_profile == 1 ? SkinChanger::gloveKits : SkinChanger::skinKits;
					auto display_index = 0;

					SkinChanger::displayKits = main_kits;

					// we dont need custom gloves
					if (current_profile == 1)
					{
						for (auto i = 0; i < main_kits.size(); i++)
						{
							auto main_name = main_kits.at(i).name;

							for (auto i = 0; i < main_name.size(); i++)
								if (iswalpha((main_name.at(i))))
									main_name.at(i) = towlower(main_name.at(i));

							char search_name[64];

							if (!strcmp(game_data::glove_names[selected_entry.definition_override_vector_index].name, crypt_str("Hydra")))
								strcpy_s(search_name, sizeof(search_name), crypt_str("Bloodhound"));
							else
								strcpy_s(search_name, sizeof(search_name), game_data::glove_names[selected_entry.definition_override_vector_index].name);

							for (auto i = 0; i < sizeof(search_name); i++)
								if (iswalpha(search_name[i]))
									search_name[i] = towlower(search_name[i]);

							if (main_name.find(search_name) != std::string::npos)
							{
								SkinChanger::displayKits.at(display_index) = main_kits.at(i);
								display_index++;
							}
						}

						SkinChanger::displayKits.erase(SkinChanger::displayKits.begin() + display_index, SkinChanger::displayKits.end());
					}
					else
					{
						if (strcmp(search_skins, crypt_str(""))) //-V526
						{
							for (auto i = 0; i < main_kits.size(); i++)
							{
								auto main_name = main_kits.at(i).name;

								for (auto i = 0; i < main_name.size(); i++)
									if (iswalpha(main_name.at(i)))
										main_name.at(i) = towlower(main_name.at(i));

								char search_name[64];
								strcpy_s(search_name, sizeof(search_name), search_skins);

								for (auto i = 0; i < sizeof(search_name); i++)
									if (iswalpha(search_name[i]))
										search_name[i] = towlower(search_name[i]);

								if (main_name.find(search_name) != std::string::npos)
								{
									SkinChanger::displayKits.at(display_index) = main_kits.at(i);
									display_index++;
								}
							}

							SkinChanger::displayKits.erase(SkinChanger::displayKits.begin() + display_index, SkinChanger::displayKits.end());
						}
						else
							item_index = selected_entry.paint_kit_vector_index;
					}

					ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.f);
					if (!SkinChanger::displayKits.empty())
					{
						if (ImGui::ListBox(crypt_str("##PAINTKITS"), &item_index, [](void* data, int idx, const char** out_text) //-V107
							{
								while (SkinChanger::displayKits.at(idx).name.find(crypt_str("С‘")) != std::string::npos) //-V807
									SkinChanger::displayKits.at(idx).name.replace(SkinChanger::displayKits.at(idx).name.find(crypt_str("С‘")), 2, crypt_str("Рµ"));

								*out_text = SkinChanger::displayKits.at(idx).name.c_str();
								return true;
							}, nullptr, SkinChanger::displayKits.size(), SkinChanger::displayKits.size() > 9 ? 9 : SkinChanger::displayKits.size()) || !all_skins[current_profile])
						{
							SkinChanger::scheduleHudUpdate();
							need_update[current_profile] = true;

							auto i = 0;

							while (i < main_kits.size())
							{
								if (main_kits.at(i).id == SkinChanger::displayKits.at(item_index).id)
								{
									selected_entry.paint_kit_vector_index = i;
									break;
								}

								i++;
							}

						}
					}
					ImGui::PopStyleVar();

					if (ImGui::InputInt(crypt_str("Seed"), &selected_entry.seed, 1, 100))
						SkinChanger::scheduleHudUpdate();

					if (ImGui::InputInt(crypt_str("StatTrak"), &selected_entry.stat_trak, 1, 15))
						SkinChanger::scheduleHudUpdate();

					if (ImGui::SliderFloat(crypt_str("Wear"), &selected_entry.wear, 0.0f, 1.0f))
						drugs = true;
					else if (drugs)
					{
						SkinChanger::scheduleHudUpdate();
						drugs = false;
					}

					ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 6 * c_menu::get().dpi_scale);
					ImGui::Text(crypt_str("Quality"));
					ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 5 * c_menu::get().dpi_scale);
					if (ImGui::Combo(crypt_str("##Quality_combo"), &selected_entry.entity_quality_vector_index, [](void* data, int idx, const char** out_text)
						{
							*out_text = game_data::quality_names[idx].name;
							return true;
						}, nullptr, IM_ARRAYSIZE(game_data::quality_names)))
						SkinChanger::scheduleHudUpdate();

						if (current_profile != 1)
						{
							if (!g_cfg.skins.custom_name_tag[current_profile].empty())
								strcpy_s(selected_entry.custom_name, sizeof(selected_entry.custom_name), g_cfg.skins.custom_name_tag[current_profile].c_str());

							ImGui::Text(crypt_str("Name Tag"));
							ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.f);

							if (ImGui::InputText(crypt_str("##nametag"), selected_entry.custom_name, sizeof(selected_entry.custom_name)))
							{
								g_cfg.skins.custom_name_tag[current_profile] = selected_entry.custom_name;
								SkinChanger::scheduleHudUpdate();
							}

							ImGui::PopStyleVar();
						}

						ImGui::PopItemWidth();

						ImGui::EndGroup();

						ImGui::SameLine();
						ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 266 * dpi_scale - 200 * dpi_scale);

						ImGui::BeginGroup();
						if (ImGui::ImageButton(all_skins[current_profile], ImVec2(190 * dpi_scale, 155 * dpi_scale)))
						{
							// maybe i will do smth later where, who knows :/
						}
						ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 6 * c_menu::get().dpi_scale);
						ImGui::Text(crypt_str("Gun Selection"));
						ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 5 * c_menu::get().dpi_scale);
						ImGui::Combo(" ", &current_profile, items, IM_ARRAYSIZE(items));
						if (ImGui::Button("<"))
							if (current_profile != 0) {
								current_profile -= 1;
							}
							else {
								current_profile = 35;
							}
						ImGui::SameLine();
						if (ImGui::Button(">"))
							if (current_profile != 35) {
								current_profile++;
							}
							else {
								current_profile = 0;
							}

						ImGui::EndGroup();

						// update element
						selected_entry.update();

						// we need to reset profile in the end to prevent render images with massive's index == -1
						if (leave && (preview_reverse || !active_animation))
						{
							ImGui::SetScrollY(0);
							current_profile = next_id;
							leave = false;
						}

				}
			}
			ImGui::EndChild();
			tab_end();
		
	}
	ImGui::EndChild();
}
















//New Menu Start

                                                                                                                                                                               
/*
                                                                                                                                                                                    
                                                                                                                                                                                    
NNNNNNNN        NNNNNNNN                                                                     MMMMMMMM               MMMMMMMM                                                        
N:::::::N       N::::::N                                                                     M:::::::M             M:::::::M                                                        
N::::::::N      N::::::N                                                                     M::::::::M           M::::::::M                                                        
N:::::::::N     N::::::N                                                                     M:::::::::M         M:::::::::M                                                        
N::::::::::N    N::::::N    eeeeeeeeeeee  wwwwwww           wwwww           wwwwwww          M::::::::::M       M::::::::::M    eeeeeeeeeeee    nnnn  nnnnnnnn    uuuuuu    uuuuuu  
N:::::::::::N   N::::::N  ee::::::::::::ee w:::::w         w:::::w         w:::::w           M:::::::::::M     M:::::::::::M  ee::::::::::::ee  n:::nn::::::::nn  u::::u    u::::u  
N:::::::N::::N  N::::::N e::::::eeeee:::::eew:::::w       w:::::::w       w:::::w            M:::::::M::::M   M::::M:::::::M e::::::eeeee:::::een::::::::::::::nn u::::u    u::::u  
N::::::N N::::N N::::::Ne::::::e     e:::::e w:::::w     w:::::::::w     w:::::w             M::::::M M::::M M::::M M::::::Me::::::e     e:::::enn:::::::::::::::nu::::u    u::::u  
N::::::N  N::::N:::::::Ne:::::::eeeee::::::e  w:::::w   w:::::w:::::w   w:::::w              M::::::M  M::::M::::M  M::::::Me:::::::eeeee::::::e  n:::::nnnn:::::nu::::u    u::::u  
N::::::N   N:::::::::::Ne:::::::::::::::::e    w:::::w w:::::w w:::::w w:::::w               M::::::M   M:::::::M   M::::::Me:::::::::::::::::e   n::::n    n::::nu::::u    u::::u  
N::::::N    N::::::::::Ne::::::eeeeeeeeeee      w:::::w:::::w   w:::::w:::::w                M::::::M    M:::::M    M::::::Me::::::eeeeeeeeeee    n::::n    n::::nu::::u    u::::u  
N::::::N     N:::::::::Ne:::::::e                w:::::::::w     w:::::::::w                 M::::::M     MMMMM     M::::::Me:::::::e             n::::n    n::::nu:::::uuuu:::::u  
N::::::N      N::::::::Ne::::::::e                w:::::::w       w:::::::w                  M::::::M               M::::::Me::::::::e            n::::n    n::::nu:::::::::::::::uu
N::::::N       N:::::::N e::::::::eeeeeeee         w:::::w         w:::::w                   M::::::M               M::::::M e::::::::eeeeeeee    n::::n    n::::n u:::::::::::::::u
N::::::N        N::::::N  ee:::::::::::::e          w:::w           w:::w                    M::::::M               M::::::M  ee:::::::::::::e    n::::n    n::::n  uu::::::::uu:::u
NNNNNNNN         NNNNNNN    eeeeeeeeeeeeee           www             www                     MMMMMMMM               MMMMMMMM    eeeeeeeeeeeeee    nnnnnn    nnnnnn    uuuuuuuu  uuuu
                                                                                                                                                                                    
                                                                                                                                                                                    
*/
                                                                                                                                                                                    
                                                                                                                                                                                    
                                                                                                                                                                                    
                                                                                                                                                                               
                                                                                                                                                                               
                                                                                                                                                                               
 






                                                                                                                                                                               
                                                                                                                                                                               
                                                                                                                                                                               











//Rage








/*


RRRRRRRRRRRRRRRRR
R::::::::::::::::R
R::::::RRRRRR:::::R
RR:::::R     R:::::R
  R::::R     R:::::R  aaaaaaaaaaaaa     ggggggggg   ggggg    eeeeeeeeeeee
  R::::R     R:::::R  a::::::::::::a   g:::::::::ggg::::g  ee::::::::::::ee
  R::::RRRRRR:::::R   aaaaaaaaa:::::a g:::::::::::::::::g e::::::eeeee:::::ee
  R:::::::::::::RR             a::::ag::::::ggggg::::::gge::::::e     e:::::e
  R::::RRRRRR:::::R     aaaaaaa:::::ag:::::g     g:::::g e:::::::eeeee::::::e
  R::::R     R:::::R  aa::::::::::::ag:::::g     g:::::g e:::::::::::::::::e
  R::::R     R:::::R a::::aaaa::::::ag:::::g     g:::::g e::::::eeeeeeeeeee
  R::::R     R:::::Ra::::a    a:::::ag::::::g    g:::::g e:::::::e
RR:::::R     R:::::Ra::::a    a:::::ag:::::::ggggg:::::g e::::::::e
R::::::R     R:::::Ra:::::aaaa::::::a g::::::::::::::::g  e::::::::eeeeeeee
R::::::R     R:::::R a::::::::::aa:::a gg::::::::::::::g   ee:::::::::::::e
RRRRRRRR     RRRRRRR  aaaaaaaaaa  aaaa   gggggggg::::::g     eeeeeeeeeeeeee
												 g:::::g
									 gggggg      g:::::g
									 g:::::gg   gg:::::g
									  g::::::ggg:::::::g
									   gg:::::::::::::g
										 ggg::::::ggg
											ggggg

*/





void c_menu::DrawRageTab()
{
	padding(8, 8);
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.11f, 0.10f, 0.11f, 0.7f));
	ImGui::BeginChild("##WeaponsSections", ImVec2(600, 60));
	if (ImGui::BlssButton("Automatics", hooks::rage_weapon == 4 ? true : false, ImVec2(85, 60))) hooks::rage_weapon = 4; ImGui::SameLine(0, 0);
	if (ImGui::BlssButton("Scout", hooks::rage_weapon == 5 ? true : false, ImVec2(85, 60))) hooks::rage_weapon = 5; ImGui::SameLine(0, 0);
	if (ImGui::BlssButton("AWP", hooks::rage_weapon == 6 ? true : false, ImVec2(85, 60))) hooks::rage_weapon = 6; ImGui::SameLine(0, 0);
	if (ImGui::BlssButton("Rifles", hooks::rage_weapon == 3 ? true : false, ImVec2(85, 60))) hooks::rage_weapon = 3; ImGui::SameLine(0, 0);
	if (ImGui::BlssButton("Heavy pistol", hooks::rage_weapon == 0 ? true : false, ImVec2(85, 60))) hooks::rage_weapon = 0; ImGui::SameLine(0, 0);
	if (ImGui::BlssButton("Pistols", hooks::rage_weapon == 1 ? true : false, ImVec2(85, 60))) hooks::rage_weapon = 1; ImGui::SameLine(0, 0);
	if (ImGui::BlssButton("Anti-Aim", hooks::rage_weapon == 8 ? true : false, ImVec2(88, 60))) hooks::rage_weapon = 8; ImGui::SameLine(0, 0);

	ImGui::EndChild();
	ImGui::PopStyleColor();
	auto pages = 0;
	switch (hooks::rage_weapon)
	{
	default:
		ImGui::Columns(2, NULL, false);
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.11f, 0.10f, 0.11f, 0.7f));
		ImGui::BeginChild("##RageTab", ImVec2(290, 415));
		//padding(8, 8);
		padding(110, 8);
		ImGui::Text("Rage General");
		padding(8, 2);
		ImGui::Checkbox(crypt_str("Enable Ragebot"), &g_cfg.ragebot.enable); padding(8, 2);
		ImGui::SliderInt(crypt_str("Rage FOV"), &g_cfg.ragebot.field_of_view, 1, 180, false, crypt_str("%d°"));
		ImGui::Checkbox(crypt_str("Silent Aim"), &g_cfg.ragebot.silent_aim); padding(8, 2);
		ImGui::Checkbox(crypt_str("Automatic wall"), &g_cfg.ragebot.autowall);padding(8, 2);
		ImGui::Checkbox(crypt_str("Aimbot With Zeus"), &g_cfg.ragebot.zeus_bot); padding(8, 2);
		ImGui::Checkbox(crypt_str("Aimbot With Knife"), &g_cfg.ragebot.knife_bot); padding(8, 2);
		ImGui::Checkbox(crypt_str("Automatic Shoot"), &g_cfg.ragebot.autoshoot); padding(8, 2);
		ImGui::Checkbox(crypt_str("Automatic Scope"), &g_cfg.ragebot.autoscope); padding(8, 2);
		ImGui::Checkbox(crypt_str("Pitch Desync correction"), &g_cfg.ragebot.pitch_antiaim_correction); padding(8, 2);
		draw_keybind(crypt_str("Auto Peek"), &g_cfg.misc.automatic_peek, crypt_str("##AUTOPEEK__HOTKEY")); padding(8, 2);
		if (g_cfg.ragebot.weapon[hooks::rage_weapon].autostop)
			draw_multicombo(crypt_str("Modifiers"), g_cfg.ragebot.weapon[hooks::rage_weapon].autostop_modifiers, autostop_modifiers, ARRAYSIZE(autostop_modifiers), preview);

		ImGui::Spacing(); padding(8, 2);
		ImGui::Checkbox(crypt_str("Double Tap"), &g_cfg.ragebot.double_tap); padding(8, 2);

		if (g_cfg.ragebot.double_tap)
		{
			ImGui::SameLine();
			draw_keybind(crypt_str(""), &g_cfg.ragebot.double_tap_key, crypt_str("##HOTKEY_DT")); padding(8, 2);
			ImGui::Checkbox(crypt_str("Slow Teleport"), &g_cfg.ragebot.slow_teleport); padding(8, 2);
		}

		ImGui::Checkbox(crypt_str("Hide Shots"), &g_cfg.antiaim.hide_shots); padding(8, 2);

		if (g_cfg.antiaim.hide_shots)
		{
			ImGui::SameLine();
			draw_keybind(crypt_str(""), &g_cfg.antiaim.hide_shots_key, crypt_str("##HOTKEY_HIDESHOTS")); padding(8, 2);
		}
		ImGui::Checkbox(crypt_str("Enable Max Misses"), &g_cfg.ragebot.weapon[hooks::rage_weapon].max_misses); padding(8, 2);

		if (g_cfg.ragebot.weapon[hooks::rage_weapon].max_misses)
		{
			ImGui::SliderInt(crypt_str("Max Misses"), &g_cfg.ragebot.weapon[hooks::rage_weapon].max_misses_amount, 0, 6); padding(8, 2);
		}
		ImGui::PopStyleColor();
		ImGui::EndChild();
		ImGui::NextColumn();
		{
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.11f, 0.10f, 0.11f, 0.7f));
			ImGui::BeginChild("##AccuracyTab", ImVec2(290, 415));
			padding(120, 8);
			ImGui::Text("Accuracy");
			padding(8, 2);
			draw_multicombo(crypt_str("Hitboxes"), g_cfg.ragebot.weapon[hooks::rage_weapon].hitboxes, hitboxes, ARRAYSIZE(hitboxes), preview); padding(8, 2);

			ImGui::Checkbox(crypt_str("Hitchance"), &g_cfg.ragebot.weapon[hooks::rage_weapon].hitchance); padding(8, 2);

			if (g_cfg.ragebot.weapon[hooks::rage_weapon].hitchance){
				ImGui::SliderInt(crypt_str("Hitchance Amount"), &g_cfg.ragebot.weapon[hooks::rage_weapon].hitchance_amount, 0, 100); padding(8, 2);
			}

			ImGui::SliderInt(crypt_str("Minimum Visbile Damage"), &g_cfg.ragebot.weapon[hooks::rage_weapon].minimum_visible_damage, 0, 120, true); padding(8, 2);

            ImGui::SliderInt(crypt_str("Minimum Wall Damage"), &g_cfg.ragebot.weapon[hooks::rage_weapon].minimum_damage, 0, 120, true); padding(8, 2);
			draw_keybind(crypt_str("Damage Override"), &g_cfg.ragebot.weapon[hooks::rage_weapon].damage_override_key, crypt_str("##HOTKEY__DAMAGE_OVERRIDE")); padding(8, 2);

			if (g_cfg.ragebot.weapon[hooks::rage_weapon].damage_override_key.key > KEY_NONE && g_cfg.ragebot.weapon[hooks::rage_weapon].damage_override_key.key < KEY_MAX) {
				ImGui::SliderInt(crypt_str("Minimum Override Damage"), &g_cfg.ragebot.weapon[hooks::rage_weapon].minimum_override_damage, 1, 120, true); padding(8, 2);
			}

			ImGui::Spacing(); padding(8, 2);
			ImGui::Checkbox(crypt_str("Static Point Scale"), &g_cfg.ragebot.weapon[hooks::rage_weapon].static_point_scale); padding(8, 2);

			if (g_cfg.ragebot.weapon[hooks::rage_weapon].static_point_scale)
			{
				ImGui::SliderFloat(crypt_str("Head Scale"), &g_cfg.ragebot.weapon[hooks::rage_weapon].head_scale, 0.0f, 1.0f, g_cfg.ragebot.weapon[hooks::rage_weapon].head_scale ? crypt_str("%.2f") : crypt_str("None")); padding(8, 2);
				ImGui::SliderFloat(crypt_str("Body Scale"), &g_cfg.ragebot.weapon[hooks::rage_weapon].body_scale, 0.0f, 1.0f, g_cfg.ragebot.weapon[hooks::rage_weapon].body_scale ? crypt_str("%.2f") : crypt_str("None")); padding(8, 2);
			}
			ImGui::Checkbox(crypt_str("Prefer Body Aim"), &g_cfg.ragebot.weapon[hooks::rage_weapon].prefer_body_aim); padding(8, 2);

			draw_keybind(crypt_str("Force Body Aim"), &g_cfg.ragebot.body_aim_key, crypt_str("##HOKEY_FORCE_BODY_AIM")); padding(8, 2);

			ImGui::PopStyleColor();
			ImGui::EndChild();
		}
		ImGui::Columns(1);
		break;
	case 8:
		ImGui::Columns(2, NULL, false);
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.11f, 0.10f, 0.11f, 0.7f));
		ImGui::BeginChild("##RageTab", ImVec2(290, 415));
		static auto type = 0;
		padding(95, 8);
		ImGui::Text("Anti-Aim General");
		padding(8, 8);
		ImGui::Checkbox(crypt_str("Enable Anti-Aim"), &g_cfg.antiaim.enable); padding(8, 2);
			draw_combo(crypt_str("Pitch"), g_cfg.antiaim.type[type].pitch, pitch, ARRAYSIZE(pitch));
			padding(8, 2);	
			draw_combo(crypt_str("Movement Type"), type, movement_type, ARRAYSIZE(movement_type));
			padding(8, 2);
			draw_combo(crypt_str("Yaw"), g_cfg.antiaim.type[type].yaw, yaw, ARRAYSIZE(yaw));
			padding(8, 2);
			draw_combo(crypt_str("Base Angle"), g_cfg.antiaim.type[type].base_angle, baseangle, ARRAYSIZE(baseangle));

			if (g_cfg.antiaim.type[type].yaw)
			{
				ImGui::SliderInt(g_cfg.antiaim.type[type].yaw == 1 ? crypt_str("Jitter Range") : crypt_str("Spin Range"), &g_cfg.antiaim.type[type].range, 1, 180); padding(0, 2);

				if (g_cfg.antiaim.type[type].yaw == 2) {
					ImGui::SliderInt(crypt_str("Spin Speed"), &g_cfg.antiaim.type[type].speed, 1, 15); padding(8, 2);
				}
			}

			draw_combo(crypt_str("Desync"), g_cfg.antiaim.type[type].desync, desync, ARRAYSIZE(desync)); padding(8, 2);

			if (g_cfg.antiaim.type[type].desync)
			{
				if (type == ANTIAIM_STAND)
				{
					draw_combo(crypt_str("LBY Type"), g_cfg.antiaim.lby_type, lby_type, ARRAYSIZE(lby_type));
				}

				if (type != ANTIAIM_STAND || !g_cfg.antiaim.lby_type)
				{
					ImGui::SliderInt(crypt_str("Desync Range"), &g_cfg.antiaim.type[type].desync_range, 1, 60); padding(0, 2);
					ImGui::SliderInt(crypt_str("Inverted Desync Range"), &g_cfg.antiaim.type[type].inverted_desync_range, 1, 60); padding(0, 2);
					ImGui::SliderInt(crypt_str("Body Lean"), &g_cfg.antiaim.type[type].body_lean, 0, 100); padding(0, 2);
					ImGui::SliderInt(crypt_str("Inverted Body Lean"), &g_cfg.antiaim.type[type].inverted_body_lean, 0, 100); padding(0, 2);
				}

				if (g_cfg.antiaim.type[type].desync == 1)
				{
					draw_keybind(crypt_str("Invert Desync"), &g_cfg.antiaim.flip_desync, crypt_str("##HOTKEY_INVERT_DESYNC")); padding(8, 2);
				}
			}

			draw_keybind(crypt_str("Manual Back"), &g_cfg.antiaim.manual_back, crypt_str("##HOTKEY_INVERT_BACK")); padding(8, 2);

			draw_keybind(crypt_str("Manual Left"), &g_cfg.antiaim.manual_left, crypt_str("##HOTKEY_INVERT_LEFT")); padding(8, 2);

			draw_keybind(crypt_str("Manual Right"), &g_cfg.antiaim.manual_right, crypt_str("##HOTKEY_INVERT_RIGHT")); padding(8, 2);

			if (g_cfg.antiaim.manual_back.key > KEY_NONE && g_cfg.antiaim.manual_back.key < KEY_MAX || g_cfg.antiaim.manual_left.key > KEY_NONE && g_cfg.antiaim.manual_left.key < KEY_MAX || g_cfg.antiaim.manual_right.key > KEY_NONE && g_cfg.antiaim.manual_right.key < KEY_MAX)
			{
				ImGui::Checkbox(crypt_str("Manuals Indicator"), &g_cfg.antiaim.flip_indicator); padding(8, 2);
				ImGui::SameLine();
				ImGui::ColorEdit(crypt_str("##invc"), &g_cfg.antiaim.flip_indicator_color, ALPHA); padding(8, 2);
			}
			ImGui::EndChild();
			ImGui::PopStyleColor();
			ImGui::NextColumn(); {
				ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.11f, 0.10f, 0.11f, 0.7f));
				ImGui::BeginChild("", ImVec2(290, 415));
				padding(110, 8);
				ImGui::Text("Movement");
				padding(8, 8);
				ImGui::Checkbox(crypt_str("Fast Stop"), &g_cfg.misc.fast_stop); padding(8, 2);
				ImGui::Checkbox(crypt_str("Slide Walk"), &g_cfg.misc.slidewalk); padding(8, 2);
				ImGui::Checkbox(crypt_str("No Duck Cooldown"), &g_cfg.misc.noduck); padding(8, 2);

				if (g_cfg.misc.noduck){
					draw_keybind(crypt_str("Fake Duck"), &g_cfg.misc.fakeduck_key, crypt_str("##FAKEDUCK__HOTKEY")); padding(8, 2); 
				}

				draw_keybind(crypt_str("Slow Walk"), &g_cfg.misc.slowwalk_key, crypt_str("##SLOWWALK__HOTKEY")); padding(8, 2);


				ImGui::Checkbox(crypt_str("Fake Lag"), &g_cfg.antiaim.fakelag); padding(8, 2);
				if (g_cfg.antiaim.fakelag)
				{
					draw_combo(crypt_str("Fake Lag Type"), g_cfg.antiaim.fakelag_type, fakelags, ARRAYSIZE(fakelags)); padding(0, 2);
					ImGui::SliderInt(crypt_str("Limit"), &g_cfg.antiaim.fakelag_amount, 1, 16); padding(8, 2);

					draw_multicombo(crypt_str("Fake Lag Triggers"), g_cfg.antiaim.fakelag_enablers, lagstrigger, ARRAYSIZE(lagstrigger), preview); padding(8, 2);

					auto enabled_fakelag_triggers = false;

					for (auto i = 0; i < ARRAYSIZE(lagstrigger); i++)
						if (g_cfg.antiaim.fakelag_enablers[i])
							enabled_fakelag_triggers = true;

					if (enabled_fakelag_triggers)	{
						ImGui::SliderInt(crypt_str("Triggers Limit"), &g_cfg.antiaim.triggers_fakelag_amount, 1, 16); padding(8, 2);
					}
				}
				ImGui::PopStyleColor();
				ImGui::EndChild();
			}
			ImGui::Columns(1);
			break;
	}
}










/*




LLLLLLLLLLL                                                       iiii          tttt
L:::::::::L                                                      i::::i      ttt:::t
L:::::::::L                                                       iiii       t:::::t
LL:::::::LL                                                                  t:::::t
  L:::::L                   eeeeeeeeeeee       ggggggggg   gggggiiiiiiittttttt:::::ttttttt
  L:::::L                 ee::::::::::::ee    g:::::::::ggg::::gi:::::it:::::::::::::::::t
  L:::::L                e::::::eeeee:::::ee g:::::::::::::::::g i::::it:::::::::::::::::t
  L:::::L               e::::::e     e:::::eg::::::ggggg::::::gg i::::itttttt:::::::tttttt
  L:::::L               e:::::::eeeee::::::eg:::::g     g:::::g  i::::i      t:::::t
  L:::::L               e:::::::::::::::::e g:::::g     g:::::g  i::::i      t:::::t
  L:::::L               e::::::eeeeeeeeeee  g:::::g     g:::::g  i::::i      t:::::t
  L:::::L         LLLLLLe:::::::e           g::::::g    g:::::g  i::::i      t:::::t    tttttt
LL:::::::LLLLLLLLL:::::Le::::::::e          g:::::::ggggg:::::g i::::::i     t::::::tttt:::::t
L::::::::::::::::::::::L e::::::::eeeeeeee   g::::::::::::::::g i::::::i     tt::::::::::::::t
L::::::::::::::::::::::L  ee:::::::::::::e    gg::::::::::::::g i::::::i       tt:::::::::::tt
LLLLLLLLLLLLLLLLLLLLLLLL    eeeeeeeeeeeeee      gggggggg::::::g iiiiiiii         ttttttttttt
														g:::::g
											gggggg      g:::::g
											g:::::gg   gg:::::g
											 g::::::ggg:::::::g
											  gg:::::::::::::g
												ggg::::::ggg
												   gggggg

*/







void c_menu::LegitTab()
{

	padding(8, 8);
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.11f, 0.10f, 0.11f, 0.7f));
	ImGui::BeginChild("##WeaponsSections", ImVec2(600, 60));
	if (ImGui::BlssButton("Deagle", hooks::legit_weapon == 0 ? true : false, ImVec2(100, 60))) hooks::legit_weapon = 0; ImGui::SameLine(0, 0);
	if (ImGui::BlssButton("Pistols", hooks::legit_weapon == 1 ? true : false, ImVec2(100, 60))) hooks::legit_weapon = 1; ImGui::SameLine(0, 0);
	if (ImGui::BlssButton("Rifles", hooks::legit_weapon == 2 ? true : false, ImVec2(100, 60))) hooks::legit_weapon = 2; ImGui::SameLine(0, 0);
	if (ImGui::BlssButton("SMGs", hooks::legit_weapon == 3 ? true : false, ImVec2(100, 60))) hooks::legit_weapon = 3; ImGui::SameLine(0, 0);
	if (ImGui::BlssButton("Snipers", hooks::legit_weapon == 4 ? true : false, ImVec2(100, 60))) hooks::legit_weapon = 4; ImGui::SameLine(0, 0);
	if (ImGui::BlssButton("Heavy", hooks::legit_weapon == 5 ? true : false, ImVec2(100, 60))) hooks::legit_weapon = 5; ImGui::SameLine(0, 0);

	ImGui::EndChild();
	ImGui::PopStyleColor();
	auto pages = 0;
	switch (hooks::legit_weapon)
	{
	default:
		ImGui::Columns(2, NULL, false);
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.11f, 0.10f, 0.11f, 0.7f));
		ImGui::BeginChild("##LegitTab", ImVec2(290, 415));
		padding(100, 8);
		ImGui::Text("Legit General");
		padding(8, 6);
		ImGui::Checkbox(crypt_str("Enable"), &g_cfg.legitbot.enabled);
		ImGui::SameLine();
		draw_keybind(crypt_str(""), &g_cfg.legitbot.key, crypt_str("##HOTKEY_LGBT_KEY")); padding(8, 2);

		if (g_cfg.legitbot.enabled)
			g_cfg.ragebot.enable = false;

		ImGui::Checkbox(crypt_str("Friendly Fire"), &g_cfg.legitbot.friendly_fire);
		padding(8, 2); ImGui::Checkbox(crypt_str("Auto Pistol"), &g_cfg.legitbot.autopistol);

		padding(8, 2); ImGui::Checkbox(crypt_str("Auto Scope"), &g_cfg.legitbot.autoscope); padding(8, 2);

		if (g_cfg.legitbot.autoscope)
			ImGui::Checkbox(crypt_str("Unscope After Shot"), &g_cfg.legitbot.unscope);

	
		ImGui::Checkbox(crypt_str("Shoot While Flashed"), &g_cfg.legitbot.do_if_local_flashed);
		padding(8, 2); ImGui::Checkbox(crypt_str("Shoot While Smoked"), &g_cfg.legitbot.do_if_enemy_in_smoke);
		padding(8, 2); ImGui::Checkbox(crypt_str("Enable While Jumping"), &g_cfg.legitbot.do_if_local_in_air);
		padding(8, 2); ImGui::Checkbox(crypt_str("No No Scope"), &g_cfg.legitbot.sniper_in_zoom_only);

		padding(8, 2); draw_keybind(crypt_str("Automatic Fire Key"), &g_cfg.legitbot.autofire_key, crypt_str("##HOTKEY_AUTOFIRE_LGBT_KEY"));
		padding(8, 2); ImGui::SliderInt(crypt_str("Automatic Fire Delay"), &g_cfg.legitbot.autofire_delay, 0, 12, false, (!g_cfg.legitbot.autofire_delay ? crypt_str("None") : (g_cfg.legitbot.autofire_delay == 1 ? crypt_str("%d tick") : crypt_str("%d ticks"))));

		ImGui::EndChild();
		ImGui::PopStyleColor();
		ImGui::NextColumn(); {
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.11f, 0.10f, 0.11f, 0.7f));
			ImGui::BeginChild("", ImVec2(290, 415));
			padding(120, 8);
			ImGui::Text("Accuracy");
			ImGui::Spacing();
			padding(8, 2);
			const char* hitbox_legit[3] = { crypt_str("Nearest"), crypt_str("Head"), crypt_str("Body") }; padding(8, 2);

			draw_combo(crypt_str("Hitbox"), g_cfg.legitbot.weapon[hooks::legit_weapon].priority, hitbox_legit, ARRAYSIZE(hitbox_legit)); padding(8, 2);

			draw_combo(crypt_str("FOV Type"), g_cfg.legitbot.weapon[hooks::legit_weapon].fov_type, LegitFov, ARRAYSIZE(LegitFov)); padding(8, 2);
			ImGui::SliderFloat(crypt_str("Legitbot FOV"), &g_cfg.legitbot.weapon[hooks::legit_weapon].fov, 0.f, 30.f, crypt_str("%.2f"));

			ImGui::Spacing();

			padding(8, 2); ImGui::SliderFloat(crypt_str("Silent Aim FOV"), &g_cfg.legitbot.weapon[hooks::legit_weapon].silent_fov, 0.f, 30.f, (!g_cfg.legitbot.weapon[hooks::legit_weapon].silent_fov ? crypt_str("None") : crypt_str("%.2f")));

			ImGui::Spacing();

			padding(8, 2);  draw_combo(crypt_str("Smoothing Type"), g_cfg.legitbot.weapon[hooks::legit_weapon].smooth_type, LegitSmooth, ARRAYSIZE(LegitSmooth)); padding(8, 2);
			ImGui::SliderFloat(crypt_str("Smoothing Amount"), &g_cfg.legitbot.weapon[hooks::legit_weapon].smooth, 0.f, 12.f, crypt_str("%.1f")); padding(8, 2);

			ImGui::Spacing();

			padding(8, 2); draw_combo(crypt_str("Recoil Control Type"), g_cfg.legitbot.weapon[hooks::legit_weapon].rcs_type, RCSType, ARRAYSIZE(RCSType));
			padding(8, 2); ImGui::SliderFloat(crypt_str("Recoil Control Amount"), &g_cfg.legitbot.weapon[hooks::legit_weapon].rcs, 0.f, 100.f, crypt_str("%.0f%%"), 1.f); padding(8, 2);

			if (g_cfg.legitbot.weapon[hooks::legit_weapon].rcs > 0)
			{
				
				ImGui::SliderFloat(crypt_str("Recoil Control Smooth"), &g_cfg.legitbot.weapon[hooks::legit_weapon].custom_rcs_smooth, 0.f, 12.f, (!g_cfg.legitbot.weapon[hooks::legit_weapon].custom_rcs_smooth ? crypt_str("None") : crypt_str("%.1f"))); //-V550
				ImGui::SliderFloat(crypt_str("Recoil Control FOV"), &g_cfg.legitbot.weapon[hooks::legit_weapon].custom_rcs_fov, 0.f, 30.f, (!g_cfg.legitbot.weapon[hooks::legit_weapon].custom_rcs_fov ? crypt_str("None") : crypt_str("%.2f"))); //-V550
			}

			ImGui::Spacing();

			padding(8, 2); ImGui::SliderInt(crypt_str("Automatic Wall Damage"), &g_cfg.legitbot.weapon[hooks::legit_weapon].awall_dmg, 0, 100, false, (!g_cfg.legitbot.weapon[hooks::legit_weapon].awall_dmg ? crypt_str("None") : crypt_str("%d")));
			padding(8, 2); ImGui::SliderInt(crypt_str("Automatic Fire Hitchance"), &g_cfg.legitbot.weapon[hooks::legit_weapon].autofire_hitchance, 0, 100, false, (!g_cfg.legitbot.weapon[hooks::legit_weapon].autofire_hitchance ? crypt_str("None") : crypt_str("%d")));
			padding(8, 2); ImGui::SliderFloat(crypt_str("Target Switch Delay"), &g_cfg.legitbot.weapon[hooks::legit_weapon].target_switch_delay, 0.f, 1.f);
			padding(8, 2); ImGui::Checkbox(crypt_str("Automatic Stop"), &g_cfg.legitbot.weapon[hooks::legit_weapon].auto_stop);
			ImGui::EndChild();
			ImGui::PopStyleColor();
		}
		ImGui::Columns(1);
		break;
	}
}










/*
* 
VVVVVVVV           VVVVVVVV iiii                                                       lllllll
V::::::V           V::::::Vi::::i                                                      l:::::l
V::::::V           V::::::V iiii                                                       l:::::l
V::::::V           V::::::V                                                            l:::::l
 V:::::V           V:::::Viiiiiii     ssssssssss   uuuuuu    uuuuuu    aaaaaaaaaaaaa    l::::l     ssssssssss
  V:::::V         V:::::V i:::::i   ss::::::::::s  u::::u    u::::u    a::::::::::::a   l::::l   ss::::::::::s
   V:::::V       V:::::V   i::::i ss:::::::::::::s u::::u    u::::u    aaaaaaaaa:::::a  l::::l ss:::::::::::::s
	V:::::V     V:::::V    i::::i s::::::ssss:::::su::::u    u::::u             a::::a  l::::l s::::::ssss:::::s
	 V:::::V   V:::::V     i::::i  s:::::s  ssssss u::::u    u::::u      aaaaaaa:::::a  l::::l  s:::::s  ssssss
	  V:::::V V:::::V      i::::i    s::::::s      u::::u    u::::u    aa::::::::::::a  l::::l    s::::::s
	   V:::::V:::::V       i::::i       s::::::s   u::::u    u::::u   a::::aaaa::::::a  l::::l       s::::::s
		V:::::::::V        i::::i ssssss   s:::::s u:::::uuuu:::::u  a::::a    a:::::a  l::::l ssssss   s:::::s
		 V:::::::V        i::::::is:::::ssss::::::su:::::::::::::::uua::::a    a:::::a l::::::ls:::::ssss::::::s
		  V:::::V         i::::::is::::::::::::::s  u:::::::::::::::ua:::::aaaa::::::a l::::::ls::::::::::::::s
		   V:::V          i::::::i s:::::::::::ss    uu::::::::uu:::u a::::::::::aa:::al::::::l s:::::::::::ss
			VVV           iiiiiiii  sssssssssss        uuuuuuuu  uuuu  aaaaaaaaaa  aaaallllllll  sssssssssss

*/






void c_menu::DrawVisualsTab()
{
	static int visualsPgs = 0;
	padding(8, 8);
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.11f, 0.10f, 0.11f, 0.7f));
	ImGui::BeginChild("##WeaponsSections", ImVec2(600, 60));
	if (ImGui::BlssButton("Enemy", visualsPgs == 0 ? true : false, ImVec2(150, 60))) visualsPgs = 0; ImGui::SameLine(0, 0);
	if (ImGui::BlssButton("Team", visualsPgs == 1 ? true : false, ImVec2(150, 60))) visualsPgs = 1; ImGui::SameLine(0, 0);
	if (ImGui::BlssButton("Local", visualsPgs == 2 ? true : false, ImVec2(150, 60))) visualsPgs = 2; ImGui::SameLine(0, 0);
	if (ImGui::BlssButton("World", visualsPgs == 3 ? true : false, ImVec2(150, 60))) visualsPgs = 3; ImGui::SameLine(0, 0);
	
	ImGui::EndChild();
	ImGui::PopStyleColor();

	if (visualsPgs < 3)
	{

		ImGui::Columns(2, NULL, false);
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.11f, 0.10f, 0.11f, 0.7f));
		ImGui::BeginChild("##Misc", ImVec2(290, 415));
		padding(125, 8);
		ImGui::Text("ESP");
		padding(8, 8);
		
		ImGui::Checkbox(crypt_str("Enable "), &g_cfg.player.enable); padding(8, 2);

		ImGui::Checkbox(crypt_str("Bounding Box"), &g_cfg.player.type[visualsPgs].box); padding(8, 2);
		ImGui::SameLine(); padding(8, 2);
		ImGui::ColorEdit(crypt_str("##boxcolor"), &g_cfg.player.type[visualsPgs].box_color, ALPHA); padding(8, 2);


		ImGui::Checkbox(crypt_str("Name"), &g_cfg.player.type[visualsPgs].name); padding(8, 2);
		ImGui::SameLine();
		ImGui::ColorEdit(crypt_str("##namecolor"), &g_cfg.player.type[visualsPgs].name_color, ALPHA); padding(8, 2);

		ImGui::Checkbox(crypt_str("Health Bar"), &g_cfg.player.type[visualsPgs].health); padding(8, 2);
		ImGui::Checkbox(crypt_str("Health Color"), &g_cfg.player.type[visualsPgs].custom_health_color); padding(8, 2);
		ImGui::SameLine();
		ImGui::ColorEdit(crypt_str("##healthcolor"), &g_cfg.player.type[visualsPgs].health_color, ALPHA); padding(8, 2);

		

		for (auto i = 0, j = 0; i < ARRAYSIZE(flags); i++)
		{
			if (g_cfg.player.type[visualsPgs].flags[i])
			{
				if (j)
					preview += crypt_str(", ") + (std::string)flags[i];
				else
					preview = flags[i];

				j++;
			}
		}


		if (visualsPgs == ENEMY)
		{
			ImGui::Checkbox(crypt_str("Out Of FOV Arrow"), &g_cfg.player.arrows); padding(8, 2);
			ImGui::SameLine(); padding(8, 2);
			ImGui::ColorEdit(crypt_str("##arrowscolor"), &g_cfg.player.arrows_color, ALPHA); padding(8, 2);

			if (g_cfg.player.arrows)
			{
				ImGui::SliderInt(crypt_str("Arrows Distance"), &g_cfg.player.distance, 1, 100); padding(8, 10);
				ImGui::SliderInt(crypt_str("Arrows Size"), &g_cfg.player.size, 1, 100); padding(8, 2);
			}
		}

		draw_multicombo(crypt_str("Flags"), g_cfg.player.type[visualsPgs].flags, flags, ARRAYSIZE(flags), preview); padding(8, 2);
		draw_multicombo(crypt_str("Weapon"), g_cfg.player.type[visualsPgs].weapon, weaponplayer, ARRAYSIZE(weaponplayer), preview); padding(8, 2);


		if (g_cfg.player.type[visualsPgs].weapon[WEAPON_ICON] || g_cfg.player.type[visualsPgs].weapon[WEAPON_TEXT])
		{
			ImGui::Text(crypt_str("Color"));
			ImGui::SameLine();
			ImGui::ColorEdit(crypt_str("##weapcolor"), &g_cfg.player.type[visualsPgs].weapon_color, ALPHA); padding(8, 2);
		}

		ImGui::Checkbox(crypt_str("Footsteps"), &g_cfg.player.type[visualsPgs].footsteps); padding(8, 2);
		ImGui::SameLine();
		ImGui::ColorEdit(crypt_str("##footstepscolor"), &g_cfg.player.type[visualsPgs].footsteps_color, ALPHA); padding(8, 2);

		ImGui::Checkbox(crypt_str("Skeleton"), &g_cfg.player.type[visualsPgs].skeleton); padding(8, 2);
		ImGui::SameLine();
		ImGui::ColorEdit(crypt_str("##skeletoncolor"), &g_cfg.player.type[visualsPgs].skeleton_color, ALPHA); padding(8, 2);

		ImGui::Checkbox(crypt_str("Ammo Bar"), &g_cfg.player.type[visualsPgs].ammo); padding(8, 2);
		ImGui::SameLine();
		ImGui::ColorEdit(crypt_str("##ammocolor"), &g_cfg.player.type[visualsPgs].ammobar_color, ALPHA); padding(8, 2);

		if (g_cfg.player.type[visualsPgs].footsteps)
		{
			ImGui::SliderInt(crypt_str("Thickness"), &g_cfg.player.type[visualsPgs].thickness, 1, 10); padding(8, 2);
			ImGui::SliderInt(crypt_str("Radius"), &g_cfg.player.type[visualsPgs].radius, 50, 500); padding(8, 2);
		}
		ImGui::Checkbox(crypt_str("Glow"), &g_cfg.player.type[visualsPgs].glow);

		if (g_cfg.player.type[visualsPgs].glow)
		{
			draw_combo(crypt_str("Glow type"), g_cfg.player.type[visualsPgs].glow_type, glowtype, ARRAYSIZE(glowtype));
			ImGui::Text(crypt_str("Color "));
			ImGui::SameLine();
			ImGui::ColorEdit(crypt_str("##glowcolor"), &g_cfg.player.type[visualsPgs].glow_color, ALPHA);
		}

		if (visualsPgs == ENEMY || visualsPgs == TEAM)
		{
			padding(8, 2); ImGui::Checkbox(crypt_str("Snap Lines"), &g_cfg.player.type[visualsPgs].snap_lines); padding(8, 2);
			ImGui::SameLine();
			ImGui::ColorEdit(crypt_str("##snapcolor"), &g_cfg.player.type[visualsPgs].snap_lines_color, ALPHA); padding(8, 2);

			if (visualsPgs == ENEMY)
			{
				if (g_cfg.ragebot.enable)
				{
					ImGui::Checkbox(crypt_str("Aimbot Bones"), &g_cfg.player.show_multi_points); padding(8, 2);
					ImGui::SameLine();
					ImGui::ColorEdit(crypt_str("##showmultipointscolor"), &g_cfg.player.show_multi_points_color, ALPHA); padding(8, 2);
				}

				ImGui::Checkbox(crypt_str("Aimbot Hitboxes"), &g_cfg.player.lag_hitbox); padding(8, 2);
				ImGui::SameLine();
				ImGui::ColorEdit(crypt_str("##lagcompcolor"), &g_cfg.player.lag_hitbox_color, ALPHA); padding(8, 2);
			}
		}
		ImGui::EndChild();
		ImGui::PopStyleColor();
		ImGui::NextColumn();
		{
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.11f, 0.10f, 0.11f, 0.7f));
			ImGui::BeginChild("##Chams", ImVec2(290, 415));
			padding(120, 8);
			ImGui::Text("Chams");
			ImGui::Spacing();
			padding(8, 2);
			if (visualsPgs == LOCAL)
				draw_combo(crypt_str("Type"), g_cfg.player.local_chams_type, local_chams_type, ARRAYSIZE(local_chams_type));

			if (visualsPgs != LOCAL || !g_cfg.player.local_chams_type)
				draw_multicombo(crypt_str("Chams"), g_cfg.player.type[visualsPgs].chams, g_cfg.player.type[visualsPgs].chams[PLAYER_CHAMS_VISIBLE] ? chamsvisact : chamsvis, g_cfg.player.type[visualsPgs].chams[PLAYER_CHAMS_VISIBLE] ? ARRAYSIZE(chamsvisact) : ARRAYSIZE(chamsvis), preview);
			padding(8, 2);
			if (g_cfg.player.type[visualsPgs].chams[PLAYER_CHAMS_VISIBLE] || visualsPgs == LOCAL && g_cfg.player.local_chams_type) //-V648
			{
				if (visualsPgs == LOCAL && g_cfg.player.local_chams_type)
				{
					ImGui::Checkbox(crypt_str("Enable Desync Chams"), &g_cfg.player.fake_chams_enable);
					padding(8, 2); ImGui::Checkbox(crypt_str("Visualize Lag"), &g_cfg.player.visualize_lag);
					padding(8, 2); ImGui::Checkbox(crypt_str("Layered"), &g_cfg.player.layered);

					padding(8, 2); draw_combo(crypt_str("Player Chams "), g_cfg.player.fake_chams_type, chamstype, ARRAYSIZE(chamstype));

					padding(8, 2); ImGui::Text(crypt_str("Color "));
					ImGui::SameLine();
					ImGui::ColorEdit(crypt_str("##fakechamscolor"), &g_cfg.player.fake_chams_color, ALPHA);

					if (g_cfg.player.fake_chams_type != 6)
					{
						padding(8, 2); ImGui::Checkbox(crypt_str("Double Chams "), &g_cfg.player.fake_double_material);
						ImGui::SameLine();
						ImGui::ColorEdit(crypt_str("##doublematerialcolor"), &g_cfg.player.fake_double_material_color, ALPHA);
					}

					padding(8, 2); ImGui::Checkbox(crypt_str("Animate Chams"), &g_cfg.player.fake_animated_material);
					ImGui::SameLine();
					ImGui::ColorEdit(crypt_str("##animcolormat"), &g_cfg.player.fake_animated_material_color, ALPHA);
				}
				else
				{
					padding(8, 2); draw_combo(crypt_str("Player Chams Material"), g_cfg.player.type[visualsPgs].chams_type, chamstype, ARRAYSIZE(chamstype));

					if (g_cfg.player.type[visualsPgs].chams[PLAYER_CHAMS_VISIBLE])
					{
						padding(8, 2); ImGui::Text(crypt_str("Visible "));
						ImGui::SameLine();
						ImGui::ColorEdit(crypt_str("##chamsvisible"), &g_cfg.player.type[visualsPgs].chams_color, ALPHA);
					}

					if (g_cfg.player.type[visualsPgs].chams[PLAYER_CHAMS_VISIBLE] && g_cfg.player.type[visualsPgs].chams[PLAYER_CHAMS_INVISIBLE])
					{
						padding(8, 2); ImGui::Text(crypt_str("Invisible "));
						ImGui::SameLine();
						ImGui::ColorEdit(crypt_str("##chamsinvisible"), &g_cfg.player.type[visualsPgs].xqz_color, ALPHA);
					}

					if (g_cfg.player.type[visualsPgs].chams_type != 6)
					{
						padding(8, 2); ImGui::Checkbox(crypt_str("Double Chams "), &g_cfg.player.type[visualsPgs].double_material);
						ImGui::SameLine();
						ImGui::ColorEdit(crypt_str("##doublematerialcolor"), &g_cfg.player.type[visualsPgs].double_material_color, ALPHA);
					}

					padding(8, 2); ImGui::Checkbox(crypt_str("Animated Chams"), &g_cfg.player.type[visualsPgs].animated_material);
					ImGui::SameLine();
					ImGui::ColorEdit(crypt_str("##animcolormat"), &g_cfg.player.type[visualsPgs].animated_material_color, ALPHA);

					if (visualsPgs == ENEMY)
					{
						padding(8, 2); ImGui::Checkbox(crypt_str("Backtrack Chams"), &g_cfg.player.backtrack_chams);

						if (g_cfg.player.backtrack_chams)
						{
							padding(8, 2); draw_combo(crypt_str("Backtrack Chams Material"), g_cfg.player.backtrack_chams_material, chamstype, ARRAYSIZE(chamstype));

							padding(8, 2); ImGui::Text(crypt_str("Color "));
							ImGui::SameLine();
							ImGui::ColorEdit(crypt_str("##backtrackcolor"), &g_cfg.player.backtrack_chams_color, ALPHA);
						}
					}
				}
			}

			if (visualsPgs == ENEMY || visualsPgs == TEAM)
			{
				padding(8, 2); ImGui::Checkbox(crypt_str("Ragdoll Chams"), &g_cfg.player.type[visualsPgs].ragdoll_chams);

				if (g_cfg.player.type[visualsPgs].ragdoll_chams)
				{
					padding(8, 2); draw_combo(crypt_str("Ragdoll Chams Material"), g_cfg.player.type[visualsPgs].ragdoll_chams_material, chamstype, ARRAYSIZE(chamstype));

					padding(8, 2); ImGui::Text(crypt_str("Color "));
					ImGui::SameLine();
					ImGui::ColorEdit(crypt_str("##ragdollcolor"), &g_cfg.player.type[visualsPgs].ragdoll_chams_color, ALPHA);
				}
			}
			

			if (visualsPgs == LOCAL)
			{
				ImGui::Checkbox(crypt_str("Custom Scope"), &g_cfg.esp.new_scope); padding(8, 2);
				ImGui::SameLine();
				ImGui::ColorEdit(crypt_str("##new_scope_color"), &g_cfg.esp.new_scope_color, ALPHA);
			}

			ImGui::Spacing();

			padding(8, 2); draw_combo(crypt_str("Player Model T"), g_cfg.player.player_model_t, player_model_t, ARRAYSIZE(player_model_t)); padding(8, 2);
			padding(8, 2); draw_combo(crypt_str("Player Model CT"), g_cfg.player.player_model_ct, player_model_ct, ARRAYSIZE(player_model_ct)); padding(8, 2);
					
			ImGui::Spacing();

			padding(8, 2); draw_combo(crypt_str("Arms Chams Material"), g_cfg.esp.arms_chams_type, chamstype, ARRAYSIZE(chamstype));
			padding(8, 2); ImGui::Checkbox(crypt_str("Arms Chams"), &g_cfg.esp.arms_chams);
			ImGui::SameLine();
			ImGui::ColorEdit(crypt_str("##armscolor"), &g_cfg.esp.arms_chams_color, ALPHA);
			if (g_cfg.esp.arms_chams_type != 6)
			{
				padding(8, 2); ImGui::Checkbox(crypt_str("Arms Double Chams "), &g_cfg.esp.arms_double_material);
				ImGui::SameLine();
				ImGui::ColorEdit(crypt_str("##armsdoublematerial"), &g_cfg.esp.arms_double_material_color, ALPHA);
			}

			padding(8, 2); ImGui::Checkbox(crypt_str("Arms Animated Chams "), &g_cfg.esp.arms_animated_material);
			ImGui::SameLine();
			ImGui::ColorEdit(crypt_str("##armsanimatedmaterial"), &g_cfg.esp.arms_animated_material_color, ALPHA);

			ImGui::Spacing();

			padding(8, 2); ImGui::Checkbox(crypt_str("Weapon Chams"), &g_cfg.esp.weapon_chams);
			ImGui::SameLine();
			ImGui::ColorEdit(crypt_str("##weaponchamscolors"), &g_cfg.esp.weapon_chams_color, ALPHA);

			padding(8, 2); draw_combo(crypt_str("Weapon Chams"), g_cfg.esp.weapon_chams_type, chamstype, ARRAYSIZE(chamstype));

			if (g_cfg.esp.weapon_chams_type != 6)
			{
				padding(8, 2); ImGui::Checkbox(crypt_str("Double Chams "), &g_cfg.esp.weapon_double_material);
				ImGui::SameLine();
				ImGui::ColorEdit(crypt_str("##weapondoublematerial"), &g_cfg.esp.weapon_double_material_color, ALPHA);
			}

			padding(8, 2); ImGui::Checkbox(crypt_str("Animated Chams "), &g_cfg.esp.weapon_animated_material);
			ImGui::SameLine();
			ImGui::ColorEdit(crypt_str("##weaponanimatedmaterial"), &g_cfg.esp.weapon_animated_material_color, ALPHA);
		
			ImGui::EndChild();
		}
		ImGui::Columns(1);
	}
	if (visualsPgs > 2)
	{
		ImGui::Columns(2, NULL, false);
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.11f, 0.10f, 0.11f, 0.7f));
		ImGui::BeginChild("##Misc", ImVec2(290, 250));
		padding(120, 8);
		ImGui::Text("Indicators");
		padding(8, 2);
		ImGui::Checkbox(crypt_str("Enable Visuals"), &g_cfg.player.enable); padding(8, 2);

		draw_multicombo(crypt_str("Indicators"), g_cfg.esp.indicators, indicators, ARRAYSIZE(indicators), preview); padding(8, 2);
		ImGui::Checkbox(crypt_str("Grenade Prediction"), &g_cfg.esp.grenade_prediction); padding(8, 2);
		ImGui::SameLine();
		ImGui::ColorEdit(crypt_str("##grenpredcolor"), &g_cfg.esp.grenade_prediction_color, ALPHA); padding(8, 2);
		
	if (g_cfg.esp.grenade_prediction)
		{
			ImGui::Checkbox(crypt_str("On Click"), &g_cfg.esp.on_click); padding(8, 2);
			ImGui::Text(crypt_str("Tracer Color ")); padding(8, 2);
			ImGui::SameLine();
			ImGui::ColorEdit(crypt_str("##tracergrenpredcolor"), &g_cfg.esp.grenade_prediction_tracer_color, ALPHA); padding(8, 2);
		}


		ImGui::Checkbox(crypt_str("Grenade Projectiles"), &g_cfg.esp.projectiles); padding(8, 2);

		if (g_cfg.esp.projectiles){
			draw_multicombo(crypt_str("Grenade ESP"), g_cfg.esp.grenade_esp, proj_combo, ARRAYSIZE(proj_combo), preview); padding(8, 2);
	}

		if (g_cfg.esp.grenade_esp[GRENADE_ICON] || g_cfg.esp.grenade_esp[GRENADE_TEXT])
		{
			ImGui::Text(crypt_str("Color ")); padding(8, 2);
			ImGui::SameLine();
			ImGui::ColorEdit(crypt_str("##projectcolor"), &g_cfg.esp.projectiles_color, ALPHA); padding(8, 2);
		}

		

		if (g_cfg.esp.grenade_esp[GRENADE_GLOW])
		{
			ImGui::Text(crypt_str("Glow Color ")); padding(8, 2);
			ImGui::SameLine();
			ImGui::ColorEdit(crypt_str("##grenade_glow_color"), &g_cfg.esp.grenade_glow_color, ALPHA); padding(8, 2);
		}


		if (g_cfg.esp.grenade_esp[GRENADE_BOX])
		{
			ImGui::Text(crypt_str("Box Color ")); padding(8, 2);
			ImGui::SameLine();
			ImGui::ColorEdit(crypt_str("##grenade_box_color"), &g_cfg.esp.grenade_box_color, ALPHA); padding(8, 2);
		}

		ImGui::Checkbox(crypt_str("Smoke Timer"), &g_cfg.esp.smoke_timer); padding(8, 2);
		ImGui::SameLine();
		ImGui::ColorEdit(crypt_str("##smokecolor"), &g_cfg.esp.smoke_timer_color, ALPHA); padding(8, 2);

		ImGui::Checkbox(crypt_str("Fire Timer"), &g_cfg.esp.molotov_timer); padding(8, 2);
		ImGui::SameLine();
		ImGui::ColorEdit(crypt_str("##molotovcolor"), &g_cfg.esp.molotov_timer_color, ALPHA); padding(8, 2);

	

		ImGui::Checkbox(crypt_str("Bomb Indicator"), &g_cfg.esp.bomb_timer); padding(8, 2);
		draw_multicombo(crypt_str("Weapon ESP"), g_cfg.esp.weapon, weaponesp, ARRAYSIZE(weaponesp), preview); padding(8, 2);

		if (g_cfg.esp.weapon[WEAPON_ICON] || g_cfg.esp.weapon[WEAPON_TEXT] || g_cfg.esp.weapon[WEAPON_DISTANCE])
		{
			ImGui::Text(crypt_str("Color ")); padding(8, 2);
			ImGui::SameLine();
			ImGui::ColorEdit(crypt_str("##weaponcolor"), &g_cfg.esp.weapon_color, ALPHA); padding(8, 2);
		}



		if (g_cfg.esp.weapon[WEAPON_GLOW])
		{
			ImGui::Text(crypt_str("Glow Color ")); padding(8, 2);
			ImGui::SameLine();
			ImGui::ColorEdit(crypt_str("##weaponglowcolor"), &g_cfg.esp.weapon_glow_color, ALPHA); padding(8, 2);
		}



		if (g_cfg.esp.weapon[WEAPON_BOX])
		{
			ImGui::Text(crypt_str("Box Color ")); padding(8, 2);
			ImGui::SameLine();
			ImGui::ColorEdit(crypt_str("##weaponboxcolor"), &g_cfg.esp.box_color, ALPHA); padding(8, 2);
		}

		if (g_cfg.esp.weapon[WEAPON_AMMO])
		{
			ImGui::Text(crypt_str("Ammo Bar Color ")); padding(8, 2);
			ImGui::SameLine();
			ImGui::ColorEdit(crypt_str("##weaponammocolor"), &g_cfg.esp.weapon_ammo_color, ALPHA); padding(8, 2);
		}
		ImGui::EndChild();
		ImGui::PopStyleColor();
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.11f, 0.10f, 0.11f, 0.7f));
		ImGui::BeginChild("##Tracers", ImVec2(290, 150));
		padding(110, 8);
		ImGui::Text("Tracers");
		padding(8, 2); ImGui::Checkbox(crypt_str("Local Bullet Tracers"), &g_cfg.esp.bullet_tracer); padding(8, 2);
		ImGui::SameLine();
		ImGui::ColorEdit(crypt_str("##bulltracecolor"), &g_cfg.esp.bullet_tracer_color, ALPHA); padding(8, 2);
		ImGui::Checkbox(crypt_str("Client Bullet Impacts"), &g_cfg.esp.client_bullet_impacts); padding(8, 2);
		ImGui::SameLine();
		ImGui::ColorEdit(crypt_str("##clientbulletimpacts"), &g_cfg.esp.client_bullet_impacts_color, ALPHA); padding(8, 2);
		ImGui::Checkbox(crypt_str("Server Bullet Impacts"), &g_cfg.esp.server_bullet_impacts); padding(8, 2);
		ImGui::SameLine();
		ImGui::ColorEdit(crypt_str("##serverbulletimpacts"), &g_cfg.esp.server_bullet_impacts_color, ALPHA); padding(8, 2);
		ImGui::Checkbox(crypt_str("Enemy Bullet Tracers"), &g_cfg.esp.enemy_bullet_tracer); padding(8, 2);
		ImGui::SameLine();
		ImGui::ColorEdit(crypt_str("##enemybulltracecolor"), &g_cfg.esp.enemy_bullet_tracer_color, ALPHA); padding(8, 2);
		
		ImGui::EndChild();
		ImGui::PopStyleColor();
		ImGui::NextColumn();
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.11f, 0.10f, 0.11f, 0.7f));
		ImGui::BeginChild("##More", ImVec2(290, 415));
		{
			padding(100, 8); ImGui::Text("World Modulation");
			padding(8, 2); draw_multicombo(crypt_str("Removals"), g_cfg.esp.removals, removals, ARRAYSIZE(removals), preview); padding(8, 2);
		if (g_cfg.esp.removals[REMOVALS_ZOOM]) {
			ImGui::Checkbox(crypt_str("Fix Zoom Sensivity"), &g_cfg.esp.fix_zoom_sensivity);
		}
		ImGui::Spacing();
		padding(8, 2); ImGui::SliderInt(crypt_str("Field of View"), &g_cfg.esp.fov, 0, 89);
		padding(8, 2); ImGui::Checkbox(crypt_str("World Effects"), &g_cfg.esp.world_modulation);


		padding(8, 2); ImGui::Checkbox(crypt_str("Fog Changer"), &g_cfg.esp.fog);

		if (g_cfg.esp.fog)
		{
			padding(8, 2); ImGui::SliderInt(crypt_str("Distance"), &g_cfg.esp.fog_distance, 0, 2500);
			padding(8, 2); ImGui::SliderInt(crypt_str("Density"), &g_cfg.esp.fog_density, 0, 100);

			padding(8, 2); ImGui::Text(crypt_str("Color "));
			ImGui::SameLine();
			ImGui::ColorEdit(crypt_str("##fogcolor"), &g_cfg.esp.fog_color, NOALPHA);
		}


		if (g_cfg.esp.world_modulation)
		{
			padding(8, 2); ImGui::SliderFloat(crypt_str("Bloom"), &g_cfg.esp.bloom, 0.0f, 750.0f);
			padding(8, 2); ImGui::SliderFloat(crypt_str("Ambient"), &g_cfg.esp.ambient, 0.0f, 1500.0f);
			padding(8, 2); ImGui::SliderFloat(crypt_str("Exposure"), &g_cfg.esp.exposure, 0.0f, 2000.0f);
		}

		padding(8, 2); ImGui::Checkbox(crypt_str("Rain"), &g_cfg.esp.rain);
		padding(8, 2); ImGui::Checkbox(crypt_str("Full Bright"), &g_cfg.esp.bright);

		padding(8, 2); draw_combo(crypt_str("Skybox"), g_cfg.esp.skybox, skybox, ARRAYSIZE(skybox));

		padding(8, 2); ImGui::Text(crypt_str("Color "));
		ImGui::SameLine();

		if (g_cfg.esp.skybox == 21)
		{
			static char sky_custom[64] = "\0";

			if (!g_cfg.esp.custom_skybox.empty())
				strcpy_s(sky_custom, sizeof(sky_custom), g_cfg.esp.custom_skybox.c_str());

			ImGui::Text(crypt_str("Name"));
			ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.f);

			if (ImGui::InputText(crypt_str("##customsky"), sky_custom, sizeof(sky_custom)))
				g_cfg.esp.custom_skybox = sky_custom;

			ImGui::PopStyleVar();
		}
		padding(8, 8);
		
		ImGui::PopStyleColor();
		ImGui::EndChild();
		}
		ImGui::Columns(1);
	}
}




/*

MMMMMMMM               MMMMMMMM  iiii
M:::::::M             M:::::::M i::::i
M::::::::M           M::::::::M  iiii
M:::::::::M         M:::::::::M
M::::::::::M       M::::::::::Miiiiiii     ssssssssss       cccccccccccccccc
M:::::::::::M     M:::::::::::Mi:::::i   ss::::::::::s    cc:::::::::::::::c
M:::::::M::::M   M::::M:::::::M i::::i ss:::::::::::::s  c:::::::::::::::::c
M::::::M M::::M M::::M M::::::M i::::i s::::::ssss:::::sc:::::::cccccc:::::c
M::::::M  M::::M::::M  M::::::M i::::i  s:::::s  ssssss c::::::c     ccccccc
M::::::M   M:::::::M   M::::::M i::::i    s::::::s      c:::::c
M::::::M    M:::::M    M::::::M i::::i       s::::::s   c:::::c
M::::::M     MMMMM     M::::::M i::::i ssssss   s:::::s c::::::c     ccccccc
M::::::M               M::::::Mi::::::is:::::ssss::::::sc:::::::cccccc:::::c
M::::::M               M::::::Mi::::::is::::::::::::::s  c:::::::::::::::::c
M::::::M               M::::::Mi::::::i s:::::::::::ss    cc:::::::::::::::c
MMMMMMMM               MMMMMMMMiiiiiiii  sssssssssss        cccccccccccccccc


*/








void c_menu::DrawMiscTab()
{
	static int pages = 0;
	padding(8, 8);
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.11f, 0.10f, 0.11f, 0.7f));
	ImGui::BeginChild("##WeaponsSections", ImVec2(600, 60));
	if (ImGui::BlssButton("Main", pages == 0 ? true : false, ImVec2(200, 60))) pages = 0; ImGui::SameLine(0, 0);
	if (ImGui::BlssButton("Settings", pages == 1 ? true : false, ImVec2(200, 60))) pages = 1; ImGui::SameLine(0, 0);


	ImGui::EndChild();
	ImGui::PopStyleColor();
	if (pages == 0)
	{
		ImGui::Columns(2, NULL, false);
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.11f, 0.10f, 0.11f, 0.7f));
		ImGui::BeginChild("##GameOptions", ImVec2(290, 150));
		padding(8, 8);
		padding(110, 10);
		ImGui::Text(crypt_str("Game Options")); padding(10, 2);
		ImGui::Checkbox(crypt_str("Autoaccept"), &g_cfg.add_shonax.autoaccept); padding(10, 2);
		ImGui::Checkbox(crypt_str("Anti-Untrusted"), &g_cfg.misc.anti_untrusted); padding(10, 2);
		ImGui::Checkbox(crypt_str("Unlock Inventory Access"), &g_cfg.misc.inventory_access); padding(10, 2);
		ImGui::Checkbox(crypt_str("Rank Reveal"), &g_cfg.misc.rank_reveal); padding(10, 2);
		ImGui::Checkbox(crypt_str("Clantag"), &g_cfg.misc.clantag_spammer);
		draw_multicombo(crypt_str("Logs"), g_cfg.misc.events_to_log, events, ARRAYSIZE(events), preview);

		draw_multicombo(crypt_str("Logs output"), g_cfg.misc.log_output, events_output, ARRAYSIZE(events_output), preview);

		if (g_cfg.misc.events_to_log[EVENTLOG_HIT] || g_cfg.misc.events_to_log[EVENTLOG_ITEM_PURCHASES] || g_cfg.misc.events_to_log[EVENTLOG_BOMB])
		{
			ImGui::Text(crypt_str("Color"));

			ImGui::ColorEdit(crypt_str("##logcolor"), &g_cfg.misc.log_color, ImGuiWindowFlags_NoTitleBar);
		}
		ImGui::EndChild();
		padding(0, 8);
		ImGui::BeginChild("##Movement", ImVec2(290, 250));
		padding(110, 10);
		ImGui::Text(crypt_str("Movement")); padding(10, 2);
		draw_combo(crypt_str("Auto Strafe"), g_cfg.misc.airstrafe, strafes, ARRAYSIZE(strafes)); padding(10, 2);
		ImGui::Checkbox(crypt_str("Auto Bhop"), &g_cfg.misc.bunnyhop); padding(10, 2);
		draw_keybind(crypt_str("Edge Jump"), &g_cfg.misc.edge_jump, crypt_str("##EDGEJUMP__HOTKEY")); padding(10, 2);
		draw_keybind(crypt_str("Edge Bug"), &g_cfg.misc.edge_bug, crypt_str("##EDGEBUG__HOTKEY")); padding(10, 2);
		ImGui::Checkbox(crypt_str("Fast stop"), &g_cfg.misc.fast_stop); padding(10, 2);
		ImGui::Checkbox(crypt_str("Crouch Midair"), &g_cfg.misc.crouch_in_air); padding(10, 2);
		ImGui::EndChild();
		ImGui::BeginChild("##Buybot", ImVec2(290, 250));
		padding(110, 10);
		ImGui::Text(crypt_str("Buybot")); padding(10, 2);
		ImGui::Checkbox(crypt_str("Enable buybot"), &g_cfg.misc.buybot_enable);
		if (g_cfg.misc.buybot_enable)
		{
			draw_combo(crypt_str("Snipers"), g_cfg.misc.buybot1, mainwep, ARRAYSIZE(mainwep));
			padding(0, 3);
			draw_combo(crypt_str("Pistols"), g_cfg.misc.buybot2, secwep, ARRAYSIZE(secwep));
			padding(0, 3);
			draw_multicombo(crypt_str("Other"), g_cfg.misc.buybot3, grenades, ARRAYSIZE(grenades), preview);
		}
		ImGui::EndChild();
		ImGui::PopStyleColor();
		ImGui::NextColumn();
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.11f, 0.10f, 0.11f, 0.7f));
		ImGui::BeginChild("##MiscVisuals", ImVec2(290, 415));
		padding(120, 10);
		ImGui::Text(crypt_str("Misc Visuals")); padding(10, 2);
		draw_multicombo(crypt_str("Hit Marker"), g_cfg.esp.hitmarker, hitmarkers, ARRAYSIZE(hitmarkers), preview); padding(10, 2);
		ImGui::Checkbox(crypt_str("Watermark"), &g_cfg.menu.watermark); padding(10, 2);
		ImGui::Checkbox(crypt_str("Spectators List"), &g_cfg.misc.spectators_list); padding(10, 2);
		ImGui::Checkbox(crypt_str("Kill Effect"), &g_cfg.esp.kill_effect); padding(10, 2);
		ImGui::Checkbox(crypt_str("Damage Marker"), &g_cfg.esp.damage_marker); padding(10, 2);
		ImGui::Checkbox(crypt_str("Custom Scope"), &g_cfg.esp.new_scope); padding(10, 2);
		ImGui::SameLine();
		ImGui::ColorEdit(crypt_str("##new_scope_color"), &g_cfg.esp.new_scope_color, ALPHA);
		if (g_cfg.esp.kill_effect)
		{
			ImGui::SliderFloat(crypt_str("Duration"), &g_cfg.esp.kill_effect_duration, 0.01f, 3.0f);
		}
		draw_keybind(crypt_str("Thirdperson"), &g_cfg.misc.thirdperson_toggle, crypt_str("##TPKEY__HOTKEY")); padding(10, 2);
		ImGui::Checkbox(crypt_str("Thirdperson When Spectating"), &g_cfg.misc.thirdperson_when_spectating); padding(10, 2);
		if (g_cfg.misc.thirdperson_toggle.key > KEY_NONE && g_cfg.misc.thirdperson_toggle.key < KEY_MAX)
		{
			ImGui::SliderInt(crypt_str("Thirdperson distance"), &g_cfg.misc.thirdperson_distance, 100, 300); padding(10, 2);
		}
		ImGui::Checkbox(crypt_str("Show Zues Range"), &g_cfg.esp.taser_range); padding(10, 2);
		ImGui::Checkbox(crypt_str("Show Spread"), &g_cfg.esp.show_spread); padding(10, 2);
		ImGui::SameLine();
		ImGui::ColorEdit(crypt_str("##spredcolor"), &g_cfg.esp.show_spread_color, ALPHA); padding(10, 2);
		ImGui::Checkbox(crypt_str("Penetration Crosshair"), &g_cfg.esp.penetration_reticle); padding(10, 2);
		ImGui::Checkbox(crypt_str("Aspect Ratio"), &g_cfg.misc.aspect_ratio); padding(10, 2);
		if (g_cfg.misc.aspect_ratio)
		{
			padding(0, 2);
			ImGui::SliderFloat(crypt_str("Amount"), &g_cfg.misc.aspect_ratio_amount, 1.0f, 2.0f);
		}
		ImGui::Checkbox(crypt_str("Preserve Killfeed"), &g_cfg.esp.preserve_killfeed); padding(10, 2);
		ImGui::EndChild();
		ImGui::PopStyleColor();
		ImGui::Columns(1);
	}

	auto previous_check_box = false;

	for (auto& current : c_lua::get().scripts)
	{
		auto& items = c_lua::get().items.at(c_lua::get().get_script_id(current));

		for (auto& item : items)
		{
			std::string item_name;

			auto first_point = false;
			auto item_str = false;

			for (auto& c : item.first)
			{
				if (c == '.')
				{
					if (first_point)
					{
						item_str = true;
						continue;
					}
					else
						first_point = true;
				}

				if (item_str)
					item_name.push_back(c);
			}

			switch (item.second.type)
			{
			case NEXT_LINE:
				previous_check_box = false;
				break;
			case CHECK_BOX:
				previous_check_box = true;
				ImGui::Checkbox(item_name.c_str(), &item.second.check_box_value);
				break;
			case COMBO_BOX:
				previous_check_box = false;
				draw_combo(item_name.c_str(), item.second.combo_box_value, [](void* data, int idx, const char** out_text)
					{
						auto labels = (std::vector <std::string>*)data;
						*out_text = labels->at(idx).c_str(); //-V106
						return true;
					}, &item.second.combo_box_labels, item.second.combo_box_labels.size());
				break;
			case SLIDER_INT:
				previous_check_box = false;
				ImGui::SliderInt(item_name.c_str(), &item.second.slider_int_value, item.second.slider_int_min, item.second.slider_int_max);
				break;
			case SLIDER_FLOAT:
				previous_check_box = false;
				ImGui::SliderFloat(item_name.c_str(), &item.second.slider_float_value, item.second.slider_float_min, item.second.slider_float_max);
				break;
			case COLOR_PICKER:
				if (previous_check_box)
					previous_check_box = false;
				else
					ImGui::Text((item_name + ' ').c_str());

				ImGui::SameLine();
				ImGui::ColorEdit((crypt_str("##") + item_name).c_str(), &item.second.color_picker_value, ALPHA, true);
				break;
			}
		}
	}

	if (pages == 1)
	{

		float mod22 = 0.4;
		ImGui::Columns(2, NULL, false);
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.11f, 0.10f, 0.11f, 0.7f));
		ImGui::Text("Configs:");
		ImGui::BeginChild(crypt_str("##CONFIGS__FIRST"), ImVec2(290, 450));

		static auto should_update = true;
		if (should_update)
		{
			should_update = false;

			cfg_manager->config_files();
			files = cfg_manager->files;

			for (auto& current : files)
				if (current.size() > 2)
					current.erase(current.size() - 3, 3);
		}
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.f);
		padding(40, 20);
		ImGui::ListBoxConfigArray(crypt_str("##CONFIGS"), &g_cfg.selected_config, files, 7);
		ImGui::PopStyleVar();
		padding(0, 4);
		static auto next_save = false;
		static auto prenext_save = false;
		static auto clicked_sure = false;
		static auto save_time = m_globals()->m_realtime;
		static auto save_alpha = 1.0f;
		save_alpha = math::clamp(save_alpha + (4.f * ImGui::GetIO().DeltaTime * (!prenext_save ? 1.f : -1.f)), 0.01f, 1.f);
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, save_alpha * public_alpha/* * (1.f - preview_alpha)*/);

		static char config_name[64] = "\0";
		padding(40, 10);
		ImGui::InputText(crypt_str("##configname"), config_name, sizeof(config_name));
		ImGui::PopStyleVar();
		padding(0, 4);
		if (ImGui::CustomButton(crypt_str("Create Config"), crypt_str("##CONFIG__CREATE"), ImVec2(290 * dpi_scale, 26 * dpi_scale)))
		{
			g_cfg.new_config_name = config_name;
			add_config();
		}

		if (!next_save)
		{
			clicked_sure = false;

			if (prenext_save && save_alpha <= 0.01f)
				next_save = true;

			if (ImGui::CustomButton(crypt_str("Save Config"), crypt_str("##CONFIG__SAVE"), ImVec2(290 * dpi_scale, 26 * dpi_scale)))
			{
				save_time = m_globals()->m_realtime;
				save_config();
			}
		}
		else
		{
			if (prenext_save && save_alpha <= 0.01f)
			{
				prenext_save = false;
				next_save = !clicked_sure;
			}

			if (ImGui::CustomButton(crypt_str("Are You Sure?"), crypt_str("##AREYOUSURE__SAVE"), ImVec2(290 * dpi_scale, 26 * dpi_scale)))
			{

				prenext_save = true;
				clicked_sure = true;
			}

			if (!clicked_sure && m_globals()->m_realtime > save_time + 1.5f)
			{
				prenext_save = true;
				clicked_sure = true;
			}
		}
		ImGui::PopStyleVar();
		if (ImGui::CustomButton(crypt_str("Load Config"), crypt_str("##CONFIG__LOAD"), ImVec2(290 * dpi_scale, 26 * dpi_scale)))
			load_config();

		static auto next_delete = false;
		static auto prenext_delete = false;
		static auto clicked_sure_del = false;
		static auto delete_time = m_globals()->m_realtime;
		static auto delete_alpha = 1.0f;

		delete_alpha = math::clamp(delete_alpha + (4.f * ImGui::GetIO().DeltaTime * (!prenext_delete ? 1.f : -1.f)), 0.01f, 1.f);
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, delete_alpha * public_alpha/* * (1.f - preview_alpha)*/);

		if (ImGui::CustomButton(crypt_str("Remove Config"), crypt_str("##CONFIG__delete"), ImVec2(290 * dpi_scale, 26 * dpi_scale)))
		{
			remove_config();
			delete_time = m_globals()->m_realtime;
			clicked_sure_del = true;
		}

		if (ImGui::CustomButton(crypt_str("Open Configs Folder"), crypt_str("##CONFIG__FOLDER"), ImVec2(290 * dpi_scale, 26 * dpi_scale)))
		{
			std::string folder;
			auto get_dir = [&folder]() -> void
			{
				static TCHAR path[MAX_PATH];


				if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, NULL, path)))
					folder = std::string(path) + crypt_str("\\Plagueware\\Configs\\");

				CreateDirectory(folder.c_str(), NULL);
			};
			get_dir();
			ShellExecute(NULL, crypt_str("open"), folder.c_str(), NULL, NULL, SW_SHOWNORMAL);
		}


		if (ImGui::CustomButton(crypt_str("Refresh Configs"), crypt_str("##CONFIG__REFRESH"), ImVec2(290 * dpi_scale, 26 * dpi_scale)))
		{
			cfg_manager->config_files();
			files = cfg_manager->files;

			for (auto& current : files)
				if (current.size() > 2)
					current.erase(current.size() - 3, 3);
		}

		//Luas

		ImGui::EndChild();
		ImGui::NextColumn();
		ImGui::Text("Luas:");
		ImGui::BeginChild(crypt_str("##LUA_FIRST"), ImVec2(290, 450));
		{
			ImGui::PushItemWidth(250 * c_menu::get().dpi_scale);
			static auto should_update = true;

			if (should_update)
			{
				should_update = false;
				scripts = c_lua::get().scripts;

				for (auto& current : scripts)
				{
					if (current.size() >= 5 && current.at(current.size() - 1) == 'c')
						current.erase(current.size() - 5, 5);
					else if (current.size() >= 4)
						current.erase(current.size() - 4, 4);
				}
			}

			ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.f);
			padding(20, 20);
			if (scripts.empty())
				ImGui::ListBoxConfigArray(crypt_str("##LUAS"), &selected_script, scripts, 7);
			else
			{
				auto backup_scripts = scripts;

				for (auto& script : scripts)
				{
					auto script_id = c_lua::get().get_script_id(script + crypt_str(".lua"));

					if (script_id == -1)
						continue;

					if (c_lua::get().loaded.at(script_id))
						scripts.at(script_id) += crypt_str(" [loaded]");
				}

				ImGui::ListBoxConfigArray(crypt_str("##LUAS"), &selected_script, scripts, 7);
				scripts = std::move(backup_scripts);
			}

			ImGui::PopStyleVar();

			if (ImGui::CustomButton(crypt_str("Load Lua"), crypt_str("##SCRIPTS__LOAD"), ImVec2(145 * dpi_scale, 26 * dpi_scale)))
			{
				c_lua::get().load_script(selected_script);
				c_lua::get().refresh_scripts();

				scripts = c_lua::get().scripts;

				if (selected_script >= scripts.size())
					selected_script = scripts.size() - 1; //-V103

				for (auto& current : scripts)
				{
					if (current.size() >= 5 && current.at(current.size() - 1) == 'c')
						current.erase(current.size() - 5, 5);
					else if (current.size() >= 4)
						current.erase(current.size() - 4, 4);
				}

				eventlogs::get().add(crypt_str("Loaded ") + scripts.at(selected_script) + crypt_str(" script"), false); //-V106
			}
			ImGui::SameLine();
			if (ImGui::CustomButton(crypt_str("Unload Lua"), crypt_str("##SCRIPTS__UNLOAD"), ImVec2(145 * dpi_scale, 26 * dpi_scale)))
			{
				c_lua::get().unload_script(selected_script);
				c_lua::get().refresh_scripts();

				scripts = c_lua::get().scripts;

				if (selected_script >= scripts.size())
					selected_script = scripts.size() - 1; //-V103

				for (auto& current : scripts)
				{
					if (current.size() >= 5 && current.at(current.size() - 1) == 'c')
						current.erase(current.size() - 5, 5);
					else if (current.size() >= 4)
						current.erase(current.size() - 4, 4);
				}

				eventlogs::get().add(crypt_str("Unloaded ") + scripts.at(selected_script) + crypt_str(" script"), false); //-V106
			}
			if (ImGui::CustomButton(crypt_str("Refresh"), crypt_str("##LUA__REFRESH"), ImVec2(290 * dpi_scale, 26 * dpi_scale)))
			{
				c_lua::get().refresh_scripts();
				scripts = c_lua::get().scripts;

				if (selected_script >= scripts.size())
					selected_script = scripts.size() - 1; //-V103

				for (auto& current : scripts)
				{
					if (current.size() >= 5 && current.at(current.size() - 1) == 'c')
						current.erase(current.size() - 5, 5);
					else if (current.size() >= 4)
						current.erase(current.size() - 4, 4);
				}
			}

			if (ImGui::CustomButton(crypt_str("Edit Lua"), crypt_str("##LUA__EDIT"), ImVec2(290 * dpi_scale, 26 * dpi_scale)))
			{
				loaded_editing_script = false;
				editing_script = scripts.at(selected_script);
			}




			if (ImGui::CustomButton(crypt_str("Refresh Luas"), crypt_str("##SCRIPTS__RELOAD"), ImVec2(290 * dpi_scale, 26 * dpi_scale)))
			{
				c_lua::get().reload_all_scripts();
				c_lua::get().refresh_scripts();

				scripts = c_lua::get().scripts;

				if (selected_script >= scripts.size())
					selected_script = scripts.size() - 1; //-V103

				for (auto& current : scripts)
				{
					if (current.size() >= 5 && current.at(current.size() - 1) == 'c')
						current.erase(current.size() - 5, 5);
					else if (current.size() >= 4)
						current.erase(current.size() - 4, 4);
				}
			}

			if (ImGui::CustomButton(crypt_str("Unload All Luas"), crypt_str("##SCRIPTS__UNLOADALL"), ImVec2(290, 26 * dpi_scale)))
			{
				c_lua::get().unload_all_scripts();
				c_lua::get().refresh_scripts();

				scripts = c_lua::get().scripts;

				if (selected_script >= scripts.size())
					selected_script = scripts.size() - 1; //-V103

				for (auto& current : scripts)
				{
					if (current.size() >= 5 && current.at(current.size() - 1) == 'c')
						current.erase(current.size() - 5, 5);
					else if (current.size() >= 4)
						current.erase(current.size() - 4, 4);
				}
			}

		}
		ImGui::EndChild();

		ImGui::Columns(1);
	}



}









void c_menu::draw(bool is_open)
{
	static int active_sidebar_tab = 0;
	static auto w = 0, h = 0, current_h = 0;
	m_engine()->GetScreenSize(w, current_h);

	if (h != current_h)
	{
		if (h)
			update_scripts = true;

		h = current_h;
		update_dpi = true;
	}

	// animation related code
	static float m_alpha = 0.0002f;
	m_alpha = math::clamp(m_alpha + (3.f * ImGui::GetIO().DeltaTime * (is_open ? 1.f : -1.f)), 0.0001f, 1.f);

	// set alpha in class to use later in widgets
	public_alpha = m_alpha;

	if (m_alpha <= 0.0001f)
		return;

	// set new alpha
	ImGui::PushStyleVar(ImGuiStyleVar_Alpha, m_alpha);

	// setup colors and some styles
	if (!menu_setupped)
		menu_setup(ImGui::GetStyle());

	ImGui::PushStyleColor(ImGuiCol_ScrollbarGrab, ImVec4(ImGui::GetStyle().Colors[ImGuiCol_ScrollbarGrab].x, ImGui::GetStyle().Colors[ImGuiCol_ScrollbarGrab].y, ImGui::GetStyle().Colors[ImGuiCol_ScrollbarGrab].z, m_alpha));

	// last active tab to switch effect & reverse alpha & preview alpha
	// IMPORTANT: DO TAB SWITCHING BY LAST_TAB!!!!!
	static int last_tab = active_sidebar_tab;
	static bool preview_reverse = false;

	ImGui::SetNextWindowSize(ImVec2(820, 560));

	ImGui::Begin(crypt_str("Plagueware"), nullptr, ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar);
	{
		ImVec2 p = ImGui::GetCursorScreenPos();
		const auto [r, g, b] { util::rainbowColor(m_globals()->m_realtime, 2.f) };
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(p.x, p.y), ImVec2(p.x + 820, p.y + 4), ImColor(r, g, b), 6, ImDrawCornerFlags_TopLeft | ImDrawCornerFlags_TopRight);

	

	ImGui::BeginGroup();
	{
		//ImGui::GetCurrentWindow()->Flags &= ~ImGuiWindowFlags_ShowBorders;
		ImGui::GetWindowDrawList()->AddImage(hooks::skinImg, ImVec2(ImGui::GetWindowPos().x + 15, ImGui::GetWindowPos().y + 20), ImVec2(ImGui::GetWindowPos().x + 145, ImGui::GetWindowPos().y + 155), ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, 255));
		ImGui::NewLine(); ImGui::NewLine(); ImGui::NewLine(); ImGui::NewLine(); ImGui::NewLine(); ImGui::NewLine(); ImGui::NewLine(); ImGui::NewLine();
		ImGui::SameLine((44) - (100 / 2));

		ImGui::SameLine((47) - (100 / 2));
		if (ImGui::OwOButton("                     Ragebot, Anti-aim", "d", c_menu::get().gotham, "       Rage", c_menu::get().futura_large, active_sidebar_tab == 0 ? true : false, ImVec2(110, 40)))active_sidebar_tab = 0;
		ImGui::NewLine();
		ImGui::SameLine((47) - (100 / 2));
		if (ImGui::OwOButton("                     Aimbot, Smooth", "e", c_menu::get().gotham, "       Legit", c_menu::get().futura_large, active_sidebar_tab == 1 ? true : false, ImVec2(110, 40)))active_sidebar_tab = 1;
		ImGui::NewLine();
		ImGui::SameLine((47) - (100 / 2));
		if (ImGui::OwOButton("                     World, Visuals", "h", c_menu::get().gotham, "       Visuals", c_menu::get().futura_large, active_sidebar_tab == 2 ? true : false, ImVec2(110, 40)))active_sidebar_tab = 2;
		ImGui::NewLine();
		ImGui::SameLine((47) - (100 / 2));
		if (ImGui::OwOButton("                     Skins, Inventory", "g", c_menu::get().gotham, "       Skins", c_menu::get().futura_large, active_sidebar_tab == 3 ? true : false, ImVec2(110, 40)))active_sidebar_tab = 3;
		ImGui::NewLine();
		ImGui::SameLine((47) - (100 / 2));
		if (ImGui::OwOButton("                     Configs, Exploits", "f", c_menu::get().gotham, "       Misc", c_menu::get().futura_large, active_sidebar_tab == 4 ? true : false, ImVec2(110, 40)))active_sidebar_tab = 4;
	}
	ImGui::EndGroup();

	ImGui::SameLine(175.f);
	auto size = ImVec2(620, 500);
	padding(8, 30);
	ImGui::BeginChild(crypt_str("##content_area"), size); // there wiil be main cheat functional
	{	
		ImGui::PushFont(c_menu::get().futura_small);
		switch (active_sidebar_tab % 9)
		{
		case 0: DrawRageTab(); break;
		case 1: LegitTab(); break;
		case 2: DrawVisualsTab(); break;
		case 3:	SkinChanger(); break;
		case 4: DrawMiscTab(); break;
		default: break;
		}
		ImGui::PopFont();
		
	}
	ImGui::EndChild();
	}

	ImGui::End();

	ImGui::PopStyleColor();
	ImGui::PopStyleVar();
}