/*
 * Copyright (2017) Benoit Gschwind
 *
 * view_notebook.cxx is part of page-compositor.
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

#include "page-view-notebook.hxx"

#include "page-view.hxx"
#include "page-client-managed.hxx"
#include "page-workspace.hxx"
#include "page-page.hxx"
#include "page-grab-handlers.hxx"

namespace page {

view_notebook_t::view_notebook_t(tree_t * ref, client_managed_p client) :
	view_rebased_t{ref, client}
{
	// disable move/resizes.
	g_connect(_client->meta_window(), "position-changed", &view_notebook_t::_handler_position_changed);
	g_connect(_client->meta_window(), "size-changed", &view_notebook_t::_handler_size_changed);

	g_object_set(G_OBJECT(_client->meta_window_actor()), "no-shadow", TRUE, NULL);
//	meta_window_maximize(_client->meta_window(), META_MAXIMIZE_BOTH);

}

view_notebook_t::view_notebook_t(view_rebased_t * src) :
	view_rebased_t{src}
{
	// disable move/resizes.
	g_connect(_client->meta_window(), "position-changed", &view_notebook_t::_handler_position_changed);
	g_connect(_client->meta_window(), "size-changed", &view_notebook_t::_handler_size_changed);

	g_object_set(G_OBJECT(_client->meta_window_actor()), "no-shadow", TRUE, NULL);

}

view_notebook_t::~view_notebook_t()
{
	g_disconnect_from_obj(_client->meta_window());
}

auto view_notebook_t::shared_from_this() -> view_notebook_p
{
	return static_pointer_cast<view_notebook_t>(tree_t::shared_from_this());
}

bool view_notebook_t::is_iconic() const
{
	return not _is_visible;
}

bool view_notebook_t::has_focus() const
{
	return meta_window_has_focus(_client->meta_window());
}

auto view_notebook_t::title() const -> string const &
{
	return _client->title();
}

//auto view_notebook_t::icon() const -> shared_ptr<icon16>
//{
//	return _client->icon();
//}

void view_notebook_t::delete_window(xcb_timestamp_t t) {
	log::printf("request close for '%s'\n", title().c_str());
	_client->delete_window(t);
}

auto view_notebook_t::parent_notebook() -> notebook_p
{
	assert((_parent != nullptr) and (_parent->parent() != nullptr));
	return dynamic_pointer_cast<notebook_t>(_parent->parent()->shared_from_this());
}

void view_notebook_t::_handler_position_changed(MetaWindow * window)
{
	/* disable frame move */
	if (_is_client_owner())
		meta_window_move_frame(window, FALSE, _client->_absolute_position.x, _client->_absolute_position.y);
}

void view_notebook_t::_handler_size_changed(MetaWindow * window)
{
	/* disable frame resize */
	if (_is_client_owner())
		meta_window_move_resize_frame(window, FALSE, _client->_absolute_position.x, _client->_absolute_position.y, _client->_absolute_position.w, _client->_absolute_position.h);
}

void view_notebook_t::xxactivate(xcb_timestamp_t time)
{
	auto nbk = parent_notebook();
	nbk->activate(shared_from_this(), time);
}

void view_notebook_t::remove_this_view()
{
	auto nbk = parent_notebook();
	nbk->remove_view_notebook(shared_from_this());
}

void view_notebook_t::set_focus_state(bool is_focused)
{
	view_rebased_t::set_focus_state(is_focused);
	parent_notebook()->_client_focus_change(_client.get());
}

void view_notebook_t::reconfigure()
{
	auto _ctx = _root->_ctx;
	auto _dpy = _root->_ctx->dpy();

	_base_position.x = _client->_absolute_position.x;
	_base_position.y = _client->_absolute_position.y;
	_base_position.w = _client->_absolute_position.w;
	_base_position.h = _client->_absolute_position.h;

	_orig_position.x = 0;
	_orig_position.y = 0;
	_orig_position.w = _client->_absolute_position.w;
	_orig_position.h = _client->_absolute_position.h;

	_reconfigure_windows();

}

//auto view_notebook_t::button_press(xcb_button_press_event_t const * e) -> button_action_e {
//
//	if (e->event != _base->id() and e->event != _client->_client_proxy->id()) {
//		return BUTTON_ACTION_CONTINUE;
//	}
//
//	if (e->detail == (XCB_BUTTON_INDEX_3) and (e->state & (XCB_MOD_MASK_1))) {
//		_root->_ctx->grab_start(make_shared<grab_bind_view_notebook_t>(_root->_ctx, shared_from_this(), e->detail, rect{e->root_x-10, e->root_y-10, 20, 20}), e->time);
//		return BUTTON_ACTION_HAS_ACTIVE_GRAB;
//	} else {
//		_root->set_focus(shared_from_this(), e->time);
//		return BUTTON_ACTION_REPLAY;
//	}
//
//	return BUTTON_ACTION_CONTINUE;
//}

} /* namespace page */
