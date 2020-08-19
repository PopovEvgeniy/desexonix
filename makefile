install:
	@echo Installation in progress. Please wait
	@gcc desexonix.c -g0 -O0 -o desexonix
	@chmod ugo+rx desexonix
	@cp -f -p desexonix /bin/
	@echo Installation was successfuly complete
uninstall:
	@rm -f /bin/desexonix
	@echo Uninstallation was successfuly complete