install:
	@echo Installation in progress. Please wait
	@gcc desexonix.c -g0 -O0 -o /bin/desexonix
	@chmod ugo+rx /bin/desexonix
	@echo Installation successfully complete
uninstall:
	@rm -f /bin/desexonix
	@echo Uninstallation was successfully complete