#include "../utils.h"
#include "../../sdk/interfaces.h"
#include "../../features/features.h"

std::mutex mutex;

namespace render {
	void init() {
		ImGui::CreateContext();

		ImGui_ImplWin32_Init(input::m_hwnd);
		ImGui_ImplDX9_Init(interfaces::d3d_device);

		m_draw_list = std::make_shared<ImDrawList>(ImGui::GetDrawListSharedData());
		m_temp_draw_list = std::make_shared<ImDrawList>(ImGui::GetDrawListSharedData());

		auto& io = ImGui::GetIO();
		auto& style = ImGui::GetStyle();

		style.WindowMinSize = ImVec2(500, 450);

		ImFontConfig tahoma14;
		tahoma14.RasterizerFlags = ImGuiFreeType::ForceAutoHint;
		fonts::m_tahoma14 = io.Fonts->AddFontFromFileTTF(_("C:\\Windows\\Fonts\\Tahoma.ttf"), 14.f, &tahoma14, io.Fonts->GetGlyphRangesCyrillic());

		ImGuiFreeType::BuildFontAtlas(io.Fonts);
	}

	vec2_t text(const std::string& txt, vec2_t pos, float size, const col_t& clr, ImFont* font, int flags) {
		if (!font->ContainerAtlas)
			return vec2_t();

		auto text_size = font->CalcTextSizeA(size, FLT_MAX, 0.f, txt.c_str());

		flags & FONT_CENTERED_X ? pos.x -= text_size.x * 0.5f : 0;

		flags & FONT_CENTERED_Y ? pos.y -= text_size.y * 0.5f : 0;

		m_draw_list->PushTextureID(font->ContainerAtlas->TexID);

		flags & FONT_DROP_SHADOW ? m_draw_list->AddText(font, size, ImVec2(pos.x + 1, pos.y + 1), col_t(clr.a()).direct(), txt.c_str()) : 0;

		if (flags & FONT_OUTLINE) {
			m_draw_list->AddText(font, size, ImVec2(pos.x + 1, pos.y + 1), col_t(clr.a()).direct(), txt.c_str());
			m_draw_list->AddText(font, size, ImVec2(pos.x - 1, pos.y - 1), col_t(clr.a()).direct(), txt.c_str());
			m_draw_list->AddText(font, size, ImVec2(pos.x + 1, pos.y - 1), col_t(clr.a()).direct(), txt.c_str());
			m_draw_list->AddText(font, size, ImVec2(pos.x - 1, pos.y + 1), col_t(clr.a()).direct(), txt.c_str());
		}

		m_draw_list->AddText(font, size, ImVec2(pos.x, pos.y), clr.direct(), txt.c_str());

		m_draw_list->PopTextureID();

		return vec2_t(text_size.x, text_size.y);
	}

	void line(const vec2_t& from, const vec2_t& to, const col_t& clr) {
		m_draw_list->AddLine(ImVec2(from.x, from.y), ImVec2(to.x, to.y), clr.direct());
	}

	void rect(const vec2_t& pos, const vec2_t& size, const col_t& clr) {
		m_draw_list->AddRect(ImVec2(pos.x, pos.y), ImVec2(pos.x + size.x, pos.y + size.y), clr.direct());
	}

	void rect_filled(const vec2_t& pos, const vec2_t& size, const col_t& clr) {
		m_draw_list->AddRectFilled(ImVec2(pos.x, pos.y), ImVec2(pos.x + size.x, pos.y + size.y), clr.direct());
	}

	void add_to_draw_list() {
		std::unique_lock<std::mutex> lock(mutex, std::try_to_lock);
		if (!lock.owns_lock())
			return;

		*ImGui::GetBackgroundDrawList() = *m_temp_draw_list;
	}

	void begin() {
		m_draw_list->Clear();
		m_draw_list->PushClipRectFullScreen();

		auto screen_size = ImGui::GetIO().DisplaySize;
		render::m_screen_size = vec2_t(screen_size.x, screen_size.y);

		// call ur visuals etc... here

		{
			std::unique_lock<std::mutex> lock(mutex);
			*m_temp_draw_list = *m_draw_list;
		}
	}

	void multi_rect(const std::vector<vec2_t> points, const col_t& clr) {
		m_draw_list->_Path.reserve(m_draw_list->_Path.Size + points.size() + 1);

		for (auto& point : points)
			m_draw_list->_Path.push_back(ImVec2(point.x, point.y));

		m_draw_list->AddPolyline(m_draw_list->_Path.Data, m_draw_list->_Path.Size, clr.direct(), true, 1.f);
		m_draw_list->_Path.Size = 0;
	}

	void multi_rect_filled(const std::vector<vec2_t> points, const col_t& clr) {
		m_draw_list->_Path.reserve(m_draw_list->_Path.Size + points.size() + 1);

		for (auto& point : points)
			m_draw_list->_Path.push_back(ImVec2(point.x, point.y));

		m_draw_list->AddConvexPolyFilled(m_draw_list->_Path.Data, m_draw_list->_Path.Size, clr.direct());
		m_draw_list->_Path.Size = 0;
	}

	bool world_to_screen(const vec3_t& in, vec2_t& out) {
		auto screen_transform = [](const vec3_t& in, vec2_t& out) -> bool {
			static const auto& matrix = *reinterpret_cast<v_matrix*>(*SIG("client.dll", "0F 10 05 ? ? ? ? 8D 85 ? ? ? ? B9").self_offset(0x3).cast<uintptr_t*>() + 0xB0);

			out.x = matrix[0][0] * in.x + matrix[0][1] * in.y + matrix[0][2] * in.z + matrix[0][3];
			out.y = matrix[1][0] * in.x + matrix[1][1] * in.y + matrix[1][2] * in.z + matrix[1][3];

			auto w = matrix[3][0] * in.x + matrix[3][1] * in.y + matrix[3][2] * in.z + matrix[3][3];

			if (w < 0.001f) {
				out.x *= 100000.f;
				out.y *= 100000.f;
				return true;
			}

			auto inv_w = 1.f / w;
			out.x *= inv_w;
			out.y *= inv_w;

			return false;
		};

		if (!screen_transform(in, out)) {
			out.x = (m_screen_size.x * 0.5f) + (out.x * m_screen_size.x) * 0.5f;
			out.y = (m_screen_size.y * 0.5f) - (out.y * m_screen_size.y) * 0.5f;
			return true;
		}

		return false;
	}

	vec2_t m_screen_size;

	std::shared_ptr<ImDrawList> m_draw_list;
	std::shared_ptr<ImDrawList> m_temp_draw_list;
}

namespace fonts {
	ImFont* m_tahoma14 = nullptr;
}