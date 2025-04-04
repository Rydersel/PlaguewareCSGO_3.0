#include "c_font.h"
#include <utility>
#include <cmath>
#include <cfenv>

c_font::c_font() : height(0), flags(0), weight(0), heighest_char(0), dev(nullptr), texture(nullptr),
vertex_buffer(nullptr), text_width(0), text_height(0), text_scale(0), spacing(0), saved(nullptr),
draw(nullptr), line_height(0) {}

c_font::c_font(std::string font, const uint32_t height, const uint32_t weight, const uint32_t highest_char, const uint32_t flags) : font(
	std::
	move(font)), height(height),
	flags(flags), weight(weight),
	heighest_char(highest_char),
	dev(nullptr), texture(nullptr),
	vertex_buffer(nullptr),
	text_width(0), text_height(0),
	text_scale(0), spacing(0),
	saved(nullptr), draw(nullptr),
	line_height(0)
{
	text_coords.resize(highest_char - 32);

	for (auto& coord : text_coords)
		coord.resize(4);
}

c_font::~c_font()
{
	delete_device_objects();
}

HRESULT c_font::init_device_objects(IDirect3DDevice9 * dev)
{
	if (!dev)
		return E_FAIL;

	this->dev = dev;

	this->text_scale = 1.0f;

	if (this->height > 60)
		this->text_width = this->text_height = 8192;
	else if (this->height > 30)
		this->text_width = this->text_height = 4096;
	else if (this->height > 15)
		this->text_width = this->text_height = 2048;
	else
		this->text_width = this->text_height = 1024;

	D3DCAPS9 d3d_caps;
	this->dev->GetDeviceCaps(&d3d_caps);

	if (this->text_width > d3d_caps.MaxTextureWidth)
	{
		this->text_scale = static_cast<float>(d3d_caps.MaxTextureWidth) / static_cast<float>(this->text_width);
		this->text_width = this->text_height = d3d_caps.MaxTextureWidth;
	}

	const uint32_t hr = this->dev->CreateTexture(this->text_width, this->text_height, 1, D3DUSAGE_DYNAMIC, D3DFMT_A4R4G4B4,
		D3DPOOL_DEFAULT, &this->texture, nullptr);

	if (FAILED(hr))
		return hr;

	uint32_t * bitmap_bits;
	BITMAPINFO bmi;
	ZeroMemory(&bmi.bmiHeader, sizeof(BITMAPINFOHEADER));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = static_cast<int>(this->text_width);
	bmi.bmiHeader.biHeight = -static_cast<int>(this->text_height);
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biBitCount = 32;

	const auto dc = CreateCompatibleDC(nullptr);
	const auto bit_map = CreateDIBSection(dc, &bmi, DIB_RGB_COLORS,
		reinterpret_cast<void**>(&bitmap_bits), nullptr, 0);

	if (dc == nullptr)
		return E_FAIL;

	if (bit_map == nullptr)
		return E_FAIL;

	SetMapMode(dc, MM_TEXT);

	//const uint32_t height = -MulDiv(this->height, static_cast<uint32_t>(dpi * this->text_scale), 72);
	const auto font = CreateFont(this->height, 0, 0, 0, this->weight, this->flags,
		FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY,
		VARIABLE_PITCH, this->font.c_str());

	if (!font)
		return E_FAIL;

	const auto old = SelectObject(dc, bit_map);
	const auto font_old = SelectObject(dc, font);

	SetTextColor(dc, RGB(255, 255, 255));
	SetBkColor(dc, 0);
	SetTextAlign(dc, TA_TOP);

	uint32_t y = 0;
	wchar_t str[2] = L" ";
	SIZE size;

	GetTextExtentPoint32W(dc, L" ", 1, &size);
	auto x = this->spacing = static_cast<uint32_t>(ceil(size.cy * 0.3f));

	for (uint32_t c = 32; c < heighest_char - 1; c++)
	{
		str[0] = c;
		GetTextExtentPoint32W(dc, str, 1, &size);

		if (static_cast<uint32_t>(x + size.cx + this->spacing) > this->text_width)
		{
			x = this->spacing;
			y += size.cy + 1;
		}

		ExtTextOutW(dc, x + 0, y + 0, ETO_OPAQUE, nullptr, str, 1, nullptr);

		this->text_coords[c - 32][0] = static_cast<float>(x + 0 - this->spacing) / this->text_width;
		this->text_coords[c - 32][1] = static_cast<float>(y + 0 + 0) / this->text_height;
		this->text_coords[c - 32][2] = static_cast<float>(x + size.cx + this->spacing) / this->text_width;
		this->text_coords[c - 32][3] = static_cast<float>(y + size.cy + 0) / this->text_height;

		x += size.cx + 2 * this->spacing;
	}

	D3DLOCKED_RECT d3dlr;
	this->texture->LockRect(0, &d3dlr, nullptr, 0);
	auto dest_row = static_cast<uint8_t*>(d3dlr.pBits);

	for (y = 0; y < this->text_height; y++)
	{
		auto dest = reinterpret_cast<uint16_t*>(dest_row);
		for (x = 0; x < this->text_width; x++)
		{
			const auto alpha = static_cast<uint8_t>((bitmap_bits[this->text_width * y + x] & 0xFF) >> 4);
			*dest++ = alpha > 0 ? static_cast<uint16_t>((alpha << 12) | 0x0fff) : 0;
		}
		dest_row += d3dlr.Pitch;
	}

	this->texture->UnlockRect(0);
	SelectObject(dc, old);
	SelectObject(dc, font_old);
	DeleteObject(bit_map);
	DeleteObject(font);
	DeleteDC(dc);

	this->get_text_extent("IQ", &size);
	this->line_height = static_cast<float>(size.cy);
	return S_OK;
}

