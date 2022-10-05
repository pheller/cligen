BUILD=$(PWD)/build
SOURCE=$(PWD)/..
cligen-builder: Dockerfile
	docker build . -t cligen-builder --iidfile cligen-builder

build:
	mkdir build

Makefile: cligen-builder ../CMakeLists.txt build
	cd build
	docker run -v $(BUILD):/tmp/build -v $(SOURCE):/tmp/cligen cligen-builder sh -c "cd /tmp/build; cmake /tmp/cligen"

compile: Makefile
	docker run -v `pwd`/build:/tmp/build -v `pwd`/..:/tmp/cligen cligen-builder sh -c "cd /tmp/build; make"

test: compile
	docker run -v `pwd`/build:/tmp/build -v `pwd`/..:/tmp/cligen cligen-builder sh -c "cd /tmp/build; ctest"

memcheck: compile
	docker run -v `pwd`/build:/tmp/build -v `pwd`/..:/tmp/cligen cligen-builder sh -c "cd /tmp/build; ctest -T memcheck"

package: compile
	docker run -v `pwd`/build:/tmp/build -v `pwd`/..:/tmp/cligen cligen-builder sh -c "cd /tmp/build; make package"

source-package: Makefile
	docker run -v `pwd`/build:/tmp/build -v `pwd`/..:/tmp/cligen cligen-builder sh -c "cd /tmp/build; make package_source"

clean:
	rm -rf build cligen-builder