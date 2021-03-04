#include "c_renderer.h"
#include "../fonts/profont.h"
#include "../security/string_obfuscation.h"
#include <utility>
#include "../fonts/D3DFont.h"

std::optional<int> Color::alpha_override = std::nullopt;

c_renderer::c_renderer(IDirect3DDevice9* dev)
{
	DWORD fnt;
	AddFontMemResourceEx(reinterpret_cast<void*>(profont), sizeof(profont), nullptr, &fnt);
	
	DWORD fnt1;
	AddFontMemResourceEx(reinterpret_cast<void*>(pro_font_12), sizeof(pro_font_12), nullptr, &fnt1);

	DWORD fnt2;
	AddFontMemResourceEx(reinterpret_cast<void*>(pro_font_13), sizeof(pro_font_13), nullptr, &fnt2);
	fonts[fnv1a("pro11")] = c_font("Twiddlybitz", 11, FW_REGULAR);
	fonts[fnv1a("pro12")] = c_font("Twiddlybitz", 13, FW_REGULAR);
	fonts[fnv1a("pro13")] = c_font("Twiddlybitz", 14, FW_NORMAL);
	fonts[fnv1a("indicator_font")] = c_font("Verdana", 20, FW_MEDIUM);
	

	fonts[fnv1a("name_font")] = c_font("ProFont for Powerline", 11, FW_NORMAL);
	fonts[fnv1a("flag_font")] = c_font("ProFont for Powerline", 11, FW_NORMAL); 
	fonts[fnv1a("pro17")] = c_font("ProFont for Powerline", 17, FW_REGULAR);
	fonts[fnv1a("weapons")] = c_font("undefeated", 15, FW_REGULAR);


	fonts[fnv1a("choke_font")] = c_font("Twiddlybitz", 14, FW_NORMAL);
	fonts[fnv1a("menu_font")] = c_font("Twiddlybitz", 12, FW_MEDIUM);
	fonts[fnv1a("menu_controls")] = c_font("Twiddlybitz", 11, FW_MEDIUM);
	 
	init_device_objects(dev);
}





void c_renderer::line(const Vector2D from, const Vector2D to, const Color color) const
{
	const auto col = color.direct();

	vertex vert[2] =
	{
		{ from.x, from.y, 0.0f, 1.0f, col },
		{ to.x, to.y, 0.0f, 1.0f, col }
	};

	dev->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
	dev->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, TRUE);

	dev->SetTexture(0, nullptr);
	dev->DrawPrimitiveUP(D3DPT_LINELIST, 1, &vert, sizeof(vertex));

	dev->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, FALSE);
	dev->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, FALSE);
}

void c_renderer::rect(const Vector2D from, const Vector2D size, const Color color) const
{
	const auto to = from + size;
	const auto col = color.direct();

	vertex vert[5] =
	{
		{ from.x, from.y, 0.0f, 1.0f, col },
		{ to.x, from.y, 0.0f, 1.0f, col },
		{ to.x, to.y, 0.0f, 1.0f, col },
		{ from.x, to.y, 0.0f, 1.0f, col },
		{ from.x, from.y, 0.0f, 1.0f, col }
	};

	dev->SetTexture(0, nullptr);
	dev->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, &vert, sizeof(vertex));
}

void c_renderer::rect_linear_gradient(const Vector2D from, const Vector2D size, const Color color1, const Color color2, const bool horizontal) const
{
	const auto to = from + size;
	const auto col1 = color1.direct();
	const auto col2 = color2.direct();

	vertex vert[5] =
	{
		{ from.x, from.y, 0.0f, 1.0f, col2 },
	{ to.x, from.y, 0.0f, 1.0f, horizontal ? col2 : col1 },
	{ to.x, to.y, 0.0f, 1.0f, col2 },
	{ from.x, to.y, 0.0f, 1.0f, horizontal ? col1 : col2 },
	{ from.x, from.y, 0.0f, 1.0f, col1 }
	};

	dev->SetTexture(0, nullptr);
	dev->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, &vert, sizeof(vertex));
}

