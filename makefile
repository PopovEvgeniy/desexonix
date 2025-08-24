install:
	@echo Installation in progress. Please wait
	@$(CC) desexonix.c -g0 -O0 -o /bin/desexonix
	@chmod ugo+rx /bin/desexonix
	@echo Installation was successfully completed
uninstall:
	@rm -f /bin/desexonix
	@echo Uninstallation was successfully completed