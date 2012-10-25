include Makefile.inc

# MFLAGS = -s ( da um "make --help" pra ver )

all:test

$(NAME): driver grlib OLED
	@echo -n "Creating lib ... "
	$(AR) $(AR_FLAGS) $(LIB_DIR)/lib$(NAME)-$(DEVICE).a $(OBJ_DIR)/*.o
	@echo "Done."

driver: force_look
	$(MAKE) clean
	clear
	@echo "Working with" $(DEVICE)
	@echo "Entering" $(PWD)/$(GRLIB_DIR) "..."
	cd $(GRLIB_DIR); $(MAKE) $(MFLAGS)
	@echo -n "Leaving" $(PWD)/$(GRLIB_DIR) "..."	
	cd ..
	@echo "Done."

grlib: force_look
	@echo "Entering" $(PWD)/$(DRIVER_DIR) "..."
	cd $(DRIVER_DIR); $(MAKE) $(MFLAGS)
	@echo -n "Leaving" $(PWD)/$(DRIVER_DIR) "..."	
	cd ..
	@echo "Done."

#Polish library
OLED: force_look
	@echo "Entering" $(PWD)/$(SRC_DIR) "..."
	cd $(SRC_DIR); $(MAKE) $(MFLAGS)
	@echo -n "Leaving" $(PWD)/$(SRC_DIR) "..."	
	cd ..
	@echo "Done."

force_look:
#	true

#Gerando documentação	
gen-docs: $(HDR) $(SRC) 
	$(DOXYGEN) $(DOXYGENFLAGS)
	cd ./doc/gen/latex; $(MAKE) ; rm -f *.ps *.dvi *.aux *.toc *.idx *.ind *.ilg *.log *.out *.brf *.blg *.bbl ; cp *.pdf ../$(NAME).pdf

test: $(NAME)
	@echo "Entering" $(PWD)/$(TEST_DIR) "..."	
	cd $(TEST_DIR); $(MAKE) $(MFLAGS)

upload: test
	cd $(TEST_DIR); $(MAKE) $(MFLAGS) $@

clean:
	clear
	@echo "Cleaning up..."
	@find . -name '*~' -exec rm -f {} \;
	@find . -name '*.o' -exec rm -f {} \;
	@find . -name lib$(NAME)-$(DEVICE).a -exec rm -f {} \;
	@echo "Cleaning up test files..."	
	cd $(TEST_DIR); $(MAKE) $(MFLAGS) $@
	@echo "Done."