void c_renderer::rect_full_linear_gradient(const Vector2D from, const Vector2D size, Color color1, Color color2, Color color3,
	Color color4) const
{
	const auto to = from + size;
	const auto col1 = color1.direct();
	const auto col2 = color2.direct();
	const auto col3 = color3.direct();
	const auto col4 = color4.direct();

	vertex vert[5] = {
	{ from.x, from.y, 0.0f, 1.0f, col1 },
	{ to.x, from.y, 0.0f, 1.0f, col2 },
	{ to.x, to.y, 0.0f, 1.0f, col3 },
	{ from.x, to.y, 0.0f, 1.0f, col4 },
	{ from.x, from.y, 0.0f, 1.0f, col1 }
	};

	dev->SetTexture(0, nullptr);
	dev->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, &vert, sizeof(vertex));
}


void c_renderer::loki_gradient(const Vector2D from, const Vector2D size, const Color color1,
	const Color color2, const Color color3, const Color color4 ) const
{
	const auto to = from + size;
	const auto col1 = color1.direct();
	const auto col2 = color2.direct();
	const auto col3 = color3.direct();
	const auto col4 = color4.direct();

	vertex vert[4] =
	{
		{ from.x, from.y, 0.0f, 1.0f, col1 },
	{ to.x, from.y, 0.0f, 1.0f, col2 },
	{ from.x, to.y, 0.0f, 1.0f, col3 },
	{ to.x, to.y, 0.0f, 1.0f, col4 }
	};

	dev->SetTexture(0, nullptr);
	dev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &vert, sizeof(vertex));
}

void c_renderer::rect_filled(const Vector2D from, const Vector2D size, const Color color) const
{
	const auto to = from + size;
	const auto col = color.direct();

	vertex vert[4] =
	{
		{ from.x, from.y, 0.0f, 1.0f, col },
	{ to.x, from.y, 0.0f, 1.0f, col },
	{ from.x, to.y, 0.0f, 1.0f, col },
	{ to.x, to.y, 0.0f, 1.0f, col }
	};

	dev->SetTexture(0, nullptr);
	dev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &vert, sizeof(vertex));
}

void c_renderer::rect_filled_linear_gradient(const Vector2D from, const Vector2D size, const Color color1,
	const Color color2, const bool horizontal) const
{
	const auto to = from + size;
	const auto col1 = color1.direct();
	const auto col2 = color2.direct();

	vertex vert[4] =
	{
		{ from.x, from.y, 0.0f, 1.0f, col1 },
	{ to.x, from.y, 0.0f, 1.0f, horizontal ? col2 : col1 },
	{ from.x, to.y, 0.0f, 1.0f, horizontal ? col1 : col2 },
	{ to.x, to.y, 0.0f, 1.0f, col2 }
	};

	dev->SetTexture(0, nullptr);
	dev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &vert, sizeof(vertex));
}

void c_renderer::rect_filled_radial_gradient(const Vector2D from, const Vector2D size, const Color color1,
	const Color color2)
{
	const auto center = from + size / 2.0f;
	const auto radius = (center - from).Length();

	D3DVIEWPORT9 new_port;
	new_port.X = static_cast<uint32_t>(from.x);
	new_port.Y = static_cast<uint32_t>(from.y);
	new_port.Width = static_cast<uint32_t>(size.x);
	new_port.Height = static_cast<uint32_t>(size.y);

	dev->SetViewport(&new_port);
	circle_filled_radial_gradient(center, radius, color1, color2);
	dev->SetViewport(&port);
}

void c_renderer::rect_filled_diamond_gradient(const Vector2D from, const Vector2D size, const Color color1,
	const Color color2) const
{
	const auto to = from + size;
	const auto col1 = color1.direct();
	const auto col2 = color2.direct();

	vertex vert[6] =
	{
		{ (from.x + to.x) / 2.0f, (from.y + to.y) / 2.0f, 0.0f, 1.0f, col2 },
	{ from.x, from.y, 0.0f, 1.0f, col1 },
	{ to.x, from.y, 0.0f, 1.0f, col1 },
	{ to.x, to.y, 0.0f, 1.0f, col1 },
	{ from.x, to.y, 0.0f, 1.0f, col1 },
	{ from.x, from.y, 0.0f, 1.0f, col1 }
	};

	dev->SetTexture(0, nullptr);
	dev->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 5, &vert, sizeof(vertex));
}

