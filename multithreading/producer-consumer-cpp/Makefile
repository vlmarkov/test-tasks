BUILD_DIR := build

all:
	@echo 'Create build directory'
	mkdir -p $(BUILD_DIR)
	echo 'Compile scheduler programm'
	cd ./$(BUILD_DIR) && cmake ../ && cmake --build . -- -j4

clean:
	@echo 'Clean build directory'
	rm -Rf $(BUILD_DIR)
