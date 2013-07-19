#
# Doxygen processing
#
if BUILD_DOXYGEN
html_DATA = html/
endif

.PHONY: html/
html/ : Doxyfile
	@DOXYGEN@ $<

clean-local:
	-rm -rf html/
