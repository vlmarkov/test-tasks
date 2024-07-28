BUILD_DIR := build

all:
	@echo 'Create build directory'
	mkdir -p $(BUILD_DIR)
	echo 'Compile test programm'
	cd ./$(BUILD_DIR) && cmake ../ && cmake --build . -- -j4

tests-all:
	@echo 'Create build directory'
	mkdir -p $(BUILD_DIR)
	@echo 'Compile tests for test programm'
	cd ./$(BUILD_DIR) && cmake ../ \
		-DENABLE_TESTING=True \
		&& cmake --build . -- -j4 \
		&& cd ./libs/module_a/t && ctest . -- -j4 \
		&& cd ../../module_b/t && ctest . -- -j4

tests-small:
	@echo 'Create build directory'
	mkdir -p $(BUILD_DIR)
	@echo 'Compile tests for test programm'
	cd ./$(BUILD_DIR) && cmake ../ \
		-DENABLE_TESTING=True \
		&& cmake --build . -- -j4 \
		&& cd ./libs/module_a/t && ctest -L small . -- -j4 \
		&& cd ../../module_b/t && ctest -L small . -- -j4

tests-medium:
	@echo 'Create build directory'
	mkdir -p $(BUILD_DIR)
	@echo 'Compile tests for test programm'
	cd ./$(BUILD_DIR) && cmake ../ \
		-DENABLE_TESTING=True \
		&& cmake --build . -- -j4 \
		&& cd ./libs/module_a/t && ctest -L medium . -- -j4 \
		&& cd ../../module_b/t && ctest -L medium . -- -j4

tests-large:
	@echo 'Create build directory'
	mkdir -p $(BUILD_DIR)
	@echo 'Compile tests for test programm'
	cd ./$(BUILD_DIR) && cmake ../ \
		-DENABLE_TESTING=True \
		&& cmake --build . -- -j4 \
		&& cd ./libs/module_a/t && ctest -L large . -- -j4 \
		&& cd ../../module_b/t && ctest -L large . -- -j4

clean:
	@echo 'Clean build directory'
	rm -Rf $(BUILD_DIR)
