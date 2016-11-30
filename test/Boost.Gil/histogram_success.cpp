/*
    Copyright 2005-2007 Adobe Systems Incorporated
   
    Use, modification and distribution are subject to the Boost Software License,
    Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).

    See http://opensource.adobe.com/gil for most recent version including documentation.
*/

/*************************************************************************************************/

/// \file
/// \brief Example file to demonstrate a way to compute histogram
/// \author Lubomir Bourdev and Hailin Jin
/// \date February 27, 2007

#include <algorithm>
#include <fstream>
#include <boost/gil/image.hpp>
#include <boost/gil/typedefs.hpp>
#include <boost/gil/color_convert.hpp>
#include <boost/gil/extension/io/jpeg_io.hpp>
#include <bibi/boost/gil.h>

using namespace boost::gil;
using namespace bibi::boost::gil;

void gray_image_hist(const ImageView& img_view, auto& hist) {
//    for_each_pixel(img_view,++lambda::var(hist)[lambda::_1]);
    for (typename ImageView::iterator it=img_view.begin(); it!=img_view.end(); ++it)
        ++hist[*it];
}

void get_hist(const ImageView& img_view, auto& hist) {
    gray_image_hist(color_converted_view<gray8_pixel_t>(img_view), hist);
}

int main() {
    rgb8_image_t img;
    jpeg_read_image("test.jpg",img);

    int histogram[256];
    std::fill(histogram,histogram+256,0);
    get_hist(const_view(img),histogram);

    std::fstream histo_file("out-histogram.txt",std::ios::out);
    for(std::size_t ii=0;ii<256;++ii)
        histo_file << histogram[ii] << std::endl;
    histo_file.close();

    return 0;
}