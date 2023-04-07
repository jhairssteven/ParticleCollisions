APP_NAME := ParticleCollisions
SRC_DIR  := src
INCLUDE_DIR := include
BUILD_DIR := proj/cmake/build

run: proj/cmake/build/Debug/$(APP_NAME)/$(APP_NAME)
	mkdir -p $(BUILD_DIR) && cd $(BUILD_DIR) && ./Debug/$(APP_NAME)/$(APP_NAME)

proj/cmake/build/Debug/$(APP_NAME)/$(APP_NAME): $(SRC_DIR) $(INCLUDE_DIR)
	mkdir -p $(BUILD_DIR) && cd $(BUILD_DIR) && cmake .. && make

clean:
	rm -r $(BUILD_DIR)