HRESULT c_font::restore_device_objects()
{
	HRESULT hr;

	if (FAILED(hr = this->dev->CreateVertexBuffer(max_vertices * sizeof(font2dvertex),
		D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC, 0,
		D3DPOOL_DEFAULT, &this->vertex_buffer, nullptr)))
		return hr;

	for (uint8_t which = 0; which < 2; which++)
	{
		this->dev->BeginStateBlock();
		this->dev->SetTexture(0, this->texture);

		if (d3d_font_zenable& this->flags)
			this->dev->SetRenderState(D3DRS_ZENABLE, true);
		else
			this->dev->SetRenderState(D3DRS_ZENABLE, false);

		this->dev->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		this->dev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		this->dev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		this->dev->SetRenderState(D3DRS_ALPHATESTENABLE, true);
		this->dev->SetRenderState(D3DRS_ALPHAREF, 0x08);
		this->dev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
		this->dev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		this->dev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		this->dev->SetRenderState(D3DRS_STENCILENABLE, false);
		this->dev->SetRenderState(D3DRS_CLIPPING, true);
		this->dev->SetRenderState(D3DRS_CLIPPLANEENABLE, false);
		this->dev->SetRenderState(D3DRS_VERTEXBLEND, D3DVBF_DISABLE);
		this->dev->SetRenderState(D3DRS_INDEXEDVERTEXBLENDENABLE, false);
		this->dev->SetRenderState(D3DRS_FOGENABLE, false);
		this->dev->SetRenderState(D3DRS_COLORWRITEENABLE,
			D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN |
			D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA);
		this->dev->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		this->dev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		this->dev->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		this->dev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		this->dev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		this->dev->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
		this->dev->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
		this->dev->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
		this->dev->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
		this->dev->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
		this->dev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
		this->dev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
		this->dev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);

		if (which == 0)
			this->dev->EndStateBlock(&this->saved);
		else
			this->dev->EndStateBlock(&this->draw);
	}

	return S_OK;
}

HRESULT c_font::invalidate_device_objects()
{
	safe_release(this->vertex_buffer);
	safe_release(this->saved);
	safe_release(this->draw);
	safe_release(this->texture);

	return S_OK;
}

HRESULT c_font::delete_device_objects()
{
	this->dev = nullptr;

	return S_OK;
}

