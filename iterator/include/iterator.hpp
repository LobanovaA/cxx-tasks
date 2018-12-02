/* Image iterator.
 * @file
 * @date 2018-08-05
 * @author Anonymous
 */

#ifndef __ITERATOR_HPP__
#define __ITERATOR_HPP__

#include <algorithm>
#include <type_traits>
#include <vector>
#include <utility>

#include <boost/iterator/iterator_adaptor.hpp>

//{ image iterator
template<class Iterator>
class image_iterator: public boost::iterator_adaptor<image_iterator<Iterator>, Iterator>
{
public:
    image_iterator(Iterator it, size_t width, size_t stride) : image_iterator::iterator_adaptor_(it), width_(width), stride_(stride) { }
private:
    friend class boost::iterator_core_access;

    size_t width_;
    size_t stride_;

    size_t index = 0;

    void increment()
    {
        advance(1);
    }

    void decrement()
    {
        advance(-1);
    }

    void advance(ptrdiff_t n)
    {
        int spacing = n;
        int trash_count = stride_ - width_;
        int offset = spacing > 0 ? (index % (int)stride_) : -(width_- index % (int)stride_);
        int stride_count = (offset + spacing) / (int)width_;
        spacing += stride_count * trash_count;

        this->base_reference() += spacing;
        index += spacing;
    }

    ptrdiff_t distance_to( image_iterator const& dst ) const
    {
        int delta = dst.base() - this->base();
        int offset = delta > 0 ? this->index : dst.index % (int)stride_;

        int pixel_count = abs(delta) + offset;

        return (pixel_count / (int)stride_ * (int)width_ + pixel_count % (int)stride_ - offset)*(abs(delta)/delta);
    }
};
//}

template<class Container = std::vector<uint8_t>>
class image
{
public:
    image(size_t width, size_t height, size_t stride):
        data(stride * height),
        width_(width),
        stride_(stride)
    {}

    auto begin()
    {
        return image_iterator(data.begin(), width_, stride_);
    }

    auto end()
    {
        return image_iterator(data.end(), width_, stride_);
    }

    auto begin() const
    {
        return image_iterator(data.begin(), width_, stride_);
    }

    auto end() const
    {
        return image_iterator(data.end(), width_, stride_);
    }

private:
    Container data; // image data including strides. Access by (x, y): data[y * stride_ + x]
    size_t width_;
    size_t stride_;
};

#endif // __ITERATOR_HPP__
