module_LTLIBRARIES	  += modules/dummy/libdummy.la

modules_dummy_libdummy_la_CFLAGS		 = \
	$(INCUBATOR_CFLAGS)			           \
	-I$(top_srcdir)/modules/dummy		   \
	-I$(top_builddir)/modules/dummy

modules_dummy_libdummy_la_SOURCES		 = \
	modules/dummy/dummy-grammar.y	       \
	modules/dummy/dummy.c		           \
	modules/dummy/dummy.h		           \
	modules/dummy/dummy-parser.c	       \
	modules/dummy/dummy-parser.h	       \
	modules/dummy/dummy-plugin.c

modules_dummy_libdummy_la_LIBADD		 = \
	$(INCUBATOR_LIBS)

modules_dummy_libdummy_la_LDFLAGS		 = \
	-avoid-version -module -no-undefined

BUILT_SOURCES					+= \
	modules/dummy/dummy-grammar.y  \
	modules/dummy/dummy-grammar.c  \
	modules/dummy/dummy-grammar.h

modules/dummy mod-dummy: modules/dummy/libdummy.la

EXTRA_DIST					+=     \
	modules/dummy/dummy-grammar.ym \
	modules/dummy/dummy-example.conf

.PHONY: modules/dummy mod-dummy
