BUILD=$(PWD)/build
SOURCE=$(PWD)/..

#PLATFORM=--platform linux/amd64
PLATFORM=
cligen-builder: Dockerfile
	docker build $(PLATFORM) . -t cligen-builder --iidfile cligen-builder

build:
	mkdir build

Makefile: cligen-builder ../CMakeLists.txt build
	cd build
	docker run $(PLATFORM) --rm -v $(BUILD):/tmp/build -v $(SOURCE):/tmp/cligen cligen-builder sh -c "cd /tmp/build; cmake /tmp/cligen"

compile: Makefile
	docker run $(PLATFORM) --rm -v `pwd`/build:/tmp/build -v `pwd`/..:/tmp/cligen cligen-builder sh -c "cd /tmp/build; make"

test: compile
	docker run $(PLATFORM) --rm -v `pwd`/build:/tmp/build -v `pwd`/..:/tmp/cligen cligen-builder sh -c "cd /tmp/build; ctest"

memcheck: compile
	docker run $(PLATFORM) --rm -v `pwd`/build:/tmp/build -v `pwd`/..:/tmp/cligen cligen-builder sh -c "cd /tmp/build; ctest -T memcheck"

package: compile
	docker run $(PLATFORM) --rm -v `pwd`/build:/tmp/build -v `pwd`/..:/tmp/cligen cligen-builder sh -c "cd /tmp/build; make package"

source-package: Makefile
	docker run $(PLATFORM) --rm -v `pwd`/build:/tmp/build -v `pwd`/..:/tmp/cligen cligen-builder sh -c "cd /tmp/build; make package_source"

shell:
	docker run $(PLATFORM) -it --rm -v `pwd`/build:/tmp/build -v `pwd`/..:/tmp/cligen cligen-builder  sh

clean:
	rm -rf build cligen-builder