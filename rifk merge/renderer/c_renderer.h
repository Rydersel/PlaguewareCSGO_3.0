#pragma once

#include "../../includes.hpp"



#include "c_font.h"
#include "../security/fnv1a.h"
#include <unordered_map>

#include <functional>

#include <map>

class CD3DFont;




class c_renderer
{
	struct vertex {
		float x, y, z, rhw;
		uint32_t color;
	};

public:
	c_renderer(IDirect3DDevice9* dev);

	void line(Vector2D from, Vector2D to, Color color) const;

	void rect(Vector2D from, Vector2D size, Color color) const;
	void rect_linear_gradient(Vector2D from, Vector2D size, Color color1, Color color2, bool horizontal) const;
	void rect_full_linear_gradient(Vector2D from, Vector2D size, Color color1, Color color2, Color color3, Color color4) const;
	void loki_gradient(const Vector2D from, const Vector2D size, const Color color1, const Color color2, const Color color3, const Color color4) const;
	void rect_filled(Vector2D from, Vector2D size, Color color) const;
	void rect_filled_linear_gradient(Vector2D from, Vector2D size, Color color1, Color color2, bool horizontal = false) const;
	void rect_filled_radial_gradient(Vector2D from, Vector2D size, Color color1, Color color2);
	void rect_filled_diamond_gradient(Vector2D from, Vector2D size, Color color1, Color color2) const;

	void parallelogram(Vector2D from, Vector2D size, Color color, uint8_t side = 0, float radius = 8.f) const;
	void parallelogram_filled_linear_gradient(Vector2D from, Vector2D size, Color color1, Color color2,
		uint8_t side = 0, bool horizontal = false, float radius = 8.f) const;

	void triangle(Vector2D pos1, Vector2D pos2, Vector2D pos3, Color color) const;
	void triangle_linear_gradient(Vector2D pos1, Vector2D pos2, Vector2D pos3, Color color1,
		Color color2, Color color3) const;
	void triangle_filled(Vector2D pos1, Vector2D pos2, Vector2D pos3, Color color) const;
	void triangle_filled_linear_gradient(Vector2D pos1, Vector2D pos2, Vector2D pos3, Color color1,
		Color color2, Color color3) const;

	void circle(Vector2D center, float radius, Color color);
	void circle_filled(Vector2D center, float radius, Color color);
	void circle_filled_radial_gradient(Vector2D center, float radius, Color color1, Color color2);

	void text(Vector2D pos, const char* str, Color color, uint32_t font = default_font, uint8_t flags = 0);
	Vector2D get_text_size(const char* str, uint32_t font);

	//void ball(Vector center, float radius, matrix3x4 transform, Color col, viewmatrix& matrix);

	void create_texture(void* src, uint32_t size, LPDIRECT3DTEXTURE9* texture) const;
	void create_sprite(LPD3DXSPRITE* sprite) const;
	static void image(Vector2D position, LPDIRECT3DTEXTURE9 texture, LPD3DXSPRITE sprite, float scl = 1.f, float alpha = 1.f);

	inline void scale(Vector2D& vec) const;
	Vector2D get_center() const;

	Vector2D get_viewport() const;

	viewmatrix& world_to_screen_matrix();
	bool screen_transform(const Vector& in, Vector2D& out, viewmatrix& matrix) const;

	bool world2screen(Vector In, Vector& Out, matrix3x4t matrix);

	
	bool is_on_screen(const Vector& in, float width, viewmatrix& matrix) const;

	
	void refresh_viewport();
	void init_device_objects(IDirect3DDevice9* dev);
	void invalidate_device_objects();
	void setup_render_state() const;
	void register_reset_handler(std::function<void()> handler);

private:
	static constexpr auto points = 64;
	static constexpr auto points_sphere_latitude = 16;
	static constexpr auto points_sphere_longitude = 24;
	static constexpr auto default_font = fnv1a("pro13");

	IDirect3DDevice9* dev {};
	D3DVIEWPORT9 port {};
	std::vector<Vector2D> lookup_table;
	std::vector<Vector> lookup_sphere;
	std::unordered_map<uint32_t, c_font> fonts;
	std::unordered_map<uint32_t, CD3DFont*> betterfonts;
	std::vector<std::function<void()>> reset_handlers;

	void build_lookup_table();
};


inline c_renderer d3d_shonax_render(m_device());
