run: build
	./show-version-info-file-flags.exe show-version-info-file-flags.exe

build: show-version-info-file-flags.exe

clean:
	rm -f show-version-info-file-flags.exe

show-version-info-file-flags.exe: main.c main.rc
	gcc -Os -o $@ main.c main.rc -lversion -luser32 -municode
	strip $@