HRESULT c_font::get_text_extent(const char* text, SIZE * size)
{
	if (!text || !size)
		return E_FAIL;

	auto row_width = 0.0f;
	const auto row_height = (this->text_coords[0][3] - this->text_coords[0][1]) * this->text_height;
	auto width = 0.0f;
	auto height = row_height;

	while (*text)
	{
		const auto c = static_cast<uint32_t>(*text++);

		if (c == '\n')
		{
			row_width = 0.0f;
			height += row_height;
		}

		if (c - 32 < 0 || c - 32 >= heighest_char - 32)
			continue;

		const auto x1 = this->text_coords[c - 32][0];
		const auto x2 = this->text_coords[c - 32][2];

		row_width += (x2 - x1) * this->text_width - 2 * this->spacing;

		if (row_width > width)
			width = row_width;
	}

	size->cx = static_cast<int>(width) - 1;
	size->cy = static_cast<int>(height) - 1;
	return S_OK;
}

HRESULT c_font::draw_string(float x, float y, uint32_t color, const char* text, uint8_t flags)
{
	if (!this->dev || !text)
		return E_FAIL;

	this->saved->Capture();
	this->draw->Apply();
	this->dev->SetFVF(d3dfvf_font2dvertex);
	this->dev->SetPixelShader(nullptr);
	this->dev->SetStreamSource(0, this->vertex_buffer, 0, sizeof(font2dvertex));

	this->dev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	this->dev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	if (flags & centered_x)
	{
		SIZE sz;
		get_text_extent(text, &sz);
		x -= static_cast<float>(sz.cx) * 0.5f;
		x = std::roundf(x) + 1;
	}

	if (flags & centered_y)
	{
		SIZE sz;
		get_text_extent(text, &sz);
		y -= static_cast<float>(sz.cy) * 0.5f;
		y = std::roundf(y) + 1;
	}

	if (flags& right_aligned)
	{
		SIZE sz;
		get_text_extent(text, &sz);
		x -= static_cast<float>(sz.cx);
		x = std::roundf(x) + 1;
	}

	x -= this->spacing;
	const auto start_x = x;

	font2dvertex* vertices = nullptr;
	uint32_t num_triangles = 0;
	this->vertex_buffer->Lock(0, 0, reinterpret_cast<void**>(&vertices), D3DLOCK_DISCARD);

	while (*text)
	{
		const auto c = static_cast<uint32_t>(*text++);

		if (c == '\n')
		{
			x = start_x;
			y += (this->text_coords[0][3] - this->text_coords[0][1]) * this->text_height;
		}

		if (c - 32 < 0 || c - 32 >= heighest_char - 32)
			continue;

		const auto x1 = this->text_coords[c - 32][0];
		const auto y1 = this->text_coords[c - 32][1];
		const auto x2 = this->text_coords[c - 32][2];
		const auto y2 = this->text_coords[c - 32][3];

		const auto w = (x2 - x1) * this->text_width / this->text_scale;
		const auto h = (y2 - y1) * this->text_height / this->text_scale;

		if (c != ' ')
		{
			auto shadowcol = D3DCOLOR_ARGB(color >> 24 & 255, 0, 0, 0);
			if (flags & drop_shadow)
			{
				*vertices++ = { {x + 0 + 0.5f, y + h + 0.5f, 1.0f, 1.0f}, shadowcol, x1, y2 };
				*vertices++ = { {x + 0 + 0.5f, y + 0 + 0.5f, 1.0f, 1.0f}, shadowcol, x1, y1 };
				*vertices++ = { {x + w + 0.5f, y + h + 0.5f, 1.0f, 1.0f}, shadowcol, x2, y2 };
				*vertices++ = { {x + w + 0.5f, y + 0 + 0.5f, 1.0f, 1.0f}, shadowcol, x2, y1 };
				*vertices++ = { {x + w + 0.5f, y + h + 0.5f, 1.0f, 1.0f}, shadowcol, x2, y2 };
				*vertices++ = { {x + 0 + 0.5f, y + 0 + 0.5f, 1.0f, 1.0f}, shadowcol, x1, y1 };
				num_triangles += 2;

				*vertices++ = { {x + 0 - 1.f, y + h + 0.5f, 1.0f, 1.0f}, shadowcol, x1, y2 };
				*vertices++ = { {x + 0 - 1.f, y + 0 + 0.5f, 1.0f, 1.0f}, shadowcol, x1, y1 };
				*vertices++ = { {x + w - 1.f, y + h + 0.5f, 1.0f, 1.0f}, shadowcol, x2, y2 };
				*vertices++ = { {x + w - 1.f, y + 0 + 0.5f, 1.0f, 1.0f}, shadowcol, x2, y1 };
				*vertices++ = { {x + w - 1.f, y + h + 0.5f, 1.0f, 1.0f}, shadowcol, x2, y2 };
				*vertices++ = { {x + 0 - 1.f, y + 0 + 0.5f, 1.0f, 1.0f}, shadowcol, x1, y1 };
				num_triangles += 2;

				*vertices++ = { {x + 0 - 1.f, y + h - 1.f, 1.0f, 1.0f}, shadowcol, x1, y2 };
				*vertices++ = { {x + 0 - 1.f, y + 0 - 1.f, 1.0f, 1.0f}, shadowcol, x1, y1 };
				*vertices++ = { {x + w - 1.f, y + h - 1.f, 1.0f, 1.0f}, shadowcol, x2, y2 };
				*vertices++ = { {x + w - 1.f, y + 0 - 1.f, 1.0f, 1.0f}, shadowcol, x2, y1 };
				*vertices++ = { {x + w - 1.f, y + h - 1.f, 1.0f, 1.0f}, shadowcol, x2, y2 };
				*vertices++ = { {x + 0 - 1.f, y + 0 - 1.f, 1.0f, 1.0f}, shadowcol, x1, y1 };
				num_triangles += 2;

				*vertices++ = { {x + 0 + 0.5f, y + h - 0.5f, 1.0f, 1.0f}, shadowcol, x1, y2 };
				*vertices++ = { {x + 0 + 0.5f, y + 0 - 0.5f, 1.0f, 1.0f}, shadowcol, x1, y1 };
				*vertices++ = { {x + w + 0.5f, y + h - 0.5f, 1.0f, 1.0f}, shadowcol, x2, y2 };
				*vertices++ = { {x + w + 0.5f, y + 0 - 0.5f, 1.0f, 1.0f}, shadowcol, x2, y1 };
				*vertices++ = { {x + w + 0.5f, y + h - 0.5f, 1.0f, 1.0f}, shadowcol, x2, y2 };
				*vertices++ = { {x + 0 + 0.5f, y + 0 - 0.5f, 1.0f, 1.0f}, shadowcol, x1, y1 };
				num_triangles += 2;
			}

			*vertices++ = { {x + 0 - 0.5f, y + h - 0.5f, 1.0f, 1.0f}, color, x1, y2 };
			*vertices++ = { {x + 0 - 0.5f, y + 0 - 0.5f, 1.0f, 1.0f}, color, x1, y1 };
			*vertices++ = { {x + w - 0.5f, y + h - 0.5f, 1.0f, 1.0f}, color, x2, y2 };
			*vertices++ = { {x + w - 0.5f, y + 0 - 0.5f, 1.0f, 1.0f}, color, x2, y1 };
			*vertices++ = { {x + w - 0.5f, y + h - 0.5f, 1.0f, 1.0f}, color, x2, y2 };
			*vertices++ = { {x + 0 - 0.5f, y + 0 - 0.5f, 1.0f, 1.0f}, color, x1, y1 };
			num_triangles += 2;

			if (num_triangles * 3 > (max_vertices - 6))
			{
				this->vertex_buffer->Unlock();
				this->dev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, num_triangles);
				vertices = nullptr;
				this->vertex_buffer->Lock(0, 0, reinterpret_cast<void**>(&vertices), D3DLOCK_DISCARD);
				num_triangles = 0L;
			}
		}

		x += w - 2 * this->spacing;
	}

	this->vertex_buffer->Unlock();
	if (num_triangles > 0)
		this->dev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, num_triangles);

	this->saved->Apply();
	return S_OK;
}
