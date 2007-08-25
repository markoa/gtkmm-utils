EXTRA_DIST = Doxyfile

all-local: gendoc

clean-local:
	@rm -rf html
	@rm -f gendoc

distclean:
	@rm -rf html
	@rm -f gendoc

gendoc:
	@echo  "Generating gendocumentation..."
	$(DOXYGEN) Doxyfile 
	@echo "Documentation Generated"
	touch gendoc

install-data-local:
	mkdir -p $(DESTDIR)$(docdir)
	cp -rf html $(DESTDIR)$(docdir)

.PHONY: all-local install-data-local clean-local distclean-local
