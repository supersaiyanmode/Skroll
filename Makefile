CPPCOMPILER=g++
CCOMPILER=gcc
FLAGS=-Wall -g -O3
LIBRARIES=`pkg-config --libs libglfw` -lm -lGLU -lGL -lXrandr
UNITS=obj/main.o obj/TextureManager.o obj/Thread.o obj/Tile.o obj/PictureTile.o obj/Coverflow.o
SOIL_DEPENDS=soil/image_DXT.c  soil/image_helper.c  soil/SOIL.c  soil/stbi_DDS_aug_c.h  soil/stb_image_aug.c \
		soil/image_DXT.h  soil/image_helper.h  soil/SOIL.h  soil/stbi_DDS_aug.h  soil/stb_image_aug.h
SOIL_UNITS=obj/soil/image_DXT.o obj/soil/image_helper.o obj/soil/SOIL.o soil/stb_image_aug.o

all: $(SOIL_UNITS) $(UNITS)
	$(CPPCOMPILER) $(SOIL_UNITS) $(UNITS) $(LIBRARIES) -o coverflow

obj/soil/%.o : soil/%.c
	@mkdir -p obj/soil
	$(CCOMPILER) -c $< -o $@

obj/main.o : main.cpp
	@mkdir -p obj
	$(CPPCOMPILER) -c $(FLAGS) $< -o $@ 
obj/%.o : %.cpp %.h
	@mkdir -p obj
	$(CPPCOMPILER) -c $(FLAGS) $< -o $@ 
clean:
	rm -rf $(UNITS) $(SOIL_UNITS) coverflow
