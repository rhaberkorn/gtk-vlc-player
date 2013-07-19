#
# Doxygen processing
#
if BUILD_DOXYGEN
doc_DATA = doxygen/
endif

.PHONY: doxygen/
doxygen/ : Doxyfile
	@DOXYGEN@ $<

clean-local:
	-rm -rf doxygen/
