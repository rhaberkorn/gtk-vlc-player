#
# Doxygen processing
#
if BUILD_DOXYGEN

EXTRA_DIST = html

all-local : Doxyfile
	@DOXYGEN@ $<

clean-local:
	-$(RM) -r html/

install-data-local:
	$(MKDIR_P) $(DESTDIR)$(htmldir)
	cp -r $(srcdir)/html $(DESTDIR)$(htmldir)

uninstall-local:
	-$(RM) -r $(DESTDIR)$(htmldir)

endif
