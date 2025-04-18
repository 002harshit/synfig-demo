/* === S Y N F I G ========================================================= */
/*!	\file synfigapp/main.cpp
**	\brief Template File
**
**	\legal
**	Copyright (c) 2002-2005 Robert B. Quattlebaum Jr., Adrian Bentley
**
**	This file is part of Synfig.
**
**	Synfig is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 2 of the License, or
**	(at your option) any later version.
**
**	Synfig is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with Synfig.  If not, see <https://www.gnu.org/licenses/>.
**	\endlegal
*/
/* ========================================================================= */

/* === H E A D E R S ======================================================= */

#ifdef USING_PCH
#	include "pch.h"
#else
#ifdef HAVE_CONFIG_H
#	include <config.h>
#endif

#include "main.h"
#include "action.h"

#include <synfig/general.h>

#include <synfig/color.h>
#include <synfig/gradient.h>
#include <glibmm.h>

#include <list>

#include <synfigapp/localization.h>

#endif

/* === U S I N G =========================================================== */

using namespace synfig;
using namespace synfigapp;

/* === M A C R O S ========================================================= */

#ifndef SYNFIG_USER_APP_DIR
#ifdef __APPLE__
#define SYNFIG_USER_APP_DIR	"Library/Synfig"
#elif defined(_WIN32)
#define SYNFIG_USER_APP_DIR	"Synfig"
#else
#define SYNFIG_USER_APP_DIR	".config/synfig"
#endif
#endif

/* === S T A T I C S ======================================================= */

static ReferenceCounter synfigapp_ref_count_(0);
static synfigapp::Action::Main* action_main;

static Color outline_;
static Color fill_;
static Gradient gradient_;
static bool gradient_default_colors_;

static synfig::Distance bline_width_;

//static Color::BlendMethod blend_method_;
//static Real opacity_;

// Settings should be initialized before input_devices_ because
// input_devices_ uses `Main::settings()` to store settings
static Settings settings_;

static synfigapp::InputDevice::Handle selected_input_device_;
static std::list<synfigapp::InputDevice::Handle> input_devices_;

sigc::signal<void> signal_outline_color_changed_;
sigc::signal<void> signal_fill_color_changed_;
sigc::signal<void> signal_gradient_changed_;
sigc::signal<void> signal_bline_width_changed_;
sigc::signal<void> signal_interpolation_changed_;

static synfig::Waypoint::Interpolation interpolation_;

/* === P R O C E D U R E S ================================================= */

/* === M E T H O D S ======================================================= */

synfigapp::Main::Main(const synfig::String &rootpath, synfig::ProgressCallback *cb):
	synfig::Main(rootpath,cb),
	ref_count_(synfigapp_ref_count_)
{
	if(ref_count_.count())
		return;

	synfigapp_ref_count_.reset();
	ref_count_=synfigapp_ref_count_;

	// Add initialization after this point

#ifdef ENABLE_NLS
	String locale_dir;
	locale_dir = rootpath+"/share/locale";
	
	bindtextdomain(GETTEXT_PACKAGE, Glib::locale_from_utf8(locale_dir).c_str() );
	bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
#endif

	action_main=new synfigapp::Action::Main();

	set_outline_color(Color::black());
	set_fill_color(Color::white());
	set_gradient_default_colors();
	set_bline_width(Distance(1,Distance::SYSTEM_POINTS));
	//set_opacity(1.0);
	//set_blend_method(Color::BLEND_BY_LAYER);
}

synfigapp::Main::~Main()
{
	ref_count_.detach();
	if(!synfigapp_ref_count_.unique())
		return;
	synfigapp_ref_count_.detach();

	// Add deinitialization after this point

	delete action_main;

	selected_input_device_=0;
	input_devices_.clear();
}

Settings&
synfigapp::Main::settings()
{
	return settings_;
}

sigc::signal<void>&
synfigapp::Main::signal_outline_color_changed()
{
	return signal_outline_color_changed_;
}

sigc::signal<void>&
synfigapp::Main::signal_fill_color_changed()
{
	return signal_fill_color_changed_;
}

sigc::signal<void>&
synfigapp::Main::signal_gradient_changed()
{
	return signal_gradient_changed_;
}

sigc::signal<void>&
synfigapp::Main::signal_bline_width_changed()
{
	return signal_bline_width_changed_;
}

/*
sigc::signal<void>&
synfigapp::Main::signal_blend_method_changed()
{
	return signal_blend_method_changed_;
}

sigc::signal<void>&
synfigapp::Main::signal_opacity_changed()
{
	return signal_opacity_changed_;
}
*/

sigc::signal<void>&
synfigapp::Main::signal_interpolation_changed()
{
	return signal_interpolation_changed_;
}

const synfig::Color&
synfigapp::Main::get_outline_color()
{
	return outline_;
}

const synfig::Color&
synfigapp::Main::get_fill_color()
{
	return fill_;
}

