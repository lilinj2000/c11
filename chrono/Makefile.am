AUTOMAKE_OPTIONS = foreign

noinst_PROGRAMS = unittest

unittest_SOURCES = ChronoTest.cc

unittest_CPPFLAGS = -I$(top_srcdir) \
		$(GTEST_CPPFLAGS)


unittest_LDADD = $(GTEST_LIBADD)


unittest_LDFLAGS = $(LIBADD_DL) -Wl,--no-as-needed -pthread

# header files
noinst_HEADERS = 