void c_renderer::parallelogram(const Vector2D from, const Vector2D size, Color color, const uint8_t side, const float radius) const
{
	const auto to = from + size;
	const auto col = color.direct();

	vertex vert[5] =
	{
		{ from.x + (side != 1 ? radius : 0.0f), from.y, 0.0f, 1.0f, col },
	{ to.x, from.y, 0.0f, 1.0f, col },
	{ to.x - (side != 2 ? radius : 0.0f), to.y, 0.0f, 1.0f, col },
	{ from.x, to.y, 0.0f, 1.0f, col },
	{ from.x + (side != 1 ? radius : 0.0f), from.y, 0.0f, 1.0f, col }
	};

	dev->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
	dev->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, TRUE);

	dev->SetTexture(0, nullptr);
	dev->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, &vert, sizeof(vertex));

	dev->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, FALSE);
	dev->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, FALSE);
}

void c_renderer::parallelogram_filled_linear_gradient(const Vector2D from, const Vector2D size, Color color1,
	Color color2, const uint8_t side, const bool horizontal, const float radius) const
{
	const auto to = from + size;
	const auto col1 = color1.direct();
	const auto col2 = color2.direct();

	vertex vert[4] =
	{
		{ from.x + (side != 1 ? radius : 0.0f), from.y, 0.0f, 1.0f, col1 },
	{ to.x, from.y, 0.0f, 1.0f, horizontal ? col2 : col1 },
	{ from.x, to.y, 0.0f, 1.0f, horizontal ? col1 : col2 },
	{ to.x - (side != 2 ? radius : 0.0f), to.y, 0.0f, 1.0f, col2 }
	};

	dev->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
	dev->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, TRUE);

	dev->SetTexture(0, nullptr);
	dev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &vert, sizeof(vertex));

	dev->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, FALSE);
	dev->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, FALSE);
}

void c_renderer::triangle(const Vector2D pos1, const Vector2D pos2, const Vector2D pos3, const Color color) const
{
	const auto col = color.direct();

	vertex vert[4] =
	{
		{ pos1.x, pos1.y, 0.0f, 1.0f, col },
	{ pos2.x, pos2.y, 0.0f, 1.0f, col },
	{ pos3.x, pos3.y, 0.0f, 1.0f, col },
	{ pos1.x, pos1.y, 0.0f, 1.0f, col }
	};

	dev->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
	dev->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, TRUE);

	dev->SetTexture(0, nullptr);
	dev->DrawPrimitiveUP(D3DPT_LINESTRIP, 3, &vert, sizeof(vertex));

	dev->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, FALSE);
	dev->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, FALSE);
}

void c_renderer::triangle_linear_gradient(const Vector2D pos1, const Vector2D pos2, const Vector2D pos3, Color color1, Color color2, Color color3) const
{
	const auto col1 = color1.direct();
	const auto col2 = color2.direct();
	const auto col3 = color3.direct();

	vertex vert[4] =
	{
		{ pos1.x, pos1.y, 0.0f, 1.0f, col1 },
	{ pos2.x, pos2.y, 0.0f, 1.0f, col2 },
	{ pos3.x, pos3.y, 0.0f, 1.0f, col3 },
	{ pos1.x, pos1.y, 0.0f, 1.0f, col1 }
	};

	dev->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
	dev->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, TRUE);

	dev->SetTexture(0, nullptr);
	dev->DrawPrimitiveUP(D3DPT_LINESTRIP, 3, &vert, sizeof(vertex));

	dev->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, FALSE);
	dev->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, FALSE);
}

void c_renderer::triangle_filled(const Vector2D pos1, const Vector2D pos2, const Vector2D pos3, const Color color) const
{
	const auto col = color.direct();

	vertex vert[4] =
	{
		{ pos1.x, pos1.y, 0.0f, 1.0f, col },
	{ pos2.x, pos2.y, 0.0f, 1.0f, col },
	{ pos3.x, pos3.y, 0.0f, 1.0f, col }
	};

	dev->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
	dev->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, TRUE);

	dev->SetTexture(0, nullptr);
	dev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 1, &vert, sizeof(vertex));

	dev->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, FALSE);
	dev->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, FALSE);
}

