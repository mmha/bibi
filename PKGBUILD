pkgname=bibi
pkgver=0.1.0
pkgrel=1
pkgdesc="C++ Standard Library Concepts"
arch=('x86' 'x86_64' 'armv7h')
license=('boost')
makedepends=('cmake')

build() {
	cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr
	make
}

package() {
	make DESTDIR="$pkgdir" install
}