PROJECT=yet_another_pong_clone
OBJECTS =     $(patsubst src/%.c, build/%.o, $(wildcard src/*.c))
WEB_OBJECTS = $(patsubst src/%.c, web/build/%.o, $(wildcard src/*.c))

build: $(OBJECTS)
	gcc -Iinclude -lGL -lm -lpthread -ldl -lrt -lX11 build/*.o lib/libraylib.a  -o $(PROJECT)

build/%.o: src/%.c include/%.h
	gcc  -Wall -Wextra -Iinclude -c $< -o $@

clean:
	rm -rf build/* $(PROJECT)

web/build/%.o: src/%.c include/%.h
	emcc  -Wall -Wextra -Iinclude -DPLATFORM_WEB -c $< -o $@

web: $(WEB_OBJECTS)
	emcc -Iinclude -Os --shell-file include/shell.html -s USE_GLFW=3 -s ASYNCIFY --preload-file data web/build/* lib/libraylib.web.a -o web/index.html
	zip web/$(PROJECT).zip web/index.*
	emrun web/index.html

web_clean:
	rm web/index.* web/build/*