void c_renderer::triangle_filled_linear_gradient(const Vector2D pos1, const Vector2D pos2, const Vector2D pos3,
	const Color color1, const Color color2, const Color color3) const
{
	const auto col1 = color1.direct();
	const auto col2 = color2.direct();
	const auto col3 = color3.direct();

	vertex vert[4] =
	{
		{ pos1.x, pos1.y, 0.0f, 1.0f, col1 },
	{ pos2.x, pos2.y, 0.0f, 1.0f, col2 },
	{ pos3.x, pos3.y, 0.0f, 1.0f, col3 }
	};

	dev->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
	dev->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, TRUE);

	dev->SetTexture(0, nullptr);
	dev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 1, &vert, sizeof(vertex));

	dev->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, FALSE);
	dev->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, FALSE);
}

void c_renderer::circle(const Vector2D center, const float radius, const Color color)
{
	const auto col = color.direct();
	build_lookup_table();

	vertex vert[points + 1] = {};

	for (auto i = 0; i <= points; i++)
		vert[i] =
	{
		center.x + radius * lookup_table[i].x,
		center.y - radius * lookup_table[i].y,
		0.0f,
		1.0f,
		col
	};

	dev->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
	dev->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, TRUE);

	dev->SetTexture(0, nullptr);
	dev->DrawPrimitiveUP(D3DPT_LINESTRIP, points, &vert, sizeof(vertex));

	dev->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, FALSE);
	dev->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, FALSE);
}

void c_renderer::circle_filled(const Vector2D center, const float radius, const Color color)
{
	const auto col = color.direct();
	build_lookup_table();

	vertex vert[points + 1] = {};

	for (auto i = 0; i <= points; i++)
		vert[i] =
	{
		center.x + radius * lookup_table[i].x,
		center.y - radius * lookup_table[i].y,
		0.0f,
		1.0f,
		col
	};

	dev->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
	dev->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, TRUE);

	dev->SetTexture(0, nullptr);
	dev->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, points, &vert, sizeof(vertex));

	dev->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, FALSE);
	dev->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, FALSE);
}

void c_renderer::circle_filled_radial_gradient(const Vector2D center, const float radius, const Color color1,
	const Color color2)
{
	const auto col1 = color1.direct();
	const auto col2 = color2.direct();
	build_lookup_table();

	vertex vert[points + 2] = {};

	for (auto i = 1; i <= points; i++)
		vert[i] =
	{
		center.x + radius * lookup_table[i].x,
		center.y - radius * lookup_table[i].y,
		0.0f,
		1.0f,
		col1
	};

	vert[0] = { center.x, center.y, 0.0f, 1.0f, col2 };
	vert[points + 1] = vert[1];

	dev->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
	dev->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, TRUE);

	dev->SetTexture(0, nullptr);
	dev->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, points, &vert, sizeof(vertex));

	dev->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, FALSE);
	dev->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, FALSE);
}



void c_renderer::text(const Vector2D pos, const char* str, Color color, const uint32_t font, const uint8_t flags)
{
	auto f = fonts.at(font);
	auto result = f.draw_string(std::roundf(pos.x), std::roundf(pos.y), color.direct(), str, flags);
}

Vector2D c_renderer::get_text_size(const char* str, const uint32_t font)
{
	SIZE size;
	fonts.at(font).get_text_extent(str, &size);
	return Vector2D(static_cast<float>(size.cx), static_cast<float>(size.cy));
}


void c_renderer::create_texture(void* src, const uint32_t size, LPDIRECT3DTEXTURE9* texture) const
{
	D3DXCreateTextureFromFileInMemory(dev, src, size, texture);
}

void c_renderer::create_sprite(LPD3DXSPRITE* sprite) const
{
	D3DXCreateSprite(dev, sprite);
}

