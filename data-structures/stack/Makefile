BUILD_DIR := build

all:
	mkdir -p $(BUILD_DIR)
	cd ./$(BUILD_DIR) && cmake ../ && cmake --build . -- -j4

tests: all
	mkdir -p $(BUILD_DIR)
	cd ./$(BUILD_DIR) && cmake ../ \
		-DENABLE_TESTING=True \
		&& cmake --build . -- -j4 && ctest . -- -j4

clean:
	rm -Rf $(BUILD_DIR)
