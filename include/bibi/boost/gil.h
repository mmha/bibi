#pragma once
#include "../Core.h"
#include "../Iterator.h"
#include <boost/gil/gil_concept.hpp>
#include <boost/gil/color_base.hpp>
#include <boost/gil/color_convert.hpp>

namespace bibi
{
namespace boost
{
namespace gil
{

template<typename T>
concept bool Regular =
	DefaultConstructible<T> &&
	CopyConstructible<T> &&
	EqualityComparable<T> &&
	CopyAssignable<T> &&
	Swappable<T>;

template<typename P>
concept bool PointND = 
	Regular<P> &&
	requires(const P pc, P p)
	{
		typename P::value_type;
		{::boost::gil::axis_value<0>(pc)} -> typename P::template axis<0>::coord_t;
		{::boost::gil::axis_value<P::num_dimensions - 1>(pc)} -> typename P::template axis<P::num_dimensions>::coord_t;
		{P::num_dimensions} -> size_t;
		{p[0]} -> typename P::value_type;
	};

template<typename P>
concept bool Point2D =
	PointND<P> &&
	P::num_dimensions == 2 &&
	requires(const P pc)
	{
		{pc.x} -> typename P::value_type;
		{pc.y} -> typename P::value_type;
	};

template<typename Cs>
concept bool ColorSpace = true;

template<typename Cs1, typename Cs2>
constexpr auto colorSpacesCompatible() -> bool
{
	return isSame<Cs1, Cs2>();
}

template<typename Cs1, typename Cs2>
concept bool ColorSpacesCompatible = colorSpacesCompatible<Cs1, Cs2>();

template<typename CM>
concept bool ChannelMapping = true;

template<typename T>
concept bool Channel =
	EqualityComparable<T> &&
	requires(T c)
	{
		typename ::boost::gil::channel_traits<T>::value_type;
		typename ::boost::gil::channel_traits<T>::reference;
		typename ::boost::gil::channel_traits<T>::pointer;
		typename ::boost::gil::channel_traits<T>::const_reference;
		typename ::boost::gil::channel_traits<T>::const_pointer;
		{::boost::gil::channel_traits<T>::min_value()};
		{::boost::gil::channel_traits<T>::max_value()};
	};

template<typename T>
concept bool MutableChannel =
		CopyAssignable<T> &&
		Swappable<T> &&
		Channel<T>;

template<typename T>
concept bool ChannelValue =
	Channel<T> &&
	Regular<T>;

template<typename T1, typename T2>
constexpr auto channelsCompatible() -> bool
{
	return isSame<typename ::boost::gil::channel_traits<T1>::value_type, typename ::boost::gil::channel_traits<T2>::value_type>();
}

template<typename T1, typename T2>
concept bool ChannelsCompatible = colorSpacesCompatible<T1, T2>();

template<typename SrcChannel, typename DstChannel>
concept bool ChannelConvertible =
	Channel<SrcChannel> &&
	MutableChannel<DstChannel> &&
	requires(SrcChannel s, DstChannel d)
	{
		{d = ::boost::gil::channel_convert<DstChannel, SrcChannel>(s)} -> DstChannel &;
	};

template<typename C>
concept bool ColorBase = 
	CopyConstructible<C> &&
	EqualityComparable<C> &&
	ColorSpace<typename C::layout_t::color_space_t> &&
	requires(const C cb, C x)
	{
		typename C::layout_t::channel_mapping_t; // TODO: channel_mapping_t must be an MPL RandomAccessSequence
		typename ::boost::gil::kth_element_type<C, ::boost::gil::size<C>::value-1>::type;
		typename ::boost::gil::kth_element_const_reference_type<C, ::boost::gil::size<C>::value-1>::type;
		{::boost::gil::size<C>::value} -> size_t;

		{::boost::gil::at_c<::boost::gil::size<C>::value - 1>(cb)} -> typename ::boost::gil::kth_element_const_reference_type<C,::boost::gil::size<C>::value - 1>::type;
		// functions that work for every pixel (no need to require them)
		{::boost::gil::semantic_at_c<0>(cb)};
		{::boost::gil::semantic_at_c<::boost::gil::size<C>::value - 1>(cb)};
		// also static_max(cb), static_min(cb), static_fill(cb,value), and all variations of static_for_each(), static_generate(), static_transform()
	};

template<typename C>
concept bool MutableColorBase =
	ColorBase<C> &&
	CopyAssignable<C> &&
	Swappable<C>;

template<typename C>
concept bool ColorBaseValue =
	MutableColorBase<C> &&
	Regular<C>;

template<typename C>
concept bool HomogenousColorBase = 
	ColorBase<C> &&
	isSame<
		typename ::boost::gil::kth_element_type<C, 0>::type,
		typename ::boost::gil::kth_element_type<C, ::boost::gil::size<C>::value - 1>::type>() &&
	requires(C c)
	{
		{::boost::gil::detail::dynamic_at_c(c, 0)} -> typename ::boost::gil::kth_element_type<C, 0>::type;
	};

template<typename C>
concept bool MutableHomogenousColorBase =
	HomogenousColorBase<C> &&
	MutableColorBase<C>;

template<typename C>
concept bool HomogenousColorBaseValue =
	MutableHomogenousColorBase<C> &&
	Regular<C>;

template<typename C1, typename C2>
concept bool ColorBasesCompatible =
	isSame<
		typename C1::layout_t::color_space_t, 
		typename C2::layout_t::color_space_t>();

template<typename P>
concept bool PixelBased = 
	ColorSpace<typename ::boost::gil::color_space_type<P>::type> &&
	ChannelMapping<typename ::boost::gil::channel_mapping_type<P>::type> &&
	requires
	{
		{::boost::gil::is_planar<P>::value} -> bool;
		{::boost::gil::num_channels<P>::value} -> size_t;
	};

template<typename P>
concept bool HomogenousPixelBased =
	PixelBased<P> &&
	Channel<typename ::boost::gil::channel_type<P>::type>;

template<typename P>
concept bool Pixel = 
	ColorBase<P> &&
	PixelBased<P> &&
	::boost::gil::is_pixel<P>::value &&
	requires
	{
		typename P::value_type;
		typename P::reference;
		typename P::const_reference;
	};

template<typename P>
concept bool MutablePixel = 
	Pixel<P> &&
	P::is_mutable;

template<typename P>
concept bool HomogenousPixel =
	Pixel<P> &&
	HomogenousColorBase<P> &&
	HomogenousPixelBased<P>;

template<typename P>
concept bool MutableHomogenousPixel =
	HomogenousPixel<P> &&
	MutableHomogenousColorBase<P>;

template<typename P>
concept bool PixelValue = 
	Pixel<P> &&
	Regular<P>;

template<typename P>
concept bool HomogenousPixelValue =
	HomogenousPixel<P> &&
	Regular<P>;

template<typename SrcP, typename DstP>
concept bool PixelConvertible =
	Pixel<SrcP> &&
	MutablePixel<DstP> &&
	requires(SrcP src, DstP dst)
	{
		{::boost::gil::color_convert(src, dst)};
	};

template<typename D>
concept bool PixelDereferenceAdaptor =
	Callable<D, std::decay_t<typename D::result_type>, typename D::argument_type> &&
	DefaultConstructible<D> &&
	CopyConstructible<D> &&
	CopyAssignable<D> &&
	Pixel<std::decay_t<typename D::result_type>> &&
	requires
	{
		typename D::value_type;
		typename D::reference;
		typename D::const_reference;
		{D::is_mutable} -> bool;
	};

template<typename T>
concept bool HasDynamicXStepType =
	requires
	{
		typename ::boost::gil::dynamic_x_step_type<T>::type;
	};

template<typename T>
concept bool HasDynamicYStepType =
	requires
	{
		typename ::boost::gil::dynamic_y_step_type<T>::type;
	};

template<typename T>
concept bool HasTransposedType =
	requires
	{
		typename ::boost::gil::transposed_type<T>::type;
	};

template<typename Iterator>
concept bool PixelIterator =
	RandomAccessIterator<Iterator> &&
	PixelBased<Iterator> &&
	PixelValue<typename std::iterator_traits<Iterator>::value_type>;

template<typename Iterator>
concept bool MutablePixelIterator =
	PixelIterator<Iterator> &&
	MutableIterator<Iterator>;

template<typename Iterator>
concept bool MemoryBasedIterator =
	RandomAccessIterator<Iterator> &&
	requires(Iterator it)
	{
		{::boost::gil::memunit_step(it)} -> ptrdiff_t;
		{::boost::gil::memunit_distance(it, it)} -> ptrdiff_t;
		{::boost::gil::memunit_advance(it, 3)};
	};

template<typename Iterator>
concept bool StepIterator =
	ForwardIterator<Iterator> &&
	requires(Iterator it)
	{
		{it.set_step(0)};
	};

template<typename Iterator>
concept bool MutableStepIterator =
	StepIterator<Iterator> &&
	MutableIterator<Iterator>;

template<typename Iterator>
concept bool IteratorAdaptor =
	ForwardIterator<Iterator> &&
	ForwardIterator<typename ::boost::gil::iterator_adaptor_get_base<Iterator>::type> &&
	::boost::gil::is_iterator_adaptor<Iterator>::value &&
	requires(Iterator it)
	{
		typename ::boost::gil::iterator_adaptor_rebind<Iterator, void *>::type;
		{it.base()} -> typename ::boost::gil::iterator_adaptor_get_base<Iterator>::type;
	};

template<typename Iterator>
concept bool MutableIteratorAdaptor =
	IteratorAdaptor<Iterator> &&
	MutableIterator<Iterator>;

template<typename Loc>
concept bool RandomAccessNDLocator =
	RandomAccessIterator<typename Loc::template axis<0>::iterator> &&
	RandomAccessIterator<typename Loc::template axis<Loc::num_dimensions - 1>::iterator> &&
	PointND<typename Loc::point_t> &&
	Loc::point_t::num_dimensions == Loc::num_dimensions &&
	//isSame<typename std::iterator_traits<typename Loc::axis<0>::iterator>::difference_type, Loc::point_t::template axis<0>::coord_t::value>() &&
	//isSame<typename std::iterator_traits<typename Loc::axis<Loc::num_dimensions - 1>::iterator>::difference_type, Loc::point_t::template axis<Loc::num_dimensions - 1>::coord_t::value>() &&
	requires(Loc l,
		typename Loc::difference_type d)
	{
		typename Loc::value_type; 
		typename Loc::reference;         // result of dereferencing
		typename Loc::difference_type;   // result of operator-(pixel_locator, pixel_locator)
		typename Loc::cached_location_t; // type used to store relative location (to allow for more efficient repeated access)
		typename Loc::const_t;           // same as this type, but over const values
		typename Loc::point_t;           // same as difference_type

		//{l += d} -> typename Loc::reference;
		//{l -= d} -> typename Loc::reference;
		//{l + d} -> Loc;
		//{l - d} -> Loc;
		{l[d]} -> typename Loc::reference;
		{*l} -> typename Loc::reference;
		{l.cache_location(d)} -> typename Loc::cached_location_t;

		{l.template axis_iterator<0>(d)} -> typename Loc::template axis<0>::iterator;
		{l.template axis_iterator<Loc::num_dimensions - 1>(d)} -> typename Loc::template axis<Loc::num_dimensions - 1>::iterator;
		{Loc::num_dimensions} -> size_t;
	};

template<typename Loc>
concept bool RandomAccess2DLocator =
	RandomAccessNDLocator<Loc> &&
	Loc::num_dimensions == 2 &&
	Point2D<typename Loc::point_t> &&
	requires(Loc l)
	{
		typename ::boost::gil::dynamic_x_step_type<Loc>::type;
		typename ::boost::gil::dynamic_y_step_type<Loc>::type;
		typename ::boost::gil::transposed_type<Loc>::type;

		typename Loc::x_iterator;
		typename Loc::y_iterator;
		typename Loc::x_coord_t;
		typename Loc::y_coord_t;

		typename ::boost::gil::dynamic_y_step_type<
			typename ::boost::gil::dynamic_x_step_type<
			typename ::boost::gil::transposed_type<Loc
		>::type>::type>::type;
	};

template<typename Loc>
concept bool PixelLocator =
	RandomAccess2DLocator<Loc> &&
	PixelIterator<typename Loc::x_iterator> &&
	PixelIterator<typename Loc::y_iterator> &&
	isSame<typename Loc::x_coord_t, typename Loc::y_coord_t>() &&
	requires
	{
		typename Loc::coord_t;
	};

template<typename Loc>
concept bool MutableRandomAccessNDLocator =
	RandomAccessNDLocator<Loc> &&
	RandomAccessIterator<typename Loc::template axis<0>::iterator> &&
	RandomAccessIterator<typename Loc::template axis<Loc::num_dimensions - 1>::iterator>;

template<typename Loc>
concept bool MutableRandomAccess2DLocator =
	MutableRandomAccessNDLocator<Loc> &&
	RandomAccess2DLocator<Loc>;

template<typename Loc>
concept bool MutablePixelLocator =
	PixelLocator<Loc> &&
	RandomAccessIterator<typename Loc::template axis<0>::iterator> &&
	RandomAccessIterator<typename Loc::template axis<Loc::num_dimensions - 1>::iterator>;

template<typename View>
concept bool RandomAccessNDImageView =
	Regular<View> &&
	//RandomAccessNDImageView<typename View::const_t> && // same as View, but over immutable values
	PointND<typename View::point_t> &&                   // N-dimensional point
	RandomAccessNDLocator<typename View::locator> &&     // N-dimensional locator
	RandomAccessIterator<typename View::iterator> &&    // 1-dimensional iterator over all values
	RandomAccessIterator<typename View::reverse_iterator> &&
	requires(const View vc,
	         View v,
	         const typename View::point_t p,
	         const typename View::difference_type diff)
	{
		typename View::value_type;
		typename View::reference;       // result of dereferencing
		typename View::difference_type; // result of operator-(iterator,iterator) (1-dimensional!)
		typename View::const_t;         // same as View, but over immutable values
		typename View::size_type;

		{vc.size()}             -> typename View::size_type;
		{vc[diff]}              -> typename View::reference;
		{vc.begin()}            -> typename View::iterator;
		{vc.end()}              -> typename View::iterator;
		{vc.rbegin()}           -> typename View::reverse_iterator;
		{vc.rend()}             -> typename View::reverse_iterator;
		{v.at(p)}               -> typename View::iterator;
		{vc.dimensions()}       -> typename View::point_t;
		{vc.is_1d_traversable()} -> bool;
		{vc.template axis_iterator<0>(p)}   -> typename View::template axis<0>::iterator;
		//{vc.template axis_iterator<View::point_t::num_dimensions>(p)}   -> typename View::template axis<View::point_t::num_dimensions>::iterator;
		//{vc(p)}                 -> typename View::iterator;
	};

template<typename View>
concept bool RandomAccess2DImageView =
	RandomAccessNDImageView<View> &&
	View::num_dimensions == 2 &&
	RandomAccess2DLocator<typename View::locator> &&
	requires(typename View::x_coord_t xd,
		     typename View::y_coord_t yd,
		     typename View::point_t d,
		     View view)
	{
		{View(xd, yd, typename View::xy_locator{})} -> View;
		{view.xy_at(xd, yd)}                        -> typename View::xy_locator;
		{view.width()}                              -> typename View::x_coord_t;
		{view.height()}                             -> typename View::y_coord_t;
		{view.x_at(d)}                              -> typename View::x_iterator;
		{view.x_at(xd,yd)}                          -> typename View::x_iterator;
		{view.row_begin(xd)}                        -> typename View::x_iterator;
		{view.row_end(xd)}                          -> typename View::x_iterator;
		{view.y_at(d)}                              -> typename View::y_iterator;
		{view.y_at(xd,yd)}                          -> typename View::y_iterator;
		{view.col_begin(xd)}                        -> typename View::y_iterator;
		{view.col_end(xd)}                          -> typename View::y_iterator;
	};

template<typename View>
concept bool ImageView =
	RandomAccess2DImageView<View> &&
	PixelLocator<typename View::xy_locator>;

template<typename View>
concept bool MutableRandomAccessNDImageView =
	RandomAccessNDImageView<View> &&
	MutableRandomAccessNDLocator<typename View::locator> &&
	RandomAccessIterator<typename View::iterator> &&
	RandomAccessIterator<typename View::reverse_iterator> &&
	RandomAccessIterator<typename View::template axis<0>::iterator> &&
	RandomAccessIterator<typename View::template axis<View::num_dimensions - 1>::iterator> &&
	MutableIterator<typename View::iterator> &&
	MutableIterator<typename View::reverse_iterator> &&
	MutableIterator<typename View::template axis<0>::iterator> &&
	MutableIterator<typename View::template axis<View::num_dimensions - 1>::iterator>;


template<typename View>
concept bool MutableRandomAccess2DImageView =
	RandomAccess2DImageView<View> &&
	MutableRandomAccessNDImageView<View>;

template<typename View>
concept bool MutableImageView =
	ImageView<View> &&
	MutableRandomAccessNDImageView<View>;

template<typename Img>
concept bool RandomAccessNDImage =
	Regular<Img> &&
	MutableRandomAccessNDImageView<typename Img::view_t> &&
	PointND<typename Img::point_t> &&
	CopyAssignable<typename Img::const_view_t> &&
	CopyAssignable<typename Img::view_t> &&
	requires(typename Img::point_t pt,
		     typename Img::value_type fill_value,
		     Img img)
	{
		{img.dimensions()} -> typename Img::point_t;
		{Img(pt)} -> Img;
		{Img(pt,1)} -> Img;
		{Img(pt,fill_value,1)} -> Img;
		{img.recreate(pt)};
		{img.recreate(pt,1)};
		{img.recreate(pt, fill_value, 1)};
	};

template<typename Img>
concept bool RandomAccess2DImage =
	RandomAccessNDImage<Img> &&
	MutableRandomAccess2DImageView<typename Img::view_t> &&
	requires(Img img)
	{
		typename Img::x_coord_t;
		typename Img::y_coord_t;
		typename Img::value_type;
		{img.width()} -> typename Img::x_coord_t;
		{img.height()} -> typename Img::y_coord_t;
	};

template<typename Img>
concept bool Image =
	RandomAccess2DImage<Img> &&
	MutableImageView<typename Img::view_t> &&
	isSame<typename Img::coord_t, typename Img::x_coord_t>() &&
	isSame<typename Img::coord_t, typename Img::y_coord_t>();

}
}
}
