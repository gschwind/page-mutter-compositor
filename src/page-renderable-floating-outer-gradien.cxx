/*
 * Copyright (2017) Benoit Gschwind
 *
 * renderable_floating_outer_gradien.cxx is part of page-compositor.
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

#include "page-renderable-floating-outer-gradien.hxx"
#include "page-workspace.hxx"

namespace page {

renderable_floating_outer_gradien_t::renderable_floating_outer_gradien_t(tree_t * ref, rect r, double shadow_width,
		double radius) :
		tree_t{ref->_root},
		_r(r), _shadow_width(shadow_width), _radius(radius) {

}

renderable_floating_outer_gradien_t::~renderable_floating_outer_gradien_t() { }

/**
 * draw the area of a renderable to the destination surface
 * @param cr the destination surface context
 * @param area the area to redraw
 **/
void renderable_floating_outer_gradien_t::render(cairo_t * cr, region const & area)
{

	for (auto & cl : area.rects()) {

		cairo_save(cr);

		/** draw left shawdow **/
		cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);
		cairo_clip(cr, cl & rect(_r.x - _shadow_width, _r.y + _radius,
				_shadow_width, _r.h - _radius));
		::cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
		cairo_pattern_t * grad0 = cairo_pattern_create_linear(
				_r.x - _shadow_width, 0.0, _r.x, 0.0);
		cairo_pattern_add_color_stop_rgba(grad0, 0.0, 0.0, 0.0, 0.0, 0.00);
		//cairo_pattern_add_color_stop_rgba(grad0, 0.5, 0.0, 0.0, 0.0, 0.05);
		cairo_pattern_add_color_stop_rgba(grad0, 1.0, 0.0, 0.0, 0.0, 0.20);
		cairo_mask(cr, grad0);
		cairo_pattern_destroy(grad0);

		/** draw right shadow **/
		cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);
		cairo_clip(cr, cl & rect(_r.x + _r.w, _r.y + _radius, _shadow_width,
				_r.h - _radius));
		::cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
		cairo_pattern_t * grad1 = cairo_pattern_create_linear(_r.x + _r.w,
				0.0, _r.x + _r.w + _shadow_width, 0.0);
		cairo_pattern_add_color_stop_rgba(grad1, 1.0, 0.0, 0.0, 0.0, 0.00);
		//cairo_pattern_add_color_stop_rgba(grad1, 0.5, 0.0, 0.0, 0.0, 0.05);
		cairo_pattern_add_color_stop_rgba(grad1, 0.0, 0.0, 0.0, 0.0, 0.20);
		cairo_mask(cr, grad1);
		cairo_pattern_destroy(grad1);

		/** draw top shadow **/
		cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);
		cairo_clip(cr, cl & rect(_r.x + _radius, _r.y - _shadow_width,
				_r.w - 2 * _radius, _shadow_width));
		::cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
		cairo_pattern_t * grad2 = cairo_pattern_create_linear(0.0,
				_r.y - _shadow_width, 0.0, _r.y);
		cairo_pattern_add_color_stop_rgba(grad2, 0.0, 0.0, 0.0, 0.0, 0.00);
		//cairo_pattern_add_color_stop_rgba(grad2, 0.5, 0.0, 0.0, 0.0, 0.05);
		cairo_pattern_add_color_stop_rgba(grad2, 1.0, 0.0, 0.0, 0.0, 0.20);
		cairo_mask(cr, grad2);
		cairo_pattern_destroy(grad2);

		/** draw bottom shadow **/
		cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);
		cairo_clip(cr, cl & rect(_r.x, _r.y + _r.h, _r.w, _shadow_width));
		::cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
		cairo_pattern_t * grad3 = cairo_pattern_create_linear(0.0,
				_r.y + _r.h, 0.0, _r.y + _r.h + _shadow_width);
		cairo_pattern_add_color_stop_rgba(grad3, 1.0, 0.0, 0.0, 0.0, 0.00);
		//cairo_pattern_add_color_stop_rgba(grad3, 0.5, 0.0, 0.0, 0.0, 0.05);
		cairo_pattern_add_color_stop_rgba(grad3, 0.0, 0.0, 0.0, 0.0, 0.20);
		cairo_mask(cr, grad3);
		cairo_pattern_destroy(grad3);

		/** draw top-left corner **/
		cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);

		cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
		cairo_reset_clip(cr);
		cairo_new_path(cr);
		cairo_move_to(cr, _r.x - _shadow_width, _r.y - _shadow_width);
		cairo_line_to(cr, _r.x - _shadow_width + _shadow_width + _radius, _r.y - _shadow_width);
		cairo_line_to(cr, _r.x - _shadow_width + _shadow_width + _radius, _r.y - _shadow_width + _shadow_width);
		cairo_arc_negative(cr, _r.x - _shadow_width + _shadow_width + _radius, _r.y - _shadow_width + _shadow_width + _radius, _radius, 3.0*M_PI/2.0, 2.0*M_PI/2.0);
		cairo_line_to(cr, _r.x - _shadow_width, _r.y - _shadow_width + _shadow_width + _radius);
		cairo_close_path(cr);
		::cairo_clip(cr);

		rect cl0(_r.x - _shadow_width, _r.y - _shadow_width, _shadow_width + _radius, _shadow_width + _radius);
		cl0 &= cl;
		cairo_rectangle(cr, cl0.x, cl0.y, cl0.w, cl0.h);
		::cairo_clip(cr);

		cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);


		//cairo_clip(cr, cl & i_rect(_r.x - _shadow_width, _r.y - _shadow_width,
		//		_shadow_width + _radius, _shadow_width + _radius));
		::cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
		cairo_pattern_t * r0grad = cairo_pattern_create_radial(_r.x + _radius,
				_r.y + _radius, _radius, _r.x + _radius, _r.y + _radius,
				_shadow_width + _radius);
		cairo_pattern_add_color_stop_rgba(r0grad, 0.0, 0.0, 0.0, 0.0, 0.20);
		//cairo_pattern_add_color_stop_rgba(r0grad, 0.5, 0.0, 0.0, 0.0, 0.05);
		cairo_pattern_add_color_stop_rgba(r0grad, 1.0, 0.0, 0.0, 0.0, 0.00);
		cairo_mask(cr, r0grad);
		cairo_pattern_destroy(r0grad);

		/** draw top-right corner **/

		cairo_reset_clip(cr);
		cairo_new_path(cr);
		cairo_move_to(cr, _r.x + _r.w - _radius, _r.y - _shadow_width);
		cairo_line_to(cr, _r.x + _r.w - _radius, _r.y - _shadow_width + _shadow_width);
		cairo_arc(cr, _r.x + _r.w - _radius, _r.y - _shadow_width + _shadow_width + _radius, _radius, 3.0*M_PI/2.0, 4.0*M_PI/2.0);
		cairo_line_to(cr, _r.x + _r.w - _radius + _shadow_width + _radius, _r.y - _shadow_width + _shadow_width + _radius);
		cairo_line_to(cr, _r.x + _r.w - _radius + _shadow_width + _radius, _r.y - _shadow_width);
		cairo_close_path(cr);
		::cairo_clip(cr);

		rect cl1(_r.x + _r.w - _radius, _r.y - _shadow_width, _shadow_width + _radius, _shadow_width + _radius);
		cl1 &= cl;
		cairo_rectangle(cr, cl1.x, cl1.y, cl1.w, cl1.h);
		::cairo_clip(cr);

		cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);
		//cairo_clip(cr, cl & i_rect(_r.x + _r.w - _radius, _r.y - _shadow_width,
		//		_shadow_width + _radius, _shadow_width + _radius));
		::cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
		cairo_pattern_t * r1grad = cairo_pattern_create_radial(
				_r.x + _r.w - _radius, _r.y + _radius, _radius,
				_r.x + _r.w - _radius, _r.y + _radius, _shadow_width + _radius);
		cairo_pattern_add_color_stop_rgba(r1grad, 0.0, 0.0, 0.0, 0.0, 0.20);
		//cairo_pattern_add_color_stop_rgba(r1grad, 0.5, 0.0, 0.0, 0.0, 0.05);
		cairo_pattern_add_color_stop_rgba(r1grad, 1.0, 0.0, 0.0, 0.0, 0.00);
		cairo_mask(cr, r1grad);
		cairo_pattern_destroy(r1grad);

		/** bottom-left corner **/
		cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);
		cairo_clip(cr, cl & rect(_r.x - _shadow_width, _r.y + _r.h, _shadow_width,
				_shadow_width));
		::cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
		cairo_pattern_t * r2grad = cairo_pattern_create_radial(_r.x,
				_r.y + _r.h, 0.0, _r.x, _r.y + _r.h, _shadow_width);
		cairo_pattern_add_color_stop_rgba(r2grad, 0.0, 0.0, 0.0, 0.0, 0.20);
		//cairo_pattern_add_color_stop_rgba(r2grad, 0.5, 0.0, 0.0, 0.0, 0.05);
		cairo_pattern_add_color_stop_rgba(r2grad, 1.0, 0.0, 0.0, 0.0, 0.00);
		cairo_mask(cr, r2grad);
		cairo_pattern_destroy(r2grad);

		/** draw bottom-right corner **/
		cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);
		cairo_clip(cr, cl & rect(_r.x + _r.w, _r.y + _r.h, _shadow_width,
				_shadow_width));
		::cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
		cairo_pattern_t * r3grad = cairo_pattern_create_radial(_r.x + _r.w,
				_r.y + _r.h, 0.0, _r.x + _r.w, _r.y + _r.h, _shadow_width);
		cairo_pattern_add_color_stop_rgba(r3grad, 0.0, 0.0, 0.0, 0.0, 0.20);
		//cairo_pattern_add_color_stop_rgba(r3grad, 0.5, 0.0, 0.0, 0.0, 0.05);
		cairo_pattern_add_color_stop_rgba(r3grad, 1.0, 0.0, 0.0, 0.0, 0.00);
		cairo_mask(cr, r3grad);
		cairo_pattern_destroy(r3grad);

		cairo_restore(cr);
	}

}

