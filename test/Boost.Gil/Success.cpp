#include <iostream>
#include <bibi/boost/gil.h>
#include <boost/gil/gil_all.hpp>

void f(bibi::boost::gil::RandomAccessNDImageView v) {

}

int main() {
	f(boost::gil::gray8c_view_t{});
}