void c_renderer::image(const Vector2D position, LPDIRECT3DTEXTURE9 texture, LPD3DXSPRITE sprite, const float scl, const float alpha)
{
	D3DXMATRIX world;
	D3DXMATRIX rotation;
	D3DXMATRIX scale;
	D3DXMATRIX translation;
	D3DXMatrixIdentity(&world);

	D3DXMatrixScaling(&scale, scl, scl, 1.f);
	D3DXMatrixRotationYawPitchRoll(&rotation, 0.f, 0.f, 0.f);
	D3DXMatrixTranslation(&translation, 0.f, 0.f, 0.f);
	world = rotation * scale * translation;

	D3DSURFACE_DESC img_info;
	texture->GetLevelDesc(0, &img_info);

	auto vec = D3DXVECTOR3(position.x, position.y, 0.f);
	sprite->SetTransform(&world);
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(texture, nullptr, nullptr, &vec, D3DCOLOR_RGBA(255, 255, 255, static_cast<int>(255 * alpha)));
	sprite->End();
}

Vector2D c_renderer::get_center() const
{
	return Vector2D(static_cast<float>(port.Width), static_cast<float>(port.Height)) / 2.f;
}

Vector2D c_renderer::get_viewport() const
{
	return Vector2D(static_cast<float>(port.Width), static_cast<float>(port.Height));
}

viewmatrix& c_renderer::world_to_screen_matrix()
{
	static auto view_matrix = *reinterpret_cast<uintptr_t*>(util::FindSignature("client.dll", "0F 10 05 ? ? ? ? 8D 85 ? ? ? ? B9") + 3) + 176;
	return *reinterpret_cast<viewmatrix*>(view_matrix);
	
}

void c_renderer::refresh_viewport()
{
	this->dev->GetViewport(&port);
}

void c_renderer::init_device_objects(IDirect3DDevice9* dev)
{
	this->dev = dev;
	this->dev->GetViewport(&port);

	for (auto& font : fonts)
	{
		font.second.init_device_objects(dev);
		font.second.restore_device_objects();
	}

	for (auto f : betterfonts) {
		f.second->InitDeviceObjects(dev);
		f.second->RestoreDeviceObjects();
	}
}

void c_renderer::invalidate_device_objects()
{
	dev = nullptr;

	for (auto& font : fonts)
		font.second.invalidate_device_objects();

	for (auto f : betterfonts) {
		f.second->InvalidateDeviceObjects();
	}

	for (auto& handler : reset_handlers)
		handler();
}

void c_renderer::setup_render_state() const
{
	dev->SetVertexShader(nullptr);
	dev->SetPixelShader(nullptr);
	dev->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE); // NOLINT
	dev->SetRenderState(D3DRS_LIGHTING, FALSE);
	dev->SetRenderState(D3DRS_FOGENABLE, FALSE);
	dev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	dev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	dev->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	dev->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE);
	dev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	dev->SetRenderState(D3DRS_STENCILENABLE, FALSE);

	dev->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, FALSE);
	dev->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, FALSE);

	dev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	dev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	dev->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);
	dev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	dev->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_INVDESTALPHA);
	dev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	dev->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ONE);

	dev->SetRenderState(D3DRS_SRGBWRITEENABLE, FALSE);
	dev->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN // NOLINT NOLINTNEXTLINE
		| D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA);

	dev->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	dev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	dev->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	dev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	dev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	dev->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	dev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_NONE);
	dev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_NONE);
}

void c_renderer::register_reset_handler(const std::function<void()> handler)
{
	reset_handlers.push_back(handler);
}

void c_renderer::build_lookup_table()
{
	if (!lookup_table.empty())
		return;

	for (auto i = 0; i <= points; i++)
		lookup_table.emplace_back(
		std::cos(2.f * D3DX_PI * (i / static_cast<float>(points))),
		std::sin(2.f * D3DX_PI * (i / static_cast<float>(points)))
		);

	for (auto lat = 0; lat < points_sphere_latitude; lat++)
	{
		const auto a1 = D3DX_PI * static_cast<float>(lat + 1) / (points_sphere_latitude + 1);
		const auto sin1 = sin(a1);
		const auto cos1 = cos(a1);

		for (auto lon = 0; lon <= points_sphere_longitude; lon++)
		{
			const auto a2 = 2 * D3DX_PI * static_cast<float>(lon) / points_sphere_longitude;
			const auto sin2 = sin(a2);
			const auto cos2 = cos(a2);

			lookup_sphere.emplace_back(sin1 * cos2, cos1, sin1 * sin2);
		}
	}
}