/**
 * Derived class must return opaque region for this object,
 * If unknown it's safe to leave this empty.
 **/
region renderable_floating_outer_gradien_t::get_opaque_region()
{
	return region{};
}

/**
 * Derived class must return visible region,
 * If unknow the whole screen can be returned, but draw will be called each time.
 **/
region renderable_floating_outer_gradien_t::get_visible_region()
{

	region ret;
	ret += rect(_r.x - _shadow_width, _r.y + _radius, _shadow_width,
			_r.h - _radius);
	ret += rect(_r.x + _r.w, _r.y + _radius, _shadow_width,
			_r.h - _radius);
	ret += rect(_r.x + _radius, _r.y - _shadow_width,
			_r.w - 2 * _radius, _shadow_width);
	ret += rect(_r.x, _r.y + _r.h, _r.w, _shadow_width);
	ret += rect(_r.x - _shadow_width, _r.y - _shadow_width,
			_shadow_width + _radius, _shadow_width + _radius);
	ret += rect(_r.x + _r.w - _radius, _r.y - _shadow_width,
			_shadow_width + _radius, _shadow_width + _radius);
	ret += rect(_r.x - _shadow_width, _r.y + _r.h, _shadow_width,
			_shadow_width);
	ret += rect(_r.x + _r.w, _r.y + _r.h, _shadow_width,
			_shadow_width);

	return ret;
}

region renderable_floating_outer_gradien_t::get_damaged()
{
	return region{};
}

}


