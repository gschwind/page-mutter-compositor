/*
 * Copyright (2017) Benoit Gschwind
 *
 * view_rebased.cxx is part of page-compositor.
 *
 * page-compositor is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * page-compositor is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with page-compositor.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "page-view-rebased.hxx"

#include "page-page.hxx"
#include "page-workspace.hxx"

namespace page {

view_rebased_t::_base_frame_t::~_base_frame_t()
{
//	xcb_destroy_window(_ctx->_dpy->xcb(), _window->id());
//	xcb_free_colormap(_ctx->_dpy->xcb(), _colormap);
//	_ctx->_page_windows.erase(_window->id());
}


view_rebased_t::_base_frame_t::_base_frame_t(page_t * ctx, xcb_visualid_t visual, uint8_t depth) :
	_ctx{ctx}
{
//
//	auto _dpy = _ctx->_dpy;
//	/**
//	 * Create the base window, window that will content managed window
//	 **/
//
//	xcb_visualid_t root_visual = _dpy->root_visual()->visual_id;
//	int root_depth = _dpy->find_visual_depth(_dpy->root_visual()->visual_id);
//
//	/**
//	 * If window visual is 32 bit (have alpha channel, and root do not
//	 * have alpha channel, use the window visual, otherwise always prefer
//	 * root visual.
//	 **/
//	if (depth == 32 and root_depth != 32) {
//		_visual = visual;
//		_depth = depth;
//	} else {
//		_visual = _dpy->default_visual_rgba()->visual_id;
//		_depth = 32;
//	}
//
//	/** if visual is 32 bits, this values are mandatory **/
//	_colormap = xcb_generate_id(_dpy->xcb());
//	xcb_create_colormap(_dpy->xcb(), XCB_COLORMAP_ALLOC_NONE, _colormap, _dpy->root(), _visual);
//
//	uint32_t value_mask = 0;
//	uint32_t value[4];
//
//	value_mask |= XCB_CW_BACK_PIXEL;
//	value[0] = _dpy->xcb_screen()->black_pixel;
//
//	value_mask |= XCB_CW_BORDER_PIXEL;
//	value[1] = _dpy->xcb_screen()->black_pixel;
//
//	value_mask |= XCB_CW_OVERRIDE_REDIRECT;
//	value[2] = True;
//
//	value_mask |= XCB_CW_COLORMAP;
//	value[3] = _colormap;
//
//	xcb_window_t base = xcb_generate_id(_dpy->xcb());
//	_ctx->_page_windows.insert(base);
//	xcb_create_window(_dpy->xcb(), _depth, base, _dpy->root(), -10, -10,
//			1, 1, 0, XCB_WINDOW_CLASS_INPUT_OUTPUT, _visual, value_mask,
//			value);
//	_window = _dpy->ensure_client_proxy(base);
}


view_rebased_t::view_rebased_t(tree_t * ref, client_managed_p client) :
	view_t{ref, client}
{
//	_client->_client_proxy->set_border_width(0);
//	_base = std::unique_ptr<_base_frame_t>{new _base_frame_t(_root->_ctx, _client->_client_proxy->visualid(), _client->_client_proxy->visual_depth())};
//	_base->_window->select_input(MANAGED_BASE_WINDOW_EVENT_MASK);
//	_grab_button_unsafe();
//	xcb_flush(_root->_ctx->_dpy->xcb());
}

view_rebased_t::view_rebased_t(view_rebased_t * src) :
	view_t{src->_root, src->_client},
	_base{std::move(src->_base)}, // Take the ownership
	_base_position{src->_base_position},
	_orig_position{src->_orig_position}
{

}

view_rebased_t::~view_rebased_t()
{
	release_client();
}

auto view_rebased_t::shared_from_this() -> view_rebased_p
{
	return static_pointer_cast<view_rebased_t>(tree_t::shared_from_this());
}

void view_rebased_t::_reconfigure_windows()
{
	auto _ctx = _root->_ctx;
	auto _dpy = _ctx->_display;

	if(not _is_client_owner())
		return;

	if (_is_visible and _root->is_enable()) {
		if(meta_window_is_fullscreen(_client->meta_window()))
			meta_window_unmake_fullscreen(_client->meta_window());
		meta_window_unminimize(_client->meta_window());
		meta_window_move_resize_frame(_client->_meta_window, FALSE, _client->_absolute_position.x, _client->_absolute_position.y, _client->_absolute_position.w, _client->_absolute_position.h);
		//clutter_actor_show(CLUTTER_ACTOR(_client->meta_window_actor()));
		log::printf("%s\n", _client->_absolute_position.to_string().c_str());
	} else {
		log::printf("minimize %p\n", _client->meta_window());
		meta_window_minimize(_client->meta_window());
	}

}

void view_rebased_t::_on_focus_change(client_managed_t * c)
{
//	if (_client->_has_focus) {
//		_client->net_wm_state_add(_NET_WM_STATE_FOCUSED);
//		_ungrab_button_unsafe();
//	} else {
//		_client->net_wm_state_remove(_NET_WM_STATE_FOCUSED);
//		_grab_button_unsafe();
//	}
}

void view_rebased_t::set_focus_state(bool is_focused)
{
//	view_t::set_focus_state(is_focused);
//	if (_client->_has_focus) {
//		_ungrab_button_unsafe();
//	} else {
//		_grab_button_unsafe();
//	}
}

void view_rebased_t::update_layout(time64_t const time)
{
	if (not _is_visible)
		return;

//	/** update damage_cache **/
//	region dmg = _client_view->get_damaged();
//	dmg.translate(_base_position.x, _base_position.y);
//	_damage_cache += dmg;
//	_client_view->clear_damaged();
}

void view_rebased_t::render(cairo_t * cr, region const & area)
{
//	auto pix = _client_view->get_pixmap();
//	if(pix == nullptr)
//		return;
//
//	cairo_save(cr);
//	cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
//	cairo_set_source_surface(cr, pix->get_cairo_surface(),
//			_base_position.x, _base_position.y);
//	region r = get_visible_region() & area;
//	for (auto &i : r.rects()) {
//		cairo_clip(cr, i);
//		cairo_mask_surface(cr, pix->get_cairo_surface(),
//				_base_position.x, _base_position.y);
//	}
//	cairo_restore(cr);
}

void view_rebased_t::on_workspace_enable()
{
	acquire_client();
	reconfigure();
}

void view_rebased_t::on_workspace_disable()
{
	auto _ctx = _root->_ctx;
	auto _dpy = _root->_ctx->dpy();
	if (_is_client_owner()) {
		log::printf("minimize %p\n", _client->meta_window());
		meta_window_minimize(_client->meta_window());
	}
}

auto view_rebased_t::get_default_view() const -> ClutterActor *
{
	return CLUTTER_ACTOR(_client->_meta_window_actor);
}

} /* namespace page */