void c_renderer::scale(Vector2D& vec) const
{
	vec.x = (vec.x + 1.f) * port.Width / 2.f;
	vec.y = (-vec.y + 1.f) * port.Height / 2.f;
}

bool c_renderer::screen_transform(const Vector& in, Vector2D& out, viewmatrix& matrix) const
{
	out.x = matrix[0][0] * in.x + matrix[0][1] * in.y + matrix[0][2] * in.z + matrix[0][3];
	out.y = matrix[1][0] * in.x + matrix[1][1] * in.y + matrix[1][2] * in.z + matrix[1][3];

	const auto w = matrix[3][0] * in.x + matrix[3][1] * in.y + matrix[3][2] * in.z + matrix[3][3];

	if (w < 0.001f)
	{
		out.x *= 100000;
		out.y *= 100000;
		return false;
	}

	const auto invw = 1.0f / w;
	out.x *= invw;
	out.y *= invw;

	/*printf("%.1f - %.1f - %.1f - %.1f\n%.1f - %.1f - %.1f - %.1f\n%.1f - %.1f - %.1f - %.1f\n%.1f - %.1f - %.1f - %.1f\n\n",
		matrix[0][0], matrix[0][1], matrix[0][2], matrix[0][3],
		matrix[1][0], matrix[1][1], matrix[1][2], matrix[1][3],
		matrix[2][0], matrix[2][1], matrix[2][2], matrix[2][3],
		matrix[3][0], matrix[3][1], matrix[3][2], matrix[3][3]);*/
	scale(out);
	return true;
}
bool c_renderer::world2screen(Vector In, Vector& Out, matrix3x4t matrix)
{
	matrix3x4t ViewMatrix = matrix;

	Out.x = ViewMatrix.matrix[0] * In.x + ViewMatrix.matrix[1] * In.y + ViewMatrix.matrix[2] * In.z + ViewMatrix.matrix[3];
	Out.y = ViewMatrix.matrix[4] * In.x + ViewMatrix.matrix[5] * In.y + ViewMatrix.matrix[6] * In.z + ViewMatrix.matrix[7];
	Out.z = ViewMatrix.matrix[12] * In.x + ViewMatrix.matrix[13] * In.y + ViewMatrix.matrix[14] * In.z + ViewMatrix.matrix[15];
	if (Out.z < 0.01f) return false;
	float Inverse = 1.f / Out.z;
	Out.x *= Inverse;
	Out.y *= Inverse;

	double X = port.Width / 2;
	double Y = port.Height / 2;
	X += 0.5 * Out.x * port.Width + 0.5;
	Y -= 0.5 * Out.y * port.Height + 0.5;
	Out.x = (float)X;
	Out.y = (float)Y;
	if (Out.x > port.Width || Out.x < 0 || Out.y > port.Height || Out.y < 0)return false;
	return true;
}
bool c_renderer::is_on_screen(const Vector& in, const float width, viewmatrix& matrix) const
{
	auto out = Vector2D(matrix[0][0] * in.x + matrix[0][1] * in.y + matrix[0][2] * in.z + matrix[0][3],
		matrix[1][0] * in.x + matrix[1][1] * in.y + matrix[1][2] * in.z + matrix[1][3]);

	const auto w = matrix[3][0] * in.x + matrix[3][1] * in.y + matrix[3][2] * in.z + matrix[3][3];

	if (w < 0.001f)
	{
		out.x *= 100000;
		out.y *= 100000;
		return false;
	}

	const auto invw = 1.0f / w;
	out.x *= invw;
	out.y *= invw;

	scale(out);
	return !(out.x - width > port.Width || out.x + width < 1.f);
}