const synfig::Gradient&
synfigapp::Main::get_gradient()
{
	return gradient_;
}

/*
const synfig::Real&
synfigapp::Main::get_opacity()
{
	return 1.0;
}
*/

synfig::Color::BlendMethod
synfigapp::Main::get_blend_method()
{
	return Color::BLEND_BY_LAYER;
}

void
synfigapp::Main::set_outline_color(synfig::Color color)
{
	outline_=color;
	signal_outline_color_changed()();
	if(selected_input_device_)
		selected_input_device_->set_outline_color(outline_);
	if(gradient_default_colors_)
	{
		gradient_=Gradient(fill_,outline_);
		signal_gradient_changed()();
	}
}

void
synfigapp::Main::set_fill_color(synfig::Color color)
{
	fill_=color;
	signal_fill_color_changed()();

	if(selected_input_device_)
		selected_input_device_->set_fill_color(fill_);

	if(gradient_default_colors_)
	{
		gradient_=Gradient(fill_,outline_);
		signal_gradient_changed()();
	}
}

void
synfigapp::Main::set_gradient(synfig::Gradient gradient)
{
	gradient_=gradient;
	gradient_default_colors_=false;
	signal_gradient_changed()();
}

void
synfigapp::Main::set_gradient_default_colors()
{
	gradient_default_colors_=true;
	gradient_=Gradient(fill_,outline_);
	signal_gradient_changed()();
}

void
synfigapp::Main::color_swap()
{
	const Color tmp(outline_);
	outline_=fill_;
	fill_=tmp;

	if(selected_input_device_)
	{
		selected_input_device_->set_outline_color(outline_);
		selected_input_device_->set_fill_color(fill_);
	}

	signal_outline_color_changed()();
	signal_fill_color_changed()();

	if(gradient_default_colors_)
	{
		gradient_=Gradient(fill_,outline_);
		signal_gradient_changed()();
	}
}

synfig::Waypoint::Interpolation
synfigapp::Main::get_interpolation()
{
	return interpolation_;
}


void
synfigapp::Main::set_interpolation(synfig::Waypoint::Interpolation x)
{
	if(interpolation_!=x)
	{
		interpolation_=x;

		signal_interpolation_changed()();
	}
}

const synfig::Distance&
synfigapp::Main::get_bline_width()
{
	return bline_width_;
}

void
synfigapp::Main::set_bline_width(synfig::Distance x)
{
	if(x<0)x=0;
	if(x!=bline_width_)
	{
		bline_width_=x;

		if(selected_input_device_)
			selected_input_device_->set_bline_width(x);

		signal_bline_width_changed()();
	}
}

/*
void
synfigapp::Main::set_opacity(synfig::Real x)
{
	opacity_=x;
	if(selected_input_device_)
		selected_input_device_->set_opacity(opacity_);
	signal_opacity_changed()();
}

void
synfigapp::Main::set_blend_method(synfig::Color::BlendMethod x)
{
	blend_method_=x;
	if(selected_input_device_)
		selected_input_device_->set_blend_method(x);
	signal_blend_method_changed()();
}
*/

InputDevice::Handle
synfigapp::Main::add_input_device(synfig::String id, InputDevice::Type type)
{
	input_devices_.push_back(new InputDevice(id,type));
	return input_devices_.back();
}

InputDevice::Handle
synfigapp::Main::find_input_device(const synfig::String& id)
{
	std::list<InputDevice::Handle>::iterator iter;
	for(iter=input_devices_.begin();iter!=input_devices_.end();++iter)
		if((*iter)->get_id()==id)
			return *iter;
	return nullptr;
}

InputDevice::Handle
synfigapp::Main::select_input_device(const synfig::String& id)
{
	InputDevice::Handle input_device(find_input_device(id));
	if(!input_device)
		return nullptr;
	if(!select_input_device(input_device))
		return nullptr;
	return input_device;
}

bool
synfigapp::Main::select_input_device(InputDevice::Handle input_device)
{
	assert(input_device);

	// synfig::info("Input device changed to \"%s\"",input_device->get_id().c_str());

	selected_input_device_=input_device;

	set_bline_width(input_device->get_bline_width());
	set_outline_color(input_device->get_outline_color());
	set_fill_color(input_device->get_fill_color());
	//set_opacity(input_device->get_opacity());
	//set_blend_method(input_device->get_blend_method());

	return true;
}

InputDevice::Handle
synfigapp::Main::get_selected_input_device()
{
	return selected_input_device_;
}

void
synfigapp::Main::set_state(synfig::String state)
{
	if(selected_input_device_)
		selected_input_device_->set_state(state);
}

synfig::filesystem::Path
synfigapp::Main::get_user_app_directory()
{
	std::string dir = Glib::getenv("SYNFIG_USER_SETTINGS");
	if (!dir.empty()) {
		return filesystem::Path(dir);
	}
	return filesystem::Path(Glib::get_home_dir()).append(SYNFIG_USER_APP_DIR);
}
