MAINTAINERCLEANFILES = \
	Makefile.in

AM_CPPFLAGS = \
	-I$(top_builddir) \
	-I$(top_srcdir)/src \
	@INCLTDL@

EXTRA_DIST = \
	pch.h \
	synfig.nsh \
	synfig.h


TARGETHEADERS = \
	target_multi.h \
	target_null.h \
	target_null_tile.h \
	target_scanline.h \
	target_tile.h \
	targetparam.h

TARGETSOURCES = \
	target_multi.cpp \
	target_scanline.cpp \
	target_tile.cpp


IMPORTERHEADERS = \
	listimporter.h

IMPORTERSOURCES = \
	listimporter.cpp


VALUEHEADERS = \
	blinepoint.h \
	widthpoint.h \
	dashitem.h \
	gradient.h \
	weightedvalue.h \
	pair.h \
	type.h \
	synfig_export.h \
	base_types.h \
	value.h

VALUESOURCES = \
	blinepoint.cpp \
	widthpoint.cpp \
	dashitem.cpp \
	gradient.cpp \
	type.cpp \
	base_types.cpp \
	value.cpp


SYNFIGHEADERS = \
	angle.h \
	bezier.h \
	canvasbase.h \
	clock.h \
	general.h \
	localization.h \
	progresscallback.h \
	guidset.h \
	interpolation.h \
	quick_rng.h \
	real.h \
	complex.h \
	releases.h \
	segment.h \
	smartfile.h \
	string.h \
	string_helper.h \
	types.h \
	vector.h \
	transformation.h \
	version.h \
	boneweightpair.h \
	activepoint.h \
	blur.h \
	blur/boxblur.h \
	blur/gaussian.h \
	bone.h \
	canvas.h \
	color.h \
	context.h \
	_curve_func.h \
	curve.h \
	curve_helper.h \
	curveset.h \
	distance.h \
	exception.h \
	guid.h \
	importer.h \
	keyframe.h \
	layer.h \
	loadcanvas.h \
	main.h \
	misc.h \
	module.h \
	node.h \
	palette.h \
	paramdesc.h \
	pen.h \
	polynomial_root.h \
	rect.h \
	reference_counter.h \
	renddesc.h \
	render.h \
	savecanvas.h \
	surface_etl.h \
	surface.h \
	synfig_iterations.h \
	target.h \
	time.h \
	timepointcollect.h \
	transform.h \
	uniqueid.h \
	valuenode.h \
	valuenode_registry.h \
	waypoint.h \
	matrix.h \
	filesystem.h \
	filesystem_path.h \
	filesystemnative.h \
	filesystemgroup.h \
	filesystemtemporary.h \
	filecontainer.h \
	filecontainerzip.h \
	zstreambuf.h \
	valueoperations.h \
	valuetransformation.h \
	splineexporter.h \
	soundprocessor.h \
	canvasfilenaming.h \
	os.h \
	token.h \
	threadpool.h

SYNFIGSOURCES = \
	activepoint.cpp \
	bone.cpp \
	blur.cpp \
	canvas.cpp \
	context.cpp \
	curve.cpp \
	curve_helper.cpp \
	curveset.cpp \
	distance.cpp \
	exception.cpp \
	guid.cpp \
	importer.cpp \
	keyframe.cpp \
	layer.cpp \
	loadcanvas.cpp \
	main.cpp \
	module.cpp \
	node.cpp \
	palette.cpp \
	paramdesc.cpp \
	polynomial_root.cpp \
	rect.cpp \
	renddesc.cpp \
	render.cpp \
	savecanvas.cpp \
	string_helper.cpp \
	surface.cpp \
	synfig_iterations.cpp \
	target.cpp \
	time.cpp \
	timepointcollect.cpp \
	transform.cpp \
	uniqueid.cpp \
	valuenode.cpp \
	valuenode_registry.cpp \
	waypoint.cpp \
	matrix.cpp \
	filesystem.cpp \
	filesystem_path.cpp \
	filesystemnative.cpp \
	filesystemgroup.cpp \
	filesystemtemporary.cpp \
	filecontainer.cpp \
	filecontainerzip.cpp \
	zstreambuf.cpp \
	valueoperations.cpp \
	splineexporter.cpp \
	soundprocessor.cpp \
	canvasfilenaming.cpp \
	os.cpp \
	token.cpp \
	threadpool.cpp


libsynfig_src = \
	$(VALUEHEADERS) \
	$(VALUESOURCES) \
	$(TARGETHEADERS) \
	$(TARGETSOURCES) \
	$(SYNFIGHEADERS) \
	$(SYNFIGSOURCES) \
	$(IMPORTERHEADERS) \
	$(IMPORTERSOURCES)

libsynfig_include_HH = \
	$(SYNFIGHEADERS) \
	$(TARGETHEADERS) \
	$(IMPORTERHEADERS) \
	$(VALUEHEADERS)

include color/Makefile_insert
include debug/Makefile_insert
include layers/Makefile_insert
include rendering/Makefile_insert
include valuenodes/Makefile_insert

lib_LTLIBRARIES = libsynfig.la

libsynfig_la_SOURCES = \
	$(libsynfig_src)

nobase_include_synfig_HEADERS = \
	$(libsynfig_include_HH)


libsynfig_la_LIBADD = \
	@LIBLTDL@ \
	@SYNFIG_LIBS@ \
	@LIBADD_DL@

libsynfig_la_CXXFLAGS = \
	@SYNFIG_CFLAGS@ \
	-DLIBDIR="\"@libdir@\"" \
	-DSYSCONFDIR="\"@sysconfdir@\""

libsynfig_la_LDFLAGS = \
	-export-dynamic \
	-no-undefined \
	-version-info 0:0:0


include_synfigdir = @synfigincludedir@/synfig
